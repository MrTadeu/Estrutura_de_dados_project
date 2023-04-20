#include "../includes/Utils.h"

int Aleatorio(int min, int max){
    int resultado = min + rand() % (max-min + 1);
    return resultado;
}
