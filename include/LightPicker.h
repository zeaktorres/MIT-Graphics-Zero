#pragma once

#include <GL/glut.h>
#include <hscpp/module/Tracker.h>

#include <string>

class LightPicker {
  // Register this object with hscpp's tracking system. The first argument must
  // be equal to the type of the enclosing class. The second argument must be a
  // unique key, which will be used by hscpp to identify the object's
  // constructor. When HSCPP_DISABLE is defined, this macro will evaluate to
  // nothing.
  HSCPP_TRACK(LightPicker, "LightPicker");

 public:
  hscpp_virtual ~LightPicker() = default;

  // A default constructor is required.
  LightPicker();

  void Init(GLfloat Lt0pos[], int index);

  // Functions must be virtual in order for a swapped object to call the new
  // implementation. The "hscpp_virtual" macro evaluates to "virtual" if
  // HSCPP_DISABLE is not defined. If HSCPP_DISABLE is defined, hscpp_virtual
  // will evaluate to nothing.
  //
  // Note that the use of the "final" keyword may cause hot module reloading to
  // break. This is due to the compiler optimizing the call by devirtualizing
  // it.
  hscpp_virtual void UpdateFirst(float value);
  hscpp_virtual void UpdateSecond(float value);

  hscpp_virtual GLfloat *getLightPosition();

 private:
  GLfloat *m_Lt0pos;
  int m_Index = -1;
};
