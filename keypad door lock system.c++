#include <Keypad.h>
#include <Servo.h>

Servo myServo;

// -------- KEYPAD --------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// -------- PINS --------
int servoPin = 10;
int buzzer = 11;

void setup() {

  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);

  myServo.attach(servoPin);

  // Locked position
  myServo.write(0);

  Serial.println("Press A to Unlock");
}

void loop() {

  char key = keypad.getKey();

  if (key) {

    Serial.print("Key Pressed: ");
    Serial.println(key);

    // -------- CORRECT BUTTON --------
    if (key == 'A') {

      unlockDoor();

    }

    // -------- WRONG BUTTON --------
    else {

      wrongAlarm();

    }
  }
}

// ================= FUNCTIONS =================

// Unlock Door
void unlockDoor() {

  Serial.println("Correct Button!");

  // Small beep
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);

  // Open servo
  myServo.write(90);

  delay(3000);

  // Close servo
  myServo.write(0);

  Serial.println("Door Locked Again");
}

// Wrong Alarm
void wrongAlarm() {

  Serial.println("Wrong Button!");

  for (int i = 0; i < 3; i++) {

    digitalWrite(buzzer, HIGH);
    delay(200);

    digitalWrite(buzzer, LOW);
    delay(200);
  }
}