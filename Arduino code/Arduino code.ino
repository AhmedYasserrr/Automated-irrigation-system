#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int Y = 24.5;   // Y is the height of the ultrasounic sensor
int Z = 8;  //Z is the distance between the stick and the plant
int h = 0;  //h is the height of the plant
int x = 0;
const int trigPin = 11;
const int echoPin = 10;
long duration;
int distance;
int average = 0;
int old_dis = 0;
int averag;
int i;
int j;
float angl = 0;
float angle = 0;
float tangente = 0;
int F_pump1 = 4;
int F_pump2 = 3;
int water_pump1 = 6;
int water_pump2 = 5;
void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(13, OUTPUT);
  pinMode(F_pump1, OUTPUT);
  pinMode(F_pump2, OUTPUT);
  pinMode(water_pump1, OUTPUT);
  pinMode(water_pump2, OUTPUT);
}

void loop()
{
  for (pos = 0; pos < 224; pos += 3)
  {
    myservo.write(pos);
    angl = pos * 90;
    angl = angl / 112;
    if (pos <= 90) {
      angle = 90 - angl;
      j = 1;
    }
    else {
      angle = angl - 90;
      j = 2;
    }
    angle = angle * 3.14;
    angle = angle / 180;
    tangente = tan(angle);

    for (i = 1; i <= 100; i += 1)
    { // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance = duration * 0.034 / 2;
      //    if((distance-old_dis)> 40 || (distance-old_dis)<-40){distance = old_dis;}
      //  old_dis = distance;
      average = distance + average;
      averag = average / i - 1;
      delay(10);
    }

    Serial.print("Distance: ");
    if (averag > 60 || average < 0) {
      Serial.println("Out of Range ");
    }
    else {
      Serial.println(averag);
      average = 0;
      break;
    }
    average = 0;
    delay(50);
  }

  for (i = 1; i <= 100; i += 1)
  { // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    //    if((distance-old_dis)> 40 || (distance-old_dis)<-40){distance = old_dis;}
    //  old_dis = distance;
    average = distance + average;
    averag = average / i - 1;
    delay(10);
  }
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Final Distance: ");
  Serial.println(averag);
  if (j = 2) {
    h = Z * tangente;
    h = Y - h;
  }
  else {
    h = Z * tangente;
    h = Y + h;
  }
  Serial.print(" height: ");
  Serial.println(h);
  delay(50000);
  for (pos = pos; pos > 0; pos -= 1) {
    myservo.write(pos);
    delay(50);
  }

  int i = 0;
  while (i < 20) {
    Serial.println(h);
    delay(10);
    i = i + 1;
  }

  int j = 0;

  while (!Serial.available());
  x = Serial.readString().toInt();
  Serial.print(x);

  if (x != 0) {
    digitalWrite(13, HIGH);
    Serial.println(x);
    Serial.print("is recived");
    delay(1000);
    digitalWrite(13, LOW);
    Serial.println(x);
    Serial.println("is recived");
    delay(1000);
    digitalWrite(13, HIGH);
    Serial.println(x);
    Serial.print("is recived");
    delay(1000);
    x = x / 10;
    moisture(x);
  }
}
void moisture(int L) {
  digitalWrite(water_pump1, HIGH);
  digitalWrite(water_pump2, LOW);
  delay(5000);
  digitalWrite(water_pump1, LOW);
  digitalWrite(water_pump2, LOW);
}
