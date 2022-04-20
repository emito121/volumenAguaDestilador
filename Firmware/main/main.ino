#include "inicializaciones.h"

const int TriggerAd = 6;   //Pin digital
const int EchoAd = 5;   //Pin digital

long t1; //timepo que demora en llegar el eco
long d1; //distancia en centimetros
int contador = 0;

char restTime; //variable para controlar los eco

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(TriggerAd, OUTPUT); //pin como salida
  pinMode(EchoAd, INPUT);  //pin como entrada
  iniTimer2(); //inicio timer 2
  interrupts();//Habilito las interrupciones
}

void loop() {
  // put your main code here, to run repeatedly:
}

ISR(TIMER2_COMPA_vect)//Rutina interrupción Timer2, configurado a 10us
{
    if (contador == 2000) { //para que no se sature agrego 20ms entre ciclos
      if (restTime = 'OFF') { //si se debe enviar el eco
        digitalWrite(TriggerAd, HIGH);
        restTime = 'ON'; //para que de un descanso de 10us antes de leer el eco
      }
      if (restTime = 'ON') { //si se esta esperando el eco
        digitalWrite(TriggerAd, LOW);
        t1 = pulseIn(EchoAd, HIGH); //obtenemos el ancho del pulso
        d1 = t1 / 59;           //escalamos el tiempo a una distancia en cm
              Serial.print("DistanciaAd: ");
              Serial.print(d1);      //Enviamos serialmente el valor de la distancia
              Serial.print("cm");
              Serial.println();
              Serial.print(t1);
              Serial.print(volumenTanque(t1));
              Serial.println();
        contador = 0;
        restTime = 'OFF'; //si se debe enviar el eco
//        if (d1 < 60) {
//          digitalWrite(LEDAd, 1);
//          obstaculos = obstaculos | 0b00000001;
//          Serial.write(obstaculos);
//        }
      }
      }

    contador++; //suma al contador cada vez que se genera la interrupcion
    //conteo2++;

//    if (conteo2 == REINICIO){
//      obstaculos = 0b00000000;
//      conteo2 = 0;
//    }
  }

int volumenTanque(float tiempo){
  
  int ppVolumen = tiempo*-44493.80593087+131;
  
  return ppVolumen;
  }
