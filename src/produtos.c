

void verProdutos(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    for (int i = 0; i < n_produtos; i++){
        if (Produtos[i].ativo == 1){
            printf("\nID: %d Nome: %s Preço: %.2f€\n", Produtos[i].id, Produtos[i].nome, Produtos[i].preco);
        }
    }
}

