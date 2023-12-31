#pragma once

#include <hscpp/module/Tracker.h>

#include <string>

class ColorPicker {
  // Register this object with hscpp's tracking system. The first argument must
  // be equal to the type of the enclosing class. The second argument must be a
  // unique key, which will be used by hscpp to identify the object's
  // constructor. When HSCPP_DISABLE is defined, this macro will evaluate to
  // nothing.
  HSCPP_TRACK(ColorPicker, "ColorPicker");

 public:
  hscpp_virtual ~ColorPicker() = default;

  // A default constructor is required.
  ColorPicker();

  void Init(int colorChoice, int index);

  // Functions must be virtual in order for a swapped object to call the new
  // implementation. The "hscpp_virtual" macro evaluates to "virtual" if
  // HSCPP_DISABLE is not defined. If HSCPP_DISABLE is defined, hscpp_virtual
  // will evaluate to nothing.
  //
  // Note that the use of the "final" keyword may cause hot module reloading to
  // break. This is due to the compiler optimizing the call by devirtualizing
  // it.
  hscpp_virtual void Update(int colorChoice);

  hscpp_virtual int getColorChoice();

 private:
  int m_ColorChoice;
  int m_Index = -1;
};
