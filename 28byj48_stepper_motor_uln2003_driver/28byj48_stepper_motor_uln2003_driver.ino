// credits for this sketch goes to Stein. 
// Stein's email address: harelabb@lyse.net

#include <SerialStepper.h>
#include <arduinostepper.h>

// Define 2 steppers
Stepper steppers[2];

// each using an ArduinoStepper control
ArduinoStepperControl stepper_ctl[] = {
  ArduinoStepperControl {4, 5, 6, 7},
  ArduinoStepperControl {8, 9, 10, 11}// the pins
 };


// Helper function to check if all the steppers has reached target
bool anyRunning() {
  for (const auto& stepper : steppers) {
    if (stepper.running()) {
      return true;
    }
  }
  return false;
}


void setup() {
  /// Initialize the stepper motor controllers
  for (auto& ctl : stepper_ctl) {
    ctl.begin();
  }

  /// Assign steppers to the controllers
  for (int i = 0; i <2 ; ++i) {
    stepper_ctl[i].addStepper(steppers[i]);
  }

  // Set stepper speed to 16 RPM
  for (auto& stepper : steppers) {
    stepper.speed(7);
  }

}

// Forward is CCW
constexpr auto CCW   = Stepper::BACKWARD;
constexpr auto CW  = Stepper::FORWARD;



void loop() {
  float pos = 0; // keep track of position

  delay(4000);

  // need to loop until time for next delay
  // the clock must be updated before the step terget is set
  
  loopClock::tick();

  for (auto& stepper: steppers) {
    stepper.direction(CW);
    

    steppers[0].turn(1.0);
    steppers[1].turn(0.625);

  }
  
  while (anyRunning()) {
    loopClock::tick();
    for (auto& ctl : stepper_ctl) {
      ctl.run();
    }
    yield();
  }

delay(2000);

}
