int buf[10];
 
 
void setup() {
  Serial.begin(9600);
  Serial.println("Usinainfo");
  delay(500);
}
 
 
 
void loop() {
  for (int i = 0; i < 10; i++) {     
    buf[i] = analogRead(A0);  
    delay(10);
  }
 
 
  int valorMedio = 0;
  for (int i = 2; i < 8; i++) {  
    
    valorMedio += buf[i];
  }
 
 
  float tensao = (valorMedio * 5.0) / 1024.0 / 6;
  Serial.println(tensao);
  delay(250);
}