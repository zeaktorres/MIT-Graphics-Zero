#include "include/LightPicker.h"

LightPicker::LightPicker() {
  // The default constructor is called on a runtime swap. You can set a callback
  // method to execute right before and right after an object has been swapped,
  // and serialize data.
  auto cb = [this](hscpp::SwapInfo &info) {
    switch (info.Phase()) {
      case hscpp::SwapPhase::BeforeSwap:
        // This object is about to be deleted, so serialize out its state. Any
        // type can be serialized so long as it has a default constructor and is
        // copyable.
        info.Serialize("LightPosition", m_Lt0pos);

        info.Serialize("Index", m_Index);
        break;
      case hscpp::SwapPhase::AfterSwap:
        // This object has just been created, replacing an older version.
        info.Unserialize("LightPosition", m_Lt0pos);

        info.Unserialize("Index", m_Index);
        // This new object is in a new dynamic library, but it still has access
        // to global data in GlobalUserData.

        break;
    }
  };

  // Set the lambda callback. When HSCPP_DISABLE is defined, this macro
  // evaluates to nothing. To avoid creating a lambda in a shipped build, the
  // lambda can be placed directly within the macro. However, this will make it
  // more difficult to debug, as breakpoints can't be placed within a macro.
  Hscpp_SetSwapHandler(cb);
}

void LightPicker::Init(GLfloat Lt0pos[], int index) {
  m_Lt0pos = Lt0pos;
  m_Index = index;
}
void LightPicker::UpdateFirst(float value) { m_Lt0pos[0] += value; }
void LightPicker::UpdateSecond(float value) { m_Lt0pos[1] += value; }

GLfloat *LightPicker::getLightPosition() { return m_Lt0pos; }
