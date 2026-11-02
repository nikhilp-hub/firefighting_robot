// ---------------- PIN DEFINITIONS ----------------

// Relay (active LOW)
#define RELAY 23

// Flame sensors (fire = 1)
#define FLAME_LEFT 18
#define FLAME_RIGHT 19

// Line sensors (black = 1)
#define L1 25
#define L2 33
#define L3 32
#define L4 35

// Motor driver (L298N)
#define IN1 12
#define IN2 14
#define IN3 27
#define IN4 26
// ---------------- SETUP ----------------

void setup() {

  // Relay
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH); // blower OFF at start

  // Flame sensors
  pinMode(FLAME_LEFT, INPUT);
  pinMode(FLAME_RIGHT, INPUT);

  // Line sensors
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(L4, INPUT);

  // Motor driver
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// ---------------- LOOP ----------------

void loop() {

  int flameLeft = digitalRead(FLAME_LEFT);
  int flameRight = digitalRead(FLAME_RIGHT);

  // ---- FIRE DETECTED ----
  if (flameLeft == 1 || flameRight == 1) {

    stopMotors();

    // turn toward flame
    if (flameLeft == 1 && flameRight == 0) {
      turnLeft();
    }
    else if (flameRight == 1 && flameLeft == 0) {
      turnRight();
    }

    digitalWrite(RELAY, LOW); // blower ON
  }

  // ---- NORMAL LINE FOLLOW ----
  else {

    digitalWrite(RELAY, HIGH); // blower OFF
    lineFollow();
  }
}

// ---------------- MOTOR FUNCTIONS ----------------

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ---------------- LINE FOLLOW ----------------

void lineFollow() {

  int s1 = digitalRead(L1);
  int s2 = digitalRead(L2);
  int s3 = digitalRead(L3);
  int s4 = digitalRead(L4);

  // black = 1

  if (s2 == 1 && s3 == 1) {
    forward();
  }
  else if (s1 == 1) {
    turnLeft();
  }
  else if (s4 == 1) {
    turnRight();
  }
  else {
    stopMotors();
  }
}