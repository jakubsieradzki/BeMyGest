#include "../dep/GlueGL.h"
#include "../dep/OpenNiUtil.h"

#include "BeeThree.h"
#include "Flute.h"
#include "SoundMaker.h"
#include "AreaManager.h"
#include "AbstractArea.h"
#include <iostream>

using namespace stk;

void initContext(xn::Context *context);
int soundMakerEx();

const unsigned int WINDOW_W = 800;
const unsigned int WINDOW_H = 600;
const char* GESTURE = "Wave";
bool hand_recognized = false;
XnPoint3D projective_point;

auto& glue = bmg::GlueGL::getInstance();
xn::GestureGenerator gesture_generator;
xn::HandsGenerator hands_generator;
xn::DepthGenerator depth_generator;
xn::ImageGenerator image_generator;

// CALLBACKS
// Define hand & gesture recognition callbacks
void XN_CALLBACK_TYPE Gesture_Recognized(
    xn::GestureGenerator& generator,
    const XnChar* strGesture,
    const XnPoint3D* pIDPosition,
    const XnPoint3D* pEndPosition,
    void* pCookie)
{
  gesture_generator.RemoveGesture(strGesture);
  hands_generator.StartTracking(*pEndPosition);
}

void XN_CALLBACK_TYPE Gesture_Process(
    xn::GestureGenerator& generator,
    const XnChar* strGesture,
    const XnPoint3D* pPosition,
    XnFloat fProgress,
    void* pCookie)
{
}

void XN_CALLBACK_TYPE Hand_Create(
    xn::HandsGenerator& generator,
    XnUserID nId,
    const XnPoint3D* pPosition,
    XnFloat fTime,
    void* pCookie)
{
  hand_recognized = true;
}

void XN_CALLBACK_TYPE Hand_Update(
    xn::HandsGenerator& generator,
    XnUserID nId,
    const XnPoint3D* pPosition,
    XnFloat fTime,
    void* pCookie)
{
  depth_generator.ConvertRealWorldToProjective(1, pPosition, &projective_point);
  //scale point
  xn::DepthMetaData metaData;
  depth_generator.GetMetaData(metaData);
  projective_point.X *= WINDOW_W;
  projective_point.X /= metaData.XRes();
  
  projective_point.Y *= WINDOW_H;
  projective_point.Y /= metaData.YRes();
}

void XN_CALLBACK_TYPE Hand_Destroy(
    xn::HandsGenerator& generator,
    XnUserID nId,
    XnFloat fTime,
    void* pCookie)
{
  gesture_generator.AddGesture(GESTURE, NULL);
  hand_recognized = false;
}

// MAIN
int main(int argc, char* argv[])
{
	auto& glue = bmg::GlueGL::getInstance();  
	glue.Init(argc, argv, WINDOW_W, WINDOW_H, "SoundBoard"); 
	xn::Context context;
	
	// Stk initialization
	Stk::setSampleRate( 44100.0 );
	Stk::setRawwavePath( "resource/rawwaves/" );

	// init context
	initContext(&context);
	context.SetGlobalMirror(true);

	// create AreaManager & add areas
	AreaManager areaManager(&glue);
	StkFloat notes[9] = {
		329.63, 349.23, 392.00,
		440.0, 493.88, 523.25,
		587.33, 659.25, 698.46
	};
	int delta = 150;
	for (unsigned int i = 0; i < (sizeof(notes)/sizeof(*notes)); ++i)
	{
		int m = i % 3;
		int n = i / 3;
    areaManager.addArea(new SoundArea(200 + (delta*m), 150 + (delta*n), 100, 100, AreaColor(0.1, 0.1, 1.0, 0.5), new Flute(300.0), notes[i]));
	}

	xn::ImageMetaData image_metadata;
	// display function
	glue.BindDisplayFunc([&]{
		glue.BeginDraw();

		// here goes code for app main loop
		XnStatus status = context.WaitAndUpdateAll();
		bmg::OnError(status, []{
		  std::cout << "Couldn't update and wait for new data!" << std::endl;
		});
		
		image_generator.GetMetaData(image_metadata);
		unsigned imageX = image_metadata.XRes();
		unsigned imageY = image_metadata.YRes();

		glue.DrawOnTexture(
		  (void*)image_metadata.RGB24Data(), 
		  imageX, imageY,
		  imageX, imageY,
		  0, 0, WINDOW_W, WINDOW_H);		
		
		// draw hand point
		if (hand_recognized) {
			// Draw point over tracked hand
			glue.DrawPointOverRegion(projective_point.X, projective_point.Y, 0, 0);	
			areaManager.update(projective_point.X, projective_point.Y);
		}
		// AreaManager draw
		areaManager.draw();

		glue.EndDraw();
	});

	glue.BindKeyboardFunc([](unsigned char key, int x, int y){
		switch(key) {
		case 27:
			exit(1);
		}
	});

	glue.Run();
	context.Release();
	
	return 0;	
}

void initContext(xn::Context *context)
{
	XnStatus status = context->Init();
	bmg::OnError(status, []{
		std::cout << "Couldn't init OpenNi!" << std::endl;
		exit(1);
	});
  	
	// image & depth
	status = image_generator.Create(*context);
	bmg::OnError(status, []{
		std::cout << "Couldn't create image generator!" << std::endl;
	});

	status = depth_generator.Create(*context);
	bmg::OnError(status, []{
		std::cout << "Couldn't create depth generator!" << std::endl;
	});

	// Create gesture & hands generators
	status = gesture_generator.Create(*context);
	bmg::OnError(status, []{
		std::cout << "Couldn't create gesture generator!" << std::endl;
	});
	status = hands_generator.Create(*context);
	bmg::OnError(status, []{
		std::cout << "Couldn't create hands generator!" << std::endl;
	});

	// Register to callbacks
	XnCallbackHandle h1, h2;
	gesture_generator
		.RegisterGestureCallbacks(Gesture_Recognized, Gesture_Process, NULL, h1);
	hands_generator
		.RegisterHandCallbacks(Hand_Create, Hand_Update, Hand_Destroy, NULL, h2);

	status = context->StartGeneratingAll();
	bmg::OnError(status, []{
		std::cout << "Couldn't generate all data!" << std::endl;
	});

	status = gesture_generator.AddGesture(GESTURE, NULL);
	bmg::OnError(status, []{
		std::cout << "Couldn't add gesture!" << std::endl;
	});
}

int soundMakerEx()
{
	Stk::setSampleRate( 44100.0 );
	Stk::setRawwavePath( "resource/rawwaves/" );
	
	SoundMaker soundMaker;
	try 
	{
		soundMaker.setInstrument(new BeeThree());
	}
	catch ( StkError &e)
	{
		e.printMessage();
		return 1;
	}
	
	soundMaker.playNote(50.0, 0.5);
	soundMaker.startStream();

	char keyhit;
	StkFloat notes[5] = {440.0, 493.88, 523.25, 587.33, 659.25};
	for (unsigned int i = 0; i < (sizeof(notes)/sizeof(*notes)); ++i)
	{
		soundMaker.playNote(notes[i], 0.5);
		std::cout << "\nPlaying note. Enter for next\n";
		std::cin.get( keyhit );
	}

	soundMaker.closeStream();

	return 0;
}