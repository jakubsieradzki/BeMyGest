#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <boost/lexical_cast.hpp>
#include "global.h"
#include "GameMgr.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Seashell.h"
#include "Enemy.h"
#include "Starfish.h"
#include "GFX.h"
#include "Map.h"
#include "Player.h"

#include "OpenNiUtil.h"

const float PI = 3.14159265358f;
const int MAX_DEPTH = 10000;
const char* GESTURE = "Wave";
bool hand_recognized = false;
XnPoint3D projective_point;

xn::DepthGenerator depth_generator;
xn::GestureGenerator gesture_generator;
xn::HandsGenerator hands_generator;

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

int main()
{
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Electricus", sf::Style::Default);
  window.setMouseCursorVisible(false);
  window.setFramerateLimit(50);
  sf::Font font;// = sf::Font();
  bool stop = false;

  Map map("resource/map/1.txt", 10, 15, 50);

  GameMgr::getInstance().loadSounds();
  GameMgr::getInstance().setCellSize(map.grid_element_x, map.grid_element_y);
  sf::Music* bg_music = new sf::Music();
  bg_music -> openFromFile("resource/sfx/background.ogg");
  bg_music -> setVolume(70.0f);
  sf::Clock level_clock;

  sf::Texture beczka = GFX::LoadTexture("resource/beczka.png");
  sf::Texture ryba = GFX::LoadTexture("resource/ryba.png");
  sf::Texture starfish = GFX::LoadTexture("resource/starfish.png");
  sf::Texture zdechla_ryba = GFX::LoadTexture("resource/zdechla_ryba.png");
  sf::Texture muszla1 = GFX::LoadTexture("resource/muszla.png");
  sf::Texture muszla2 = GFX::LoadTexture("resource/muszla2.png");
  sf::Texture fish1 = GFX::LoadTexture("resource/wegorz1.png");
  sf::Texture fish2 = GFX::LoadTexture("resource/wegorz2.png");
  sf::Texture fish3 = GFX::LoadTexture("resource/wegorz3.png");
  // umieszcamy assety na mapie nr 1
  for(int i = 0; i < (map.size); ++i)
  {
    Tile* temp = map.tiles[i];
    Entity* entity;

    switch(temp -> sign)
    {
    case 'M': // muszla1
      entity = EntityFactory::
        CreateDynamicSeashell(&muszla1, 5, (temp->col)*(map.grid_element_y), 0.2f);
      map.setEntity(entity, temp -> row, temp -> col);
      break;
    case 'N': // muszla2
      entity = EntityFactory::
          CreateDynamicSeashell(&muszla2, 5, (temp->col)*(map.grid_element_y), 0.3f);
      map.setEntity(entity, temp -> row, temp -> col);
      break;
    case 'B': // beczka
      entity = EntityFactory::
        CreateDynamicEnemy(&beczka, BECZKA, 7, (temp->col)*(map.grid_element_y), 0.4f);
      map.setEntity(entity, temp -> row, temp -> col);
      ((Enemy*)entity) -> setType(BECZKA);
      break;
    case 'R': // ryba
      entity = EntityFactory::
        CreateDynamicEnemy(&ryba, PIRANIA, 15, (temp -> col) * (map.grid_element_y), 0.2f);
      map.setEntity(entity, temp -> row, temp -> col);
      ((Enemy*)entity) -> setType(PIRANIA);
      break;
    case 'S': // starfish
      entity = EntityFactory::
        CreateDynamicStarfish(&starfish, 20, (temp -> col) * (map.grid_element_y), 0.15f);
      map.setEntity(entity, temp -> row, temp -> col);
      break;
    case 'Z': // zdechla ryba
      entity = EntityFactory::
        CreateDynamicEnemy(&zdechla_ryba, ZDECHLA, 5, (temp->col)*(map.grid_element_y), 0.2f);
      map.setEntity(entity, temp -> row, temp -> col);
      ((Enemy*)entity) -> setType(ZDECHLA);
      break;
    default:
      break;
    }
  }

  auto fish = EntityFactory::CreatePlayer(&fish1, SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 0.8f);

  sf::Texture waves = GFX::LoadTexture("resource/fale.png");
  sf::Sprite waves1 = sf::Sprite(waves);
  sf::Sprite waves2 = sf::Sprite(waves);

  sf::Texture line = GFX::LoadTexture("resource/linia.png");
  sf::Sprite* line1 = new sf::Sprite(line);
  sf::Sprite* line2 = new sf::Sprite(line);

  float left_boundry = (SCREEN_WIDTH-MOVE_SPACE_WIDTH)/2.0f;
  float right_boundry = SCREEN_WIDTH-(SCREEN_WIDTH-MOVE_SPACE_WIDTH)/2.0f;

  line1 -> setPosition(left_boundry, 0.0f);
  line2 -> setPosition(right_boundry, 0.0f);

  waves1.setPosition(-SCREEN_WIDTH/2.0f, 0.0f);
  waves2.setPosition(SCREEN_WIDTH/2.0f, 0.0f);

  float xLeftSide = 0.0f;
  // music
  bg_music -> setLoop(true);
  bg_music -> play();
  level_clock.restart();
  int currentSecond = MAX_SECONDS_FOR_LEVEL;
  sf::Text* textScore, *textClock, *textScored;

  // <<<<<<<<<<<<<< OpenNI init
  xn::Context context;
  XnStatus status = context.Init();
  bmg::OnError(status, []{
    std::cout << "Couldn't init OpenNi!" << std::endl;
    exit(1);
  });

  xn::ImageGenerator image_generator;
  status = image_generator.Create(context);
  bmg::OnError(status, []{
    std::cout << "Couldn't create image generator!" << std::endl;
  });

  status = depth_generator.Create(context);
  bmg::OnError(status, []{
    std::cout << "Couldn't create depth generator!" << std::endl;
  });

  xn::ImageMetaData image_metadata;
  xn::DepthMetaData depth_metadata;

  // Create gesture & hands generators
  status = gesture_generator.Create(context);
  bmg::OnError(status, []{
    std::cout << "Couldn't create gesture generator!" << std::endl;
  });
  status = hands_generator.Create(context);
  bmg::OnError(status, []{
    std::cout << "Couldn't create hands generator!" << std::endl;
  });

  // Register to callbacks
  XnCallbackHandle h1, h2;
  gesture_generator
    .RegisterGestureCallbacks(Gesture_Recognized, Gesture_Process, NULL, h1);
  hands_generator
    .RegisterHandCallbacks(Hand_Create, Hand_Update, Hand_Destroy, NULL, h2);

  status = context.StartGeneratingAll();
  bmg::OnError(status, []{
    std::cout << "Couldn't generate all data!" << std::endl;
  });
  status = gesture_generator.AddGesture(GESTURE, NULL);
  bmg::OnError(status, []{
    std::cout << "Couldn't add gesture!" << std::endl;
  });
  // <<<<<<<<<<<<<< OpenNI init

  while(window.isOpen())
  {
    // here goes code for app main loop
    XnStatus status = context.WaitAndUpdateAll();
    bmg::OnError(status, []{
      std::cout << "Couldn't update and wait for new data!" << std::endl;
    });

    image_generator.GetMetaData(image_metadata);
    unsigned imageX = image_metadata.XRes();
    unsigned imageY = image_metadata.YRes();

    depth_generator.GetMetaData(depth_metadata);
    unsigned depthX = depth_metadata.XRes();
    unsigned depthY = depth_metadata.YRes();

    int x_on_screen;
    int y_on_screen;

    if (hand_recognized) {
      float x = projective_point.X;
      float y = projective_point.Y;

      if (x > 300) x = 300.0f;
      if (x < 0) x = 0.0f;
      if (y > 230) y = 230.0f;
      if (y < 0) y = 0.0f;

      float x_ratio = (300.0f-x)/300.0f;
      float y_ratio = y/230.0f;

      x_on_screen = static_cast<int>(x_ratio * SCREEN_WIDTH);
      y_on_screen = static_cast<int>(y_ratio * SCREEN_HEIGHT);

      //std::cout << "Point (" << x_on_screen << ", " << y_on_screen << ")" << std::endl;
      stop = false;
    } else {
      stop = true;
    }

    window.clear();
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        bg_music ->stop();
        window.close();
      }
    }

    int xMousePosition = x_on_screen;
    int yMousePosition = y_on_screen;

    float vectorX = xMousePosition - SCREEN_WIDTH/2.0f;
    float vectorY = yMousePosition - SCREEN_HEIGHT/2.0f;

    float magnitude = sqrt(vectorX*vectorX + vectorY*vectorY);

    if(magnitude == 0.0f)
      magnitude = 0.01f;

    vectorX /= magnitude;
    vectorY /= magnitude;

    magnitude = sqrt(vectorX*vectorX + vectorY*vectorY);

    // wektor osi OX
    float axisX = 1.0f;
    float axisY = 0.0f;
    float magnituedAxis = sqrt(axisX*axisX+axisY*axisY);
    vectorY = -vectorY;
    magnitude = sqrt(vectorX*vectorX + vectorY*vectorY);
    // k¹t miêdzy osi¹ OX a wektorem kierunku wêgorza
    float angle = acos((axisX*vectorX+axisY*vectorY)/(magnituedAxis*magnitude));
    angle = angle * 180.0f/PI;

    float xMouseOffset = SCREEN_WIDTH/2.0f - xMousePosition;
    float yMouseOffset = SCREEN_HEIGHT/2.0f - yMousePosition;

    xMouseOffset = (xMouseOffset/(SCREEN_WIDTH/2.0f))*MOVE_X_SPEED;
    yMouseOffset = (yMouseOffset/(SCREEN_HEIGHT/2.0f))*MOVE_Y_SPEED;

    if(!stop)
    {
      textScore = new sf::Text("Punkty: " + boost::lexical_cast<std::string>(GameMgr::getInstance().getScore()), font, 25);
      textScore -> setPosition(10.0f, 0.0f);
      textScore -> setColor(sf::Color::Blue);
      textClock = new sf::Text("Czas: " + boost::lexical_cast<std::string>(currentSecond), font, 25);
      textClock -> setPosition(680.0f, 0.0f);
      textClock -> setColor(sf::Color::Blue);
    }
    else
    {
      textScored = new sf::Text("Zdobyte: " + boost::lexical_cast<std::string>(GameMgr::getInstance().getScore()) + " pkt.", font, 40);
      textScored -> setColor(sf::Color::Blue);
      textScored -> setPosition(280.0f, 280.0f);
    }

    if(vectorY > 0.0f)
    {
      fish.sprite().setRotation(-angle);
      fish.collisionAura().setRotation(-angle);
    }
    else
    {
      fish.sprite().setRotation(angle);
      fish.collisionAura().setRotation(angle);
    }

    static int fishNumber = 1;
    static int frameNumber = 1;

    switch(fishNumber) {
    case 1:
      fish.sprite().setTexture(fish1);
      break;
    case 2:
      fish.sprite().setTexture(fish2);
      break;
    case 3:
      fish.sprite().setTexture(fish3);
      break;
    }

    if(++frameNumber > 6){
      if(++fishNumber>3)
      fishNumber = 1;
      frameNumber = 1;
    }
    if(!stop)
    {
      fish.move(-xMouseOffset, -yMouseOffset);

      if(fish.sprite().getPosition().x < left_boundry)
      fish.setPosition(left_boundry, fish.sprite().getPosition().y);
      if(fish.sprite().getPosition().x > right_boundry)
      fish.setPosition(right_boundry, fish.sprite().getPosition().y);
      if(fish.sprite().getPosition().y < MOVE_SPACE_TOP_OFFSET)
      fish.setPosition(fish.sprite().getPosition().x, MOVE_SPACE_TOP_OFFSET);
      if(fish.sprite().getPosition().y > (SCREEN_HEIGHT - MOVE_SPACE_BOTTOM_OFFSET))
      fish.setPosition(fish.sprite().getPosition().x, SCREEN_HEIGHT - MOVE_SPACE_BOTTOM_OFFSET);

      xLeftSide -= xMouseOffset;
      // animacja fali
      waves1.move(xMouseOffset, 0.0f);
      waves2.move(xMouseOffset, 0.0f);

      if(waves1.getPosition().x <= -(float)SCREEN_WIDTH)
      {
        waves1.setPosition((float)SCREEN_WIDTH, 0.0f);
        waves2.setPosition(0.0f, 0.0f);
      }
      else if (waves1.getPosition().x >= (float)SCREEN_WIDTH)
      {
        waves1.setPosition(-(float)SCREEN_WIDTH, 0.0f);
        waves2.setPosition(0.0f, 0.0f);
      }
      if(waves2.getPosition().x <= -(float)SCREEN_WIDTH)
      {
        waves2.setPosition((float)SCREEN_WIDTH, 0.0f);
        waves1.setPosition(0.0f, 0.0f);
      }
      else if(waves2.getPosition().x >= (float)SCREEN_WIDTH)
      {
        waves2.setPosition(-(float)SCREEN_WIDTH, 0.0f);
        waves1.setPosition(0.0f, 0.0f);
      }
    }
    // t³o
    window.draw(waves1);
    window.draw(waves2);

    // linie ograniczaj¹ce ruch rybki
    //window.draw(*line1);
    //window.draw(*line2);

    for(int i = 0; i < (map.counter); ++i)
    {
      // just for sure
      if((map.assets[i]) != NULL)
      {
        if(!stop)
          map.assets[i] -> animate(xMouseOffset);
        if((!map.assets[i] -> remove) && (map.assets[i] -> x_position_on_map >= xLeftSide-300.0f))
        {
          if(map.assets[i] -> x_position_on_map < xLeftSide+SCREEN_WIDTH+300.0f)
          {
            // kolizje
            fish.isCollides(map.assets[i]);
            // rysujemy
            window.draw(map.assets[i] -> sprite());
           // window.draw(map.assets[i] -> collisionAura());
          }
        }
      }
    }

    // PLAYAER
    window.draw(fish.sprite());
   // window.draw(fish.collisionAura());

    // GUI
    if(!stop)
    {
      window.draw(*textScore);
      window.draw(*textClock);
    }
    else
      window.draw(*textScored);

    window.display();
    if(level_clock.getElapsedTime().asSeconds() > 1.0f)
    {
      --currentSecond;
      level_clock.restart();
      if(currentSecond == 0)
      stop = true;
    }
  }
}