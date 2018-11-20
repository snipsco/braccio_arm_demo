#include <Wire.h>
#include <Stepper.h>

#include <Braccio.h>
#include <Servo.h>

#define STEPS 64
#define REVOLUTION 2048
#define SLAVE_ADDRESS 0x04

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

//naming Arduino pin

int count = 0;
int number = 0;

int M1 = 90;
int M2 = 90;
int M3 = 90;
int M4 = 90;
int M5 = 90;
int M6 = 73;

void move_to() {
  Braccio.ServoMovement(20, M1, M2, M3, M4, M5, M6);
}

void setup() {
  // start serial for output
  Serial.begin(9600);
  Serial.println("Ready!");
  pinMode(LED_BUILTIN, OUTPUT);

  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Braccio.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(analogRead(0));
  M1 = random(1, 179);

  // the arm is aligned upwards  and the gripper is closed
  //(step delay, M1, M2, M3, M4, M5, M6);
  move_to();
}

void move_base_right(int number) {
  M1 += number;
  move_to();
}

void move_base_left(int number) {
  M1 -= number;
  move_to();
}

void move_shoulder_up(int number) {
  M2 += number;
  move_to();
}

void move_shoulder_down(int number) {
  M2 -= number;
  move_to();
}

void move_elbow_up(int number) {
  M3 += number;
  move_to();
}

void move_elbow_down(int number) {
  M3 -= number;
  move_to();
}

void move_wrist_up(int number) {
  M4 += number;
  move_to();
}

void move_wrist_down(int number) {
  M4 -= number;
  move_to();
}

void rotation_wrist_right(int number) {
  M5 += number;
  move_to();
}

void rotation_wrist_left(int number) {
  M5 -= number;
  move_to();
}

void open_gripper() {
  M6 = 10;
  move_to();
}

void close_gripper() {
  M6 = 50;
  move_to();
}

void return_position() {
  M1 = random(1, 179), M2 = 90, M3 = 90, M4 = 90, M5 = 90, M6 = 73;
  move_to();
}

void taking_ball() {
  //The braccio moves to the ball. Only the M2 servo will moves
  //  M1 = 0, 
  M2 = 90, 
  M3 = 180, 
  M4 = 180, 
  M5 = 90, 
  M6 = 10;
  //Braccio.ServoMovement(20,           0,  90, 180, 180,  90,   10);
  move_to();
  //Close the gripper to take the ball. Only the M6 servo will moves
  //Braccio.ServoMovement(10,           0,  90, 180, 180,  90,  60 );
//  M1 = 0, 
  M2 = 90, M3 = 180, M4 = 180, M5 = 90, M6 = 60;
  move_to();
  delay(1500);
  return_position();
}

void dance() {

  for (int i = 0; i < 3; i++) {
    //                          //(step delay, M1, M2, M3, M4, M5, M6);
    //  Braccio.ServoMovement(15,           0,  15, 180, 170, 0,  73);
    M1 = 0, M2 = 15, M3 = 180, M4 = 170, M5 = 0, M6 = 73;
    move_to();
    //Wait 1 second
    delay(1000);

    //  Braccio.ServoMovement(15,           180,  165, 0, 0, 180,  10);
    M1 = 180, M2 = 165, M3 = 0, M4 = 0, M5 = 180, M6 = 10;
    move_to();
    //Wait 1 second
    delay(1000);
  }
}

void release_ball() {
  //Return to the start position.
  //Braccio.ServoMovement(20,         0,   90, 180,  180,  90, 60);
//  M1 = 0, 
  M2 = 90, M3 = 180, M4 = 180, M5 = 90, M6 = 60;
  move_to();
  //Open the gripper
  //Braccio.ServoMovement(20,         0,   90, 180,  180,  90, 10 );
//  M1 = 0, 
  M2 = 90, M3 = 180, M4 = 180, M5 = 90, M6 = 10;
  move_to();
  delay(1500);
  return_position();
}





