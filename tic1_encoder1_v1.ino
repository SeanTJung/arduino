// This code has the function of controlling one tic stepper lead screw motor using one rotary encoder

// include neccesary libraries
#include <Tic.h> 
#include <Encoder.h> 

//Define
Encoder myEnc(2,3); // Encoder Output A and B connected to Arduino Pins 2 and 3

TicI2C tic; // Tic can be configured on Polulu software

// Define required variables
long int oldPosition = -999;
long int newPosition;

// Define the current limit, in milliamps, to use while moving the motor.
//const uint16_t currentLimitWhileMoving = 500;

// Define the current limit, in milliamps, to use while stopped.
//const uint16_t currentLimitWhileStopped = 0;

  // put your setup code here, to run once:
void setup() {
  // Specify what type of Tic we are talking to.  This affects
  // how the setCurrentLimit command works.
  // tic.setProduct(TicProduct::T825);
  // tic.setProduct(TicProduct::T834);
  // tic.setProduct(TicProduct::T500);
  // tic.setProduct(TicProduct::T249);
  // tic.setProduct(TicProduct::Tic36v4);

  // Set up I2C
  Wire.begin();

  Serial.begin(9600); // begins the serial monitor
  Serial.println("Encoder Positions:"); // displays on serial monitor

  // Give the Tic some time to start up.
  delay(20);

  // Set the Tic's current position to 0, so that when we command
  // it to move later, it will move a predictable amount.
  tic.haltAndSetPosition(0);

  // Tells the Tic that it is OK to start driving the motor.  The
  // Tic's safe-start feature helps avoid unexpected, accidental
  // movement of the motor: if an error happens, the Tic will not
  // drive the motor again until it receives the Exit Safe Start
  // command.  The safe-start feature can be disbled in the Tic
  // Control Center.
  tic.exitSafeStart();
}

// Sends a "Reset command timeout" command to the Tic.
void resetCommandTimeout()
{
  tic.resetCommandTimeout();
}

// Delays for the specified number of milliseconds while
// resetting the Tic's command- timeout so that its movement does
// not get interrupted by errors.
void delayWhileResettingCommandTimeout(uint32_t ms)
{
  uint32_t start = millis();
  do
  {
    resetCommandTimeout();
  } while ((uint32_t)(millis() - start) <= ms);
}

// Polls the Tic, waiting for it to reach the specified target
// position.  Note that if the Tic detects an error, the Tic will
// probably go into safe-start mode and never reach its target
// position, so this function will loop infinitely.  If that
// happens, you will need to reset your Arduino.
void waitForPosition(int32_t targetPosition)
{
  do
  {
    resetCommandTimeout();
  } while (tic.getCurrentPosition() != targetPosition);
}


// put your main code here, to run repeatedly:
void loop() {
  newPosition= myEnc.read(); // reads position of the encoder
  if (newPosition !=oldPosition)
  {
    oldPosition=newPosition;
  }
  // Tell the Tic to move to position 100, and wait until it gets
  // there.
  tic.setTargetPosition(oldPosition);
  waitForPosition(oldPosition);

  // Tell the Tic to move to position -100, and delay for 3000 ms
  // to give it time to get there.
  // tic.setTargetPosition(-100);
  // delayWhileResettingCommandTimeout(3000);

}
