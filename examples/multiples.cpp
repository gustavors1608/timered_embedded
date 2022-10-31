//executa um blink no pino 2 a cada 200ms
#include <Arduino.h>
#include "timered.cpp"

//objeto da lib para controlar um led
timered led;
timered notify;

//funcao callback, fica invertendo o estado do led
void blink(){
  digitalWrite(2, !digitalRead(2));
  if(digitalRead(2) == false){
    Serial.println(" Apaguei");
  }
}

//funcao callback, envia mensagem
void send_mensage(){
  Serial.print("falta ");
  Serial.print(led.get_time_end(true));
  Serial.println(" ms para o led mudar seu estado ");
}
void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  //configura as funcoes de callback, o intervalo de tempo e se deve ser ciclica
  led.time_funcion(blink,2000,true);
  notify.time_funcion(send_mensage,1000, true);
}

void loop() {
  led.vrf_function(); //verifica se ja deve executar a func
  notify.vrf_function();
}