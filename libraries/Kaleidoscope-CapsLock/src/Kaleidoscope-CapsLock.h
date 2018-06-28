#pragma once

#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-Macros.h"
#include "LEDUtils.h"

class CapsLock_ : public KaleidoscopePlugin {
 public:
  CapsLock_(void) {}

  void begin(void) final;

  static uint8_t capsLockLayer;

 private:
  static void loopHook(const bool postClear);

  static byte row, col;
  static bool cleanupDone;
};

extern CapsLock_ CapsLock;
