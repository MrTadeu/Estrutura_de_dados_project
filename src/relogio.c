#include "../includes/TipoDados.h"
#ifdef _WIN32
    void dormir(){
        Sleep(1000);
    }   
#endif


#ifdef __linux__
    void dormir(){
        usleep(1000000);
    }
#endif


void *ThreadTempo(){
    while(1){
        time_t tempoTot;
        //struct tm * timeinfo;
        time (&tempoTot);
        timeinfo = localtime (&tempoTot);
        //printf ( "Current local time and date: %s", asctime (timeinfo) );
        dormir();
    }
}

  