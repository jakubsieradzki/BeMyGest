#include "../dep/OpenNiUtil.h"

#include <SFML/Graphics.hpp>

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
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "SoundBoard");	
	xn::Context context;
	AreaManager* current_area_manager;
	
	// Stk initialization
	Stk::setSampleRate( 44100.0 );
	Stk::setRawwavePath( "resource/rawwaves/" );

	// init context
	initContext(&context);
	context.SetGlobalMirror(false);

	// create areas
	AreaManager *sound_area = new AreaManager(&window);	
	AreaManager *menu_area = new AreaManager(&window);

	// define sound area
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
		sound_area->addArea(new SoundArea(200 + (delta*m), 150 + (delta*n), 100, 100, sf::Color(0.0f, 0.0f, 255.0f, 125.0f), new Flute(300.0), notes[i]));
	}
	// define menu area
	Button *btn = new Button(200, 50, 200, 100, sf::Color(0.0f, 0.0f, 255.0f, 200.0f));
	btn->setAction([&current_area_manager, &sound_area] {		
		current_area_manager = sound_area;
	});
	menu_area->addArea(btn);
	current_area_manager = menu_area;

	xn::ImageMetaData image_metadata;
  while (window.isOpen()) 
  {
    // handle events
    sf::Event event;
    while (window.pollEvent(event)) 
    {
      if (event.type == sf::Event::Closed 
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();      
    }
    // draw
    window.clear();
    XnStatus status = context.WaitAndUpdateAll();
    bmg::OnError(status, []{
      std::cout << "Couldn't update and wait for new data!" << std::endl;
    });

    image_generator.GetMetaData(image_metadata);
    unsigned imageX = image_metadata.XRes();
    unsigned imageY = image_metadata.YRes();

    sf::Image raw_image;
    raw_image.create(imageY, imageX);

    auto image = image_metadata.RGB24Data();
    for (unsigned i = 0; i < imageX*imageY; ++i) {
      auto current_px = image[i];
      raw_image.setPixel(i/imageX, i%imageX, 
        sf::Color(current_px.nRed, current_px.nGreen, current_px.nRed));      
    }
    sf::Texture raw_texture;   
    raw_texture.loadFromImage(raw_image);
    sf::Sprite raw_sprite(raw_texture);
    raw_sprite.setRotation(90.0f);
    raw_sprite.setPosition(WINDOW_W, 0);
    raw_sprite.setScale(WINDOW_W/(float)imageX, WINDOW_H/(float)imageY);
 
    window.draw(raw_sprite);   

    // draw hand point
    if (hand_recognized) {
      // Draw point over tracked hand
      sf::CircleShape hand_position(5.0f);
      hand_position.setPosition(WINDOW_W-projective_point.X, projective_point.Y);
      window.draw(hand_position);
      current_area_manager->update(WINDOW_W-projective_point.X, projective_point.Y);
    }
    // AreaManager draw
    current_area_manager->draw();
    window.display();
  }	

	// clean up
	context.Release();
	delete menu_area;
	delete sound_area;
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