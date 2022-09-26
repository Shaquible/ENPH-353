/* read a rotary encoder with interrupts
   Encoder hooked up with common to GROUND,
   encoder0PinA to pin 2, encoder0PinB to pin 4 (or pin 3 see below)
   it doesn't matter which encoder pin you use for A or B  

   uses Arduino pullups on A & B channel outputs
   turning on the pullups saves having to hook up resistors 
   to the A & B channel outputs 

*/ 

#define encoderXPinA  2 // A channel pin
#define encoderXPinB  21 //B channel Pin


// Pin setup
const unsigned int Aout = 10;  // Analog out pin
const float pi=3.141592;

int encoderXPos = 0; //Absolute encoder position
int encoderInitial = 0; //for velocity calc
int encoderFinal = 0; // for veloctiy calc
int encoderDelta = 0; //for velocity calc

//counts
long int counts = 0;
double velocity = 0;
int vel =0;
unsigned long time=0;
void setup() { 

  // Pin Initialization for X motor
  pinMode(encoderXPinA, INPUT); 
 // digitalWrite(encoderXPinA, HIGH);       // turn on pullup resistor
  pinMode(encoderXPinB, INPUT); 
  //digitalWrite(encoderXPinB, HIGH);       // turn on pullup resistor
  attachInterrupt(0, doEncoder_ExpandedXA, CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(2, doEncoder_ExpandedXB, CHANGE);  // encoder pin on interrupt 0 - pin 2
  
  Serial.begin (38400);
  //Serial.println("start");                // a personal quirk
} 

void loop(){
  char inByte;
  static int sending=false;
  
  if (Serial.available() > 0) 
  { // get incoming byte:
    inByte = Serial.read();
    switch(inByte)
    { case 's':
      case 'S':
       //start data output
       sending = true;
       break;
      case 'q':
      case 'Q':
       //stop data output
       sending = false;
       break;
    }
  }

  if(sending)
  { encoderInitial = encoderXPos;//initial encoder position
    time = micros();
    //delay(100); //delay for maxel to spin
    //encoderFinal = encoderXPos; //final encoder position after 0.1 s
    //encoderDelta = encoderFinal - encoderInitial;// change in encoder position
    // velocity = ((encoderDelta*2*pi)/500)/0.1; //compute angular velocity in rad/s
    Serial.print(encoderXPos,DEC); //serial prints for testing
    Serial.print(",");
    Serial.println(time, DEC);
    //delay(1);
  }
}

/* See this expanded function to get a better understanding of the
 * meanings of the four possible (pinA, pinB) value pairs:
 */
void doEncoder_ExpandedXA(){
  //delay(10);
  if (digitalRead(encoderXPinA) == HIGH) {   // found a low-to-high on channel A
    if (digitalRead(encoderXPinB) == HIGH) {  // check channel B to see which way                                     // encoder is turning
      encoderXPos = encoderXPos + 1;         // CW
    } 
    else {
      encoderXPos = encoderXPos - 1;         // CCW
    }
  }
  else if (digitalRead(encoderXPinA) == LOW) { //High to low change on channel A
    if(digitalRead(encoderXPinB) == LOW){
       encoderXPos = encoderXPos + 1; // CW
    } else {
        encoderXPos = encoderXPos -1; // CCM
    } 

  }
}

void doEncoder_ExpandedXB(){
  //delay(10);
  if (digitalRead(encoderXPinB) == HIGH) {   // found a low-to-high on channel B
    if (digitalRead(encoderXPinA) == LOW) {  // check channel B to see which way                                     // encoder is turning
      encoderXPos = encoderXPos + 1;         // CW
    } 
    else {
      encoderXPos = encoderXPos - 1;         // CCW
    }
  }
  else if (digitalRead(encoderXPinB) == LOW) { //High to low change on channel A
    if(digitalRead(encoderXPinA) == HIGH){
       encoderXPos = encoderXPos + 1; // CW
    } else {
        encoderXPos = encoderXPos -1; // CCM
    } 

  }
}
