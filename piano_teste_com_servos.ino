#include <AccelStepper.h>
#include <VarSpeedServo.h>

#define STEP_PIN 3
#define DIR_PIN 4

VarSpeedServo s8; // cria o objeto servo
int angulo = 0; // declara origem do angulo como 0°
VarSpeedServo s9;
VarSpeedServo s10;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
    //s8.attach(8); //declara pino digital utilizado
    //s9.attach(9);
    //s10.attach(10);
  stepper.setMaxSpeed(4000);//4000      // a
  stepper.setAcceleration(1200);//4000  // 

  stepper.setCurrentPosition(0);
 // stepper.moveTo(-8750);        // distância pequena
}

void loop() {
  /*if (stepper.distanceToGo() == 0) {
    stepper.moveTo(-stepper.currentPosition()); // vai e volta rápido
    s8.write(180, 70, true);
    s8.write(70, 70, true);
    s9.write(180, 70, true);
    s9.write(70, 70, true);
    s10.write(180, 70, true);
    s10.write(70, 70, true);
  }*/

  stepper.runToNewPosition(-14200); //e1
  delay(1000);
  stepper.runToNewPosition(-13300); //
  delay(1000);
  stepper.runToNewPosition(-12400);
  delay(1000);
  stepper.runToNewPosition(-12000);
  delay(1000);
  stepper.runToNewPosition(-11100);
  delay(1000);
  stepper.runToNewPosition(-10250);
  delay(1000);
  stepper.runToNewPosition(-9800);
  delay(1000);

  //stepper.run();

}