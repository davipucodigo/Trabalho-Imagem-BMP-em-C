#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdint.h>

//DEFINES OPÇÕES DO MENU
#define EDITAR_ENDERECO  1
#define SEPARAR_CORES  2
#define CORTAR  3
#define SAIR 4
#define VAZIO 0

//STRUCT PARA BMP
typedef struct
{
    char magic[2];
    uint32_t file_size;
    uint16_t reserved1;  //NÃO USA
    uint16_t reserved2;  //NÃO USA

    uint32_t offset;
    uint32_t DIBhdr_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes; //NÃO USA
    uint16_t bits_per_px;
    uint32_t compress; //NÃO USA
    uint32_t x_resolution;  //NÃO USA
    uint32_t y_resolution;  //NÃO USA
    uint16_t colors;  //NÃO USA
    uint32_t important_colors;  //NÃO USA
}BMP_HEADER;

typedef struct
{
   char red, green, blue; 
}pixel;


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

    //Loop do Programa;
    while (loop) {

        //Logica de Seleção de Opções;
        MENU(endereco);
        int op;
        printf("\nDigite o N° da Opção desejada: ");
        scanf("%d", &op);
        int op;

        switch (op) {
            case EDITAR_ENDERECO: Troca_Endereco(endereco); break;
            case SEPARAR_CORES: Separar_Cores_Imagem(endereco); break;
            case CORTAR: Cortar_Imagem(endereco); break;
            case SAIR: loop = 0; break;
            default: op = VAZIO; break;
        }
        
    }

    return 0;
}