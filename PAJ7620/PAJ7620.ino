#include <DFRobot_PAJ7620U2.h>
#include <Wire.h>

DFRobot_PAJ7620U2 paj;

void setup() {
  Serial.begin(115200);
  delay(300);

  Serial.println("Gesture recognition via PAJ7620U2");
  while (paj.begin() != 0) {
    Serial.println("Init failed! Check wiring/I2C address...");
    delay(500);
  }
  paj.setGestureHighRate(false);
  Serial.println("Ready. Show a gesture.");
}

static void printGesture(uint16_t g) {
  String desc = paj.gestureDescription((DFRobot_PAJ7620U2::eGesture_t)g);
  Serial.println("--------------Gesture Recognition System---------------------------");
  Serial.print("gesture code        = "); Serial.println(g);
  Serial.print("gesture description = "); Serial.println(desc);

  switch (g) {
    case 1:   Serial.println("[RIGHT]"); break;
    case 2:   Serial.println("[LEFT]"); break;
    case 4:   Serial.println("[UP]"); break;
    case 8:   Serial.println("[DOWN]"); break;
    case 16:  Serial.println("[FORWARD]"); break;
    case 32:  Serial.println("[BACKWARD]"); break;
    case 64:  Serial.println("[CLOCKWISE]"); break;
    case 128: Serial.println("[ANTI-CLOCKWISE]"); break;
    case 256: Serial.println("[WAVE]"); break;
    case 512: Serial.println("[SLOW WAVE]"); break;
    case 3:   Serial.println("[SLOW WAVE LEFT-RIGHT]"); break;
    case 12:  Serial.println("[SLOW WAVE UP-DOWN]"); break;
    case 48:  Serial.println("[SLOW WAVE FORWARD-BACKWARD]"); break;
    default:  Serial.println("[NEW GESTURE]"); break;
  }
  Serial.println();
}

void loop() {
  DFRobot_PAJ7620U2::eGesture_t g = paj.getGesture();
  if (g != paj.eGestureNone) {
    printGesture(g);
  }
}
