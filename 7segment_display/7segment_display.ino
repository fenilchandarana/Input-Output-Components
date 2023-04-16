// Include the library
#include <TM1637Display.h>

// Define the connections pins
#define CLK 11
#define DIO 12

// Create a display object of type TM1637Display
TM1637Display display = TM1637Display(CLK, DIO);

// Create an array that turns all segments ON
const uint8_t allON[] = {0xff, 0xff, 0xff, 0xff};

// Create an array that turns all segments OFF
const uint8_t allOFF[] = {0x00, 0x00, 0x00, 0x00};

// Create an array that sets individual segments per digit to display the word "dOnE"
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

// Create degree celsius symbol
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Degree symbol
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

// Create an array that sets individual segments per digit to display the word "ALL"
const uint8_t all[] = {
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
  SEG_D | SEG_E | SEG_F,   // L
  SEG_D | SEG_E | SEG_F   // L
};

// Create an array that sets individual segments per digit to display the symbol "dash"
const uint8_t dash[] = {
SEG_G, SEG_G, SEG_G, SEG_G
};


void setup() {
  // Set the brightness to 5 (0=dimmest 7=brightest)
  display.setBrightness(3);
  display.setSegments(dash);
    delay(500);
  display.clear();
  
  display.setSegments(allOFF);
  delay(2000);
}

void loop() {

  
  display.showNumberDec(-12);     // Prints _-12
  delay(2000);
  display.clear();

  display.showNumberDec(31, false); // Prints __31
  delay(2000);
  display.clear();

    display.showNumberDec(31, true); // Prints __31
  delay(2000);
  display.clear();

  display.showNumberDec(31, true);  // Prints 0031
  delay(2000);
  display.clear();

  display.showNumberDec(14, false, 2, 1); // Prints _14_
  delay(2000);
  display.clear();

    display.showNumberDec(14, false, 2, 0); // Prints _14_
  delay(2000);
  display.clear();

    display.showNumberDec(14, false, 2, 2); // Prints _14_
  delay(2000);
  display.clear();

    

//   Prints 15°C
  int temperature = 15;
  display.showNumberDec(temperature, false, 2, 0);
  display.setSegments(celsius, 2, 2);
  delay(2000);
  display.clear();

  // Prints ALL
    display.setSegments(all, 3, 0);
      delay(2000);
  display.clear();

  // Prints dOnE
  display.setSegments(done);

  delay(2000);
  display.clear();


}
