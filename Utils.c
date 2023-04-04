#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Aleatorio(int min, int max){
    int resultado = min + rand() % (max-min + 1);
    return resultado;
}

// Fazer mais funcoes aqui