#include "TipoDados.h"

extern int Aleatorio(int min, int max);

void escolherAleatorioVetor(void *vetor, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento){
    int indice = Aleatorio(0, tamanhoVetor);
    memcpy(ptrElemento, (char *)vetor + indice * tamanhoElemento, tamanhoElemento);
}










DataStruct gerarDataValidaAleatoria(DataStruct data, int anoMin, int anoMax){

    data.ano = Aleatorio(anoMin, anoMax);
    data.mes = Aleatorio(1, 12);

    if(data.mes % 2 != 0 && data.mes < 8 || data.mes >= 8 && data.mes % 2 == 0)
        data.dia = Aleatorio(1, 31);
    else if(data.mes % 2 == 0 && data.mes <= 8 && data.mes != 2 || data.mes > 8 && data.mes % 2 != 0)
        data.dia = Aleatorio(1, 30);
    else if(data.mes == 2 && data.ano % 4 == 0)
        data.dia = Aleatorio(1, 29);
    else if(data.mes == 2 && data.ano % 4 != 0)
        data.dia = Aleatorio(1, 28);
    
    return data;
}

int DataAntes_Depois(DataStruct d1, DataStruct d2){ // Se d1 for antes de d2 return 1
    if(d2.ano > d1.ano || 
        (d2.ano == d1.ano && 
        d2.mes > d1.mes) || 
        (d2.ano == d1.ano && 
        d2.mes == d1.mes && 
        d2.dia >=  d1.dia))
        return 1;
    return 0;
}


