
/*
  Ultrasonic Theramin v1
  Plays 8 note scale depending on distance
  Different LEDs color per note
  by L. Savage, February 2023
*/


// Neo Pixel setup
#include <Adafruit_NeoPixel.h>
#define N_LEDS 5

// Define Pins
const int trigPin = 9;
const int echoPin = 10;
const int soundPin = 6;
const int ledPin = 5;
    
// Ultrasonic variables
long duration;
int distance;
// LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, ledPin, NEO_GRB + NEO_KHZ800);

//Define pins as input or output, start serial
void setup() {
  strip.begin();
  pinMode(ledPin, OUTPUT); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(soundPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
 // Clear the trigPin then send a pulse for 10ms
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);  // Reads echoPin, returns  in microseconds
  distance = duration * 0.034 / 2;  // Calculating the distance
  // Delay controls how sensitive it is to motion. A short delay smooths the sound
  delay(70);
  convert_notes(distance);  
}

// Plays note and disp[lays color depending on distance from ultrasonic sensor
void convert_notes(int d) {

  if (d > 30) {
     noTone(soundPin);
     setLEDcolor(strip.Color(0, 0, 0));    // No sound if hand is out of range
  }
  
   else if (d < 3) {
     setLEDcolor(strip.Color(25, 0, 0));   //C 262, RED 255 0 0
     tone(soundPin, 262);
     }

  else if (d < 6) {
     setLEDcolor(strip.Color(25, 12, 0));   //D 294, ORANGE 255 127 0 
     tone(soundPin, 294);
     }

  else if (d < 9) {
     setLEDcolor(strip.Color(25, 25, 0));   //E 330, YELLOW 255 255 0
     tone(soundPin, 330);
     }

  else if (d < 12) {
     setLEDcolor(strip.Color(0, 25, 0));   //F 349, GREEN 0 255 0
     tone(soundPin, 349);
     }

  else if (d < 15) {
     setLEDcolor(strip.Color(0, 0, 25));   //G 392, BLUE 0 0 255
     tone(soundPin, 392);
     }

  else if (d < 18) {
     setLEDcolor(strip.Color(7, 0, 14));   //A 440, INDIGO 75 0 130 
     tone(soundPin, 440);
     }

  else if (d < 21) {
     setLEDcolor(strip.Color(15, 0, 21));   //B 494, VIOLET 148 0 211
     tone(soundPin, 494);
     }
    
  else if (d < 30) {
     setLEDcolor(strip.Color(15, 3, 5));   // 523, PINK 
     tone(soundPin, 523);
     }

  else {
    noTone(soundPin);
    setLEDcolor(strip.Color(0, 0, 0));
  }
  
}

// Sets all LEDs one color
static void setLEDcolor(uint32_t c) {
     for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
    }
}
