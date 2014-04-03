#include "GlueGL.h"

#include <stdlib.h>
#include <GL/glut.h>

using std::function;

namespace bmg {

// glut callbacks
void displayFunc() {
  GlueGL::getInstance().display_func_();
}

void keyboardFunc(unsigned char key, int x, int y) {
  GlueGL::getInstance().keyboard_func_(key, x, y);
}

void idleFunc() {
  glutPostRedisplay();
}

void GlueGL::Init(
  int argc, 
  char* argv[], 
  unsigned screen_x, 
  unsigned screen_y,
  const char* window_name,
  bool is_fullscreen /*= false*/)
{
  screen_x_ = screen_x > 0 ? screen_x : screen_x_;
  screen_y_ = screen_y > 0 ? screen_y : screen_y_;
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(screen_x_, screen_y_);
  if (is_fullscreen) glutFullScreen();
  glutCreateWindow(window_name);
  glutSetCursor(GLUT_CURSOR_NONE);
  glutIdleFunc(idleFunc);
}

void GlueGL::BeginDraw()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, screen_x_, screen_y_, 0, -1.0, 1.0);
}

void GlueGL::EndDraw()
{
  glutSwapBuffers();
}

void GlueGL::BindKeyboardFunc(
  const function<void(unsigned char, int, int)>& func)
{
  GlueGL::keyboard_func_ = func;
  glutKeyboardFunc(keyboardFunc);
}

void GlueGL::BindDisplayFunc(const function<void()>& func)
{
  GlueGL::display_func_ = func;
  glutDisplayFunc(displayFunc);
}

void GlueGL::Run()
{
  glutMainLoop();
}

}