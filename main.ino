#include <LedControl.h>

/*
 * pins for led matrix
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 
 * pin for sound detector
 * DO2 (digital output) is connected to pin 2
 */

LedControl lc=LedControl(12,11,10,1);

//define variables for led matrix
int randNumber;
int randRow;
int randCol;

//define variables for sound sensor
int soundSensor = 2;

void setup() {
  
  Serial.begin(9600);
  
  // wake up MAX7219
  lc.shutdown(0,false);
  // Set the brightness to a medium values
  lc.setIntensity(0,15);
  // and clear the display
  lc.clearDisplay(0);

  pinMode (soundSensor, INPUT);
  
}

void loop()
{
  //set timestamp when loop begins
  unsigned long loop_begin;
  loop_begin = millis();

  //set interval
  unsigned long blink_interval;
  blink_interval = 5000;

  //turn on led matrix
  changePattern();

  // while interval limit is not reached, led matrix stays on and if-loops checks for user sound input
  while (millis() - loop_begin < blink_interval){
  reactToSound();
  }

  //clear LED Matrix
  lc.clearDisplay(0);
}

// function: turn on LED Matrix
void changePattern()
{  
  //generate random number between 8 and 64 to get a random number of leds to be turned on
  randNumber = random(8,32);

  //turn on leds on with random coordinates
  for (int i=0; i <= randNumber; i++){
    randRow = random(0,8);
    randCol = random(0,8);
    lc.setLed(0,randRow,randCol,true);
  }
}

// function: if sound is detected, change pattern
void reactToSound()
{
  int statusSensor = digitalRead (soundSensor);

  if (statusSensor == 1){
  lc.clearDisplay(0);
  changePattern();
  }
}

