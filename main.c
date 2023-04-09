#include "TipoDados.h"
#include "ListaLigada.h"


int main(){
    int totalClientes;
    printf("teste");
    ClienteStruct *DadosPessoa = (ClienteStruct *) importarClientes(&totalClientes, "DadosFornecidos/clientes.csv");
    printf("%s", DadosPessoa[0].nome);
    
    return 0;
}