#include "include/ColorPicker.h"

#include <iostream>

#include "include/SimpleDemoData.h"

ColorPicker::ColorPicker() {
  // The default constructor is called on a runtime swap. You can set a callback
  // method to execute right before and right after an object has been swapped,
  // and serialize data.
  // more difficult to debug, as breakpoints can't be placed within a macro.
}

void ColorPicker::Init(const int colorChoice, int index) {
  m_ColorChoice = colorChoice;
  m_Index = index;
}

void ColorPicker::Update(int colorIncrement) {
  // Make a change here and save to see the results live!
  m_ColorChoice += 1;
  m_ColorChoice %= 4;
}

int ColorPicker::getColorChoice() { return m_ColorChoice; }
