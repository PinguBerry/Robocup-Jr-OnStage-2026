 // ARDUINO MEGA 

#include <VarSpeedServo.h>
#include <AccelStepper.h>

#define STEP_PIN 22
#define DIR_PIN 24

// Calibration offsets between fingers to align with piano keys
float dif2 = 3.70;
float dif1 = 7.15;

// Servo objects representing robotic fingers
VarSpeedServo s8;
VarSpeedServo s9;
VarSpeedServo s10;

int angulo = 0;

// Structure representing a musical note (type + duration)
struct Notas{
  int tipo;
  int duracao;
};

// Sequence of note types and durations (melody definition)
Notas tipos[] = {{1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10},
{1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}, {1, 10}};

// Musical score (notes to be played in sequence)
const char* cifra[] = {"E1", "E1", "FA#", "A1", "A1", "A1", "B1", "DO#", "A1", "A1",
"E1", "E1", "FA#", "A1", "A1", "A1", "B1", "B1", "DO#", "B1", "B1"};

// Indicates whether a note is black key (1) or white key (0)
bool cifra2[] = {0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1};

// Servo “open position” (finger lifted above keys)
int ap = 155;

// Finger press positions (black and white keys)
int np = 110;
int nb = 40;

// Stepper motor controlling horizontal finger positioning
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// =========================
// FINGER ACTION FUNCTIONS
// =========================

// Finger 1 press on white key
void d1p(int tipo, int duracao){
  if(tipo == 1){
    s8.write(np, 200, true);
    delay(duracao);
    s8.write(ap, 250, true); // release
  }
}

// Finger 1 press on black key
void d1b(int tipo, int duracao){
  if(tipo == 1){
    s8.write(nb, 250, true);
    delay(duracao);
    s8.write(ap, 250, true);
  }
}

// Finger 2 press on white key
void d2p(int tipo, int duracao){
  if(tipo == 1){
    s9.write(np, 200, true);
    delay(duracao);
    s9.write(ap, 250, true);
  }
}

// Finger 2 press on black key
void d2b(int tipo, int duracao){
  if(tipo == 1){
    s9.write(nb, 250, true);
    delay(duracao);
    s9.write(ap, 250, true);
  }
}

// Finger 3 press on white key
void d3p(int tipo, int duracao){
  if(tipo == 1){
    s10.write(np, 200, true);
    delay(duracao);
    s10.write(ap, 250, true);
  }
}

// Finger 3 press on black key
void d3b(int tipo, int duracao){
  if(tipo == 1){
    s10.write(nb, 250, true);
    delay(duracao);
    s10.write(ap, 250, true);
  }
}


// =========================
// SETUP (INITIALIZATION + HOMING)
// =========================

void setup() {

  delay(5000);

  Serial1.begin(9600);

  // Limit switch used for homing calibration
  pinMode(26, INPUT_PULLUP);

  // Attach servo motors to pins
  s8.attach(8);
  s9.attach(9);
  s10.attach(10);

  // Move all fingers to safe starting position
  s8.write(180, 50, true);
  s9.write(180, 50, true);
  s10.write(180, 50, true);

  // Configure stepper motor speed
  stepper.setMaxSpeed(20000);

  // =========================
  // HOMING PROCEDURE
  // =========================

  stepper.setSpeed(5000);

  // Move until limit switch is triggered
  while (digitalRead(26) == HIGH) {
    stepper.runSpeed();
  }

  // Reset stepper reference position
  stepper.setCurrentPosition(0);

  stepper.setAcceleration(20000);

  // Reposition fingers after homing
  s8.write(180, 70, true);
  s9.write(180, 70, true);
  s10.write(180, 70, true);
}


// =========================
// POSITION MAPPING FUNCTIONS
// =========================

// Convert physical distance into stepper motor steps
float passos(float dist){
  return -((6400 * dist)/32.00);
}

// Map musical note to physical position on keyboard
float distancia(const char* tecla){
  if(tecla == "E1") return 35.70;
  if(tecla == "FA#") return 33.60;
  if(tecla == "SOL#") return 31.50;
  if(tecla == "A1") return 30.40;
  if(tecla == "B1") return 28.10;
  if(tecla == "DO#") return 26.00;
  if(tecla == "D2") return 24.90;

  return -1;
}


