#include "../includes/TipoDados.h"

void *ThreadGlobal(){

    while(1){
        
    }
}

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

static int CaixaIndex(Lista *caixa){ // o melhor index que tem o menor numero de clientes
    int pos = 0, index = 0;
    Elemento *caixaAux = caixa->head;
    Elemento *menor = caixaAux;

    CaixaStruct *caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
    CaixaStruct *menorInfo = (CaixaStruct *)menor->Info;
    if (menorInfo->aberta == 0){ // se o primeiro caixa estiver fechado, procura o primeiro aberto
        menorInfo = caixaAuxInfo;
        index = pos;
        while (menorInfo->aberta == 0 && caixaAux){ // NÃO ESQUECER DE VERIFICAR SE TODAS ESTÃO FECHADAS TRATAR DO ASSUSNTO
            caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
            if(caixaAuxInfo->aberta == 1){
                menorInfo = caixaAuxInfo;
                index = pos;
            }
            caixaAux = caixaAux->next;
            pos++;
        }
    }
    
    pos = 0;
    while(caixaAux){ // procura o caixa com menos clientes
        caixaAuxInfo = (CaixaStruct *)caixaAux->Info;
        if(caixaAuxInfo->tempoTotalEspera < menorInfo->tempoTotalEspera && caixaAuxInfo->aberta == 1){
            menorInfo = caixaAuxInfo;
            index = pos;
        }
        caixaAux = caixaAux->next;
        pos++;
    }
    return index;
}

static void SelecionarCaixa(Lista *caixas, Elemento *cliente){ // seleciona (adiciona) a melhor caixa para o cliente
    int index = CaixaIndex(caixas);
    Elemento *caixaAux = caixas->head;
    while(index){
        caixaAux = caixaAux->next;
        index--;
    }
    CaixaStruct *caixaAuxInfo = (CaixaStruct* )caixaAux->Info;
    AddElementoFim(caixaAuxInfo->listaPessoas, cliente);
}

/* ------------------------------#< SELEÇÃO DE CAIXA >#------------------------------*/

void *ThreadCaixa(void *arg){
    CaixaStruct *caixa = (CaixaStruct *)arg;
    while(1){
    /*     if(caixa->aberta == 1){
            if(caixa->listaPessoas->quantidadeElementos > 0){
                Elemento *cliente = caixa->listaPessoas->head;
                ClienteStruct *clienteInfo = (ClienteStruct *)cliente->Info;
                if(clienteInfo->tempoAtendimento == 0){
                    caixa->tempoTotalEspera += clienteInfo->tempoEspera;
                    caixa->tempoTotalAtendimento += clienteInfo->tempoAtendimento; */
    }
}

void criarListaThreads(Lista *listaThreads){
    pthread_t *thread = (pthread_t *)malloc(sizeof(pthread_t));
    pthread_create(&thread[11], NULL, ThreadCaixa, NULL);
    AddElementoFim(listaThreads, criarElemento(thread));
}

void criarCaixas(Lista *caixas){

}