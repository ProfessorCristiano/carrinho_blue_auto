///////////////////////////////////////////////////////////////////////////
// Programa desenvolvido por Cristiano Teixeira                          //
///////////////////////////////////////////////////////////////////////////
//                                                                       //
// Baseado em dois motores DC                                            //
// Com uso de Bibliotecas.                                               //
// Utilizando: Ponte H, Sensor H04, Servo motor                          //
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////////Nomes das funções utilizadas//////////////////////////////
///////////////////////////////////////////////////////////////////////////
//  Parado()
//  AndaFrente()
//  AndaRe()
//  ViraDireita()
//  ViraEsquerda()
//  Zerinho()
//  Circulo()
//  Verifica()
//  NovaRota()
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
////////////////////////Bloco de variáveis do motor////////////////////////
///////////////////////////////////////////////////////////////////////////
#include <AFMotor.h>                      // biblioteca da ponte H       //
#define VEL_MAX 250 				              // velocidade máxima permitida //
#define ajuste_vel 3		                 // fator de ajuste de velocidade//
AF_DCMotor MotorEsquerda(4, MOTOR12_8KHZ);//Motor Lado Direito           //
AF_DCMotor MotorDireita(3, MOTOR12_8KHZ); //Motor Lado Esquerdo          //
String motorSet = ""; 				         // Verifica a posição de movimento//
int velocidade = 0; 				              // velocidade atual            //
int raio = 0; 					                  // adicionar comentário depois //
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
////////////////////////Bloco de variáveis do ultrasom/////////////////////
///////////////////////////////////////////////////////////////////////////
#include <Ultrasonic.h>     //Carrega a biblioteca do sensor ultrassonico//
//Define os pinos para o trigger e echo                                 
#define pino_trigger A4 				// pino trigger 2                       
#define pino_echo A5    				// pino echo 4
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
int bloqF = 0;                   // se há bloqueio a frente
int bloqD = 0;                   // se há bloqueio a direita
int bloqE = 0;                   // se há bloqueio a esquerda

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
////////////////////////Bloco de variáveis do servomotor///////////////////
///////////////////////////////////////////////////////////////////////////
#include <Servo.h>         //Carrega a biblioteca do servo motor         //
Servo giro;                 //Definindo nome do servomotor               //
int angulo=0;              //Definindo angulo inicial do servomotor      //
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
////////////////////////Bloco de variáveis diversas////////////////////////
///////////////////////////////////////////////////////////////////////////
#define tom A2        				// para imitar R2D2                        //
#define ledPin A3     				// Com Luzes                               //
///////////////////////////////////////////////////////////////////////////




void setup() 
{
  delay(2000);              // espera dois segundos, para dar inicio  
  motorSet = "FOWARD"; 			// Indica posição a seguir
  Parado();					        // seta o estado dos motores para parados

  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  pinMode(tom, OUTPUT);

  giro.attach(10);     // Pino de controle do servo
  Serial.begin(9600);
  giro.write(90); // Inicia motor posição 90 ok


}



void loop() 
{
// INICIO DO ROBO
//Verifica();

}

void Verifica()
{
  float cmMsec, inMsec, teste;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print(" \n Distancia em cm: ");
  Serial.print(cmMsec);
  teste =cmMsec;
  if (teste <= 20 and teste >= 15)
    {
      //beep (tom, 300, 1000);
      bloqF=1;
      NovaRota();
    }
    else
    {
      AndaFrente();
    }
    
}

void NovaRota()
{
float cmMsec, inMsec, teste;
  
  giro.write(0);
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  teste =cmMsec;
  if (teste <= 20 and teste >= 15)
    {
      //beep (tom, 300, 1000);
      bloqF=1;
    }
    else
    {
      giro.write(180);
      long microsec = ultrasonic.timing();
      cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
      teste =cmMsec;
        if (teste <= 20 and teste >= 15)
        {
          //beep (tom, 300, 1000);
          bloqE=1;
        }
        else
        {
          giro.write(90);
          long microsec = ultrasonic.timing();
          cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
          teste =cmMsec;
          if (teste <= 20 and teste >= 15)
          {
            //beep (tom, 300, 1000);
            bloqD=1;
          }
          else
          {
            ViraDireita();          
            ViraDireita();
          }
        }
     }
}



void Parado() {
	MotorEsquerda.run(RELEASE); 
	MotorDireita.run(RELEASE);
}

void AndaFrente() {
    motorSet = "FORWARD";
    MotorEsquerda.run(FORWARD);
    MotorDireita.run(FORWARD);
  for (velocidade = 0; velocidade < VEL_MAX; velocidade +=2)
  {
    MotorEsquerda.setSpeed(velocidade+ajuste_vel);
    MotorDireita.setSpeed(velocidade);
    delay(5);
  }
}

void AndaRe() {
    motorSet = "BACKWARD";
    MotorEsquerda.run(BACKWARD);
    MotorDireita.run(BACKWARD);
  for (velocidade = 0; velocidade < VEL_MAX; velocidade +=2)
  {
    MotorEsquerda.setSpeed(velocidade+ajuste_vel);
    MotorDireita.setSpeed(velocidade);
    delay(5);
  }
}  

void ViraDireita() {
  motorSet = "RIGHT";
  MotorEsquerda.run(FORWARD);
  MotorDireita.run(BACKWARD);
  delay(400);
  motorSet = "FORWARD";
  MotorEsquerda.run(FORWARD);
  MotorDireita.run(FORWARD);      
}  

void ViraEsquerda() {
  motorSet = "LEFT";
  MotorEsquerda.run(BACKWARD);
  MotorDireita.run(FORWARD);
  delay(400);
  motorSet = "FORWARD";
  MotorEsquerda.run(FORWARD);
  MotorDireita.run(FORWARD);
}  

void Zerinho() {
  motorSet = "LEFT";
  MotorEsquerda.run(BACKWARD);
  MotorDireita.run(FORWARD);
}  

void Circulo() {
  motorSet = "LEFT";
  MotorEsquerda.run(BACKWARD);
  MotorDireita.run(FORWARD);
  for (velocidade = 0; velocidade < VEL_MAX; velocidade +=2)
  {
    MotorEsquerda.setSpeed(velocidade+ajuste_vel);
	
    MotorDireita.setSpeed(velocidade+raio);
	raio=+1;
    delay(5);
  }

/*void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{
    //digitalWrite(ledPin, HIGH);
    //use led to visualize the notes being played
 
    int x;
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)
    {
        digitalWrite(tom,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(tom,LOW);
        delayMicroseconds(delayAmount);
    }
 
    digitalWrite(ledPin, LOW);
    //set led back to low
 
    delay(20);
    //a little delay to make all notes sound separate
}*/
  
}  
