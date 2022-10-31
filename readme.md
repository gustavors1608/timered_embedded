# Timered embeddad
![MIT License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge) 
![GitHub language count](https://img.shields.io/github/languages/count/gustavors1608/timered_embedded?style=for-the-badge) 
![Plataforma](https://img.shields.io/badge/Plataforma-ESP32-green?style=for-the-badge)


Biblioteca de temporização para arduino, esp32, esp8266 etc, sendo o principal objetivo eliminar os delays do codigo e simplificar o mesmo, deixando-o mais leve, sem interrupções, alem claro simplificar a manutenção, sendo uma biblioteca simples de se usar, onde basta você passar o nome da função, a cada quanto tempo deve ser chamada, e se deve se repetir após ser executada,(ser ciclica ,no caso de um blink por exemplo ou so executar só 1 vez no momento que se encerrar o timer).


bora dar um up no seu projeto?

## Features
Algumas caracteristicas do projeto:

- simples utilização, onde basta 3 comandos da lib. 
- altamente escalável.
- facilmente personalizavel.
- baixo uso de memoria flash, e de memoria ram (pode ser otimizado mais ainda de acordo com a utilização).
- alto controle sobre a execução, onde pode ser pausada (ou cancelada), pode tambem ser verificado quanto tempo falta para a proxima execução.
- metodos para cronometrar o seu proprio codigo, não sá funções de callback, onde retornam se ja passou o tempo que vocẽ definiu ou ainda não.


## Firmware example

Exemplo de utilização da lib, onde nesse caso realiza um ```helloWorld```, (realiza um blink no pino 2)


```cpp / arduino
/*****************************************************************************
 * @author Gustavo Rodolfo Stroschon                                         *
 * @date 31/10/2022
******************************************************************************/
//executa um blink no pino 2 a cada 200ms
#include "timered.cpp"

//objeto da lib para controlar um led
timered timer;

//funcao callback, fica invertendo o estado do led
void blink(){
  digitalWrite(2, !digitalRead(2));
}
void setup() {
  pinMode(2, OUTPUT);

  timer.time_funcion(blink,200,true);//configura a funcao callback, o intervalo de tempo e se deve ser ciclica
}

void loop() {
  timer.vrf_function(); //verifica se ja deve executar a func
}

```
Após realizar o upload do codígo acima para seu arduino ou esp, o led do pino 2 deve piscar a cada 200 milisegundos

Simples, não é mesmo?




## Author
Em caso de duvidas ou sugestões...

- [Github: @gustavors1608](https://www.github.com/gustavors1608)

- [Instagram: @gustavo_stroschon](https://www.instagram.com/gustavo_stroschon)
