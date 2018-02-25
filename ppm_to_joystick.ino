#include <PPMReader.h>

// Initialize a PPMReader on digital pin 3 with 6 expected channels.
int interruptPin = 3;
int channelAmount = 7;
PPMReader ppm(interruptPin, channelAmount);

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  true, true,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
}

// Last state of the buttons
int lastButtonState[5] = {0,0,0,0,0};

void loop() {

  for (int channel = 1; channel <= channelAmount; ++channel) {
    unsigned long value = ppm.latestValidChannelValue(channel, 0);

    int16_t val = map(value, 1000, 2000, 0, 1023);

    switch(channel) {
      case 1: // row (alier)
        Joystick.setXAxis(val);
        break;
      case 2: // pitch (el)
        Joystick.setYAxis(val);
        break;
      case 3: // th
        Joystick.setThrottle(val);
        break;
      case 4: // yaw (rd)
        Joystick.setRudder(val);
        break;
    }
  }

  delay(10);
}
