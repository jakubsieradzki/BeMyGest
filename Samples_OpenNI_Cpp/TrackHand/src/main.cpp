#include "../../Common/src/GlueGL.h"
#include "../../Common/src/OpenNiUtil.h"

#include <iostream>

const int MAX_DEPTH = 10000;
const char* GESTURE = "Wave";
bool hand_recognized = false;
XnPoint3D projective_point;

auto& glue = bmg::GlueGL::getInstance();
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

int main(int argc, char* argv[]) {    
  glue.Init(argc, argv, 640, 240, "TrackHand");  

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
      320, 0, 640, 240);

    depth_generator.GetMetaData(depth_metadata);
    unsigned depthX = depth_metadata.XRes();
    unsigned depthY = depth_metadata.YRes();

    XnRGB24Pixel* transformed_depth_map = new XnRGB24Pixel[depthX * depthY];    
    bmg::CalculateDepth(
      depth_generator.GetDepthMap(), depthX, depthY, MAX_DEPTH, transformed_depth_map);

    glue.DrawOnTexture(
      (void*)transformed_depth_map, 
      depthX, depthY, 
      depthX, depthY, 
      0, 0, 
      320, 240);
    delete [] transformed_depth_map;

    if (hand_recognized) {
      // Draw point over tracked hand
      glue.DrawPointOverRegion(projective_point.X, projective_point.Y, 0, 0);
      glue.DrawPointOverRegion(projective_point.X, projective_point.Y, 320, 0);
    }

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
}