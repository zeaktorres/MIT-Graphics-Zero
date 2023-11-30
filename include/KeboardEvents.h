// app/event_manager.hpp

#ifndef KEYBOARD_EVENTS
#define KEYBOARD_EVENTS

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <vector>

template <typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
  typedef T(fnType)(U...);
  fnType **fnPointer = f.template target<fnType *>();
  return (size_t)(*fnPointer);
}

class KeyboardEvents {
 private:
  typedef std::function<void()> lambda;
  std::map<std::string, std::vector<lambda>> events;

 public:
  KeyboardEvents() {}

  KeyboardEvents *on(std::string event_name,
                     lambda callback) {  // we're using a pointer to reference
                                         // `events[event_name]` so as
    // to get reference to original object and not the copy object.
    std::vector<lambda> *listeners = &this->events[event_name];

    for (lambda i : *listeners) {
      if (getAddress(i) == getAddress(callback)) {
        return this;
      }
    }

    listeners->push_back(callback);

    return this;
  }

  bool emit(std::string event_name, int arg);
};

#endif
