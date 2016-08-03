/*
Relogio Nixie 1
This code cycles through the digits of a Nixie Tube.
Autor: Fabio Leandro Ost
Modificado: 06/06/16
*/
#include <Wire.h>                       // For some strange reasons, Wire.h must be included here
#include <DS1307new.h>
#include <Encoder.h>

#define expanderAddr B0111000
#define BT_0  0 
#define BT_1  1
//...//
#define BT_5  5
#define BT_6  6
#define BT_7  7

////////////////////InicioMelodiaMario/////////////////////////
/*************************************************
 * Public Constants
 *************************************************/
 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
 
#define melodyPin 5
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

///////////////////FimMelodiaMario///////////////////////

uint16_t startAddr = 0x0000;            // Start address to store in the NV-RAM
uint16_t lastAddr;                      // new address for storing in NV-RAM
uint16_t TimeIsSet = 0xffff; // Helper that time must not set again

int switch1 = 1;//pinos de selecao dos tubos de nixie
int switch2 = 2;
int switch3 = 4;
int switch4 = 7;
int switch5 = 12;
int switch6 = 13;
int hora=-1, minuto=-1, segundo=0, dia=27, mes=7, ano=2016;

int i=0;
long interval = 1000; //intervalo de atualizacao display 1s
long delayAjuste =300; //intervalo ajuste do botao
long previousMillis = 0;
long previousMillis2 = 0;
long intervalPlex = 3; //frequencia do multiplex 55hz
long oldPosition  =-999;//variavel para encoder
int valorVelho = 0; //funcao cronometro
int tempoCronometro = 0;
boolean pisca = false; //alterna display liga desliga
boolean encoderAtivo= false;
int cont =0;

Encoder myEnc(3, 6);


void setup() {
  //Serial.begin(9600);
  
  Wire.begin();//ajustar rtc
  RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));// Store startAddr in NV-RAM address 0x08 
  RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  
  pinMode(5, OUTPUT);//buzzer
  
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
  
  if (TimeIsSet != 0xaa55){
    ajustaHora();
    /*
    RTC.stopClock();   
    RTC.fillByYMD(2016,7,11);
    RTC.fillByHMS(18,30,0);
    RTC.setTime();
    */
    TimeIsSet = 0xaa55;
    RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
    RTC.startClock();
    previousMillis = 0;
  }
  oldPosition = myEnc.read();
  
}
 
void loop() {
  cronometro();
    //mostraHora();
   //Serial.println(leBotao());
   //Serial.println("A");   
   //delay(1000);
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
     
     
     //paraDisplay(18, 30, 0);
     /*
     Serial.print(hora);
    Serial.print(" : ");
    Serial.print(minuto);
    Serial.print(" : ");
    Serial.println(segundo);
    */
     
     paraDisplay(hora, minuto, segundo);
     
}
//////////////////////////////////////////////////////////////

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
byte expanderRead() { ///le expansor de portas
  byte _data;
  Wire.requestFrom(expanderAddr, 1);
  if(Wire.available()) {
    _data = Wire.read();
  }
  return _data;
}

/////////////// AJUSTE DA HORA ////////////////////////////////
void ajustaHora(){
  int botao=0;
  while(leBotao()!=3){
     piscaTela();
  }
  
  apagaTela();
  delay(3000);
  
  botao=0;
  
  while(botao!=3 || hora==-1){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > 300){
       botao=leBotao();
       if(botao==4){
         hora++;
         if(hora>24) hora=1;
       }else{
         if(botao==5){
           hora--;
           if(hora<1) hora=24;
         }
       }
       previousMillis = currentMillis;
    }
     paraDisplay(hora, 0, 0);
  }
   
  apagaTela();
  delay(3000);
  botao=0;
   
  while(botao!=3 || minuto==-1){
     unsigned long currentMillis = millis();
     if(currentMillis - previousMillis > 300){
         botao= leBotao();
         if(botao==4){
           minuto++;
           if(minuto>59) minuto=0;
         }else{
           if(botao==5){
             minuto--;
             if(minuto<0) minuto=59;
           }
         }
         previousMillis = currentMillis;
      }
     paraDisplay(hora, minuto, 0);
     
  }
   
    RTC.stopClock();   
    RTC.fillByYMD(ano,mes,dia);
    RTC.fillByHMS(hora,minuto,0);
    RTC.setTime();
    //RTC.startClock(); 
}

/*
void telaAjusteHora(){  
 if(hora==-1) hora=0;
  //Serial.print("hora ");
  //Serial.println(hora);
  paraDisplay(hora, 0, 0);
}

void telaAjusteMinuto(){
  if(minuto==-1) minuto=0;
  //Serial.print("minuto ");
  //Serial.println(minuto);
  paraDisplay(hora, minuto, 0); 
}
*/

