#include "../includes/TipoDados.h"

pthread_mutex_t listaLock;

void *ThreadGlobal(){
    srand(time(NULL));
    

    Global.PessoasAcabaramTempoDeCompra = criarLista();
    Global.PessoasAtendidas = criarLista();

    /* ClienteStruct *clienteAux; */
    pthread_mutex_init(&listaLock, NULL);
    int x  = 0;
    while(Opcoes.lojaAberta == 1){
        if (Aleatorio(0, 100) <= Opcoes.probGerarPessoa){ //Gerar, simular tempo de compra e inserir pessoa na fila da melhor caixa

            for (; x < 4000; x++){
                ClienteStruct *pessoa = escolherCliente();
                if(pessoa){
                    pthread_t thread;
                    pthread_create(&thread, NULL, ThreadEsperaTempoCompra, (void *)pessoa);
                    pthread_detach(thread);
                }
            }
          
            
            SelecionarCaixa();
        }
        if(Global.PessoasAtendidas->quantidadeElementos > 0){ //Libertar pessoa
            printc("\n\n\t[green]PESSOA LIBERTADA[/green]\n");
            DesocuparCliente((ClienteStruct *)Global.PessoasAtendidas->head->Info);
            destruirElemento(RemElementoInicio(Global.PessoasAtendidas), destruirCliente);
        }
        dormir(100);
    }
    return NULL;
}

/* ------------------------------#< Tempo De Espera da caixa >#------------------------------*/
void *ThreadEsperaTempoCompra(void *pessoa){
    ClienteStruct *cliente = (ClienteStruct *)pessoa;
    
    if(cliente->nome == NULL){
        printf("\n\n\t[red]ERRO: Pessoa Nula[/red]\n");
        exit(1);
    }  
    if(Opcoes.VerTransacoes == 1){
        printf("\n\nPessoa Gerada: ");
        printf("\nNome: %s", cliente->nome);
        printf("\nTempo de Compra: %d", cliente->tempoEstimadoCompra);
        printf("\nTempo de Estimado Fila: %d", cliente->tempoEstimadoFila);
        printf("\nTempo de Estimado Caixa: %d", cliente->tempoEstimadoCaixa);
        printf("\nTempo de tempoAtraso: %d", cliente->tempoAtraso);
        /* printf("\nLista de Produtos:");
         Elemento *Aux = cliente->listaProdutos->head;
        while(Aux){
            ProdutoStruct *x = (ProdutoStruct *)Aux->Info;
            printf("\t\nID: %d Nome: %s, Preco: %.2f TCompra: %.2f TCaixa: %.2f",x->id, x->nome, x->preco, x->tempoCompra, x->tempoCaixa );
            Aux = Aux->next; 
        } */
    }
   
    dormir(cliente->tempoEstimadoCompra * 1000);
    if(Opcoes.VerTransacoes == 1){
        printf("\n\n%s acabou de comprar todos os produtos em %ds",cliente->nome, cliente->tempoEstimadoCompra);
    }
    pthread_mutex_lock(&listaLock);
    AddElementoFim(Global.PessoasAcabaramTempoDeCompra, criarElemento(cliente));
    pthread_mutex_unlock(&listaLock);
    return NULL;
}
/* ------------------------------#< Tempo De Espera da caixa >#------------------------------*/

void changeStateThreadGlobal(){
    if(Opcoes.lojaAberta == 0){
        Opcoes.lojaAberta = 1;
        pthread_t GlobalThread;

        if (pthread_create(&GlobalThread, NULL, ThreadGlobal, NULL) != 0){
            printc("[red]Erro[/red] ao criar thread global!!!\n");
            exit(1);
        } 
        
        /* pthread_join(GlobalThread, NULL); */// <--- Nao dar join porque a thread global vai ficar sempre a correr
    }
    else if(Opcoes.lojaAberta == 1){
        Opcoes.lojaAberta = 0;
    }
}