
#include <VarSpeedServo.h>

VarSpeedServo pdc;
VarSpeedServo pdb;
VarSpeedServo pec;
VarSpeedServo peb;

unsigned long int tempo = 0;

int randomolho;


void setup() {
  pdc.attach(8);
  pdb.attach(9);
  pec.attach(10);
  peb.attach(11);

  pdc.slowmove(110, 80);
  pdb.slowmove(70, 80);

  
  randomSeed(analogRead(A1));
  randomolho = random(1500,3000);
  Serial.begin(9600);
}

void loop() {
  pisca();
}

void pisca(){
  
  if(millis() - tempo >= randomolho){//olho fechado
    pdc.slowmove(0, 80);
    pdb.slowmove(180, 80);
    
  } 
  
  if(millis() - tempo >= (randomolho + 700)) {//olho aberto
    
    pdc.slowmove(110, 80);
    pdb.slowmove(70, 80);
    tempo = millis();

    
    randomSeed(analogRead(A0));
    randomolho = random(1500,3000);
    
  }

  //Serial.println(randomolho);

}
