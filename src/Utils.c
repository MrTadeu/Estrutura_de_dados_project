#include "../includes/TipoDados.h"
#ifdef _WIN32
    void dormir(int tempo){
        Sleep(tempo);
    }
    void bufferclear(){
        fflush(stdin);
    }
#endif


#ifdef __linux__
    void dormir(int tempo){
        usleep(tempo * 1000);
    }
    #include <ctype.h>

    void strupr(char *str) {
        size_t i = 0;
        while (str[i]) {
            str[i] = toupper(str[i]);
            i++;
        }
    }

    void bufferclear(){
        __fpurge(stdin);
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

int generateID(int (*checkIfExists)(int), int x){
    int id = 0;
    srand(time(NULL));
    do{
        id = rand() % 1000000;
    }while(checkIfExists(id) != x);
    return id;
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


int minimo(int a, int b, int c) {
    int menor = a;

    if (b < menor)  menor = b;
    if (c < menor) menor = c;
    
    return menor;
}

int PesquisaParecido(char *str1, char *str2){// Levenshtein Distance é para ver a distancia de diferença entre as palavras não esquecer de po-las em maiúsculas (para a minha comparaçao dar certo)!
    int **matriz = calloc(strlen(str1) + 1, sizeof(int*));
    int custo;
    char *Temp1 = malloc(sizeof(char) * (strlen(str1) + 1)), *Temp2 = malloc(sizeof(char) * (strlen(str2) + 1));
    strcpy(Temp1, str1);
    strcpy(Temp2, str2);
    strupr(Temp1);
    strupr(Temp2);

    for (size_t i = 0; i < strlen(str1) + 1; i++){
        matriz[i] = calloc(strlen(str2) + 1, sizeof(int));
    }
    for (size_t i = 0; i < strlen(str1) + 1; i++){
        matriz[i][0] = i;
    }
    for (size_t i = 0; i < strlen(str2) + 1; i++){
        matriz[0][i] = i;
    }
    for (size_t i = 1; i < strlen(str1) + 1; i++){
        for (size_t j = 1; j < strlen(str2) + 1; j++){
            if (Temp1[i] == Temp2[j]) {
                custo = 0;
            } else {
                custo = 1;
            }

            matriz[i][j] = minimo(matriz[i-1][j] + 1, matriz[i][j-1] + 1, matriz[i-1][j-1] + custo);
        }
    }
    int resultado = matriz[strlen(str1)][strlen(str2)];
    for (size_t i = 0; i < strlen(str1) + 1; i++){
        free(matriz[i]);
    }
    free(Temp1);
    free(Temp2);
    free(matriz);
    return resultado;
}

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