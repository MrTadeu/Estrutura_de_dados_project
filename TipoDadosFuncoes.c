#include "TipoDados.h"

extern int Aleatorio(int min, int max);

void escolherAleatorioVetor(void *vetor, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento){
    int indice = Aleatorio(0, tamanhoVetor);
    memcpy(ptrElemento, (char *)vetor + indice * tamanhoElemento, tamanhoElemento);
}

void mostrarFuncionario(void *funcionarioArg){
    if(!funcionarioArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    FuncionarioStruct *funcionario = (FuncionarioStruct *) funcionarioArg;

    printf("FUNCIONARIO INFO:\n\tNome: %s\n\tId: %d\n\tExperiencia: %d vendas\n\tSalario: %f\n\tAtraso medio: %f\n\tBonus: %f", funcionario->nome, funcionario->id, funcionario->experiencia, funcionario->salario, funcionario->atrasoMedio, funcionario->bonus);
}
void mostrarCaixa(void *caixaArg){
    if(!caixaArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    CaixaStruct *caixa = (CaixaStruct *) caixaArg;
    
    printf("\nCAIXA INFO:\n\tId Caixa: %d\n\tTempo de Espera: %d segundos", caixa->id, caixa->tempoTotalEspera);
    mostrarFuncionario(caixa->funcionario);
    mostrarLista(caixa->listaPessoas);

}
void mostrarProduto(void *produto){

}
void mostrarCliente(void *cliente){

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


