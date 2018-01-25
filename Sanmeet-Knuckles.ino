/*
  Code Development Team
  DIGF 2005 - Atelier II
  Professor Nick Puckett
  Tuesday January 23, 2018
  NANO COMMUNICATION CODE
  This code allows Nanos to read information from the serial port sent
  from the control panel, and display corresponding images/animations on
  the OLEDs.
  THE CIRCUIT
    RX is digital pin 8 (connect to TX of other device)
    TX is digital pin 9 (connect to RX of other device)
    SDA connected to A4
    SCL connected to A5
    GND connected to GND
    VCC connected to VTN
  REFERENCES:
  https://www.arduino.cc/en/Tutorial/SoftwareSerialExample
  https://www.arduino.cc/reference/en/language/variables/data-types/bool/
  http://forum.arduino.cc/index.php?topic=42603.0
*/

// include necessary libraries
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include <SoftwareSerial.h> // * NEW
SoftwareSerial mySerial(8, 9); // RX, TX // * NEW

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//// GLOBAL VARIABLES
const int framesPerSecond = 3;
int incoming;

// *** PICK THE ENVIRONMENT YOUR CREATURE LIVES IN ***
// 1 = Desert, 2 = Forest, 3 = Water
int environment = 1;
int petStatus = 0; // 0=HAPPY, 1=SAD
////


