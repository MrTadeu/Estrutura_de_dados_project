#include "TipoDados.h"

extern int Aleatorio(int min, int max);

void escolherAleatorioVetor(void *vetor, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento){
    int indice = Aleatorio(0, tamanhoVetor);
    memcpy(ptrElemento, (char *)vetor + indice * tamanhoElemento, tamanhoElemento);
}

void mostrarFuncionario(void *funcionarioArg, int indentLevel){
    if(!funcionarioArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    FuncionarioStruct *funcionario = (FuncionarioStruct *) funcionarioArg;

    printf("\n%*sFUNCIONARIO INFO:\n%*sId Funcionario: %d\n%*sNome: %s\n%*sExperiencia: %d vendas\n%*sSalario: %f\n%*sAtraso medio: %f\n%*sBonus: %f", 
           indentLevel, "", indentLevel, "", funcionario->id, indentLevel, "", funcionario->nome, indentLevel, "", funcionario->experiencia, indentLevel, "", funcionario->salario, indentLevel, "", funcionario->atrasoMedio, indentLevel, "", funcionario->bonus);
}

void mostrarCaixa(void *caixaArg, int indentLevel){
    if(!caixaArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    CaixaStruct *caixa = (CaixaStruct *) caixaArg;
    
    printf("\n%*sCAIXA INFO:\n%*sId Caixa: %d\n%*sTempo de Espera: %d segundos", 
           indentLevel, "", indentLevel, "", caixa->id, indentLevel, "", caixa->tempoTotalEspera);
    mostrarFuncionario(caixa->funcionario, indentLevel + 1);
    mostrarLista(caixa->listaPessoas, mostrarCliente, indentLevel + 1);
}

void mostrarProduto(void *produtoArg, int indentLevel){
    if(!produtoArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    ProdutoStruct *produto = (ProdutoStruct *) produtoArg;

    printf("\n%*sPRODUTO INFO:\n%*sNome Produto: %s\n%*sId Produto: %d\n%*sPreco: %f\n%*sTempo de Compra: %f\n%*sTempo de Caixa: %f", 
           indentLevel, "", indentLevel, "", produto->nome, indentLevel, "", produto->id, indentLevel, "", produto->preco, indentLevel, "", produto->tempoCompra, indentLevel, "", produto->tempoCaixa);
}

void mostrarCliente(void *clienteArg, int indentLevel){
    if(!clienteArg){
        printf("\tError! Given info is NULL");
        return; 
    }
    ClienteStruct *cliente = (ClienteStruct *) clienteArg;
    
    printf("\n%*sCLIENTE INFO:\n\t%*sId Cliente: %d\n\t%*sNome: %s\n\t%*sData de Nascimento: %d/%d/%d\n\t%*sSaldo do Cartao: %.2f\n\t%*sTempo Estimado de Caixa: %d segundos\n\t%*sTempo Estimado de Fila: %d segundos\n\t%*sTempo de Atraso: %d segundos", 
           cliente->id, cliente->nome, cliente->dataNascimento.dia, cliente->dataNascimento.mes, cliente->dataNascimento.ano, cliente->saldoCartaoCliente,
           cliente->tempoEstimadoCaixa, cliente->tempoEstimadoFila, cliente->tempoAtraso);
    mostrarLista(cliente->listaProdutos, mostrarProduto, indentLevel + 1);
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


