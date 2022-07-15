#include "inicializaciones.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int TriggerAd = 5;   //Pin digital
const int EchoAd = 6;   //Pin digital
const int rele = 13;
int corte_flag = 0; //iniciamos la bandera baja
int volumen_tanque = 0;
int volumen_corte = 100;
int volumen_histeresis = 80;

long t1; //timepo que demora en llegar el eco
long d1; //distancia en centimetros
int contador = 0;

char restTime; //variable para controlar los eco

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);//iniciailzamos la comunicación
  lcd.init();
  lcd.backlight();
  
  pinMode(TriggerAd, OUTPUT); //pin como salida
  pinMode(EchoAd, INPUT);  //pin como entrada
  pinMode(rele, OUTPUT);  //pin como salida
  digitalWrite(rele, HIGH);
  //iniTimer2(); //inicio timer 2
  //interrupts();//Habilito las interrupciones
  lcd.setCursor(0,0);
  lcd.print("Cargando...");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TriggerAd, HIGH);
  //restTime = 'ON'; //para que de un descanso de 10us antes de leer el eco
  delayMicroseconds(10);
  digitalWrite(TriggerAd, LOW);
  t1 = pulseIn(EchoAd, HIGH); //obtenemos el ancho del pulso
  d1 = t1 / 59;           //escalamos el tiempo a una distancia en cm
  if (d1 > 0){
    volumen_tanque = volumenTanque(t1);
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print(t1);
//    lcd.setCursor(0,1);
//    lcd.print("VOLUMEN: ");
//    lcd.print(volumen_tanque);
//    lcd.print("%");
    if ((volumen_tanque < volumen_histeresis) and (corte_flag == 0)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LLENANDO...");
//      lcd.print("TIEMPO: ");
//      lcd.print(t1);
//      lcd.print(" us");
      lcd.setCursor(0,1);
      lcd.print("VOLUMEN: ");
      lcd.print(volumen_tanque);
      lcd.print("%");
    }
    
    else if ((volumen_tanque >= volumen_corte) and (corte_flag == 0)){
      digitalWrite(rele, LOW);
      corte_flag = 1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DETENIDO!");
//      lcd.print("TIEMPO: ");
//      lcd.print(t1);
//      lcd.print(" us");
      lcd.setCursor(0,1);
      lcd.print("VOLUMEN: ");
      lcd.print(volumen_tanque);
      lcd.print("%");
    }

    else if ((volumen_tanque < volumen_histeresis) and (corte_flag == 1)){
      digitalWrite(rele, HIGH);
      corte_flag = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LLENANDO...");
//      lcd.print("TIEMPO: ");
//      lcd.print(t1);
//      lcd.print(" us");
      lcd.setCursor(0,1);
      lcd.print("VOLUMEN: ");
      lcd.print(volumen_tanque);
      lcd.print("%");
    }

    else if ((volumen_tanque >= volumen_corte) and (corte_flag == 1)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DETENIDO!");
//      lcd.print("TIEMPO: ");
//      lcd.print(t1);
//      lcd.print(" us");
      lcd.setCursor(0,1);
      lcd.print("VOLUMEN: ");
      lcd.print(volumen_tanque);
      lcd.print("%");
    }

     else if ((volumen_tanque < volumen_corte) and (volumen_tanque >= volumen_histeresis) and (corte_flag == 1)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DETENIDO!");
//      lcd.print("TIEMPO: ");
//      lcd.print(t1);
//      lcd.print(" us");
      lcd.setCursor(0,1);
      lcd.print("VOLUMEN: ");
      lcd.print(volumen_tanque);
      lcd.print("%");
    }
     else if ((volumen_tanque < volumen_corte) and (volumen_tanque >= volumen_histeresis) and (corte_flag == 0)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LLENANDO...");
//      lcd.print("TIEMPO: ");
//      lcd.print(t1);
//      lcd.print(" us");
      lcd.setCursor(0,1);
      lcd.print("VOLUMEN: ");
      lcd.print(volumen_tanque);
      lcd.print("%");
    }
    delay(3000);
    }
    
}

int volumenTanque(float tiempo){
  
  int ppVolumen = tiempo*-0.023581953272125786+131.91744660427165;
  
  return ppVolumen;
  }
