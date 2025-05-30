///////////////////////////////////////////////////////////////////////////
// Programa desenvolvido por Cristiano Teixeira                          //
///////////////////////////////////////////////////////////////////////////
//                                                                       //
// Baseado em dois motores DC                                            //
// Com uso de Bibliotecas.                                               //
// Utilizando: Ponte H, com biblioteca L298N by Andrea Lombardo          //
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////////Nomes das funções utilizadas//////////////////////////////
///////////////////////////////////////////////////////////////////////////
void  Parado();
void  AndaFrente();
void  AndaRe();
void  ViraDireita();
void  ViraEsquerda();
void  Zerinho();
void  Circulo();
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
4

///////////////////////////////////////////////////////////////////////////
////////////////////////Bloco de variáveis do motor////////////////////////
///////////////////////////////////////////////////////////////////////////
#include <L298N.h>                        // biblioteca da ponte H       //
#define VEL_MAX 250                       // velocidade máxima permitida //
#define ajuste_vel 3                      // fator de ajuste de velocidade//
L298N MotorEsquerda(6, 7);                //Motor Lado Direito           //
L298N MotorDireita(9, 10);                //Motor Lado Esquerdo          //
String motorSet = "";                     // Verifica a posição de movimento//
int velocidade = 0;                       // velocidade atual            //
int raio = 0;                             // adicionar comentário depois //
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
////////////////////////Bloco de variáveis diversas////////////////////////
///////////////////////////////////////////////////////////////////////////
#define tom 11                // para imitar R2D2                        //
#define ledPin 13             // Com Luzes                               //
///////////////////////////////////////////////////////////////////////////

String comm;            

void setup()   
{  
  // SoftwareSerial "com port" data rate. JY-MCU v1.03 defaults to 9600.  
  Serial.begin(9600);  
  pinMode(tom, OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);     // Alternativa para alimentar o BlueTooth
  digitalWrite(3, HIGH);    // Alternativa para alimentar o BlueTooth
  delay(2000);              // espera dois segundos, para dar inicio  
  Parado();                 // seta o estado dos motores para parados
}  
/////////////////////////////////////////////////

void Parado() {
  MotorEsquerda.run(L298N::STOP); 
  MotorDireita.run(L298N::STOP);
}

void AndaFrente() {
    motorSet = "FORWARD";
    MotorEsquerda.run(L298N::FORWARD);
    MotorDireita.run(L298N::FORWARD);
  for (velocidade = 0; velocidade < VEL_MAX; velocidade +=2)
  {
    MotorEsquerda.setSpeed(velocidade);//+ajuste_vel);
    MotorDireita.setSpeed(velocidade);
    delay(10);
  }
}

void AndaRe() {
    motorSet = "BACKWARD";
    MotorEsquerda.run(L298N::BACKWARD);
    MotorDireita.run(L298N::BACKWARD);
  for (velocidade = 0; velocidade < VEL_MAX; velocidade +=2)
  {
    MotorEsquerda.setSpeed(velocidade);//+ajuste_vel);
    MotorDireita.setSpeed(velocidade);
    delay(10);
  }
}  

void ViraDireita() {
  motorSet = "RIGHT";
  velocidade=100;
  MotorEsquerda.setSpeed(velocidade);
   MotorDireita.setSpeed(velocidade);
  MotorEsquerda.run(L298N::FORWARD);
  MotorDireita.run(L298N::BACKWARD);       
}  

void ViraEsquerda() {
  motorSet = "LEFT";
  velocidade=100;
  MotorEsquerda.setSpeed(velocidade);
   MotorDireita.setSpeed(velocidade);
  MotorEsquerda.run(L298N::BACKWARD);
  MotorDireita.run(L298N::FORWARD); 
}  

void Zerinho() {
  motorSet = "LEFT";
  MotorEsquerda.run(L298N::BACKWARD);
  MotorDireita.run(L298N::FORWARD);
}  

void Circulo() {
  motorSet = "LEFT";
  MotorEsquerda.run(L298N::BACKWARD);
  MotorDireita.run(L298N::FORWARD);
  for (velocidade = 0; velocidade < VEL_MAX; velocidade +=2)
  {
    MotorEsquerda.setSpeed(velocidade);//+ajuste_vel);
  
    MotorDireita.setSpeed(velocidade);//+raio);
  raio=+1;
    delay(5);
  }
}
////////////////////////////// 
void loop() {
  // Read device output if available.  
  if (Serial.available()) 
  {  
    delay(100);
     comm="";
     while (Serial.available())
     {
       char c=Serial.read();  
       comm+=c;
       Serial.println(comm);
     }
  }
    if  (comm=="w")
    {
        AndaFrente();
        Serial.println("FRENTE");
        comm="";
    }
    if  (comm=="s")
    {
        AndaRe();
        Serial.println("TRAS");
        comm="";
    }
    if  (comm=="d")
    {
        ViraDireita();
        Serial.println("DIREITA");
        comm="";
    }
    if  (comm=="a")
    {
        ViraEsquerda();
        Serial.println("ESQUERDA");
        comm="";
    }
    if  (comm=="x")
    {
        if(velocidade>=250){
        velocidade=100;  
        }
        if(velocidade==100){
        velocidade=150;  
        }
        if(velocidade==150){
        velocidade=200;  
        }
        if(velocidade==200){
        velocidade=250;  
        }
        Serial.println("Velocidade");
        Serial.println(velocidade);
        comm="";
    }       
    if  (comm=="b")
    {
        Parado();
        Serial.println("PARADO");
        comm="";
    }
    if  (comm=="v")
    {
        Serial.println("VAI-VEM");
        AndaFrente();
        delay(500);
        AndaRe();
        delay(500);
        AndaFrente();
        delay(500);
        AndaRe();
        delay(500);
        Parado();
        comm="";
    }
    if  (comm=="c")
    {
        Zerinho();
        Serial.println("ZERINHO");
        comm="";
    }
  }
