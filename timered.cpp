

// requisitos:
/*
  objetivo: classe com funcoes de timer, onde seja possivel passar funcoes que podem ser chamadas a cada x tempo e tambem definir o inicio e verificacao se ja passou o tempo declarado
  metodos: set_time_end(intervalo, is_ciclic); //salva para daqui quanto tempo deve ser true quando verificar,e se deve ser uma chamada ciclica ou nao, ser chamada a cada x segundos ou somente 1 vez
           get_time_end() retorna o intervalo acima
           verify() //true ou false se ja passou ou nao do tempo acima
           
           e auxiliares:
           time_function(nome_função, intervalo, ciclica = true) //define a execucao de uma funcao  apartir dos itens acima
           vrf_function() //verifica se deve executar
*/
#include <Arduino.h>

class timered{
private:
    void (*_callback)(void);
    unsigned long _time_next = 0; //tempo de quando deve ser a proxima funcão
    unsigned long _time_interval = 0; //a cada quanto tempo
    bool _is_cyclic = true; // vai ficar re-executando?
    bool _is_run = true;//se tiver como false, pausa a execução ate virar true


public:
    timered(/* args */);
    ~timered();

    void set_time_end(unsigned long interval_ms, bool is_cyclic);
    unsigned long get_time_end(bool calculate_diference);
    bool verify();
    void can_execute(bool is_run); 

    void time_funcion(void (*name_callback)(void), unsigned long interval_ms, bool is_cyclic);
    void vrf_function();
};

timered::timered(/* args */){}
timered::~timered(){}

void timered::set_time_end(unsigned long interval_ms, bool is_cyclic){
    if(interval_ms <= 0){
        //dá não
        return;
    }

    this->_time_next = millis() + interval_ms;
    this->_time_interval = interval_ms;
    this->_is_cyclic = is_cyclic;
}

/// @brief retorna quanto tempo falta para a proxima execucao ou quando ela vai ser
/// @param calculate_diference define se deve subtrair o tempo atual para saber a diferença
unsigned long timered::get_time_end(bool calculate_diference){
    if (calculate_diference == true){
        unsigned long time_calcu = this->_time_next - millis();
        if(time_calcu > 4294900000){//quando dá estouro na var pois ja passou do tempo de verificação, a var retorna para seus valores altos, entao paramuda isso, pode atrasar ate 67 segundos que vai retornar zero ainda
            return 0;
        }else{
            return time_calcu;
        }
    }else{
        return this->_time_next;
    }
}

bool timered::verify(){
    if(this->_time_next <= millis()){
        //se ja passou
        if(_is_cyclic == true){ //re declara com os dados já passados anteriormente
            this->set_time_end(this->_time_interval, this->_is_cyclic);
        }
        return true;
    }else{
        return false;
    }
}



void timered::can_execute(bool is_run){
    this->_is_run = is_run;
}

void timered::time_funcion(void (*name_callback)(void), unsigned long interval_ms, bool is_cyclic){
    if (name_callback != __null){
        this->_callback = name_callback;
        this->set_time_end(interval_ms,is_cyclic);
    }
    //se for nulo n faz nada
}

void timered::vrf_function(){
    if(this->_is_run == true){
          
        if(this->verify() == true ){
            this->_callback();
        }
    }else{
        //pausada, entao vai ficar sempre adiando a execucao, vai ser sempre pra daqui x tempo, ate o momento que is run for true
        this->set_time_end(this->_time_interval, this->_is_cyclic);
    }

}