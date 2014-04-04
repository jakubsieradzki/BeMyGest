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
  
  xn::DepthGenerator depth_generator;  
  status = depth_generator.Create(context);
  bmg::OnError(status, []{
    std::cout << "Couldn't create depth generator!" << std::endl;
  });
  status = context.StartGeneratingAll();
  bmg::OnError(status, []{
    std::cout << "Couldn't generate all data!" << std::endl;
  });

  glue.BindDisplayFunc([&]{
    glue.BeginDraw();

    // here goes code for app main loop
    XnStatus status = context.WaitOneUpdateAll(depth_generator);
    bmg::OnError(status, []{
      std::cout << "Couldn't update and wait for new data!" << std::endl;
    });
    const XnDepthPixel* p_depth_pixel = depth_generator.GetDepthMap();

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