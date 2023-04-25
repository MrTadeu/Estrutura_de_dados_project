#include <stdio.h>
#include <stdlib.h>

void main(){
    char frase[100];
    printf("Digite uma frase com espacos: ");
    scanf("%[^\n]", frase);
}