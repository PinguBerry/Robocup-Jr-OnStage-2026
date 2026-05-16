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
  s10.write(40, 200, true);
  delay(100);

  s10.write(180, 200, true);
  delay(100);
}

void d3b(){
  s10.write(0, 200, true);
  delay(500);

  s10.write(180, 200, true);
  delay(500);
}

void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT_PULLUP);
  // put your setup code here, to run once:
  s8.attach(8); //declara pino digital utilizado
  s9.attach(9);
  s10.attach(10);

  s8.write(180, 50, true);
  s9.write(180, 50, true);
  s10.write(180, 50, true);

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
  return (3200 * dist)/8.00;
}

float distancia(const char* tecla){
  if(tecla == "E1") return 35.70;
  if(tecla == "FA#") return 33.60;
  if(tecla == "SOL#") return 31.40;
  if(tecla == "A1") return 30.30;
  if(tecla == "B1") return 28.10;
  if(tecla == "DO#") return 26.00;
  if(tecla == "D2") return 24.80;

  return -1;
}

void move(int dedo, const char* tecla){

  if(dedo == 1){
    stepper.runToNewPosition(passos(distancia(tecla) - dif1));

  } else if(dedo == 2){
    stepper.runToNewPosition(passos(distancia(tecla) - dif2));

  } else if(dedo == 3){
    stepper.runToNewPosition(passos(distancia(tecla)));
    delay(1000);
    
    if(tecla == "E1" or tecla == "A1" or tecla == "B1" or tecla == "D2"){
      d3b();
    }
    if(tecla == "FA#" or tecla == "SOL#" or tecla == "DO#"){
      d3p();
    }
  }

}

void loop() {

  move(3, "E1");
  move(3, "FA#");
  move(3, "SOL#");
  move(3, "A1");
  move(3, "B1");
  move(3, "DO#");
  move(3, "D2");

 /* move(3, "E1");
  //delay(500);
  move(3, "FA#");
  move(3, "A1");
  move(3, "A1");
  move(3, "A1");
  move(3, "B1");
  move(3, "DO#");
  move(3, "A1");
  move(3, "A1"); 

  delay(500); */

  //d1b();

}