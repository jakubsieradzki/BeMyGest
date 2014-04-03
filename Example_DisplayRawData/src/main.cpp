#include "GlueGL.h"

int main(int argc, char* argv[]) {  
  auto& glue = bmg::GlueGL::getInstance();
  
  glue.Init(argc, argv, 1024, 768, "Example_DisplayRawData");
  glue.BindDisplayFunc([&]{
    glue.BeginDraw();
    // here goes rendering code
    glue.EndDraw();
  });
  glue.BindKeyboardFunc([](unsigned char key, int x, int y){
    switch(key) {
      case 27:
        exit(1);
    }
  });
  glue.Run();
}