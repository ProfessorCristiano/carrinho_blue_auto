///////////////////////////////////////////////////////////////////////////
// Programa desenvolvido por Cristiano Teixeira                          //
///////////////////////////////////////////////////////////////////////////
//                                                                       //
// Baseado em dois motores DC                                            //
// Com uso de Bibliotecas.                                               //
// Utilizando: Ponte H, HC-06                          //
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


///////////////////////////////////////////////////////////////////////////
////////////////////////Bloco de variáveis do motor////////////////////////
///////////////////////////////////////////////////////////////////////////
#include <AFMotor.h>                      // biblioteca da ponte H       //
#define VEL_MAX 200                       // velocidade máxima permitida //
#define ajuste_vel 3                     // fator de ajuste de velocidade//
AF_DCMotor MotorEsquerda(3, MOTOR12_8KHZ);//Motor Lado Direito           //
AF_DCMotor MotorDireita(4, MOTOR12_8KHZ); //Motor Lado Esquerdo          //
String motorSet = "";                  // Verifica a posição de movimento//
int velocidade = 0;                       // velocidade atual            //
int raio = 0;                             // adicionar comentário depois //
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
////////////////////////Bloco de variáveis diversas////////////////////////
///////////////////////////////////////////////////////////////////////////
#define tom A2                // para imitar R2D2                        //
#define ledPin A3             // Com Luzes                               //
///////////////////////////////////////////////////////////////////////////



String comm;            
   
void setup()   
{  
  
  // SoftwareSerial "com port" data rate. JY-MCU v1.03 defaults to 9600.  
  Serial.begin(9600);  

  //delay(2000);              // espera dois segundos, para dar inicio  
  //motorSet = "FOWARD";       // Indica posição a seguir
  //Parado();                 // seta o estado dos motores para parados
  pinMode(tom, OUTPUT);
  pinMode(A1,OUTPUT);


}  
/////////////////////////////////////////////////


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
    MotorEsquerda.setSpeed(velocidade);//+ajuste_vel);
    MotorDireita.setSpeed(velocidade);
    delay(10);
  }
}

void AndaRe() {
    motorSet = "BACKWARD";
    MotorEsquerda.run(BACKWARD);
    MotorDireita.run(BACKWARD);
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
  MotorEsquerda.run(FORWARD);
  MotorDireita.run(BACKWARD);
        
}  

void ViraEsquerda() {
  motorSet = "LEFT";
  velocidade=100;
  MotorEsquerda.setSpeed(velocidade);
   MotorDireita.setSpeed(velocidade);
  MotorEsquerda.run(BACKWARD);
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
    
    
    if  (comm=="upPressed")
    {
        AndaFrente();
        Serial.println("FRENTE");
        comm="";
    }
    if  (comm=="upReleased")
    {
        Parado();
        Serial.println("PARADO");
        comm="";
    }
    if  (comm=="downPressed")
    {
        AndaRe();
        Serial.println("TRAS");
        comm="";
    }
    if  (comm=="downReleased")
    {
        Parado();
        Serial.println("PARADO");
        comm="";
    }
    if  (comm=="rightPressed")
    {
        ViraDireita();
        Serial.println("DIREITA");
        comm="";
    }
    if  (comm=="rightReleased")
    {
        Parado();
        Serial.println("PARADO");
        comm="";
    }
    if  (comm=="leftPressed")
    {
        ViraEsquerda();
        Serial.println("ESQUERDA");
        comm="";
    }
    if  (comm=="leftReleased")
    {
        Parado();
        Serial.println("PARADO");
        comm="";
    }
    if  (comm=="triagletPressed")
    {
        comm="";
    }   
    if  (comm=="triagletReleased")
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
    if  (comm=="xPressed")
    {
      comm="";
    }
    if  (comm=="xReleased")
    {
        Parado();
        Serial.println("PARADO");
        comm="";
    }
    if  (comm=="squarePressed")
    {
        comm="";
    }
    if  (comm=="squareReleased")
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
    if  (comm=="circlePressed")
    {
        comm="";
    }
    if  (comm=="circleReleased")
    {
        Zerinho();
        Serial.println("ZERINHO");
        comm="";
    }
   
  }

  




