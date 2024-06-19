#pragma once

#include <string>

class ColorPicker {
 public:
  // A default constructor is required.
  ColorPicker();

  void Init(int colorChoice, int index);

  void Update(int colorChoice);

  int getColorChoice();

 private:
  int m_ColorChoice;
  int m_Index = -1;
};
