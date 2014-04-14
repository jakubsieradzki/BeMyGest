#include "../../Common/src/GlueGL.h"
#include "../../Common/src/OpenNiUtil.h"

#include <iostream>

const int MAX_DEPTH = 10000;

int main(int argc, char* argv[]) {  
  auto& glue = bmg::GlueGL::getInstance();  
  glue.Init(argc, argv, 640, 240, "DisplayRawData");  
  
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

  xn::DepthGenerator depth_generator;
  status = depth_generator.Create(context);
  bmg::OnError(status, []{
    std::cout << "Couldn't create depth generator!" << std::endl;
  });

  status = context.StartGeneratingAll();
  bmg::OnError(status, []{
    std::cout << "Couldn't generate all data!" << std::endl;
  });
  xn::ImageMetaData image_metadata;
  xn::DepthMetaData depth_metadata;  

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