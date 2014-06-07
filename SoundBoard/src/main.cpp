#include "../dep/OpenNiUtil.h"

#include <SFML/Graphics.hpp>

#include "BeeThree.h"
#include "Flute.h"
#include "SoundMaker.h"
#include "AreaManager.h"
#include "AbstractArea.h"
#include "FreePlayingGame.h"
#include "FallingBlocksGame.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameScreenMgr.h"
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

int main(int argc, char* argv[])
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "SoundBoard");	  
	xn::Context context;
	
	// Stk initialization
	Stk::setSampleRate( 44100.0 );
	Stk::setRawwavePath( "resource/rawwaves/" );

	// init context
	initContext(&context);
	context.SetGlobalMirror(false);

	xn::ImageMetaData image_metadata;
  GameScreenMgr::instance().Add(FREE_PLAYING, new FreePlayingGame(&window));
  GameScreenMgr::instance().Add(MAIN_MENU, new MenuScreen(&window)); 
  GameScreenMgr::instance().Add(FALLING_GAME, new FallingBlockGame(&window)); 

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
      GameScreenMgr::instance().GetActive()
        ->update(WINDOW_W-projective_point.X, projective_point.Y);
    }    
    GameScreenMgr::instance().GetActive()->draw();
    window.display();
  }	

	// clean up
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