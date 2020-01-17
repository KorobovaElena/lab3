#include <Servo.h>

const int servoPin = 11;
const int echoPins[] = {5,6,7};
const int trigPins[] = {8,9,10};
const int border = 5;
const int positionIdle = 0;
const int positions[] = {10, 45, 90};

int dist[3];
int dir = 0;

Servo servo;

void setup() {
  Serial.begin(115200);
  servo.attach(servoPin);
  servo.write(positionIdle);
  for (int i = 0; i<3; i++) {
      pinMode(echoPins[i], INPUT);
      pinMode(trigPins[i], OUTPUT);
  }
}

void loop() {
  bool flag = false;
  for (int i = 0; i < 3; i++) {
  dist[i] = (int)readDist(i); 
  if (dist[i]<= border) {
    flag = true;
    dir = i;
  }
  }
  if (flag==true)
    servo.write(positions[dir]);
  else
    servo.write(positionIdle);
  delay(500);
}

float readDist(int i)
{
  const float speedOfSoundMPerSec = 340.0;
  const float speedOfSoundCmPerUs = speedOfSoundMPerSec / 10000.0;
  return readPulse(i) * speedOfSoundCmPerUs / 2.0;    
}

float readPulse(int i)
{
  digitalWrite(trigPins[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[i], LOW);

  long duration = pulseIn(echoPins[i], HIGH);

  return duration;
}
