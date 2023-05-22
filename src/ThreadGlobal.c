#include "../includes/TipoDados.h"


void *ThreadGlobal(){

    Global.PessoasAcabaramTempoDeCompra = criarLista();

    pthread_mutex_init(&PessoasAcabaramTempoDeCompraLock, NULL);
    pthread_mutex_init(&ClientesLock, NULL);
    
    while(Opcoes.lojaAberta == 1){
        if (Aleatorio(0, 100) <= Opcoes.probGerarPessoa){ //Gerar, simular tempo de compra e inserir pessoa na fila da melhor caixa
            ClienteStruct *pessoa = escolherCliente();
            
            if(pessoa){
                pthread_t thread;
                pthread_create(&thread, NULL, ThreadEsperaTempoCompra, (void *)pessoa);
                pthread_detach(thread); // para não ficar alocando memoria assim que acabar é como um pthread join
            }
            
            SelecionarCaixa();
        }
        dormir(1000);
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
        printf("\nLista de Produtos:");
         Elemento *Aux = cliente->listaProdutos->head;
        while(Aux){
            ProdutoStruct *x = (ProdutoStruct *)Aux->Info;
            printf("\t\nID: %d Nome: %s, QT: %dX, Preco: %.2f TCompra: %d TCaixa: %d",x->id, x->nome, x->quantidadeProdutosRepetidos, x->preco, x->tempoCompra, x->tempoCaixa );
            Aux = Aux->next; 
        }
    }
   
    dormir(cliente->tempoEstimadoCompra);
    if(Opcoes.VerTransacoes == 1){
        printf("\n\n%s acabou de comprar todos os produtos em %ds",cliente->nome, cliente->tempoEstimadoCompra);
    }
    pthread_mutex_lock(&PessoasAcabaramTempoDeCompraLock);
    AddElementoFim(Global.PessoasAcabaramTempoDeCompra, criarElemento(cliente));
    pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);

    return NULL;
}
/* ------------------------------#< Tempo De Espera da caixa >#------------------------------*/

void changeStateThreadGlobal(){
    if(Opcoes.lojaAberta == 0 && menuvalidarCaixaFuncionarios()){
        Opcoes.lojaAberta = 1;
        pthread_t GlobalThread;

        /* Elemento *CaixaElm = Global.caixas->head;
        for (int i = 0; i < Opcoes.numCaixasAbertasAranque; i++){
            CaixaStruct *caixa = (CaixaStruct *)CaixaElm->Info;
            if(n_funcionariosAtivos >= n_funcionarios){
                caixa->aberta = 0;
                caixa->funcionario = NULL;
            }
            else{
                caixa->aberta = 1;
                caixa->funcionario = (FuncionarioStruct *) escolherFuncionarios();
            }
            CaixaElm = CaixaElm->next; 
            if(CaixaElm == NULL){
                break;
            }
        } */

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

/* void *threadCalculoEstatistico(void* args){

} */

/* void *threadTempo(void *args){
    
} */