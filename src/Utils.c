#include "../includes/TipoDados.h"
#ifdef _WIN32
    void dormir(int tempo){
        Sleep((int)(tempo * Opcoes.multiplicadorTempo));
    }
    void bufferclear(){
        fflush(stdin);
    }
#endif

#ifdef __linux__
    void dormir(int tempo){
        usleep((int)(tempo * 1000 * Opcoes.multiplicadorTempo));
    }
    #include <ctype.h>
    #include <stdio_ext.h>

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
#ifndef _WIN32
    #ifndef __linux__
        void bufferclear(){
            char buffer[256];
            fgets(buffer, 256, stdin);
        }
    #endif
#endif

void setPortugues(){
    SET_UTF8_CODEPAGE;
    setlocale(LC_ALL, "pt_PT.UTF-8");
}

int Aleatorio(int min, int max){
    int resultado = min + rand() % (max-min + 1);
    return resultado;
}

/* scanfs("%d", id, "Insira o ID do funcionario que pretende editar: ", "Apenas pode inserir números inteiros!\n"); */
void scanfs(const char* formato, void *DataScanf, char *MensagemRepitida, char *AvisoError){
    int invalid = 0;
    do{
        printc("\n%s", MensagemRepitida);
        bufferclear();
        invalid = scanf(formato, DataScanf);
        invalid != 1 ? printc("[red]%s[/red]\n", AvisoError),  bufferclear() : (void)NULL;
    }while(invalid != 1);
}

/* scanfv("%d", &data, "Enter an integer between 10 and 20: ", "Invalid input. Please try again.\n", validateRange, 0, 100); */
void scanfv(const char* formato, void *DataScanf, char *MensagemRepitida, char *AvisoError, int (*validator)(void*, void*), ...){
    int invalid = 0;
    do{
        va_list args;
        va_start(args, validator);
        scanfs(formato, DataScanf, MensagemRepitida, AvisoError);
        invalid = validator(DataScanf, (void*)&args);
        if(!invalid)
            printc("[red]%s[/red]\n", AvisoError);
        va_end(args);
    }while(!invalid);
}

int validateIsAlphabetic(void* DataScanf, void *args) {
    args = args;
    char *str = (char*)DataScanf;
    size_t i = 0;
    if (strlen(str) > 1) {
        while (isalpha(str[i]) || str[i] == ' ') {
            i++;
        }
        if (i == strlen(str)) return 1;
        else {
            printc("[red]Apenas pode inserir letras!\n[/red]");
            return 0;
        }
    }
    printc("[red]O nome tem de ter pelo menos 2 letras\n[/red]");
    return 0;
}

int validateRange(void* DataScanf, void *args) {
    int lower = va_arg(*(va_list*) args, int);
    int upper = va_arg(*(va_list*) args, int);
    int value = *(int*)DataScanf;
    if (value >= lower && value <= upper) {
        return 1;
    }
    return 0;
}

int validateRangeFloat(void* DataScanf, void *args) {
    float lower = (float) va_arg(*(va_list*) args, double);
    float upper = (float) va_arg(*(va_list*) args, double);
    float value = *(float*)DataScanf;
    if (value >= lower && value <= upper) {
        return 1;
    }
    return 0;
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

int generateID(int (*checkIfExists)(int)){
    int id = 0;
    do{
        id = rand() % 10000000;
    }while(checkIfExists(id) != -1);
    return id;
}

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

int validarData(DataStruct date, int minAno, int maxAno) {
    if (date.ano < minAno || date.ano > maxAno) {
        return 0;
    }
    if (date.mes < 1 || date.mes > 12) {
        return 0;
    }
    int daysInMonth = 31;
    
    if (date.mes == 4 || date.mes == 6 || date.mes == 9 || date.mes == 11) {
        daysInMonth = 30;
    } else if (date.mes == 2) {
        if (date.ano % 4 == 0 && (date.ano % 100 != 0 || date.ano % 400 == 0)) {
            daysInMonth = 29;
        } else {
            daysInMonth = 28;
        }
    }

    if (date.dia < 1 || date.dia > daysInMonth) {
        return 0;
    }

    return 1;
}

void formatTime(long long milliseconds, char* string){// STRING SIZE[9]
    time_t segundos = milliseconds / 1000;
    struct tm* time = localtime(&segundos);

    if (time->tm_hour > 0) {
        strftime(string, 9, "%H:%M", time);
    } else if (time->tm_min > 0) {
        strftime(string, 9, "%Mm %Ss", time);
    } else if (time->tm_sec == 0) {
        snprintf(string, 9, "%lldms", milliseconds);
    } else {
        snprintf(string, 9, "%ds", time->tm_sec);
    }
}

DataStruct formatTimeStruct(long long milliseconds){
    time_t segundos = milliseconds / 1000;
    struct tm* time = localtime(&segundos);

    DataStruct formattedTime;
    formattedTime.dia = time->tm_mday;
    formattedTime.mes = time->tm_mon + 1; //1-12
    formattedTime.ano = time->tm_year + 1900; // começa em 1970
    formattedTime.hora = time->tm_hour;
    formattedTime.minuto = time->tm_min;
    formattedTime.segundo = time->tm_sec;

    return formattedTime;
}

long long getCurrentTimeMillisecounds(){
    struct timeval tv; 
    gettimeofday(&tv, NULL); 
    long long milliseconds = ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
    return milliseconds;
}