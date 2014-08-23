// Formula Zero
// Robot Vehicle firmware for the Arduino platform
//
// Copyright (c) 2014 by Valéry Farcy
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is furnished
// to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
// AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

/**
 * @file Formulazero.ino
 * @brief Arduino Formula zero vehicle firmware.
 * @author Valery Farcy
 */

#define DEBUG (1)

enum COMMAND_IDS
{
    INVALID_CMD = 0,
    DRIVE = 10
};

// Pin Functions
#define FORWARD_PIN   (9)
#define BACKWARD_PIN   (10)
#define LEFT_PIN     (11)
#define RIGHT_PIN    (12)
#define LED_PIN   (13)

// Bits to represent different directions.
// Example, to indicate Forward & Right, adding
// FORWARD_BIT + RIGHT_BIT = 9.
// This can later be decoded to drive the car
// forward and right.

#define STOP          (0)    
#define FORWARD_BIT   (1) // b'0001' (binary)
#define BACKWARD_BIT (2) // b'0010'
#define LEFT_BIT     (4) // b'0100'
#define RIGHT_BIT    (8) // b'1000'

struct Command /* http://www.c4learn.com/c-programming/c-initializing-array-of-structure/ */
/* byte is similar to char, but for unsigned values.*/
{
    byte id;     /*direction : FF (forward) FR (forward right) FL (forward left) BB (backward) BL (backward left) BR (backward right) LL (left) RR (right) SS (stop) - See https://github.com/JBionics/Programmable-RC-Car/blob/master/programmable_rc_controller/src/SequenceThread.java and https://github.com/JBionics/Programmable-RC-Car/blob/master/arduino/arduino_programmable_rc.pde*/
    byte data1;  /*speed : 0 to 255 */
    byte data2;  /*duration : 0 to 255 ms*/  
    byte checksum;  
}C[3] = {
          {FORWARD_BIT + RIGHT_BIT,15,255,0}, /*Write the car's journey here  */
          {FORWARD_BIT + LEFT_BIT,12,7,255},
          {STOP,10,11,0}
        };;




void driveCar(struct Command &newCmd)
{
    // If forward and backward are both enabled, error, remove the backward bit set
    if ((newCmd.data1 & FORWARD_BIT) && (newCmd.data1 & BACKWARD_BIT)) {
        newCmd.data1 -= BACKWARD_BIT;
    }
    
    // If left and right are both enabled, error, remove the right bit set
    if ((newCmd.data1 & LEFT_BIT) && (newCmd.data1 & RIGHT_BIT)) {
        newCmd.data1 -= RIGHT_BIT;
    }
    
    // Drive forward if enabled
    if (newCmd.data1 & FORWARD_BIT) {
        // Note: newCmd.data2 is the speed, a PWM value specified in range 0 - 255, 255 = MAX
        analogWrite(FORWARD_PIN, newCmd.data2);
    } else {
        analogWrite(FORWARD_PIN, 0);
    }
    
    // Drive backward if enabled
    if (newCmd.data1 & BACKWARD_BIT) {
        analogWrite(BACKWARD_PIN, newCmd.data2);
    } else {
        analogWrite(BACKWARD_PIN, 0);
    }
    
    // Drive left if enabled
    if (newCmd.data1 & LEFT_BIT) {
        digitalWrite(LEFT_PIN, HIGH);
    } else {
        digitalWrite(LEFT_PIN, LOW);
    }
    
    // Drive right if enabled
    if (newCmd.data1 & RIGHT_BIT) {
        digitalWrite(RIGHT_PIN, HIGH);
    } else {
        digitalWrite(RIGHT_PIN, LOW);
    }
}

void processCommand(struct Command &newCmd)
{
    switch (newCmd.id)
    {
        case DRIVE:
            /*dbg_print("Drive...");*/
            driveCar(newCmd);
            break;
        default:
            // Unknown Command, do nothing
            /*dbg_print("Invalid cmd received...");*/
            break;
    }
}


// If DEBUG is enabled, this function writes a string to the serial port
void dbg_print(const char * s)
{
#if DEBUG
    Serial.write(s);
#endif
}

void setup()
{
  pinMode(FORWARD_PIN, OUTPUT);                                                                                                                                                                                                                                                                      
  pinMode(BACKWARD_PIN, OUTPUT); 
  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  
  Command incomingCmd;
  
  /*
  Serial.println(C[0].id,HEX);
  Serial.println(C[0].data1,HEX);
  Serial.println(C[0].data2,HEX);
  Serial.println(C[0].checksum,HEX);
  
  Serial.println(C[1].id,HEX);
  Serial.println(C[1].data1,HEX);
  Serial.println(C[1].data2,HEX);
  Serial.println(C[1].checksum,HEX);
  
  Serial.println(C[2].id,HEX);
  Serial.println(C[2].data1,HEX);
  Serial.println(C[2].data2,HEX);
  Serial.println(C[2].checksum,HEX);
  
  */
  
   if (Serial.available() >= sizeof(Command)) { /*To be modified LATER !!!!!!!!!!!!!!!!!!!!!!!!*/
        // read the incoming data from C[] !!!!!!!!!!!!!!! To be modified LATER !!!!!!!!!!!!!:
        Command * mem = &incomingCmd;
        unsigned char * p = (unsigned char *)mem;
        for (int i = 0; i < sizeof(Command); i++) {
            unsigned int data = Serial.read();
            p[i] = data;
        }
  
  processCommand(incomingCmd);
  
       // Should be processed way more seriously, w/ checksum verification, like this 
       /*
        byte received_sum = incomingCmd.id + incomingCmd.data1 + incomingCmd.data2;
        if (incomingCmd.id != INVALID_CMD && received_sum == incomingCmd.checksum) {
            processCommand(incomingCmd);
            dbg_print("Good Cmd - checksum matched");
        } else {
            //Checksum didn't match, don't process the command
            dbg_print("Bad Cmd - invalid cmd or checksum didn't match");
        }     
      */
   }
/* See https://github.com/JBionics/Programmable-RC-Car/blob/master/arduino/arduino_programmable_rc.pde */
}
