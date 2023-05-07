const int GREEN = 6;
const int RED = 5;
const int BUTTON1 = 4;
const int BUTTON2 = 3;

void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
}

void loop() {
  digitalWrite(RED, digitalRead(BUTTON1) == HIGH ? HIGH : LOW);
  digitalWrite(GREEN, digitalRead(BUTTON2) == HIGH ? HIGH : LOW);
}
