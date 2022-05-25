#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int bomba = 13 ;//salida a la bomba pin 13
const int humedad = A0; //Se mide en el analógico 0
const int relay = 2;  //pin conectado relay

int sensor;
float temperatura;
float rta;

int led=10;
int sensorL;
int potenciometro;
int ilum;

const long A = 1000;     //Resistencia en oscuridad en KΩ
const int B = 4;        //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;       //Resistencia calibracion en KΩ



LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  
  Serial.begin(9600);
  pinMode(humedad, INPUT);
  pinMode(bomba, OUTPUT);
  pinMode(led,OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();

}

//void imp(int seco){
  
  //if(seco==1){

//  }
  
//}

void loop() {

  //Detector de luminosidad
  int seco = 1;
  sensorL= analogRead(A2);
  potenciometro=analogRead(A3);
  Serial.print(F("A0(V)"));
  Serial.print(F("\t"));
  Serial.print(F("A1(V)"));
  Serial.print(F("\n"));
  ilum = ((long)sensorL*A*10)/((long)B*Rc*(1024+sensorL)); 
  //mp(seco);
  Serial.print(potenciometro,1);
  Serial.print(F("\t"));
  Serial.print(sensorL,1);
  Serial.print(F("\n"));
  
  
  if(potenciometro > sensorL){
    digitalWrite(led,HIGH);
    Serial.print("led encendido");
    Serial.print("\n");

    }
  else{
    digitalWrite(led,LOW);
    Serial.print("led apagado");
    Serial.print("\n");

    }
    

   //Detector de temperatura
  
    for(int i=0;i<5;i++){
       sensor=analogRead(A1);
       temperatura=((5000.0*sensor)/1023.0)/10.0;
       rta= temperatura+rta;
       delay(500);
    }
    Serial.print("La temperatura es: ");
    Serial.print(rta/5.0,1);
    Serial.print("ºC");
    Serial.print("\n");

   


   //Detector de humedad
   
  int SensorValue = analogRead(humedad); //toma una muestra
  Serial.print(SensorValue); Serial.print(" - ");
  

  if(SensorValue >= 750){
    //Si la tierra está seca, regar durante 1 segundo y esperar a comprobar humedad otro segundo
 
    Serial.print(SensorValue);
    Serial.println("La tierra está seca, comienza el riego");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Inicia el riego");
    lcd.setCursor(0,0);
    lcd.print("T=");
    lcd.print(rta/5.0, 1);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(10,0);
    lcd.print("L=");
    lcd.print(ilum);
    lcd.display();
    
    digitalWrite(bomba, HIGH);
    delay(1000);
       
    digitalWrite(bomba,LOW);
    delay(2000);
    
  // Cursor en la 11° posición de la 2° fila
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
  else{
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Planta feliz");
    lcd.setCursor(0,0);
    lcd.print("T=");
    lcd.print(rta/5.0,1);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(10,0);
    lcd.print("L=");
    lcd.print(ilum);
    lcd.display();
    
    lcd.display();
    Serial.print(SensorValue);
  }
  rta = 0;
  //Si tierra no está seca, no riega y da valor de humedad.
  delay(1000);

  
}
