#include "../includes/TipoDados.h"
#ifdef _WIN32
    void dormir(int tempo){
        Sleep(tempo);
    }
#endif


#ifdef __linux__
    void dormir(int tempo){
        usleep(tempo * 1000);
    }
#endif

void setPortugues(){
    SET_UTF8_CODEPAGE;
    setlocale(LC_ALL, "pt_PT.UTF-8");
}

int Aleatorio(int min, int max){
    int resultado = min + rand() % (max-min + 1);
    return resultado;
}

DataStruct gerarData(int anoMin, int anoMax){
    DataStruct data;
    data.ano = Aleatorio(anoMin, anoMax);
    data.mes = Aleatorio(1, 12);

    if((data.mes % 2 != 0 && data.mes < 8) || (data.mes >= 8 && data.mes % 2 == 0))
        data.dia = Aleatorio(1, 31);
    else if((data.mes % 2 == 0 && data.mes <= 8 && data.mes != 2) || (data.mes > 8 && data.mes % 2 != 0))
        data.dia = Aleatorio(1, 30);
    else if((data.mes == 2 && data.ano % 4 == 0))
        data.dia = Aleatorio(1, 29);
    else if((data.mes == 2 && data.ano % 4 != 0))
        data.dia = Aleatorio(1, 28);
    
    return data;
}

int DataAntesDepois(DataStruct d1, DataStruct d2){ // Se d1 for antes de d2 return 1
    if(d2.ano > d1.ano || 
        (d2.ano == d1.ano && 
        d2.mes > d1.mes) || 
        (d2.ano == d1.ano && 
        d2.mes == d1.mes && 
        d2.dia >=  d1.dia))
        return 1;
    return 0;
}

int checkIFfileExists(char *filepath){
    if(access(filepath, F_OK) != -1){
        return 1;
    } 
    return 0;
}

/* void *ThreadTempo(){
    while(1){
        time_t tempoTot;
        struct tm * timeinfo;
        time (&tempoTot);
        timeinfo = localtime (&tempoTot);
        printf("%d", timeinfo->tm_sec);
        //printf ( "Current local time and date: %s", asctime (timeinfo) );
        dormir(1000);
    }
} */

struct tm getCurrentTime(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm;
}


/* int fileExists(const char* path) {
  struct stat st;
  if (stat(path, &st) == 0) {
    return 1;
  }
  return 0;
}

int fileExistAll(){
  if(fileExists("data/bin/alunos.bin") && fileExists("data/bin/cursosdisciplina.bin") && fileExists("data/bin/disciplinas.bin") && fileExists("data/bin/permission.bin") && fileExists("data/bin/professores.bin") && fileExists("data/bin/regimes.bin") && fileExists("data/bin/salas.bin")){
    return 1;
  }
  else{
    return 0;
  }
} */


/* if (fileExistAll() == 0){
        printc("[red]Error[/red] Ficheiros não existem.\n\n");
        MenuFilesNovos();
    } */