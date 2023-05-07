/*	
 *  Centro Federal de Educação Tecnológica
 *  CEFET - UnED Petrópolis
 *  Microcontroladores e Sistemas Embarcados
 *	Autores: 
 *    - Eduardo de Matos Gomes
 *    - Eduardo Paes Silva
 *  2023.1
 */

#include <Ultrasonic.h>

// Classe para controle da Ponte H
class Bridge {
	const int A, B;
	bool locked = false;

  public:
	Bridge(int A, int B) : A(A), B(B) {
		pinMode(A, OUTPUT);
		pinMode(B, OUTPUT);
	}

	void forward(int power) {
		if (locked) return;
		analogWrite(A, power);
		digitalWrite(B, LOW);
	}

	void backward(int power) {
		if (locked) return;
		digitalWrite(A, LOW);
		analogWrite(B, power);
	}

	void stop() {
		digitalWrite(A, LOW);
		digitalWrite(B, LOW);
	}

	bool &lock() { return locked; }
};

// Escopo global
Bridge right(9, 10), left(5, 6);
Ultrasonic sensor(3, 4);
const int BLOCK_PIN = 13;
bool DISCONNECTED = 0;

// Função de inicialização
void setup() {
	pinMode(BLOCK_PIN, INPUT_PULLUP);
	Serial.begin(9600);
}

// Função para evitar colisão diante de um objeto
void avoid() {
	Serial.println("Virando...");
	right.backward(250);
	left.backward(255);
	delay(500);
	right.forward(255);
	left.backward(255);
	delay(350);
	right.stop();
	left.stop();
	delay(500);
	Serial.println("Virou");
}

void loop() {
	delay(15);
	long cm = sensor.Ranging(CM);
	// Serial.println(cm);

  // Bloqueia e desbloqueia a execução do carro 
  // baseado no status da porta 13
	if (digitalRead(BLOCK_PIN)) {
		right.lock() = true;
		left.lock() = true;
		right.stop();
		left.stop();
	} else {
		left.lock() = right.lock() = false;
	}

  // Verifica a distância e evita a colisão 
  // quando o sensor de distância alertar
	if (cm <= 30) {
		avoid();
	} else {
    static long time;
		while (Serial.available() > 0) {
			char buf = Serial.read();
      DISCONNECTED = false;
			switch (buf) {
        case 'd':
        case 'D':
          Serial.println("Right");
          left.forward(200);
          right.backward(200);
          break;
        case 'a':
        case 'A':
          Serial.println("Left");
          right.forward(200);
          left.backward(200);
          break;
        case 's':
        case 'S':
          Serial.println("Backward");
          right.backward(255);
          left.backward(255);
          break;
        case 'w':
        case 'W':
          Serial.println("Forward");
          right.forward(255);
          left.forward(255);
          break;
        case '\n':
        case '\r':
          break;
        default:
          Serial.println("Stop");
          right.stop();
          left.stop();
          break;
      }
      time = millis();
		}

    // Para o carrinho caso haja desconexão
    long res = millis() - time;
    if (res > 600 && !DISCONNECTED) {
      Serial.println("Stop Disconnected");
      right.stop();
      left.stop();
      DISCONNECTED = true;
    }
	}
}