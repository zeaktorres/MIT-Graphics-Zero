#pragma once

#include <GL/glut.h>

#include <string>

class LightPicker {

 public:

  // A default constructor is required.
  LightPicker();

  void Init(GLfloat Lt0pos[], int index);

  void UpdateFirst(float value);
  void UpdateSecond(float value);

  GLfloat *getLightPosition();

 private:
  GLfloat *m_Lt0pos;
  int m_Index = -1;
};