////////// HERE ARE WHERE THE INSTRUCTIONS FOR ANIMATION FRAMES GO
//NOTE: screen dimensions: 128x64
//NOTE: use the u8g2 library to write instructions for drawing images (for example using the shape and line functions)
//NOTE: only add your desired drawing functions, buffering/clearing/timing is handled for you :)
// https://github.com/olikraus/u8g2/wiki/u8g2reference#drawbox
//
void happyFrame1(void) {  //THE FIRST FRAME OF THE 'HAPPY' ANIMATION
  // BODY OUTLINE
  u8g2.drawLine(5.5, 45.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 32.5, 4.5);
  u8g2.drawLine(32.5, 4.5, 48.5, 0.5);
  u8g2.drawLine(48.5, 0.5, 79.5, 0.5);
  u8g2.drawLine(79.5, 0.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 115.5, 50.5);
  u8g2.drawLine(123.5, 45.5, 115.5, 50.5);
  // EYES
  u8g2.drawEllipse(44, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawEllipse(85, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(81, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(40, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  // NOSE
  u8g2.drawLine(56.5, 26.5, 64.5, 23.5);
  u8g2.drawLine(64.5, 23.5, 73.5, 26.5);
  u8g2.drawFilledEllipse(64, 31, 3, 3, U8G2_DRAW_ALL);
  // MOUTH
  u8g2.drawLine(106.5, 31.5, 97.5, 27.5);
  u8g2.drawLine(106.5, 31.5, 107.5, 41.5);
  u8g2.drawLine(107.5, 41.5, 90.5, 55.5);
  u8g2.drawLine(90.5, 55.5, 83.5, 63.5);
  u8g2.drawLine(46.5, 63.5, 39.5, 55.5);
  u8g2.drawLine(39.5, 55.5, 22.5, 41.5);
  u8g2.drawLine(22.5, 41.5, 23.5, 31.5);
  u8g2.drawLine(23.5, 31.5, 32.5, 27.5);
  // EXPRESSION
  u8g2.drawLine(36.5, 41, 44.5, 42.5);
  u8g2.drawLine(44.5, 42.5, 51.5, 45.5);
  u8g2.drawLine(51.5, 45.5, 75.5, 45.5);
  u8g2.drawLine(75.5, 45.5, 83.5, 42.5);
  u8g2.drawLine(83.5, 42.5, 91.5, 41);
}
void happyFrame2(void) {  //THE SECOND FRAME OF THE 'HAPPY' ANIMATION
  //  BODY OUTLINE
  u8g2.drawLine(5.5, 45.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 32.5, 4.5);
  u8g2.drawLine(32.5, 4.5, 48.5, 0.5);
  u8g2.drawLine(48.5, 0.5, 79.5, 0.5);
  u8g2.drawLine(79.5, 0.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 115.5, 50.5);
  u8g2.drawLine(123.5, 45.5, 115.5, 50.5);
  // EYES
  u8g2.drawEllipse(44, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawEllipse(85, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(85, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(44, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  // NOSE
  u8g2.drawLine(56.5, 26.5, 64.5, 23.5);
  u8g2.drawLine(64.5, 23.5, 73.5, 26.5);
  u8g2.drawFilledEllipse(64, 31, 2, 2, U8G2_DRAW_ALL);
  // MOUTH
  u8g2.drawLine(106.5, 31.5, 97.5, 27.5);
  u8g2.drawLine(106.5, 31.5, 107.5, 41.5);
  u8g2.drawLine(107.5, 41.5, 90.5, 55.5);
  u8g2.drawLine(90.5, 55.5, 83.5, 63.5);
  u8g2.drawLine(46.5, 63.5, 39.5, 55.5);
  u8g2.drawLine(39.5, 55.5, 22.5, 41.5);
  u8g2.drawLine(22.5, 41.5, 23.5, 31.5);
  u8g2.drawLine(23.5, 31.5, 32.5, 27.5);
  // EXPRESSION
  u8g2.drawLine(36.5, 42, 44.5, 43.5);
  u8g2.drawLine(44.5, 43.5, 51.5, 46.5);
  u8g2.drawLine(51.5, 46.5, 75.5, 46.5);
  u8g2.drawLine(75.5, 46.5, 83.5, 43.5);
  u8g2.drawLine(83.5, 43.5, 91.5, 42);
}
void happyFrame3(void) {  //THE THIRD FRAME OF THE 'HAPPY' ANIMATION
  //  BODY OUTLINE
  u8g2.drawLine(5.5, 45.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 32.5, 4.5);
  u8g2.drawLine(32.5, 4.5, 48.5, 0.5);
  u8g2.drawLine(48.5, 0.5, 79.5, 0.5);
  u8g2.drawLine(79.5, 0.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 115.5, 50.5);
  u8g2.drawLine(123.5, 45.5, 115.5, 50.5);
  // EYES
  u8g2.drawEllipse(44, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawEllipse(85, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(89, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(48, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  // NOSE
  u8g2.drawLine(56.5, 26.5, 64.5, 23.5);
  u8g2.drawLine(64.5, 23.5, 73.5, 26.5);
  u8g2.drawFilledEllipse(64, 31, 3, 3, U8G2_DRAW_ALL);
  // MOUTH
  u8g2.drawLine(106.5, 31.5, 97.5, 27.5);
  u8g2.drawLine(106.5, 31.5, 107.5, 41.5);
  u8g2.drawLine(107.5, 41.5, 90.5, 55.5);
  u8g2.drawLine(90.5, 55.5, 83.5, 63.5);
  u8g2.drawLine(46.5, 63.5, 39.5, 55.5);
  u8g2.drawLine(39.5, 55.5, 22.5, 41.5);
  u8g2.drawLine(22.5, 41.5, 23.5, 31.5);
  u8g2.drawLine(23.5, 31.5, 32.5, 27.5);
  // EXPRESSION
  u8g2.drawLine(36.5, 43, 44.5, 44.5);
  u8g2.drawLine(44.5, 44.5, 51.5, 47.5);
  u8g2.drawLine(51.5, 47.5, 75.5, 47.5);
  u8g2.drawLine(75.5, 47.5, 83.5, 44.5);
  u8g2.drawLine(83.5, 44.5, 91.5, 43);
}

void sadFrame1(void) {  //THE FIRST FRAME OF THE 'SAD' ANIMATION
  // BODY OUTLINE
  u8g2.drawLine(5.5, 45.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 32.5, 4.5);
  u8g2.drawLine(32.5, 4.5, 48.5, 0.5);
  u8g2.drawLine(48.5, 0.5, 79.5, 0.5);
  u8g2.drawLine(79.5, 0.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 115.5, 50.5);
  u8g2.drawLine(123.5, 45.5, 115.5, 50.5);
  // EYES
  u8g2.drawEllipse(44, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawEllipse(85, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(81, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(40, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  // NOSE
  u8g2.drawLine(56.5, 26.5, 64.5, 23.5);
  u8g2.drawLine(64.5, 23.5, 73.5, 26.5);
  u8g2.drawFilledEllipse(64, 31, 3, 3, U8G2_DRAW_ALL);
  // MOUTH
  u8g2.drawLine(106.5, 31.5, 97.5, 27.5);
  u8g2.drawLine(106.5, 31.5, 107.5, 41.5);
  u8g2.drawLine(107.5, 41.5, 90.5, 55.5);
  u8g2.drawLine(90.5, 55.5, 83.5, 63.5);
  u8g2.drawLine(46.5, 63.5, 39.5, 55.5);
  u8g2.drawLine(39.5, 55.5, 22.5, 41.5);
  u8g2.drawLine(22.5, 41.5, 23.5, 31.5);
  u8g2.drawLine(23.5, 31.5, 32.5, 27.5);
  // EXPRESSION
  u8g2.drawLine(51.5, 42.5, 44.5, 45.5);
  u8g2.drawLine(51.5, 42.5, 75.5, 42.5);
  u8g2.drawLine(75.5, 42.5, 83.5, 45.5);
}
void sadFrame2(void) {  //THE SECOND FRAME OF THE 'SAD' ANIMATION
  //  BODY OUTLINE
  u8g2.drawLine(5.5, 45.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 32.5, 4.5);
  u8g2.drawLine(32.5, 4.5, 48.5, 0.5);
  u8g2.drawLine(48.5, 0.5, 79.5, 0.5);
  u8g2.drawLine(79.5, 0.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 115.5, 50.5);
  u8g2.drawLine(123.5, 45.5, 115.5, 50.5);
  // EYES
  u8g2.drawEllipse(44, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawEllipse(85, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(85, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(44, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  // NOSE
  u8g2.drawLine(56.5, 26.5, 64.5, 23.5);
  u8g2.drawLine(64.5, 23.5, 73.5, 26.5);
  u8g2.drawFilledEllipse(64, 31, 2, 2, U8G2_DRAW_ALL);
  // MOUTH
  u8g2.drawLine(106.5, 31.5, 97.5, 27.5);
  u8g2.drawLine(106.5, 31.5, 107.5, 41.5);
  u8g2.drawLine(107.5, 41.5, 90.5, 55.5);
  u8g2.drawLine(90.5, 55.5, 83.5, 63.5);
  u8g2.drawLine(46.5, 63.5, 39.5, 55.5);
  u8g2.drawLine(39.5, 55.5, 22.5, 41.5);
  u8g2.drawLine(22.5, 41.5, 23.5, 31.5);
  u8g2.drawLine(23.5, 31.5, 32.5, 27.5);
  // EXPRESSION
  u8g2.drawLine(51.5, 43.5, 44.5, 46.5);
  u8g2.drawLine(51.5, 43.5, 75.5, 43.5);
  u8g2.drawLine(75.5, 43.5, 83.5, 46.5);
}
void sadFrame3(void) {  //THE THIRD FRAME OF THE 'SAD' ANIMATION
  //  BODY OUTLINE
  u8g2.drawLine(5.5, 45.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 13.5, 50.5);
  u8g2.drawLine(17.5, 20.5, 32.5, 4.5);
  u8g2.drawLine(32.5, 4.5, 48.5, 0.5);
  u8g2.drawLine(48.5, 0.5, 79.5, 0.5);
  u8g2.drawLine(79.5, 0.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 96.5, 4.5);
  u8g2.drawLine(111.5, 20.5, 115.5, 50.5);
  u8g2.drawLine(123.5, 45.5, 115.5, 50.5);
  // EYES
  u8g2.drawEllipse(44, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawEllipse(85, 23, 13.5, 11, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(89, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  u8g2.drawFilledEllipse(48, 23, 7.5, 5.5, U8G2_DRAW_ALL);
  // NOSE
  u8g2.drawLine(56.5, 26.5, 64.5, 23.5);
  u8g2.drawLine(64.5, 23.5, 73.5, 26.5);
  u8g2.drawFilledEllipse(64, 31, 3, 3, U8G2_DRAW_ALL);
  // MOUTH
  u8g2.drawLine(106.5, 31.5, 97.5, 27.5);
  u8g2.drawLine(106.5, 31.5, 107.5, 41.5);
  u8g2.drawLine(107.5, 41.5, 90.5, 55.5);
  u8g2.drawLine(90.5, 55.5, 83.5, 63.5);
  u8g2.drawLine(46.5, 63.5, 39.5, 55.5);
  u8g2.drawLine(39.5, 55.5, 22.5, 41.5);
  u8g2.drawLine(22.5, 41.5, 23.5, 31.5);
  u8g2.drawLine(23.5, 31.5, 32.5, 27.5);
  // EXPRESSION
  u8g2.drawLine(51.5, 44.5, 44.5, 46.5);
  u8g2.drawLine(51.5, 44.5, 75.5, 44.5);
  u8g2.drawLine(75.5, 44.5, 83.5, 47.5);
}

//////////END OF ANIMATION FRAME INSTRUCTIONS

void setup(void) {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB14_tr);

  // set pins for OLED
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  u8g2.begin(4, 5, 6);

  mySerial.begin(4800);
  mySerial.flush();

  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop(void) {
  // Determines pet status before animations are executed
  if (mySerial.available()) {
    incoming = mySerial.read();
    Serial.println(incoming);
    if (incoming == environment) {
      petStatus = 0;
    } else {
      petStatus = 1;
    }
  }
  animateScreen();
}

//// YOU DO NOT HAVE TO MODIFY THE REST OF THE CODE:
void animateScreen() {
  // the pet's status is checked every time animateScreen() is called
  if (petStatus == 0) { //IF PET IS HAPPY, DO THIS CODE:
    u8g2.clearBuffer();
    happyFrame1();
    u8g2.sendBuffer();
    delay(1000 / framesPerSecond);

    u8g2.clearBuffer();
    happyFrame2();
    u8g2.sendBuffer();
    delay(1000 / framesPerSecond);

    u8g2.clearBuffer();
    happyFrame3();
    u8g2.sendBuffer();
    delay(1000 / framesPerSecond);

    u8g2.clearBuffer();
    happyFrame2();
    u8g2.sendBuffer();
    delay(1000 / framesPerSecond);
  }
  else { //IF PET IS NOT HAPPY, IT'S SAD. DO THIS CODE:
    u8g2.clearBuffer();
    sadFrame1();
    u8g2.sendBuffer();
    delay(1000 / framesPerSecond);

    u8g2.clearBuffer();
    sadFrame2();
    u8g2.sendBuffer();
    delay(1000 / framesPerSecond);

    u8g2.clearBuffer();
    sadFrame3();
    u8g2.sendBuffer();
    delay(1000 / framesPerSecond);

    u8g2.clearBuffer();
    sadFrame2();
    u8g2.sendBuffer();
    delay(1000 / framesPerSecond);
  }
}
