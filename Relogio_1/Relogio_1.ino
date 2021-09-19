/*
Relogio Nixie 1
This code cycles through the digits of a Nixie Tube.
Autor: Fabio Leandro Ost
first:06/06/16
Modificado: 14/01/19
*/
/////////////////////////////////////ESP
/*
Thingspeak CREDENTIALS:
fabioost@bol.com.br
Aa0840c7
*/

#include <SoftwareSerial.h>       //Software Serial library
SoftwareSerial esp8266(3, 6);   //Pin 3 and 6 act as RX and TX. Connect them to TX and RX of ESP8266   
int responseTime = 1000; //communication timeout

String mySSID = "\"SSID\"";       // WiFi SSID
String myPWD = "\"SENHA\""; // WiFi Password

String apESSID = "\"ESP3\"";
String appassword = "\"SENHA\"";

String myAPI = "Y8F458G58KQR7K84";   // API Key
String myHOST = "api.thingspeak.com";
String myPORT = "80";

#define DEBUG false
boolean disparo = true;
boolean espLigado = false;
boolean espReset = false;
  
////////////////////////////////////////FIMESP

#include <Wire.h>                       // For some strange reasons, Wire.h must be included here
#include <DS1307new.h>
//#define ENCODER_DO_NOT_USE_INTERRUPTS
//#include <Encoder.h>

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
int hora= 24, minuto=-1, segundo=0, dia=27, mes=7, ano=2016;

int i=0;
long interval = 1000; //intervalo de atualizacao display 1s
long delayAjuste =300; //intervalo ajuste do botao
long previousMillis = 0;
long previousMillis2 = 0;
long intervalPlex = 3; //frequencia do multiplex 55hz
int brilho = 100;//brilho display valor em % limite em 40 - 100
int tempoLigado = intervalPlex * brilho/100;
int tempoDesligado = intervalPlex - tempoLigado;
long oldPosition  =-999;//variavel para encoder
int valorVelho = 0; //funcao cronometro
int tempoCronometro = 0;
boolean pisca = false; //alterna display liga desliga
boolean encoderAtivo= false;
int cont =0;

//Encoder myEnc(15, 16);



void setup() {
  //Serial.begin(9600);

  ///////////////////ESP
  //Serial.begin(9600);
  esp8266.begin(9600);
 // resetEsp();
  //sendToUno("Wifi connection is running!",responseTime,DEBUG);

  /////////////////////FIMESP
  
  
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
    //ajustaHora();
    
    RTC.stopClock();   
    RTC.fillByYMD(2016,7,11);
    RTC.fillByHMS(18,30,0);
    RTC.setTime();
    
    TimeIsSet = 0xaa55;
    RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
    RTC.startClock();
    previousMillis = 0;
  }
  
 //verificaHora();
 //oldPosition = myEnc.read();
  
}
 
void loop() {
  //cronometro();
   mostraHora();
   //Serial.println(leBotao());
   //Serial.println("A");   
   //delay(1000);
}

//-------------------------------------------------//
//METODOS:

void espAtivo(){
  //testa resposta esp 
  String res = sendToEsp("AT", 200, DEBUG);
  if(find(res,"OK")) espLigado = true;
  else{
    espLigado = false;
    espReset = false;
  }
  if(espLigado && !espReset) resetEsp();
}


void verificaHora(){ 
  if (espLigado){  //verifica esp ligado e com ip
        String value ="";
        String views = getTrueTime();
        //sendToUno(views,responseTime,DEBUG);
        value = views.substring(0,2);
        int horaInternet = value.toInt();
        value = views.substring(3,5);
        int minutoInternet = value.toInt();
        value = views.substring(6,-1);
        int segundoInternet = value.toInt();
       
      if(horaInternet >= 0 && horaInternet <= 24){
        if(horaInternet != hora || minutoInternet != minuto){// || segundoInternet > (segundo + 10) || segundoInternet < (segundo - 10)){
              RTC.stopClock();   
              RTC.fillByYMD(ano,mes,dia);
              RTC.fillByHMS(horaInternet, minutoInternet, segundoInternet );
              RTC.setTime();
              RTC.startClock(); 
        }
        
      }
  }
  
}

