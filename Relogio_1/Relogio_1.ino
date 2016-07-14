/*
Relogio Nixie 1
This code cycles through the digits of a Nixie Tube.
Autor: Fabio Leandro Ost
Modificado: 06/06/16
*/
#include <Wire.h>                       // For some strange reasons, Wire.h must be included here
#include <DS1307new.h>

uint16_t startAddr = 0x0000;            // Start address to store in the NV-RAM
uint16_t lastAddr;                      // new address for storing in NV-RAM
uint16_t TimeIsSet = 0xffff; // Helper that time must not set again

int switch1 = 1;
int switch2 = 2;
int switch3 = 4;
int switch4 = 7;
int switch5 = 12;
int switch6 = 13;
int hora=0, minuto=0, segundo=0, dia=0, mes=0, ano=0;

int i=0;
long interval = 1000; //intervalo de atualizacao display 1s
long previousMillis = 0;
long intervalPlex = 3; //frequencia do multiplex 55hz

void setup() {
  //Serial.begin(9600);
  Wire.begin();//ajustar rtc
  RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));// Store startAddr in NV-RAM address 0x08 
  RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  if (TimeIsSet != 0xaa55){
    //ajustaDataHora();
    RTC.stopClock();   
    RTC.fillByYMD(2016,7,11);
    RTC.fillByHMS(18,30,0);
    RTC.setTime();
    TimeIsSet = 0xaa55;
    RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
    RTC.startClock();
  }
 
  pinMode(11, OUTPUT);// D Pinos de comunicacao 74141N
  pinMode(10, OUTPUT);// C
  pinMode(9, OUTPUT);// B
  pinMode(8, OUTPUT);// A
  
  pinMode(switch1, OUTPUT);//pinos do multiplex
  pinMode(switch2, OUTPUT);//pinos do multiplex
  pinMode(switch3, OUTPUT);//pinos do multiplex
  pinMode(switch4, OUTPUT);//pinos do multiplex
  pinMode(switch5, OUTPUT);//pinos do multiplex
  pinMode(switch6, OUTPUT);//pinos do multiplex
}
 
void loop() {
    mostraHora();
}

//-------------------------------------------------//
//METODOS:
void mostraHora(){
  
     unsigned long currentMillis = millis();
     if(currentMillis - previousMillis > interval) {
       RTC.getTime();
       hora = RTC.hour;
       minuto= RTC.minute;
       segundo = RTC.second;
       previousMillis = currentMillis;
     }
     //Serial.print(hora);
     //Serial.print(minuto);
     //Serial.println(segundo);
     
     //paraDisplay(18, 30, 0);
    
     paraDisplay(hora, minuto, segundo);
     
}

void paraDisplay(int par1, int par2, int par3){//saida para display
    int digito[7] = {0,0,0,0,0,0,0};
    
    if(par1<10){
      digito[1]=0;
      digito[2]=par1;
    }else{
      digito[1]=int(par1/10);
      digito[2]=int(par1%10);
    }
    if(par2<10){
      digito[3]=0;
      digito[4]=par2;
    }else{
      digito[3]=int(par2/10);
      digito[4]=int(par2%10);
    }
    if(par3<10){
      digito[5]=0;
      digito[6]=par3;
    }else{
      digito[5]=int(par3/10);
      digito[6]=int(par3%10);
    }
    
    digitalWrite(switch1, HIGH);
    digitalWrite(switch2, LOW);
    digitalWrite(switch3, LOW);
    digitalWrite(switch4, LOW);
    digitalWrite(switch5, LOW);
    digitalWrite(switch6, LOW);
    nixie(digito[1]);
    delay(intervalPlex);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, HIGH);
    digitalWrite(switch3, LOW);
    digitalWrite(switch4, LOW);
    digitalWrite(switch5, LOW);
    digitalWrite(switch6, LOW);
    nixie(digito[2]);
    delay(intervalPlex);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, LOW);
    digitalWrite(switch3, HIGH);
    digitalWrite(switch4, LOW);
    digitalWrite(switch5, LOW);
    digitalWrite(switch6, LOW);
    nixie(digito[3]);
    delay(intervalPlex);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, LOW);
    digitalWrite(switch3, LOW);
    digitalWrite(switch4, HIGH);
    digitalWrite(switch5, LOW);
    digitalWrite(switch6, LOW);
    nixie(digito[4]);
    delay(intervalPlex);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, LOW);
    digitalWrite(switch3, LOW);
    digitalWrite(switch4, LOW);
    digitalWrite(switch5, HIGH);
    digitalWrite(switch6, LOW);
    nixie(digito[5]);
    delay(intervalPlex);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, LOW);
    digitalWrite(switch3, LOW);
    digitalWrite(switch4, LOW);
    digitalWrite(switch5, LOW);
    digitalWrite(switch6, HIGH);
    nixie(digito[6]);
    delay(intervalPlex);
  
}

void nixie(int num){ //metodo de acionamento de um digito
  
  switch (num){
    case 0 :
      digitalWrite(11, LOW);  //D
      digitalWrite(10, LOW);  //C
      digitalWrite(9, LOW);  //B
      digitalWrite(8, LOW);  //A
      break;
    case 1 :
      digitalWrite(11, LOW);  //D
      digitalWrite(10, LOW);  //C
      digitalWrite(9, LOW);  //B
      digitalWrite(8, HIGH);  //A
      break;
    case 2 :
      digitalWrite(11, LOW);  //D
      digitalWrite(10, LOW);  //C
      digitalWrite(9, HIGH);  //B
      digitalWrite(8, LOW);  //A
      break;
    case 3 :
      digitalWrite(11, LOW);  //D
      digitalWrite(10, LOW);  //C
      digitalWrite(9, HIGH);  //B
      digitalWrite(8, HIGH);  //A
      break;
    case 4 :
      digitalWrite(11, LOW);  //D
      digitalWrite(10, HIGH);  //C
      digitalWrite(9, LOW);  //B
      digitalWrite(8, LOW);  //A
      break;
    case 5 :
      digitalWrite(11, LOW);  //D
      digitalWrite(10, HIGH);  //C
      digitalWrite(9, LOW);  //B
      digitalWrite(8, HIGH);  //A
      break;
    case 6 :
      digitalWrite(11, LOW);  //D
      digitalWrite(10, HIGH);  //C
      digitalWrite(9, HIGH);  //B
      digitalWrite(8, LOW);  //A
      break;
    case 7 :
      digitalWrite(11, LOW);  //D
      digitalWrite(10, HIGH);  //C
      digitalWrite(9, HIGH);  //B
      digitalWrite(8, HIGH);  //A
      break;
    case 8 :
      digitalWrite(11, HIGH);  //D
      digitalWrite(10, LOW);  //C
      digitalWrite(9, LOW);  //B
      digitalWrite(8, LOW);  //A
      break;
    case 9 :
      digitalWrite(11, HIGH);  //D
      digitalWrite(10, LOW);  //C
      digitalWrite(9, LOW);  //B
      digitalWrite(8, HIGH);  //A
      break;
  }
  
}
