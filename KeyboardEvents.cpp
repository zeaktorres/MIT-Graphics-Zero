#include "include/KeboardEvents.h"

bool KeyboardEvents::emit(std::string event_name, int arg) {
  std::vector<lambda> listeners = events[event_name];

  if (listeners.size() == 0) return false;

  // Run all the listeners associated with the event
  for (int idx = 0; idx < listeners.size(); idx += 1) {
    listeners[idx]();
  }

  return true;
}