void piscaTela(){
  apagaTela();
  delay(1000);
  if(cont>9) cont =0;
  nixie(cont);
  digitalWrite(switch1, HIGH);
  delay(150);
  digitalWrite(switch2, HIGH);
  delay(150);
  digitalWrite(switch3, HIGH);
  delay(150);
  digitalWrite(switch4, HIGH);
  delay(150);
  digitalWrite(switch5, HIGH);
  delay(150);
  digitalWrite(switch6, HIGH);
  delay(150);
  cont++; 
}

void apagaTela(){
  digitalWrite(switch1, LOW);
  digitalWrite(switch2, LOW);
  digitalWrite(switch3, LOW);
  digitalWrite(switch4, LOW);
  digitalWrite(switch5, LOW);
  digitalWrite(switch6, LOW);
}

int leBotao(){
   int _botao=0;
   byte returnByte = expanderRead();
   boolean bitStatus = bitRead(returnByte, BT_5);
   _botao+=1*bitStatus;
   bitStatus = bitRead(returnByte, BT_6);
   _botao+=2*bitStatus;
   bitStatus = bitRead(returnByte, BT_7);
   _botao+=3*bitStatus;
   return _botao;
}

int segundoCronometro = 60;//debug  

void leEncoder(){
    long newPosition = myEnc.read();
    if (newPosition >= oldPosition+4) {
      tempoCronometro++;
      segundoCronometro = 60;//debug
      oldPosition = newPosition;
      encoderAtivo = true;
    }else{
      if(newPosition <= oldPosition-4){
        tempoCronometro--;
        segundoCronometro = 60;//debug
        oldPosition = newPosition;
        encoderAtivo = true;
      }
    }
    if(tempoCronometro < 0){
      tempoCronometro = 0;
      encoderAtivo = false;
    }
}

void cronometro(){
  leEncoder();
  int horaCronometro=0, minutoCronometro=0; //segundoCronometro = 60;
  while(encoderAtivo){
    leEncoder();
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > 1000){
      previousMillis = currentMillis;
      segundoCronometro--;  
    }
    if(segundoCronometro < 0 && tempoCronometro > 0){
        segundoCronometro = 59;
        tempoCronometro--;
    }
    if(tempoCronometro <= 0 && segundoCronometro == 0){
      tempoCronometro = 0;
      encoderAtivo = false;
      tocaMusica();
    }
    if(tempoCronometro > 59){
      horaCronometro = (int)tempoCronometro/60;
      if(horaCronometro>24) horaCronometro=24;
      minutoCronometro = (int)tempoCronometro%60;
    }else{
      horaCronometro = 0;
      minutoCronometro = tempoCronometro;
    }
    paraDisplay(horaCronometro, minutoCronometro, segundoCronometro);
  }
  mostraHora();
    
}

void tocaMusica(){
  //sing the tunes
  sing(1);
  sing(1);
  sing(2);
  
}

///////InicioMelodiaMario/////
int song = 0;
 
void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 2) {
    //Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];
 
      buzz(melodyPin, underworld_melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
 
    }
 
  } else {
 
    //Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];
 
      buzz(melodyPin, melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
 
    }
  }
}
 
void buzz(int targetPin, long frequency, long length) {
  //digitalWrite(13, HIGH);
  efeitoDisplay(random(1,6));
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  //digitalWrite(13, LOW);
  apagaTela();
 
}

///////FimMelodiaMario////////



//////EFEITOS DE DISPLAY//////
void efeitoDisplay(int num){
  switch (num){
    case 1:
      digitalWrite(switch1, HIGH);
      digitalWrite(switch2, LOW);
      digitalWrite(switch3, LOW);
      digitalWrite(switch4, LOW);
      digitalWrite(switch5, LOW);
      digitalWrite(switch6, LOW);
      nixie(0);
      break;
    
    case 2:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, HIGH);
      digitalWrite(switch3, LOW);
      digitalWrite(switch4, LOW);
      digitalWrite(switch5, LOW);
      digitalWrite(switch6, LOW);
      nixie(0);
      break;
    
    case 3:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, LOW);
      digitalWrite(switch3, HIGH);
      digitalWrite(switch4, LOW);
      digitalWrite(switch5, LOW);
      digitalWrite(switch6, LOW);
      nixie(0);
      break;
      
    case 4:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, LOW);
      digitalWrite(switch3, LOW);
      digitalWrite(switch4, HIGH);
      digitalWrite(switch5, LOW);
      digitalWrite(switch6, LOW);
      nixie(0);
      break;
      
    case 5:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, LOW);
      digitalWrite(switch3, LOW);
      digitalWrite(switch4, LOW);
      digitalWrite(switch5, HIGH);
      digitalWrite(switch6, LOW);
      nixie(0);
      break;
      
    case 6:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, LOW);
      digitalWrite(switch3, LOW);
      digitalWrite(switch4, LOW);
      digitalWrite(switch5, LOW);
      digitalWrite(switch6, HIGH);
      nixie(0);
      break;
    
  }
}
