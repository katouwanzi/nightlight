
const int sunPin5V = 7;         //pin for 5V input for the RGB LED for Sun
const int sunPin1 = 8;          //pin for Red input for the RGB LED for Sun
const int sunPin2 = 9;          //pin for Green input for the RGB LED for Sun
const int moonPin = 10;         //pin for the moon LED
const int cityPin = 11;         //pin for the city lights LEDs
const int photocellPin = 0;     //pin for photocell analog reading
const int fsrPin = 2;           //pin for force sensitive resistor analog reading

int photocellReading = 0;     // the analog reading from the photocell
int fsrReading = 0;           // the analog reading from the force sensitive resistor
boolean started = false;

void setup() {
  //set the output pins
  pinMode(sunPin5V, OUTPUT);
  pinMode(sunPin1, OUTPUT);
  pinMode(sunPin2, OUTPUT);
  pinMode(cityPin, OUTPUT);
  pinMode(moonPin, OUTPUT);
   
  // set the Serial monitor for debugging
  Serial.begin(9600);
}

void loop() {
  //read from force sensitive pin
  fsrReading = analogRead(fsrPin);

  //print reading for debugging
  Serial.print("FSR reading = ");
  Serial.println(fsrReading);

  //if reading > 100, toggle started to turn on/off
  if(fsrReading > 100){
    started = !started;
  }

  if(started){
    // if started, read from photocell
    photocellReading = analogRead(photocellPin);

    //print reading for debugging
    Serial.print("photocell reading = ");
    Serial.println(photocellReading);     // the raw analog reading

    //call isDay() to determine if the reading is in the range for day or night.
    if(isDay(photocellReading)){
      // if the reading is within the day range, call day() to set up the outputs for LEDs.
      day();
    }
    else{
      // if the reading is within the night range, call night() to set up the outputs for LEDs.
      night();
    }
  }
  else{  
    // if not started, turn off all the LEDs.
    digitalWrite(sunPin5V, LOW);
    digitalWrite(sunPin1,HIGH);
    digitalWrite(sunPin2,HIGH);
    digitalWrite(moonPin, LOW);
    digitalWrite(cityPin, LOW);
  }

  delay(500);
}

// function to determine if it is day or night
boolean isDay(int reading){
  return reading > 200;
}

// function to setup outputs for day
void day() {
  digitalWrite(sunPin5V, HIGH);
  digitalWrite(sunPin1,LOW);
  digitalWrite(sunPin2,LOW);
  digitalWrite(moonPin, LOW);
  digitalWrite(cityPin, LOW);
}

// function to setup outputs for night
void night() {
  digitalWrite(sunPin5V, LOW);
  digitalWrite(sunPin1,HIGH);
  digitalWrite(sunPin2,HIGH);
  digitalWrite(moonPin, HIGH);
  digitalWrite(cityPin, HIGH);
}
