#include <Arduino.h>
#include <Adafruit_AS7341.h>
#define R1 3
#define R2 5
#define C 4
#define V 6

Adafruit_AS7341 as7341;
uint16_t readings[12];
unsigned long ct = 0;
unsigned long pt = 0;
unsigned long pt2 = 0;
//int r = 1;

int tr1 = 5000; // Tempo de acionamento do reagente 1
int tr2 = 10000; // Tempo de acionamento do reagente 2 
int tc = 15000; // Tempo de acionamento do carregador

void setup() {
  Serial.begin(115200);  

    while (!Serial) {
    delay(1);
  }
  
  if (!as7341.begin()){
    Serial.println("Could not find AS7341");
    while (1) { delay(10); }
  }

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_64X);
  as7341.setLEDCurrent(50); // 50mA
  as7341.enableLED(false);

  digitalWrite(R1, HIGH);
  delay(10000);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  delay(10000);
  digitalWrite(R2, LOW);
  digitalWrite(C, HIGH);
  delay(10000);
  digitalWrite(V, HIGH);
  delay(5000);
  digitalWrite(C, LOW);
  digitalWrite(V, LOW);

  // Loop externo para repetir seis vezes
  for (int ciclo = 0; ciclo < 7; ++ciclo) { // Grupo externo de injeções (pontos ou amostras) 
    for (int i = 0; i < 3; ++i) {  // Grupo interno de injeções (replicatas)
      digitalWrite(R1, HIGH);
      pt = millis();
      pt2 = millis();
      while((millis() - pt) < (2*tr1) ){ // Amostragem binária
       readings[12];
           if (!as7341.readAllChannels(readings)){
            Serial.println("Error reading all channels!");
            return;
           }
       Serial.print("ADC0/F1 415nm : ");
       Serial.println(readings[0]);
       Serial.print("ADC1/F2 445nm : ");
       Serial.println(readings[1]);
       Serial.print("ADC2/F3 480nm : ");
       Serial.println(readings[2]);
       Serial.print("ADC3/F4 515nm : ");
       Serial.println(readings[3]);
       Serial.print("ADC0/F5 555nm : ");
       Serial.println(readings[6]);
       Serial.print("ADC1/F6 590nm : ");
       Serial.println(readings[7]);
       Serial.print("ADC2/F7 630nm : ");
       Serial.println(readings[8]);
       Serial.print("ADC3/F8 680nm : ");
       Serial.println(readings[9]);
       Serial.print("ADC4/Clear    : ");
       Serial.println(readings[10]);
       Serial.print("ADC5/ NIR : ");
       Serial.println(readings[11]);
       //delay(402);
        if ((millis() - pt2) > 500){
       digitalWrite(R1, !digitalRead(R1));
       digitalWrite(R2, !digitalRead(R2));
       pt2 = millis();
        }
      }
      digitalWrite(R2, LOW);
      pt = millis();
      digitalWrite(R1, LOW);
      digitalWrite(C, HIGH);
      while ((millis() - pt) < (tc)){ // O carregador leva a solução ao detector
       readings[12];
           if (!as7341.readAllChannels(readings)){
           Serial.println("Error reading all channels!");
           return;
            }
       Serial.print("ADC0/F1 415nm : ");
       Serial.println(readings[0]);
       Serial.print("ADC1/F2 445nm : ");
       Serial.println(readings[1]);
       Serial.print("ADC2/F3 480nm : ");
       Serial.println(readings[2]);
       Serial.print("ADC3/F4 515nm : ");
       Serial.println(readings[3]);
       Serial.print("ADC0/F5 555nm : ");
       Serial.println(readings[6]);
       Serial.print("ADC1/F6 590nm : ");
       Serial.println(readings[7]);
       Serial.print("ADC2/F7 630nm : ");
       Serial.println(readings[8]);
       Serial.print("ADC3/F8 680nm : ");
       Serial.println(readings[9]);
       Serial.print("ADC4/Clear    : ");
       Serial.println(readings[10]);
       Serial.print("ADC5/ NIR : ");
       Serial.println(readings[11]);
       //delay(402);
      }
     digitalWrite(C, LOW);
    }
    pt = millis();
    Serial.print("Sample change");
    //r++;
    Serial.println();
    while((millis() - pt) < 10000 ) { // Tempo para troca de amostra
      readings[12];
          if (!as7341.readAllChannels(readings)){
          Serial.println("Error reading all channels!");
          return;
          }
      Serial.print("ADC0/F1 415nm : ");
      Serial.println(readings[0]);
      Serial.print("ADC1/F2 445nm : ");
      Serial.println(readings[1]);
      Serial.print("ADC2/F3 480nm : ");
      Serial.println(readings[2]);
      Serial.print("ADC3/F4 515nm : ");
      Serial.println(readings[3]);
      Serial.print("ADC0/F5 555nm : ");
      Serial.println(readings[6]);
      Serial.print("ADC1/F6 590nm : ");
      Serial.println(readings[7]);
      Serial.print("ADC2/F7 630nm : ");
      Serial.println(readings[8]);
      Serial.print("ADC3/F8 680nm : ");
      Serial.println(readings[9]);
      Serial.print("ADC4/Clear    : ");
      Serial.println(readings[10]);
      Serial.print("ADC5/ NIR : ");
      Serial.println(readings[11]);
      //delay(402);
    } 
      pt = millis();
      digitalWrite(V, HIGH); 
      digitalWrite(R1, HIGH);
      while((millis() - pt) < 10000 ) { // Preenchimento do canal de amostra
      readings[12];
          if (!as7341.readAllChannels(readings)){
      Serial.println("Error reading all channels!");
      return;
          }
      Serial.print("ADC0/F1 415nm : ");
      Serial.println(readings[0]);
      Serial.print("ADC1/F2 445nm : ");
      Serial.println(readings[1]);
      Serial.print("ADC2/F3 480nm : ");
      Serial.println(readings[2]);
      Serial.print("ADC3/F4 515nm : ");
      Serial.println(readings[3]);
      Serial.print("ADC0/F5 555nm : ");
      Serial.println(readings[6]);
      Serial.print("ADC1/F6 590nm : ");
      Serial.println(readings[7]);
      Serial.print("ADC2/F7 630nm : ");
      Serial.println(readings[8]);
      Serial.print("ADC3/F8 680nm : ");
      Serial.println(readings[9]);
      Serial.print("ADC4/Clear    : ");
      Serial.println(readings[10]);
      Serial.print("ADC5/ NIR : ");
      Serial.println(readings[11]);
      //delay(402);
    }
    pt = millis();
    digitalWrite(R1, LOW);
    digitalWrite(C, HIGH);
    while((millis() - pt) < 10000) {
      readings[12];
          if (!as7341.readAllChannels(readings)){
          Serial.println("Error reading all channels!");
          return;
          }
      Serial.print("ADC0/F1 415nm : ");
      Serial.println(readings[0]);
      Serial.print("ADC1/F2 445nm : ");
      Serial.println(readings[1]);
      Serial.print("ADC2/F3 480nm : ");
      Serial.println(readings[2]);
      Serial.print("ADC3/F4 515nm : ");
      Serial.println(readings[3]);
      Serial.print("ADC0/F5 555nm : ");
      Serial.println(readings[6]);
      Serial.print("ADC1/F6 590nm : ");
      Serial.println(readings[7]);
      Serial.print("ADC2/F7 630nm : ");
      Serial.println(readings[8]);
      Serial.print("ADC3/F8 680nm : ");
      Serial.println(readings[9]);
      Serial.print("ADC4/Clear    : ");
      Serial.println(readings[10]);
      Serial.print("ADC5/ NIR : ");
      Serial.println(readings[11]);
      //delay(402);
    }
    digitalWrite(C, LOW);
    digitalWrite(V, LOW);
  }
}

void loop() {
}
