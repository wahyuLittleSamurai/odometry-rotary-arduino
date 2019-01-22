#include <math.h> //add library untuk sin cos dan matematika

#define en1 6     //pwm pin motor kiri
#define in1 7     //in 1 pin motor kiri
#define in2 8     //in 2 pin m motor kiri
#define en2 11    //pwm pin motor kanan
#define in3 9
#define in4 10

const byte interruptPin3 = 3; //pin interrupt kiri
const byte interruptPin2 = 2; //pin interrupt kanan
int rotaryRight, rotaryLeft;

double resolusiEncLeft = 75;
double resolusiEncRight = 75;
double D_left, D_right, v, w;
double rRoda = 3.25;
double wheelBase = 20.0;


void setup() 
{
  Serial.begin(9600); //baud rate serial

  pinMode(A3, INPUT); //input untuk data 2 rotary encoder
  pinMode(2, INPUT);  //input untuk interrupt 1 rotary encoder

  pinMode(A2, INPUT);
  pinMode(3, INPUT);
  
  for(int i=7; i<=10; i++)
  {
    pinMode(i, OUTPUT);   // pin motor output
  }
  attachInterrupt(digitalPinToInterrupt(interruptPin3), countRight, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), countLeft, CHANGE);   //panggil func countLeft dengan status change pada interrupt
  
}

void loop() 
{
  D_left = 2 * 3.14 * rRoda * (rotaryLeft / resolusiEncLeft);
  D_right = 2 * 3.14 * rRoda * (rotaryRight / resolusiEncRight);

  v = (D_right + D_left) / 2.0; //(ie. in meters per second)
  w = (D_right - D_left) / wheelBase; //(ie. in radians per second)

  Serial.print(rotaryLeft); Serial.print("\t"); Serial.print(rotaryRight); Serial.print("\t");
  Serial.print(D_left); Serial.print("\t"); Serial.print(D_right); Serial.print("\t");
  Serial.print(v); Serial.print("\t"); Serial.println(w);
  
}
void countLeft() 
{
  if (digitalRead(2) == HIGH) 
  {
    if (digitalRead(A3) == LOW) 
    {
      rotaryLeft++;         // CW
    }
    else 
    {
      rotaryLeft--;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(A3) == HIGH) 
    {
      rotaryLeft++;          // CW
    }
    else 
    {
      rotaryLeft--;          // CCW
    }
  }

}

void countRight() 
{
  if (digitalRead(3) == HIGH) 
  {
    if (digitalRead(A2) == LOW) 
    {
      rotaryRight++;         // CW
    }
    else 
    {
      rotaryRight--;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(A2) == HIGH) 
    {
      rotaryRight++;          // CW
    }
    else 
    {
      rotaryRight--;          // CCW
    }
  }
}

void forward(int pwm1, int pwm2)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(en1, pwm1);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en2, pwm2);
}
void backward(int pwm1, int pwm2)
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(en1, pwm1);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(en2, pwm2);
}