//

void mostraHora(){
     if(espLigado && espReset) getInstructions();
  
     unsigned long currentMillis = millis();
     if(currentMillis - previousMillis > interval) {
       RTC.getTime();
       hora = RTC.hour;
       minuto= RTC.minute;
       segundo = RTC.second;
       previousMillis = currentMillis;
       
       if(segundo==0) espAtivo();
     }
     ////////regulagem brilho display por horario////////////
     
     if(hora >= 23 || hora <= 6 ){
       brilho = 40;
     }else{
       brilho = 100;
     } 
     
     calculaTemposDisplay();
     //////////fim regulagem/////////////////////////////////
     
     
     //paraDisplay(18, 30, 0);
     /*
     Serial.print(hora);
    Serial.print(" : ");
    Serial.print(minuto);
    Serial.print(" : ");
    Serial.println(segundo);
    */
   if(hora >= 5){ 
      paraDisplay(hora, minuto, segundo);
      disparo = true;
      if(hora==7 && minuto == 0 && segundo == 0) tocaMusicaUnderworld();
    }else{
      //verificaHora();
      //disparo = false;
      apagaTela(1000);
    }
     
}

void getInstructions(){
   if(esp8266.available()>0){
     String message = readWifiSerialMessage();
      
      if(find(message,"cron")){
        String tempo = message.substring(14,message.length());
        int num = tempo.toInt();
        cronometro2(num);
      }
      if(find(message,"ajusta")){
        verificaHora();
      }
       if(find(message,"under")){
        tocaMusicaUnderworld();
      }
      if(find(message,"cara")){
        cara();
      }
   }
  
}
//////////////////////////////////////////////////////////////
void calculaTemposDisplay(){
  tempoLigado = intervalPlex * brilho/100;
  tempoDesligado = intervalPlex - tempoLigado;
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
    delay(tempoLigado);
    apagaTela(tempoDesligado);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, HIGH);
    digitalWrite(switch3, LOW);
    digitalWrite(switch4, LOW);
    digitalWrite(switch5, LOW);
    digitalWrite(switch6, LOW);
    nixie(digito[2]);
    delay(tempoLigado);
    apagaTela(tempoDesligado);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, LOW);
    digitalWrite(switch3, HIGH);
    digitalWrite(switch4, LOW);
    digitalWrite(switch5, LOW);
    digitalWrite(switch6, LOW);
    nixie(digito[3]);
    delay(tempoLigado);
    apagaTela(tempoDesligado);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, LOW);
    digitalWrite(switch3, LOW);
    digitalWrite(switch4, HIGH);
    digitalWrite(switch5, LOW);
    digitalWrite(switch6, LOW);
    nixie(digito[4]);
    delay(tempoLigado);
    apagaTela(tempoDesligado);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, LOW);
    digitalWrite(switch3, LOW);
    digitalWrite(switch4, LOW);
    digitalWrite(switch5, HIGH);
    digitalWrite(switch6, LOW);
    nixie(digito[5]);
    delay(tempoLigado);
    apagaTela(tempoDesligado);
    
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, LOW);
    digitalWrite(switch3, LOW);
    digitalWrite(switch4, LOW);
    digitalWrite(switch5, LOW);
    digitalWrite(switch6, HIGH);
    nixie(digito[6]);
    delay(tempoLigado);
    apagaTela(tempoDesligado);
  
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
  
  apagaTela(3000);
  
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
   
  apagaTela(3000);
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
  setahora();
    
}

