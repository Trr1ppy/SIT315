#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262

int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // measure the ping time in cm and print it
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  Serial.print(cm);
  Serial.println("cm");
  
  //If sensor reads a distance less then a metre sound the alarm
  if (cm < 100){
    Serial.println("Intruder detected");
  	for (int thisNote = 0; thisNote < 8; thisNote++) {

    	// to calculate the note duration, take one second
    	// divided by the note type.
    	//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    	int noteDuration = 1000 / noteDurations[thisNote];
    	tone(8, melody[thisNote], noteDuration);

    	// to distinguish the notes, set a minimum time between them.
    	// the note's duration + 30% seems to work well:
    	int pauseBetweenNotes = noteDuration * 1.30;
    	delay(pauseBetweenNotes);
    	// stop the tone playing:
    	noTone(8);
  	}
  }
  // Otherwise don't sound the alarm
  else{
    Serial.println("Nothing detected");
  	delay(100);
  }
}
