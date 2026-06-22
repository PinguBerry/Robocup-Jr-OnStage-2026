#include <VarSpeedServo.h>
#include <AccelStepper.h>

#define STEP_PIN 22
#define DIR_PIN 24

float dif2 = 3.70;
float dif1 = 7.45;

VarSpeedServo s8; // cria o objeto servo
int angulo = 0; // declara origem do angulo como 0°
VarSpeedServo s9;
VarSpeedServo s10;

const char* cifra[] = {"E1", "E1", "FA#", "A1", "A1", "A1", "B1", "DO#", "A1", "A1", "E1", "E1", "FA#", "A1", "A1", "A1", "B1", "B1", "DO#", "B1", "B1", "D2", "D2", "D2", "B1", "B1", "A1", "A1", "SOL#", "SOL#", "A1", "DO#", "B1", "B1", "A1", "A1", "SOL#", "SOL#", "FA#", "FA#", "E1", "FA#", "A1", "SOL#", "A1"};

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
  Serial.println("iniciou!");

  pinMode(26, INPUT_PULLUP);

  s8.attach(8); //declara pino digital utilizado
  s9.attach(9);
  s10.attach(10);

  s8.write(180, 50, true);
  s9.write(180, 50, true);
  s10.write(180, 50, true);

  stepper.setMaxSpeed(30000);

  //----------- HOMING --------------

  stepper.setSpeed(-6000);

  /*while (digitalRead(26) == HIGH) {//low é apertado
    stepper.runSpeed();
  }*/

  stepper.setCurrentPosition(0);

  stepper.setAcceleration(15000);//4000

  //s8.write(180, 70, true);
  //s9.write(180, 70, true);
  //s10.write(180, 70, true);

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

float pos[] = {7.45, 3.70, 0};//motor 1 - 2 - 3 
float dif[] = {7.45, 3.70, 0};

void loop() {
  //s10.write(125,70, true);

  /*for(int i = 0; i < 45; i++){ // CIFRA

    

    float melhorcusto = 9999999;
    int melhordedo = 0;

    for(int dedo = 0; dedo < 3; dedo++){ //para cada dedo

      //vetor para as posições simuladas
      float pos0[3]; for(int j = 0; j < 3; j++) pos0[j] = pos[j];


      //custo para um dedo
      float cus0 = abs(pos0[dedo] - distancia(cifra[i]));

      pos0[dedo] = distancia(cifra[i]);
      
      for(int j = 0; j < 3; j++){
        if(j != dedo){
          pos0[j] = distancia(cifra[i]) + dif[j] - dif[dedo];
        }
      }

      int id1 = i + 1;//primeira proxima nota
      if(id1 > 44){
        
        if(melhorcusto > cus0){
          melhorcusto = cus0;
          melhordedo = dedo;
        }

        continue;
      }

      for(int d1 = 0; d1 < 3; d1++){//PRIMEIRA PREVISÃO

        float pos1[3]; for(int j = 0; j < 3; j++) pos1[j] = pos0[j];


        float cus1 =  abs(pos1[d1] - distancia(cifra[id1])) + cus0;

        pos1[d1] = distancia(cifra[id1]);
      
        for(int j = 0; j < 3; j++){
          if(j != d1){
            pos1[j] = distancia(cifra[id1]) + dif[j] - dif[d1];
          }
        }

        int id2 = id1 + 1;//segunda proxima nota
        if(id2 > 44) {

          if(melhorcusto > cus1){
            melhorcusto = cus1;
            melhordedo = dedo;
          }

          continue;
        }

        for(int d2 = 0; d2 < 3; d2++){//SEGUNDA PREVISÃO

          float cus2 =  abs(pos1[d2] - distancia(cifra[id2])) + cus1;

          if(melhorcusto >= cus2){
            melhorcusto = cus2;
            melhordedo = dedo;
          }

        }
      }

    }

   Serial.println(cifra[i]);
   Serial.println(melhordedo);

    pos[melhordedo] = distancia(cifra[i]);
 
    //atualiza a posição dos dedos
    for(int j = 0; j < 3; j++){

      if(j != melhordedo){
        pos[j] = distancia(cifra[i]) + dif[j] - dif[melhordedo];
      }

      //Serial.println("dedo"); Serial.println(j);
      //Serial.println(pos[j]);
    }

  }


  delay(20000000);


  //move(3, "E1");
  //move(3, "E1");
  //move(3, "A1");

  //d1b();*/
  s10.write(180, 100, true);
  s10.write(75, 100, true);//preta
  s10.write(180, 100, true);

  s9.write(180, 100, true);
  s9.write(20, 100, true);//branca
  s9.write(180, 100, true);


}
