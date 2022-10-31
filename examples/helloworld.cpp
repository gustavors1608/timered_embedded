//executa um blink no pino 2 a cada 200ms
#include <Arduino.h>
#include "timered.cpp"

//objeto da lib para controlar um led
timered timer;

//funcao callback, fica invertendo o estado do led
void blink(){
  digitalWrite(2, !digitalRead(2));
}
void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  timer.time_funcion(blink,200,true);//configura a funcao callback, o intervalo de tempo e se deve ser ciclica
}

void loop() {
  timer.vrf_function(); //verifica se ja deve executar a func
  Serial.println(timer.get_time_end(true)); //mostra quanto tempo falta para executar
  delay(10);
}