// Move selected finger to target key position
void move(int dedo, const char* tecla){

  if(dedo == 1){
    stepper.runToNewPosition(passos(distancia(tecla) - dif1));

  } else if(dedo == 2){
    stepper.runToNewPosition(passos(distancia(tecla) - dif2));

  } else if(dedo == 3){
    stepper.runToNewPosition(passos(distancia(tecla)));
  }
}


// Execute pressing motion depending on key type (black/white)
void toca(int dedo, const char* tecla, int tipo, int duracao){

  if(dedo == 1){

    if(tecla == "E1" or tecla == "A1" or tecla == "B1" or tecla == "D2"){
      d1b(tipo, duracao);
    }

    if(tecla == "FA#" or tecla == "SOL#" or tecla == "DO#"){
      d1p(tipo, duracao);
    }

  } else if(dedo == 2){

    if(tecla == "E1" or tecla == "A1" or tecla == "B1" or tecla == "D2"){
      d2b(tipo, duracao);
    }

    if(tecla == "FA#" or tecla == "SOL#" or tecla == "DO#"){
      d2p(tipo, duracao);
    }

  } else if(dedo == 3){

    if(tecla == "E1" or tecla == "A1" or tecla == "B1" or tecla == "D2"){
      d3b(tipo, duracao);
    }

    if(tecla == "FA#" or tecla == "SOL#" or tecla == "DO#"){
      d3p(tipo, duracao);
    }
  }
}


// =========================
// STATE VARIABLES
// =========================

float pos[] = {7.45, 3.70, 0}; // current finger positions
float dif[] = {7.45, 3.70, 0};


// =========================
// MAIN LOOP (MUSIC PLAYBACK + OPTIMIZATION)
// =========================

void loop() {

  // Iterate through full musical sequence
  for(int i = 0; i < 21; i++){

    float melhorcusto = 9999999;
    int melhordedo = 0;

    // Evaluate best finger for current note
    for(int dedo = 0; dedo < 3; dedo++){

      float pos0[3]; for(int j = 0; j < 3; j++) pos0[j] = pos[j];

      float cus0 = abs(pos0[dedo] - distancia(cifra[i]));

      pos0[dedo] = distancia(cifra[i]);

      for(int j = 0; j < 3; j++){
        if(j != dedo){
          pos0[j] = distancia(cifra[i]) + dif[j] - dif[dedo];
        }
      }

      int id1 = i + 1;

      if(id1 >= 21){
        if(melhorcusto > cus0){
          melhorcusto = cus0;
          melhordedo = dedo;
        }
        continue;
      }

      // Lookahead optimization (future note cost prediction)
      for(int d1 = 0; d1 < 3; d1++){

        float pos1[3]; for(int j = 0; j < 3; j++) pos1[j] = pos0[j];

        float cus1 = abs(pos1[d1] - distancia(cifra[id1])) + cus0;

        pos1[d1] = distancia(cifra[id1]);

        for(int j = 0; j < 3; j++){
          if(j != d1){
            pos1[j] = distancia(cifra[id1]) + dif[j] - dif[d1];
          }
        }

        int id2 = id1 + 1;

        if(id2 >= 21){
          if(melhorcusto > cus1){
            melhorcusto = cus1;
            melhordedo = dedo;
          }
          continue;
        }

        for(int d2 = 0; d2 < 3; d2++){

          float cus2 = abs(pos1[d2] - distancia(cifra[id2])) + cus1;

          if(melhorcusto >= cus2){
            melhorcusto = cus2;
            melhordedo = dedo;
          }
        }
      }
    }

    // Assign best finger for current note
    pos[melhordedo] = distancia(cifra[i]);

    for(int j = 0; j < 3; j++){
      if(j != melhordedo){
        pos[j] = distancia(cifra[i]) + dif[j] - dif[melhordedo];
      }
    }

    melhordedo = melhordedo + 1;

    // Execute movement + press
    move(melhordedo, cifra[i]);

    if(cifra2[i] == 1){
      Serial1.println("3");
      Serial1.println("1");
    }

    toca(melhordedo, cifra[i], tipos[i].tipo, tipos[i].duracao);

    delay(2000);
  }
}