void setahora(){
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
  apagaTela(1000);
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

void apagaTela(int tempo){
  digitalWrite(switch1, LOW);
  digitalWrite(switch2, LOW);
  digitalWrite(switch3, LOW);
  digitalWrite(switch4, LOW);
  digitalWrite(switch5, LOW);
  digitalWrite(switch6, LOW);
  delay(tempo);
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

////////////////////Teste usando pinos analogicoa A1 e A2 como 15 16
int segundoCronometro = 60;//debug  

void leEncoder(){
  /*
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    segundoCronometro = 60;//debug
    oldPosition = newPosition;
    tempoCronometro = newPosition/4;
    encoderAtivo = true;
    
    if(tempoCronometro < 0){
      tempoCronometro = 0;
      encoderAtivo = false;
    }
    //Serial.println(tempoCronometro);
  }
  
  /*
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
    */
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

////////////////////////fim teste

void tocaMusica(){
  //sing the tunes
  sing(1);
  sing(1);
  sing(2);
  
}
void tocaMusicaUnderworld(){
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
  efeitoDisplay(random(1,7));
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
  apagaTela(0);
 
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

void efeitoDisplay2(int num){
  switch (num){
    case 1:
      digitalWrite(switch1, HIGH);
      digitalWrite(switch2, LOW);
      digitalWrite(switch3, HIGH);
      digitalWrite(switch4, LOW);
      digitalWrite(switch5, LOW);
      digitalWrite(switch6, LOW);
      nixie(0);
      break;
    
    case 2:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, HIGH);
      digitalWrite(switch3, LOW);
      digitalWrite(switch4, HIGH);
      digitalWrite(switch5, LOW);
      digitalWrite(switch6, LOW);
      nixie(0);
      break;
    
    case 3:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, LOW);
      digitalWrite(switch3, HIGH);
      digitalWrite(switch4, LOW);
      digitalWrite(switch5, HIGH);
      digitalWrite(switch6, LOW);
      nixie(0);
      break;
      
    case 4:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, LOW);
      digitalWrite(switch3, LOW);
      digitalWrite(switch4, HIGH);
      digitalWrite(switch5, LOW);
      digitalWrite(switch6, HIGH);
      nixie(0);
      break;
      
    case 5:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, LOW);
      digitalWrite(switch3, HIGH);
      digitalWrite(switch4, LOW);
      digitalWrite(switch5, HIGH);
      digitalWrite(switch6, LOW);
      nixie(1);
      break;
      
    case 6:
      digitalWrite(switch1, LOW);
      digitalWrite(switch2, HIGH);
      digitalWrite(switch3, LOW);
      digitalWrite(switch4, HIGH);
      digitalWrite(switch5, LOW);
      digitalWrite(switch6, LOW);
      nixie(1);
      break;
    
  }
}
void cara(){
  int vet[13] = {2,2,1,2,6,3,3,5,3,4,3,5,3};
  int tempo = 1000;
  for(int i=1 ; i <=13; i++){
     efeitoDisplay2(vet[i]);
     if(vet[i]==5 || vet[i] == 6) tempo = 100;
     else tempo = random(1000,5000);
     delay(tempo);
  }
}

////////////////////////////ESP
String getTrueTime(){
  delay(300);
  //sendToEsp("AT+CIPCLOSE=5",3000,DEBUG);
  sendToEsp("AT+CIPSTART=1,\"TCP\",\""+ myHOST +"\","+ myPORT, 3000, DEBUG); //0
  sendToEsp("AT+CIPSEND=1,90",1000,DEBUG); //0
  
  String hostt = "GET /apps/thinghttp/send_request?api_key=";
  hostt+= myAPI;
 
  hostt+="\r\n";
  hostt+="Host:api.thingspeak.com";
  hostt+="\r\n\r\n\r\n\r\n";
  
  String views = sendToEsp(hostt,3000,DEBUG);
  sendToEsp("AT+CIPCLOSE=1",3000,DEBUG); //5

  
  /********************** Steps To filter the received data. ****************************/
  
  int i = 0;        
  //if (DEBUG)
   // Serial.println(views);

  while (views.charAt(i) != ':') // Character before required data starts.
    i++;
    
  i++;
  views = views.substring(i);
  
  int j = 0;
  while (views.charAt(j) != 'C') // Character after required data ends.
    j++;

  j-=2; 
  views = views.substring(0, j);
  
  //if (DEBUG)
    //Serial.println(views);

  return (String)(views);
}

