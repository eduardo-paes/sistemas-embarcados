const int SID_A = 3, 
          SID_B = 4,
          BTN_A = 8, 
          BTN_B = 9;

// Setup dos canais (relay e botão)
void setup() {
  pinMode(SID_A, OUTPUT);
  pinMode(SID_B, OUTPUT);
  pinMode(BTN_A, INPUT);
  pinMode(BTN_B, INPUT);
}

// Reseta os estados dos canais
void reset() {
  digitalWrite(SID_A, HIGH);
  digitalWrite(SID_B, HIGH);
}

// Inverte os estados dos canais
void invert(int port1, int port2) {
  digitalWrite(port1, HIGH);
  digitalWrite(port2, LOW);
}

// Prática com relay e motor: 
// O objetivo é fazer girar o motor para esquerda
// ou direita, através de um botão.
// Com os dois botões ativados ou desativados,
// o movimento do motor trava.
void loop() {
  digitalWrite(SID_A, !digitalRead(BTN_A));
  digitalWrite(SID_B, !digitalRead(BTN_B));
}
