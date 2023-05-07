const int GREEN = 6;
const int RED = 5;
const int BUTTON = 4;
bool btnState = 0;b
bool lastRead = 0;

void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  bool read = !digitalRead(BUTTON);
  if (read && !lastRead) {
    btnState = !btnState;
    delay(100);
  }
  lastRead = read;

  if (!btnState) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
  } else {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
  }
}
