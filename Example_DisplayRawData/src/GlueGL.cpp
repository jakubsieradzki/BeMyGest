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

void GlueGL::DrawOnTexture(  
  void* pixels, 
  unsigned tex_x, 
  unsigned tex_y, 
  unsigned data_x, 
  unsigned data_y)
{
  unsigned texture_id = 0;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
    GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
    GL_NEAREST);
  glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGB, tex_x, tex_y, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  // upper left
  glTexCoord2f(0, 0);
  glVertex2f(0, 0);
  // upper right
  glTexCoord2f((float)data_x/(float)tex_x, 0);
  glVertex2f(screen_x_/2.0, 0);
  // bottom right
  glTexCoord2f((float)data_x/(float)tex_x, (float)data_y/(float)tex_y);
  glVertex2f(screen_x_/2.0, screen_y_/2.0);
  // bottom left
  glTexCoord2f(0, (float)data_y/(float)tex_y);
  glVertex2f(0, screen_y_/2.0);

  glEnd();
  glDisable(GL_TEXTURE_2D);
}

}