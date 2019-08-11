// Rotary Encoder
#include "ESPRotary.h";
#define ROTARY_PIN_1 4
#define ROTARY_PIN_2 3
int moves_per_click = 2;
ESPRotary r = ESPRotary(ROTARY_PIN_1, ROTARY_PIN_2, moves_per_click) ;
int old_pos = 0;
int new_pos = 0;

// Keyboard Library
#include "HID-Project.h"

// keys
int keypadPins[9] = {2, 15, 10, 16, 6, 14, 8, 7, 9};
int keypadStatus;  // Used to monitor which buttons are pressed.
int timeout;  // timeout variable used in loop
int UpDownArr, SideArr = 0;
int MainVol = 1;

void setup() {
  Serial.begin(115200);
  // Rotate
  r.setChangedHandler(rotate);
  for (int i = 0; i < 9; i++) {
    pinMode(keypadPins[i], INPUT);  // Set all keypad pins as inputs
    digitalWrite(keypadPins[i], HIGH);  // pull all keypad pins high
  }
  Consumer.begin();
}

void loop() {
  r.loop();
  keypadStatus = getKeypadStatus();  // read which buttons are pressed
  if (keypadStatus != 0) {
    sendKeyPress(keypadStatus);  // send the button over USB
    timeout = 2000;  // top of the repeat delay
    while ((keypadStatus == getKeypadStatus()) && (--timeout))  // Decrement timeout and check if key is being held down
      delayMicroseconds(400);
    while (getKeypadStatus() == keypadStatus)  // while the same button is held down
    {
      sendKeyPress(keypadStatus);  // continue to send the button over USB
      delay(250);
    }
  }
}

void rotate(ESPRotary & r) {
  new_pos = r.getPosition();
  if ( old_pos > new_pos) {
    old_pos = new_pos ;
    if ( MainVol == 1) {
      Serial.println("MEDIA_VOLUME_UP");
      Consumer.write(MEDIA_VOLUME_UP);
    }
    else if ( SideArr == 1) {
      Serial.println("KEY_RIGHT_ARROW");
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.releaseAll();
    }
    else if ( UpDownArr == 1) {
      Serial.println("KEY_DOWN_ARROW");
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.releaseAll();
    }
  } else {
    old_pos = new_pos ;
    if ( MainVol == 1) {
      Serial.println("MEDIA_VOLUME_DOWN");
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    else if ( SideArr == 1) {
      Serial.println("KEY_LEFT_ARROW");
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.releaseAll();
    }
    else if ( UpDownArr == 1) {
      Serial.println("KEY_UP_ARROW");
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.releaseAll();
    }
  }
}

void sendKeyPress(int key) {
  switch (key) {
    case 1:  // 0x001
      Serial.println("MEDIA_VOLUME_MUTE");
      Consumer.write(MEDIA_VOLUME_MUTE);
      break;
    case 2:  // 0x002
      Serial.println("KEY_LEFT_CTRL+C");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_C);
      Keyboard.releaseAll();
      delay(75);
      break;
    case 4:  // 0x004
      Serial.println("KEY_LEFT_CTRL+V");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_V);
      Keyboard.releaseAll();
      delay(75);
      break;
    case 8:  // 0x008
      Serial.println("KEY_LEFT_CTRL+X");
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_X);
      Keyboard.releaseAll();
      delay(75);
      break;
    case 16:  // 0x010
      Serial.println("KEY_LEFT_ARROW");
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.releaseAll();
      delay(75);
      break;
    case 32:  // 0x020
      Serial.println("KEY_DOWN_ARROW");
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.releaseAll();
      delay(75);
      break;
    case 64:  // 0x040
      Serial.println("KEY_RIGHT_ARROW");
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.releaseAll();
      delay(75);
      break;
    case 128:  // 0x080
      Serial.println("KEY_UP_ARROW");
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.releaseAll();
      delay(75);
      break;
    case 256:  // 0x100
      Serial.println(key);
      if ( MainVol == 1 ) {
        UpDownArr = 1;
        SideArr = 0;
        MainVol = 0;
      }
      else if ( UpDownArr == 1 ) {
        UpDownArr = 0;
        SideArr = 1;
        MainVol = 0;
      }
      else {
        UpDownArr = 0;
        SideArr = 0;
        MainVol = 1;
      }
      break;
  }
}

int getKeypadStatus() {
  int keypadStatus = 0;  // this will be what's returned

  /* initialize all pins, inputs w/ pull-ups */
  for (int i = 0; i < 9; i++) {
    if (!digitalRead(keypadPins[i])) {
      keypadStatus |= 1 << i; // set the status bit of the keypad return value
    }
  }
  return keypadStatus;
}
