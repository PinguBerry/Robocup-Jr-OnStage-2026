#include <VarSpeedServo.h>
#include <AccelStepper.h>

#define STEP_PIN 3
#define DIR_PIN 4

float dif2 = 3.70;
float dif1 = 7.45;

VarSpeedServo s8; // cria o objeto servo
int angulo = 0; // declara origem do angulo como 0°
VarSpeedServo s9;
VarSpeedServo s10;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void d1p(){
  s8.write(40, 250, true);
  s8.write(180, 250, true);
}

void d1b(){
  s8.write(0, 150, true);
  s8.write(180, 150, true);
}

void d2p(){
  s9.write(40, 70, true);
  s9.write(180, 70, true);
}
void d2b(){
  s9.write(0, 200, true);
  s9.write(180, 200, true);
}

void d3p(){
  s10.write(40, 250, true);
  s10.write(180, 250, true);
}

void d3b(){
  s10.write(10, 70, true);
  s10.write(180, 70, true);
}

void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT_PULLUP);
  // put your setup code here, to run once:
  s8.attach(8); //declara pino digital utilizado
  s9.attach(9);
  s10.attach(10);

  stepper.setMaxSpeed(5000);

  //----------- HOMING --------------

  stepper.setSpeed(-4000);

  while (digitalRead(6) == HIGH) {//low é apertado
    stepper.runSpeed();
  }

  stepper.setCurrentPosition(0);

  stepper.setAcceleration(1200);//4000  // 

  s8.write(180, 70, true);
  s9.write(180, 70, true);
  s10.write(180, 70, true);

}

float passos(float dist){//com base no motor 3
  return (6400 * dist)/16.15;
}

float distancia(const char* tecla){
  if(tecla == "E1") return 25.44;
  if(tecla == "FA#") return 23.40;
  if(tecla == "SOL#") return 21.00;
  if(tecla == "A1") return 20.00;
  if(tecla == "B1") return 17.70;
  if(tecla == "DO#") return 15.60;
  if(tecla == "D2") return 14.40;
}

void move(int dedo, const char* tecla){

  if(dedo == 1){
    stepper.runToNewPosition(passos(distancia(tecla) - dif1));
  } else if(dedo == 2){
    stepper.runToNewPosition(passos(distancia(tecla) - dif2));
  } else if(dedo == 3){
    stepper.runToNewPosition(passos(distancia(tecla)));
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  //stepper.runToNewPosition(3962.84); //do meio anda 13,63cm      +- 0,2 de erro

  // BASE NO MOTOR 3
  //e1 - 25.44 
  //fa# - 23.40 
  //sol# - 21.00 
  //a1 - 20.00 
  //b1 - 17.70  
  //do#2 - 15.60 
  //d2 - 14.40 

  move(1, "E1");

  //d1b(); 

}