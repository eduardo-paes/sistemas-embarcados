const int GREEN = 6;
const int RED = 5;
const int BUTTON1 = 4;

void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
}

void invert(bool status) {
  digitalWrite(RED, status ? HIGH : LOW);
  digitalWrite(GREEN, status ? LOW : HIGH);
}

void piscaPisca() {
  bool status = false;
  while (1) {
    invert(status);
    delay(2000);
    status = !status;
  }
}

void loop() {
  if (digitalRead(BUTTON1) == LOW) {
    invert(true);
    delay(5000);
    invert(false);
  } else {
    invert(true);
  }
}
