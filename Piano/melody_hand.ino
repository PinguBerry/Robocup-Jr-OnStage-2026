#include <VarSpeedServo.h>
#include <AccelStepper.h>

#define STEP_PIN 3//22
#define DIR_PIN 2//24


float dif2 = 3.70;
float dif1 = 7.45;

VarSpeedServo s8; // cria o objeto servo
int angulo = 0; // declara origem do angulo como 0°
VarSpeedServo s9;
VarSpeedServo s10;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);


void d1p(){
  s8.write(110, 200, true);
  delay(50);
  s8.write(155, 250, true);
}

void d1b(){
  s8.write(0, 200, true);
  delay(50);
  s8.write(155, 250, true);
}

void d2p(){
  s9.write(110, 200, true);
  delay(50);
  s9.write(155, 250, true);
}

void d2b(){
  s9.write(45, 200, true);
  delay(50);
  s9.write(155, 250, true);
}

void d3p(){
  s10.write(110, 200, true);
  delay(50);

  s10.write(155, 250, true);
  //delay(100);
}

void d3b(){
  s10.write(45, 200, true);
  delay(50);

  s10.write(155, 250, true);
  //delay(500);
}

void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT_PULLUP);

  s8.attach(8); //declara pino digital utilizado
  s9.attach(9);
  s10.attach(10);

  s8.write(180, 50, true);
  s9.write(180, 50, true);
  s10.write(180, 50, true);

  stepper.setMaxSpeed(20000);//1000000

  //----------- HOMING --------------

  stepper.setSpeed(5000);

  while (digitalRead(6) == HIGH) {//low é apertado
    stepper.runSpeed();
  }

  stepper.setCurrentPosition(0);

  stepper.setAcceleration(10000);//2000000 

  s8.write(180, 70, true);
  s9.write(180, 70, true);
  s10.write(180, 70, true);

}

float passos(float dist){//com base no motor 3
  return -((6400 * dist)/31.90);
}

float distancia(const char* tecla){
  if(tecla == "E1") return 35.50;
  if(tecla == "FA#") return 33.40;
  if(tecla == "SOL#") return 31.20;
  if(tecla == "A1") return 30.10;
  if(tecla == "B1") return 27.90;
  if(tecla == "DO#") return 25.80;
  if(tecla == "D2") return 24.60;

  return -1;
}

void move(int dedo, const char* tecla){

  if(dedo == 1){
    stepper.runToNewPosition(passos(distancia(tecla) - dif1));
    if(tecla == "E1" or tecla == "A1" or tecla == "B1" or tecla == "D2"){
      d1b();
    }
    if(tecla == "FA#" or tecla == "SOL#" or tecla == "DO#"){
      d1p();
    }

  } else if(dedo == 2){
    stepper.runToNewPosition(passos(distancia(tecla) - dif2));
    if(tecla == "E1" or tecla == "A1" or tecla == "B1" or tecla == "D2"){
      d2b();
    }
    if(tecla == "FA#" or tecla == "SOL#" or tecla == "DO#"){
      d2p();
    }

  } else if(dedo == 3){
    stepper.runToNewPosition(passos(distancia(tecla)));
    
    if(tecla == "E1" or tecla == "A1" or tecla == "B1" or tecla == "D2"){
      d3b();
    }
    if(tecla == "FA#" or tecla == "SOL#" or tecla == "DO#"){
      d3p();
    }
  }

}

void loop() {
  //s10.write(125,70, true);
  //delay(100);
  //s10.write(180, 70, true);
  //delay(100);
  //s10.write(180, 200, true);

  move(3, "FA#");

  /*move(2, "E1");
  move(2, "FA#");
  move(2, "SOL#");
  move(2, "A1");
  move(2, "B1");
  move(2, "DO#");
  move(2, "D2");*/
  /*move(2, "E1");
  move(2, "E1");
  move(2, "FA#");
  move(2, "A1");
  move(2, "A1");
  move(2, "A1");
  move(2, "B1");
  move(2, "DO#");
  move(2, "A1");
  move(2, "A1");
  //making up a song about coralinee
  delay(500);

  move(2, "E1");
  move(2, "E1");
  move(2, "FA#");
  //shes a peach

  delay(500);

  move(2, "A1");
  move(2, "A1");
  move(2, "A1");

  //she's a doll

  delay(500);

  move(2, "B1");
  move(2, "B1");
  move(2, "DO#");

  //she's a pal

  move(2, "B1");
  move(2, "B1");
  
  //of mine

  delay(500);

  move(2, "D2");
  move(2, "D2");
  move(2, "D2");

  //she's as cute

  move(2, "B1");
  move(2, "B1");

  //as a

  move(2, "A1");
  move(2, "A1");

  //buttom

  move(2, "SOL#");
  move(2, "SOL#");

  //in the

  move(2, "A1");

  //eyes

  move(2, "DO#");

  //of

  move(2, "B1");
  move(2, "B1");

  //everyone

  move(2, "A1");
  move(2, "A1");

  //who

  move(2, "SOL#");
  move(2, "SOL#");

  //ever 


  move(2, "FA#");
  move(2, "FA#");

  //laid their

  move(2, "E1");

  //eyes

  move(2, "FA#");

  //on

  move(2, "A1");

  move(2, "SOL#");

  move(2, "A1");

  //coralinee


  delay(2000000);



  //move(3, "E1");
  //move(3, "E1");
  //move(3, "A1");

  //d1b();*/

}
