///////////////////////////////////////////////////////////////////////////
// Programa desenvolvido por Cristiano Teixeira                          //
///////////////////////////////////////////////////////////////////////////
//                                                                       //
// Baseado em dois motores DC                                            //
// Utilizando módulo bluetooth HC-06                                     //
// Utilizando: Ponte H L298N sem bibliotecas                             //
///////////////////////////////////////////////////////////////////////////
// Definição dos pinos para a ponte H L298N
#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10

// Velocidade dos motores (0-255)
int velocidade = 150; // Ajuste conforme necessário

void setup() {
  // Configura os pinos como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // ajuste técnico para o bluetooth
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  
  // Inicia a comunicação serial (Bluetooth)
  Serial1.begin(9600); // Leonardo usa Serial1 para comunicação com o HC-06
}

void loop() {
  if (Serial1.available() > 0) {
    char comando = Serial1.read();
    
    switch (comando) {
      case 'w': // Frente
        moverFrente();
        break;
      case 's': // Trás
        moverTras();
        break;
      case 'a': // Esquerda
        virarEsquerda();
        break;
      case 'd': // Direita
        virarDireita();
        break;
      default: // Parar
        parar();
        break;
    }
  }
}

void moverFrente() {
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
}

void moverTras() {
  analogWrite(IN1, 0);
  analogWrite(IN2, velocidade);
  analogWrite(IN3, 0);
  analogWrite(IN4, velocidade);
}

void virarEsquerda() {
  analogWrite(IN1, 0);
  analogWrite(IN2, velocidade);
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
}

void virarDireita() {
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, velocidade);
}

void parar() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}
