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
 * @file Backward.ino
 * @brief Arduino Formula zero vehicle firmware.
 * @author Valery Farcy
 */

// Pin Functions
#define BACKWARD_PIN   (10)

#define FORWARD_PIN   (9)
#define LEFT_PIN     (11)
#define RIGHT_PIN    (12)
#define LED_PIN   (13)


void setup()
{
  pinMode(BACKWARD_PIN, OUTPUT); 

  Serial.begin(115200);
  pinMode(FORWARD_PIN, OUTPUT);                                                                                                                                                                                                                                                                      
  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    
    analogWrite( BACKWARD_PIN, 15 );
    
    

}
