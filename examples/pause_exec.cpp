
#include <Arduino.h>
#include "timered.cpp"

bool flag_execute = true;

//objeto da lib para controlar um led
timered led;
timered notify;

//funcao callback, fica invertendo o estado do led
void blink(){
  digitalWrite(2, !digitalRead(2));
}

//funcao callback, envia mensagem
void send_mensage(){
  led.can_execute(flag_execute);
  flag_execute = !flag_execute;
}
void setup() {
  pinMode(2, OUTPUT);

  //configura as funcoes de callback, o intervalo de tempo e se deve ser ciclica
  led.time_funcion(blink,100,true);
  notify.time_funcion(send_mensage,1000, true);
}

void loop() {
  led.vrf_function(); //verifica se ja deve executar a func
  notify.vrf_function();
}