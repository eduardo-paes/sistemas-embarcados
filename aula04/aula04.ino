// C++ code
//
const int BUTTON = 8;
const int GREEN_MOT = 7;
const int YELLOW_MOT = 6;
const int RED_MOT = 5;
const int GREEN_PED = 4;
const int YELLOW_PED = 3;
const int RED_PED = 2;

bool btnState = 0;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(GREEN_MOT, OUTPUT);
  pinMode(YELLOW_MOT, OUTPUT);
  pinMode(RED_MOT, OUTPUT);
  pinMode(GREEN_PED, OUTPUT);
  pinMode(YELLOW_PED, OUTPUT);
  pinMode(RED_PED, OUTPUT);

  // Inicia com o semáforo verde para motorista e vermelho para pedestre
  turnOnLight(RED_PED, GREEN_PED, YELLOW_PED);
  turnOnLight(GREEN_MOT, YELLOW_MOT, RED_MOT);
}

// Acende o led (onLight) e desliga os leds (offLight1 e offLight2)
void turnOnLight(int onLight, int offLight1, int offLight2) {
  digitalWrite(onLight, HIGH);
  digitalWrite(offLight1, LOW);
  digitalWrite(offLight2, LOW);
}

// Verifica o estado do botão por tempo determinado
void readBtnLoop(int wait_time) {
  // Pega o tempo atual
  int current_time = millis();

  // Define tempo final somando os milisegundos de espera (wait_time)
  // com o tempo atual em milisegundos (current_time)
  int final_time = current_time + wait_time;
  
  // Enquanto o tempo atual for menor que o tempo final esperado,
  // segue lendo o status do botão e guardando para referência futura.

  while(current_time < final_time) {
    // Recupera valor do botão enquanto o estado atual guardado 
    // do botão for igual a 0
    if (btnState == 0)
      btnState = digitalRead(BUTTON) != HIGH ? 1 : 0;

    // Pega o tempo atual em milisegundos
    current_time = millis();
  }
}

void loop() {  
  // Inicia o processo de mudança dos leds caso o botão esteja apertado 
  // ou tenha sido pressionado num período determinado
  if (digitalRead(BUTTON) != HIGH || btnState) {
    // Reseta estado do botão
    btnState = 0;

    // Acende o led vermelho para pedestre e amarelo para motorista
    turnOnLight(RED_PED, GREEN_PED, YELLOW_PED);
    turnOnLight(YELLOW_MOT, GREEN_MOT, RED_MOT);

    // Aguarda 5s
    delay(5000);
    
    // Acende o led verde para pedestre e vermelho para motorista
    turnOnLight(GREEN_PED, YELLOW_PED, RED_PED);
    turnOnLight(RED_MOT, GREEN_MOT, YELLOW_MOT);

    // Aguarda 10s
    delay(10000);

    // Acende o led amarelo para pedestre e vermelho para motorista
    turnOnLight(YELLOW_PED, GREEN_PED, RED_PED);
    turnOnLight(RED_MOT, GREEN_MOT, YELLOW_MOT);

    // Aguarda 5s lendo o estado do botão
    readBtnLoop(5000);
    
    // Acende o led vermelho para pedestre e verde para motorista
    turnOnLight(RED_PED, GREEN_PED, YELLOW_PED);
    turnOnLight(GREEN_MOT, YELLOW_MOT, RED_MOT);

    // Aguarda 20s lendo o estado do botão
    readBtnLoop(20000);
  }
}