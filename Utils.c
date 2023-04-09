#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int Aleatorio(int min, int max){
    int resultado = min + rand() % (max-min + 1);
    return resultado;
}

char **separarPalavras(char *s, int *tamanho){

    int flag = 0, flagAux = 0;

    char Num_Indiv_String[100];
  
    char** vetorStrings = (char**) malloc(sizeof(char*) * 20);
    *tamanho = 0;

    for(int i = 0; i < strlen(s); i++){

        if(s[i] == ' '){
          flagAux = 0;

          if(flag == 1 && flagAux == 0){
            Num_Indiv_String[strlen(Num_Indiv_String)] = '\0';
            vetorStrings[(*tamanho)-1] = malloc(1 + sizeof(char) * strlen(Num_Indiv_String));
            strcpy(vetorStrings[(*tamanho)-1], Num_Indiv_String);
          }
          flag = 0; 
        }

        else{
          flagAux = 1;

          if(flag == 0 && flagAux == 1){
            (*tamanho)++;
            strcpy(Num_Indiv_String, "");
          }
          flag = 1;

          char temp[2] = {s[i], '\0'};
          strcat(Num_Indiv_String, temp);

          if(i == strlen(s)-1){
            Num_Indiv_String[strlen(Num_Indiv_String)] = '\0';
            vetorStrings[(*tamanho)-1] = malloc(1 + sizeof(char) * strlen(Num_Indiv_String));
            strcpy(vetorStrings[(*tamanho)-1], Num_Indiv_String);
          }
        }
    }
    return vetorStrings;
}


// Fazer mais funcoes aqui