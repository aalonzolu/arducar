#include <Servo.h>
//PINES DE LOS MOTORES
int IZQUIERDO_F = 6;
int IZQUIERDO_B = 7;
int DERECHO_F = 8;
int DERECHO_B = 9;

// SERVO CABEZA
Servo CABEZA;
int CABEZA_PIN = 10;
int CABEZA_POS = 60; 
int CABEZA_CENTRO = 60;
int CABEZA_DERECHA = 0;
int CABEZA_IZQUIERDA = 120;

//OJOS
long DISTANCIA;
long TIEMPO;
int OJOS_TRIG = 11;
int OJOS_ECHO = 12;


void setup() {
  //LOGS
  Serial.begin(9600);
  //CABEZA
  CABEZA.attach(CABEZA_PIN);
  CABEZA.write(CABEZA_POS);
  //OJOS
  pinMode(OJOS_TRIG, OUTPUT);
  pinMode(OJOS_ECHO, INPUT);
  //MOTOR IZQUIERDO
  pinMode(IZQUIERDO_F, OUTPUT);
  pinMode(IZQUIERDO_B, OUTPUT);
  //MOTOR DERECHO
  pinMode(DERECHO_F, OUTPUT);
  pinMode(DERECHO_B, OUTPUT);
}

void loop() 
{
  int dir = 0;
  long cm = distancia();
  if(cm <= 20)
  {
    parar();
    dir = ver();
    if(dir==1)
    {
      atras();
      delay(1000);
      derecha();
      delay(1000);
      adelante();
    }
    else if(dir==2)
    {
      atras();
      delay(1000);
      izquierda();
      delay(1000);
      adelante();
    }
  }
  else
  {
    adelante();
  }
  delay(100);
}
int distancia()
{
  digitalWrite(OJOS_TRIG,LOW);
  delayMicroseconds(5);
  digitalWrite(OJOS_TRIG, HIGH);
  delayMicroseconds(10);
  TIEMPO = pulseIn(OJOS_ECHO, HIGH);
  DISTANCIA = int(0.017*TIEMPO);
  Serial.println("Distancia ");
  Serial.println(DISTANCIA);
  Serial.println(" cm");
  return DISTANCIA;
}

int ver()
{
  long cm_derecha = 0;
  long cm_izquierda = 0;
  CABEZA.write(CABEZA_IZQUIERDA);
  delay(1000);
  cm_izquierda = distancia();
  delay(100);
  CABEZA.write(CABEZA_DERECHA);
  delay(1000);
  cm_derecha = distancia();
  delay(100);
  CABEZA.write(CABEZA_CENTRO);
  if(cm_izquierda <=35)
  {
    Serial.println("Ir a la izquierda");
    return 1;
  }
  else if(cm_derecha <=35)
  {
    Serial.println("Ir a la derecha");
    return 2;
  }
  else
  {
    Serial.println("Callejon sin salida");
    int res = random(1, 3);
    Serial.println("Res: ");
    Serial.println(res);
    return res;
  }
}
void parar()
{
  digitalWrite(DERECHO_B, LOW);
  digitalWrite(IZQUIERDO_B, LOW);
  digitalWrite(DERECHO_F, LOW);
  digitalWrite(IZQUIERDO_F, LOW);
}

void adelante()
{
  digitalWrite(DERECHO_B, LOW);
  digitalWrite(IZQUIERDO_B, LOW);
  digitalWrite(DERECHO_F, HIGH);
  digitalWrite(IZQUIERDO_F, HIGH);
}

void atras()
{
  digitalWrite(DERECHO_F, LOW);
  digitalWrite(IZQUIERDO_F, LOW);
  digitalWrite(DERECHO_B, HIGH);
  digitalWrite(IZQUIERDO_B, HIGH);
}

void izquierda()
{
  digitalWrite(DERECHO_B, LOW);
  digitalWrite(IZQUIERDO_B, HIGH);
  digitalWrite(DERECHO_F, HIGH);
  digitalWrite(IZQUIERDO_F, LOW);
}

void derecha()
{
  digitalWrite(DERECHO_B, HIGH);
  digitalWrite(IZQUIERDO_B, LOW);
  digitalWrite(DERECHO_F, LOW);
  digitalWrite(IZQUIERDO_F, HIGH);
}

