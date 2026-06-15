//ARDUINO UNO

#include <VarSpeedServo.h>
#include <AccelStepper.h>

#define STEP_PIN 6
#define DIR_PIN 5

/*#define STEP_PIN 3
#define DIR_PIN 4*/

//mudar para a maozinha 2
float dif2 = 3.70;
float dif1 = 7.15;

int angulo = 0; // declara origem do angulo como 0°

int men;
int cont = 0;
bool chegou = false;

VarSpeedServo s11; // cria o objeto servo
VarSpeedServo s12;
VarSpeedServo s13;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

const char* cifra[] = {"FA#1", "D", "A", "FA#1", "FA#1", "D", "B", "D"};

void d1p(){
  s13.write(100, 200, true);
}

void d1b(){
  s13.write(40, 200, true);
}

void d2p(){
  s12.write(90, 250, true);
  delay(10);
  s12.write(155, 250, true);
}

void d2b(){
  s12.write(15, 250, true);
  delay(10);
  s12.write(155, 250, true);
}

void d3p(){
  s11.write(90, 250, true);
  delay(10);
  s11.write(155, 250, true);
}

void d3b(){
  s11.write(15, 250, true);
  delay(10);
  s11.write(155, 250, true);
}

void setup() {
  delay(5000);
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);

  s11.attach(11);
  s12.attach(12);
  s13.attach(13);

  s11.write(180, 50, true);
  s12.write(180, 50, true);
  s13.write(180, 50, true);

  stepper.setMaxSpeed(20000);

  //----------- HOMING --------------

  stepper.setSpeed(5000);

  while (digitalRead(7) == HIGH) {//low é apertado
    stepper.runSpeed();
  }

  stepper.setCurrentPosition(0);

  stepper.setAcceleration(20000);//4000

  s11.write(180, 70, true);
  s12.write(180, 70, true);
  s13.write(180, 70, true);

  move(3, cifra[cont]);
}

float passos(float dist){//com base no motor 3
  return -((3200 * dist)/16.00);
}

float distancia(const char* tecla){
  //MAOZINHA 1
  if(tecla == "E1") return 30.70;
  if(tecla == "E2") return 44.00;

  //MAOZINHA 2
  
  if(tecla == "FA#1") return 6.60;
  if(tecla == "A") return 9.80;
  //if(tecla == "S#") return 8.80; nao usa
  if(tecla == "B") return 12.00;
  if(tecla == "D") return 15.30;
  if(tecla == "E") return 17.50;

  return -1;
}

void move(int dedo, const char* tecla){

  if(dedo == 1){
    stepper.moveTo(passos(distancia(tecla) - dif1));

  } else if(dedo == 2){
    stepper.moveTo(passos(distancia(tecla) - dif2));

  } else if(dedo == 3){
    stepper.moveTo(passos(distancia(tecla)));
  }

}

void toca(int dedo, const char* tecla){

  if(dedo == 1){
    //opa
    d1p();//pode tirar isso depois

  } else if(dedo == 2){

    if(tecla == "A" or tecla == "B" or tecla == "D" or tecla == "E"){
      d2b();
    }
    if(tecla == "FA#1"){
      d2p();
    }

  } else if(dedo == 3){
    
    if(tecla == "A" or tecla == "B" or tecla == "D" or tecla == "E"){
      d3b();
    }
    if(tecla == "FA#1"){
      d3p();
    }
  }
}

bool envia = 0;

void loop() {
  //s10.write(125,70, true);a
  //delay(100);
  //s10.write(180, 70, true);
  //delay(100);
  //s10.write(180, 200, true);
  /*stepper.run();

  if(stepper.distanceToGo() == 0 && chegou == 0){//ele chegou
    Serial.println("2");
    chegou = true;
  }*/

  stepper.run();

  if(stepper.distanceToGo() == 0 && chegou == 0 && envia){//ele chegou
    Serial.println("2");
    chegou = true;
  }

  if(Serial.available() > 0){
    men = Serial.read();

    if(men == '1'){//é pra tocar
      toca(3, cifra[cont]);

      if(cont < 7) {
        cont++;
        move(3, cifra[cont]);//já fica na posição
        chegou = 0;
      } else {
        cont = 0;
        move(3, cifra[cont]);//já fica na posição
        chegou = 0;
      }

    }

    if(men == '3'){//é pra tocar
      envia = 1;
    }
  }

  /*if(Serial.available() > 0){
    men = Serial.read();

    if(men == '1'){//é pra tocar
      toca(3, cifra[cont]);

      if(cont < 1) {
        cont++;
        //move(3, cifra[cont]);//já fica na posição
      }

    }


  }*/
  
  /*

  stepper.run();

  if(stepper.distanceToGo() == 0 && chegou == 0 && envia){//ele chegou
    Serial.println("2");
    chegou = true;
  }

  if(Serial.available() > 0){
    men = Serial.read();

    if(men == '1'){//é pra tocar
      toca(3, cifra[cont]);

      if(cont < 7) {
        cont++;
        move(3, cifra[cont]);//já fica na posição
      }

    }

    if(men == '3'){//é pra tocar
      envia = 1;
    }
  }

  */

 /* FAZER FUNÇÃO
  move(1, "E2");
  d1b();
  move(1, "E1");
  d1p();

  */

  /*
  move(3, "A");
  move(3, "A");

  move(3, "D");
  move(3, "D");

  move(1, "E2");
  d1b();
  move(1, "E1");
  d1p();

  // making up
  move(3, "A");
  move(3, "A");

  move(3, "FA#1");
  move(3, "FA#1");

  // a song about
  move(3, "D");
  move(3, "D");

  //coraline
  move(3, "A");

  move(3, "FA#1");
  move(3, "FA#1");

  move(3, "D");
  move(3, "D");

  //she's a peach
  move(3, "A");
  move(3, "A");

  move(3, "FA#1");
  move(3, "FA#1");

  //she's a doll
  move(3, "D");
  move(3, "D");

  //she's a pal of mine

  move(3, "B");
  move(3, "B");

  move(3, "D");
  move(3, "D");

  move(3, "E");
  move(3, "E");



  delay(2000);*/


  //move(3, "A1");

  //d1b();*/

}