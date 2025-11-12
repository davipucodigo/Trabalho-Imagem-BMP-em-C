#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void Troca_Endereco(char *c) {
    
    printf("\nEndereço atual: %s",c);
    printf("\nDigite Novo Endereço: ");
    scanf("%s", c);
    printf("Endereço atual Atualizado: %s",c);
    printf("\n");
}

void Separar_Cores_Imagem (char *c) {
    printf("%s",c);
}

void Cortar_Imagem(char *c) {

}

int main () {

    //Config
    setlocale(LC_ALL,"Portuguese");

    //Variaveis
    char endereco[50] = "images/";
    int loop = 1;

    enum OPCOES {
        VAZIO = 0,
        EDITAR_ENDERECO = 1,
        SEPARAR_CORES = 2,
        CORTAR = 3,
        SAIR = 4
    } OPCOES = VAZIO;

    //Loop do Programa;
    while (loop) {

        //Logica de Seleção de Opções;
        int op;
        printf("\nDigite o N° da Opção desejada: ");
        scanf("%d", &op);
        OPCOES = op;

        switch (OPCOES) {
        case EDITAR_ENDERECO: Troca_Endereco(endereco); break;

        case SEPARAR_CORES: Separar_Cores_Imagem(endereco); break;

        case CORTAR: Cortar_Imagem(endereco); break;

        case SAIR: loop = 0; break;

        default: OPCOES = VAZIO; break;
        }
        
    }

    return 0;
}