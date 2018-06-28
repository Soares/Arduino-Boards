#include "Kaleidoscope-CapsLock.h"
#include "LEDUtils.h"
#include "Kaleidoscope.h"
#include "layers.h"

byte CapsLock_::row = 255, CapsLock_::col = 255;
uint8_t CapsLock_::capsLockLayer;
bool CapsLock_::cleanupDone = true;
cRGB capslock_color = CRGB(0, 0, 255);

void CapsLock_::begin(void) {
  Kaleidoscope.useLoopHook(loopHook);
}

void CapsLock_::loopHook(bool postClear) {
  if (!postClear)
    return;

  if (!Layer.isOn(capsLockLayer)) {
    if (!cleanupDone) {
      LEDControl.set_mode(LEDControl.get_mode_index());
      cleanupDone = true;
    }
    return;
  }

  cleanupDone = false;
  bool capsState = !!(kaleidoscope::hid::getKeyboardLEDs() & LED_CAPS_LOCK);
  if (!capsState) {
    kaleidoscope::hid::pressKey(Key_CapsLock);
  }

  LEDControl.set_mode(LEDControl.get_mode_index());

  for (uint8_t r = 0; r < ROWS; r++) {
    for (uint8_t c = 0; c < COLS; c++) {
      Key k = Layer.lookupOnActiveLayer(r, c);
      Key layer_key = Layer.getKey(capsLockLayer, r, c);

      if (k == LockLayer(capsLockLayer)) {
        row  = r;
        col = c;
      }

      if (k != layer_key || k == Key_NoKey) {
        LEDControl.refreshAt(r, c);
      } else {
        LEDControl.setCrgbAt(r, c, capslock_color);
      }
    }
  }

  if (row > ROWS || col > COLS)
    return;

  cRGB color = breath_compute();
  LEDControl.setCrgbAt(row, col, color);
}

CapsLock_ CapsLock;
