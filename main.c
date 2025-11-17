#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


//STRUCT PARA BMP
typedef struct
{
    
}BMP_HEADER;

typedef struct
{
    
}PIXEL;


void MENU(char *c) {          
    printf("\n---------------------------------------------");
    printf("\n    ███████████  ██████   ██████ ███████████ ");
    printf("\n   ▒▒███▒▒▒▒▒███▒▒██████ ██████ ▒▒███▒▒▒▒▒███");
    printf("\n    ▒███    ▒███ ▒███▒█████▒███  ▒███    ▒███");
    printf("\n    ▒██████████  ▒███▒▒███ ▒███  ▒██████████ ");
    printf("\n    ▒███▒▒▒▒▒███ ▒███ ▒▒▒  ▒███  ▒███▒▒▒▒▒▒  ");
    printf("\n    ▒███    ▒███ ▒███      ▒███  ▒███        ");
    printf("\n ██ ███████████  █████     █████ █████       ");
    printf("\n▒▒ ▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒     ▒▒▒▒▒ ▒▒▒▒▒        ");
    printf("\n DAVI SANT'ANNA VIEIRA - 4324 - 2025         ");
    printf("\n");
    printf("\n1) Selecionar Imagem");
    printf("\n2) Separar Cores da Imagem '%s'",c);
    printf("\n3) Cortar Imagem '%s'",c);
    printf("\n4) Sair");   
    printf("\n---------------------------------------------");                                                                                                                                   
}

void Troca_Endereco(char *c) {
    printf("\nEndereço atual: %s",c);
    printf("\nDigite Novo Endereço: ");
    scanf("%s", c);
    printf("Endereço atual Atualizado: %s",c);
    printf("\n");
} //gg easy bro.

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
        MENU(endereco);
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