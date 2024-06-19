#include "include/LightPicker.h"

LightPicker::LightPicker() {
  // The default constructor is called on a runtime swap. You can set a callback
  // method to execute right before and right after an object has been swapped,
  // and serialize data.
  // evaluates to nothing. To avoid creating a lambda in a shipped build, the
  // lambda can be placed directly within the macro. However, this will make it
  // more difficult to debug, as breakpoints can't be placed within a macro.
}

void LightPicker::Init(GLfloat Lt0pos[], int index) {
  m_Lt0pos = Lt0pos;
  m_Index = index;
}
void LightPicker::UpdateFirst(float value) { m_Lt0pos[0] += value; }
void LightPicker::UpdateSecond(float value) { m_Lt0pos[1] += value; }

GLfloat *LightPicker::getLightPosition() { return m_Lt0pos; }