/*
   Run undefinitly
*/
void loop() {
  //   si je reçois un truc du serial alors je lis ce qui se passe
  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();
    //    B reset le buffer
    if (incomingByte == 'B') {
      // command have to start with 'B'
      number = 0;
      count = 0;
    } else if (incomingByte == 'L') {
      // command have to end with 'L'
      move_base_left(number);
      number = 0;
      count = 0;
    } else if (incomingByte == 'R') {
      // command have to end with 'R'
      move_base_right(number);
      number = 0;
      count = 0;
      //    } else if (incomingByte == 'U') {
      //      // command have to end with 'U'
      //      move_shoulder_up(number);
      //      number = 0;
      //      count = 0;
      //    } else if (incomingByte == 'D') {
      //      // command have to end with 'D'
      //      move_shoulder_down(number);
      //      number = 0;
      //      count = 0;
      //    } else if (incomingByte == 'T') {
      //      // "T" refer to elbow_up
      //      move_elbow_up(number);
      //      number = 0;
      //      count = 0;
      //    } else if (incomingByte == 'Y') {
      //      // "Y" refer to elbow_down
      //      move_elbow_down(number);
      //      number = 0;
      //      count = 0;
      //    } else if (incomingByte == 'I') {
      //      // "I" refer to wrist_up
      //      move_wrist_up(number);
      //      number = 0;
      //      count = 0;
      //    } else if (incomingByte == 'P') {
      //      // "P" refer to wrist_down
      //      move_wrist_down(number);
      //      number = 0;
      //      count = 0;
      //    } else if (incomingByte == 'Q') {
      //      // "Q" refer to wrist_right
      //      rotation_wrist_right(number);
      //      number = 0;
      //      count = 0;
      //    } else if (incomingByte == 'S') {
      //      // "S" refer to wrist_left
      //      rotation_wrist_left(number);
      //      number = 0;
      //      count = 0;
    } else if (incomingByte == 'O') {
      // "O" refer to open_gripper
      open_gripper();
      count = 0;
    } else if (incomingByte == 'C') {
      // "C" refer to close_gripper
      close_gripper();
      count = 0;
    }    else if (incomingByte == 'F') {
      // "f" refer to return_position
      number = 0;
      return_position();
      count = 0;
    }    else if (incomingByte == 'M') {
      // "M" refer to taking_ball
      taking_ball();
      count = 0;
    }    else if (incomingByte == 'X') {
      // "X" refer to dance
      dance();
      count = 0;
    }    else if (incomingByte == 'W') {
      // "W" refer to release_ball
      release_ball();
      count = 0;
    }


    //    on recoit bien des caracthère, voir coffeehack à la fin
    //
    else if (incomingByte >= '0' && incomingByte <= '9') {
      // save as an int all the character coming from Serial
      int tmp = incomingByte - '0';
      number *= 10;
      number += tmp;
      count++;
    }
  }
}

/*
   Utils
*/

/*
   turn the stepper motor to the left
*/




/*
   compute int into order
*/

////chiffre qui ne peut être quer positif
//void start_coffee(unsigned int type) {
////  int number = type % 10;
////  int coffee_type = type / 10 % 10;
////  int coffee_size = type / 100 % 10;
////  int intensity = type / 1000 % 10;
////  int special = type / 10000 % 10;
//  int special = type
//  int number = type
//  Serial.print(type);
//  if (special != 0) {
//    switch (special) {
//      case 1:
//        onoff();
//        return;
//      case 2:
//        touch_clean();
//        return;
//      case 3:
//        touch_vape();
//        return;
//    }
//  } else if (coffee_type == 9) {
//    select_intensity(intensity);
//    if (number == 1)
//      if (coffee_size == 1)
//        touch_x1();
//      else
//        touch_x1_long();
//    else if (coffee_size == 1)
//      touch_x2();
//    else
//      touch_x2_long();
//    delay(20000);
//    default_intensity(intensity);
//  }
//}