void resetEsp(){

      String res = "";
      sendToEsp("AT+RST", 2000, DEBUG); // rst
      //delay(1000);
      /*
      while (!esp8266.available()){
         //Serial.println("Esperando Esp8266...");////wait
         paraDisplay(0, 0, 0);
         delay(100);
      }
      */
      for(int i =0; i <  80; i++){
        delay(100);
        paraDisplay(0, 0, 0);
      }

      
      /*
      /////////////CONFIGURACAO DEFINITIVA///////////////////
    
      sendToEsp("AT+CWQAP", 2000, DEBUG);//DISCONECTA DA WIFII
      
      sendToEsp("AT+CWMODE_DEF=3", 2000, DEBUG);//ACEESPOINT + ESTATION
      
      //login e senha wiffi AP
      sendToEsp("AT+CWSAP_DEF="+ apESSID + "," + appassword + ",1,3",2000, DEBUG);  
      
      // Conecta a rede wireless
      sendToEsp("AT+CWJAP_DEF="+ mySSID +","+ myPWD, 2000, DEBUG);
      
      delay(3000);

      ////////////////////FIM CONFIGURACAO DEFINITIVA
      */
     
     
      // Mostra o endereco IP
      res = sendToEsp("AT+CIFSR", 1000, DEBUG);
      if(find(res,"OK")) {
        int n1=0,n2=0,n3=0;
        String res2="";
        // Mostra o endereco IP
        res = sendToEsp("AT+CIFSR", 3000, DEBUG);
        res= res.substring(10,res.length());
        res2=res.substring(res.indexOf('T')+15,res.indexOf('T')+19);
        n1 = res2.substring(1,2).toInt();
        n2 = res2.substring(2,3).toInt();
        n3 = res2.substring(3,4).toInt();
        for(int i =0; i <  20; i++){
          delay(100);
          paraDisplay(n1, n2, n3);
        }
        espReset = true;
      }
      else{
        for(int i =0; i <  20; i++){
          delay(100);
          paraDisplay(1, 1, 1);
        }
      }
      
      // Configura para multiplas conexoes
      sendToEsp("AT+CIPMUX=1", 1000, DEBUG);
      
      // Inicia o web server na porta 80
      sendToEsp("AT+CIPSERVER=1,80", 1000, DEBUG);
     // delay(3000);
      
}

String sendToEsp(String command, const int timeout, boolean debug){
  // Envio dos comandos AT para o modulo
  command+="\r\n";
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    //Serial.print(response);
  }
  return response;
}

boolean find(String string, String value){
  if(string.indexOf(value)>=0) return true;
  else return false;
}

/*
* Name: readWifiSerialMessage
* Description: Function used to read data from ESP8266 Serial.
* Params: 
* Returns: The response from the esp8266 (if there is a reponse)
*/
String  readWifiSerialMessage(){
  char value[100]; 
  int index_count = 0;
  while(esp8266.available()>0){
    value[index_count]=esp8266.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}

void cronometro2(int num){
  tempoCronometro = num;
  int horaCronometro=0, minutoCronometro=0, segundoCronometro = 0;
  encoderAtivo = true;
  while(encoderAtivo){
    getInstructions();
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > 1000){
      previousMillis = currentMillis;
      segundoCronometro--;  
    }
    if(segundoCronometro < 0 && tempoCronometro > 0){
        segundoCronometro = 59;
        tempoCronometro--;
    }
    if(tempoCronometro <= 0 && segundoCronometro <= 0){
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
/*
String sendToUno(String command, const int timeout, boolean debug){
  String response = "";
  Serial.println(command); // send the read character to the esp8266
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(Serial.available())
    {
      // The esp has data so display its output to the serial window 
      char c = Serial.read(); // read the next character.
      response+=c;
    }  
  }
  if(debug)
  {
    Serial.println(response);
  }
  return response;
}
*/
