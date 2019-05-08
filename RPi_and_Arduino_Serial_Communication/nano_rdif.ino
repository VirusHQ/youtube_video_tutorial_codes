#include <Wire.h>
#include <Adafruit_PN532.h>

#define PN532_IRQ   (2)
#define PN532_RESET (3)
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

int ledPin = LED_BUILTIN;
String readString;

void setup(void) {
  Serial.begin(115200);
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    while (1); // halt
  }
  nfc.SAMConfig();
  pinMode(ledPin, OUTPUT);
}

void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  if (success) {
    nfc.PrintHex(uid, uidLength);
    if (uidLength == 4) {
      uint32_t cardid = uid[0];
      cardid <<= 8;
      cardid |= uid[1];
      cardid <<= 8;
      cardid |= uid[2];
      cardid <<= 8;
      cardid |= uid[3];
      String ab1 = String(cardid) + "," + String(uid[0]) + "," + String(uid[1]) + "," + String(uid[2]) + "," + String(uid[3]) ;
      Serial.println(ab1);
      while (1) {
        while (Serial.available()) {
          char c = Serial.read();
          readString += c;
        }
        readString.trim();
        if (readString.length() > 0) {
          if (readString == "DerpHashTurnOn") {
            digitalWrite(ledPin, HIGH);
            break;
          }
          if (readString == "off") {
            digitalWrite(ledPin, LOW);
            break;
          }
        }
      }
      readString = "";
    }
  }
  delay(2000);
}
