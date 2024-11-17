#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
 
float calibracao_ph7 = 3.93;   
float calibracao_ph4 = 3.93;   
float calibracao_ph10 = 3.93;  
 
#define UTILIZAR_PH_10 true  
float m;
float b;
int buf[10];
 
void setup() {
  Serial.begin(9600);
 
  if (calibracao_ph7 == 0 && calibracao_ph4 == 0 && calibracao_ph10 == 0) {
    delay(500);
    Serial.println();
    Serial.println("Erro - Necessário colocar os valores de calibração no código!");
    while (1)
      ;
  }
 
  if (!UTILIZAR_PH_10 && calibracao_ph4 == 0 && calibracao_ph10 != 0 && calibracao_ph7 != 0) {
    delay(500);
    Serial.println();
    Serial.println("Erro - Você não marcou a opção UTILIZAR_PH_10 como true para utilizar pH 7 e 10.");
    while (1)
      ;
  }
 
  lcd.init();                 
  lcd.begin(16, 2);           
  lcd.backlight();            
  lcd.setCursor(0, 0);        
  lcd.print("HUGO YOSHIDA");      
  lcd.setCursor(0, 1);         
  lcd.print("Leitura de pH");  
  delay(2000);
  lcd.clear();   
 
  if (UTILIZAR_PH_10) {
    m = (7.0 - 10.0) / (calibracao_ph7 - calibracao_ph10);
    b = 10.0 - m * calibracao_ph10;
  } else {
    m = (4.0 - 7.0) / (calibracao_ph4 - calibracao_ph7);
    b = 7.0 - m * calibracao_ph7;
  }
}
 
 
void loop() {
  for (int i = 0; i < 10; i++) {  
    buf[i] = analogRead(A0);      
    delay(10);
  }
 
  for (int i = 0; i < 9; i++) {  
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        int temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
 
  int valorMedio = 0;
  for (int i = 2; i < 8; i++) {  
    valorMedio += buf[i];
  }
 
  float tensao = (valorMedio * 5.0) / 1024.0 / 6;  
  float ph = m * tensao + b;
  Serial.println(ph);
 
  lcd.setCursor(0, 0);     
  lcd.print("Valor pH: ");  
  lcd.setCursor(11, 0);    
  lcd.print(ph, 1);         
  delay(1000);              
}
