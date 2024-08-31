#include <Tic.h>
#include <Encoder.h> //includes the Encoder Library

Encoder myEnc(2,3);  // defines the Encoder object
Encoder myEnc2(4,5);  // defines the second Encoder object

//Each Tic's control mode must be set to "Serial/I2C/USB".  The
// serial device number of one Tic must be set to its default
// value of 14, and the serial device number of another Tic must
// be set to 15.
TicI2C tic1(14); 
TicI2C tic2(15);

int potPin1 = A0; // Potentiometer output connected to analog pin 0
int potPin2 = A1; // Potentiometer output connected to analog pin 1

// Define the gain
int gain1;
int gain2;
// Define the potentiometer value
int potVal1;
int potVal2;

int velocity1;
int velocity2;

//defining variables//
long int oldPosition = -999;
long int newPosition;

//position variables for second encoder
long int oldPosition2 = -999;
long int newPosition2;

void setup() {

  // Set up I2C. 
  Wire.begin();

  Serial.begin(9600); // begins the serial monitor
  Serial.println("Encoder Positions:"); // displays on serial monitor

  // Give the Tic some time to start up.
  delay(20);

  // Set the Tic's current position to 0, so that when we command
  // it to move later, it will move a predictable amount.
  tic1.haltAndSetPosition(0);
  tic2.haltAndSetPosition(0);

  // Tells the Tic that it is OK to start driving the motor.  The
  // Tic's safe-start feature helps avoid unexpected, accidental
  // movement of the motor: if an error happens, the Tic will not
  // drive the motor again until it receives the Exit Safe Start
  // command.  The safe-start feature can be disbled in the Tic
  // Control Center.
  tic1.exitSafeStart();
  tic2.exitSafeStart();
}

// Sends a "Reset command timeout" command to the Tic.
void resetCommandTimeout()
{
  tic1.resetCommandTimeout();
  tic2.resetCommandTimeout();
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

//called from void loop
void waitForPosition(int32_t targetPosition)
{
  do
  {
    resetCommandTimeout();
  } while (tic1.getCurrentPosition() != targetPosition);
}

void waitForPosition2(int32_t targetPosition)
{
  do
  {
    resetCommandTimeout();
  } while (tic2.getCurrentPosition() != targetPosition);
}

void loop() {  // put your main code here, to run repeatedly:  

// reads position of the encoder
  newPosition = myEnc.read(); 
  if (newPosition !=oldPosition)
  {  
    potVal1 = analogRead(potPin1);
    if (potVal1 == 0)
    {
      gain1 = 1;
    }  
    else if (potVal1 <= 110 && potVal1 > 0)
    {
      gain1 = 2;
    }  
    else if (potVal1 <= 1023 && potVal1 > 110)
    {
      gain1 = 3;
    }
    
    oldPosition = newPosition * gain1;

    potVal2 = analogRead(potPin2);
    if (potVal2 == 0)
    {
      Velocity1 = 300000;
    }  
    else if (potVal2 <= 110 && potVal2 > 0)
    {
      Velocity1 = 1000000;
    }  
    else if (potVal2 <= 1023 && potVal2 > 110)
    {
      Velocity1 = 2000000;
    }  
     
  }

// reads position of the second encoder
  newPosition2= myEnc2.read(); // reads position of the encoder
  if (newPosition2 !=oldPosition2)
  {
    potVal1 = analogRead(potPin1);
    if (potVal1 == 0)
    {
      gain2 = 1;
    }  
    else if (potVal1 <= 110 && potVal1 > 0)
    {
      gain2 = 3;
    }  
    else if (potVal1 <= 1023 && potVal1 > 110)
    {
      gain2 = 5;
    }

    oldPosition2 = newPosition2 * gain2;

    potVal2 = analogRead(potPin2);
    if (potVal2 == 0)
    {
      Velocity2 = 300000;
    }  
    else if (potVal2 <= 110 && potVal2 > 0)
    {
      Velocity2 = 1000000;
    }  
    else if (potVal2 <= 1023 && potVal2 > 110)
    {
      Velocity2 = 2000000;
    }
    
  }
  
  // Tell the Tic to move to position 100, and wait until it gets
  // there.
  tic1.setTargetPosition(oldPosition);
  tic1.setTargetVelocity(Velocity1);
  waitForPosition(oldPosition);

  tic2.setTargetPosition(oldPosition2);
  tic2.setTargetVelocity(Velocity2);
  waitForPosition2(oldPosition2);
}
