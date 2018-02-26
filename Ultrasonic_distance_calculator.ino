/* Recourses used for the code and circuit
 *  www.HowToMechatronics.com
 *  https://www.arduino.cc/en/tutorial/pushbutton
 *  https://create.arduino.cc/projecthub/circuito-io-team/piezo-tunes-d4a011?ref=search&ref_id=piezo&offset=2
*/ 

//Declare pin numbers
const int buttonPin = 2;        // Button to turn warning on/off
const int audioPin = 8;         // Piezo buzzer to send an audible warning
const int echoPin = 9;
const int trigPin = 10;
const int ledPin =  13;         // Led light to test distance warning when silence is preferred


//Define variables for calculation
unsigned long duration;
int distance; 
const unsigned int maxDuration = 20000;   // (approx 340cm, anything further away than this is irrelevant)
int buttonState = 0;                      // To read if button has been pressed or not.
int lastButtonState = 0;
int ledState = 0;

void setup() {
  pinMode(trigPin, OUTPUT);   // initialize the trigger pin an output
  pinMode(echoPin, INPUT);    // initialize the echo pin an input
  Serial.begin(9600);         // Starts serial communication(???)
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);  // initialize the pushbutton pin as an input
}

void loop() {
  // Turns output from trigPin off
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(1000000);

  // Turns output from trigPin on for 10μs
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echoPin input and store time (in μs) of the sound wave's travel in the duration variable
  duration = pulseIn(echoPin, HIGH);

  //Calculate distance
  distance = duration*0.034/2;
  /*speed of sound is 33120 centimetres per second (wikipedia)
   * 33120/1000000 => 0.03312cm per μs (I use 0.034)
   * Divide by 2 since sound waves travel to the object and then back to the receiver.
   */

   buttonState = digitalRead(buttonPin); //read input from pin for the pushbutton

   //Check if button is high or low
   //by comparing to previous state
   if(buttonState != lastButtonState){

    //Change led state on buttonpress
    if(buttonState ==1){
      if(ledState ==1) ledState = 0;
      else             ledState = 1;
    }
    lastButtonState = buttonState; //Store current state of button
   }
   digitalWrite(ledPin, ledState); // Switch led on (1) and off (0)

   if(distance < 10 && ledState == 1){
    tone(audioPin, 3500, 500);
    delay(1000);
    tone(audioPin, 3000, 500);
    delay(1000);
   }
   


   delay(20); // Small delay to prevent debouncing from reding buttonState too fast
   
//   while (buttonState = HIGH){
//    digitalWrite(ledPin, LOW);
//   }
//   while (buttonState = LOW){
//    digitalWrite(ledPin, LOW);
//   }
//    if(distance < 10){
//  //      tone(audioPin, 3500, 500);
//  //      delay(1000);
//  //      tone(audioPin, 3000, 500);
//  //      delay(1000);
//      
//    } else{
//      digitalWrite(ledPin, LOW);
//    }
   
  //Print distance to the Serial Monitor
  if(duration > maxDuration){
    Serial.println("Irrelevant range");
  }else{
      Serial.print("Cm: ");
      Serial.println(distance);
      //Serial.print("cm");
  }
  
  
}
