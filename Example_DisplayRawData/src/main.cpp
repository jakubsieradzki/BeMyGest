#include "GlueGL.h"
#include "OpenNiUtil.h"

#include <iostream>

int main(int argc, char* argv[]) {  
  auto& glue = bmg::GlueGL::getInstance();
  
  glue.Init(argc, argv, 1024, 768, "Example_DisplayRawData");  
  
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
  status = context.StartGeneratingAll();
  bmg::OnError(status, []{
    std::cout << "Couldn't generate all data!" << std::endl;
  });
  xn::ImageMetaData image_metadata;
  image_generator.GetMetaData(image_metadata);

  glue.BindDisplayFunc([&]{
    glue.BeginDraw();

    // here goes code for app main loop
    XnStatus status = context.WaitOneUpdateAll(image_generator);
    bmg::OnError(status, []{
      std::cout << "Couldn't update and wait for new data!" << std::endl;
    });
    const XnRGB24Pixel* image_pixels = image_metadata.RGB24Data();
    glue.DrawOnTexture(
      (void*)image_pixels, 
      320, 240, 
      image_metadata.XRes(), image_metadata.YRes());

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