#include "include/ColorPicker.h"

#include <iostream>

#include "include/SimpleDemoData.h"

ColorPicker::ColorPicker() {
  // The default constructor is called on a runtime swap. You can set a callback
  // method to execute right before and right after an object has been swapped,
  // and serialize data.
  auto cb = [this](hscpp::SwapInfo &info) {
    switch (info.Phase()) {
      case hscpp::SwapPhase::BeforeSwap:
        // This object is about to be deleted, so serialize out its state. Any
        // type can be serialized so long as it has a default constructor and is
        // copyable.
        info.Serialize("ColorChoice", m_ColorChoice);

        info.Serialize("Index", m_Index);
        break;
      case hscpp::SwapPhase::AfterSwap:
        // This object has just been created, replacing an older version.
        info.Unserialize("ColorChoice", m_ColorChoice);

        info.Unserialize("Index", m_Index);
        // This new object is in a new dynamic library, but it still has access
        // to global data in GlobalUserData.
        SimpleDemoData *pDemoData =
            hscpp::GlobalUserData::GetAs<SimpleDemoData>();

        pDemoData->colorPickers.at(m_Index) = this;

        break;
    }
  };

  // Set the lambda callback. When HSCPP_DISABLE is defined, this macro
  // evaluates to nothing. To avoid creating a lambda in a shipped build, the
  // lambda can be placed directly within the macro. However, this will make it
  // more difficult to debug, as breakpoints can't be placed within a macro.
  Hscpp_SetSwapHandler(cb);
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
