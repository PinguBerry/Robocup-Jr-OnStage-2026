#include <VarSpeedServo.h>
#include <AccelStepper.h>

#define STEP_PIN 22
#define DIR_PIN 24

/*#define STEP_PIN 3
#define DIR_PIN 4*/

//mudar para a maozinha 2
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
  s8.write(45, 200, true);
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
  pinMode(28, INPUT_PULLUP);

  stepper.setMaxSpeed(30000);

  //----------- HOMING --------------

  stepper.setSpeed(-6000);

  while (digitalRead(28) == HIGH) {//low é apertado
    stepper.runSpeed();
  }

  stepper.setCurrentPosition(0);

  stepper.setAcceleration(15000);//4000

}

float passos(float dist){//com base no motor 3
  return (3200 * dist)/8.00;
}

float distancia(const char* tecla){
  //MAOZINHA 1
  if(tecla == "E1") return 35.70;
  if(tecla == "FA#") return 33.60;
  if(tecla == "SOL#") return 31.40;
  if(tecla == "A1") return 30.30;
  if(tecla == "B1") return 28.10;
  if(tecla == "DO#") return 26.00;
  if(tecla == "D2") return 24.80;

  //MAOZINHA 2
  if(tecla == "A") return 9.80;
  //if(tecla == "S#") return 8.80; nao usa
  if(tecla == "FA#1") return 6.60;
  if(tecla == "B") return 12.00;
  if(tecla == "D") return 15.30;
  if(tecla == "E") return 17.50;

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
  
 // stepper.runToNewPosition(passos(17.50));

  //move(3, "E1");
  //move(3, "E1");
  //move(3, "A1");

  //d1b();*/

}