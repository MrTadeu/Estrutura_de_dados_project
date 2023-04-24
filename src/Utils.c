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

void AtualizarDadosTemposCaixa(CaixaStruct *lista){
    if (!lista) return;
    Elemento *aux = lista->listaPessoas->head;
    while (aux){
        ClienteStruct *cliente = (ClienteStruct *)aux->Info;
        if (cliente->tempoEstimadoCaixa > 0){
            cliente->tempoEstimadoCaixa--;
            lista->tempoTotalEspera--;
        }
        aux = aux->next;
    }
    
}

void temporizador(CaixaStruct *caixa, ClienteStruct *clientes){
    if (!caixa || !clientes) return;
    //Atualizar dados
    /* dddddddddddddddddddddddddddddddddddddddddddd */
    
    clientes->tempoEstimadoFila = 0;
    int tempo = clientes->tempoEstimadoCaixa + clientes->tempoAtraso;

    //Adicionar no ficheiro Histórico
    /*   DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD    FUNÇÃO   DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD */

    while (tempo >= 0){
        if (clientes->tempoAtraso < 0){
            clientes->tempoEstimadoCaixa--;
            caixa->tempoTotalEspera--;
            if (tempo == 0){
                caixa->tempoTotalEspera -= clientes->tempoEstimadoCaixa;
                clientes->tempoEstimadoCaixa = 0;
                break;
            }
        }
        tempo--;
        dormir(1000);
        if (clientes->tempoAtraso > 0){
            if (clientes->tempoAtraso != 0){
                clientes->tempoAtraso--;
                continue;
            }
            clientes->tempoEstimadoCaixa--;
            caixa->tempoTotalEspera--;
        }
        
    }
    
    //Remover da fila
    RemElementoInicio(caixa->listaPessoas);

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