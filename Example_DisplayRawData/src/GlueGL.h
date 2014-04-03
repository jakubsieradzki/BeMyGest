#ifndef GLUE_GL_
#define GLUE_GL_

#include <functional>

void displayFunc();

namespace bmg {
 
class GlueGL
{
public:
  void Init(
    int argc, 
    char* argv[], 
    unsigned screen_x, 
    unsigned screen_y,
    const char* window_name,
    bool is_fullscreen = false);

  void BeginDraw();
  void EndDraw();

  void Run();

  void BindKeyboardFunc(
    const std::function<void(unsigned char, int, int)>& func);
  void BindDisplayFunc(const std::function<void()>& func);  

  static GlueGL& getInstance() {
    static GlueGL instance;
    return instance;
  }
  
  std::function<void()> display_func_;
  std::function<void(unsigned char, int, int)> keyboard_func_;
private:
  GlueGL() :  screen_x_(640), screen_y_(480) {}
  GlueGL(const GlueGL&) {}
  GlueGL& operator=(const GlueGL&) {}

  unsigned screen_x_, screen_y_;  
};

}

#endif