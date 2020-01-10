#include "buzzer.h"
#include "button.h"

#define BUZZER_PIN 3
#define BUTTON_PIN 4

#define NOTE_FS3 185
#define NOTE_C3  131


Buzzer buzzer(BUZZER_PIN);
Button button(BUTTON_PIN);

const float voltsPerMeasurement = 5.0/1024.0;
const int sensorPin=A0;

int notes[] = {NOTE_FS3, NOTE_C3};
double durations[] = {2,2};
int melodyLength = 2;
float distance;

bool alarm = false;
const float maxDist = 30.0;

void setup()
{
  buzzer.setMelody(notes, durations, melodyLength);
}
void loop()
{
  switch (alarm)
  {
    case false:
    distance = readDist();
    if (distance<maxDist)
    {
      buzzer.turnSoundOn();
      alarm = true;
    }
      break;
    
    case true:
    buzzer.playSound();
    if (button.wasPressed())
    {
      buzzer.turnSoundOff();
      alarm = false;
    }
      break;
  }
}

float readDist(){
  float volts = readAnalog() * voltsPerMeasurement;
  return pow(14.7737/volts, 1.2134); // for small IR sensor (SHARP 2Y0A21)
}

float readAnalog()
{
  int sum = 0;
  int maxV = -5000;
  int minV = 5000;
  int n = 15;
  for (int i = 0; i < n; i++)
  {
    int cur = analogRead(sensorPin);
    if (cur > maxV)
    {
      maxV = cur;
    }
    if (cur < minV)
    {
      minV = cur;
    }
    sum += cur;
    delay(6);
  }
  return (sum - maxV - minV) / (float)(n - 2);
}
