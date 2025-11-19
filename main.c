#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdint.h>

//COMPILANDO na marra
// gcc main.c -o output/main

//DEFINES OPÇÕES DO MENU
#define EDITAR_ENDERECO  1
#define SEPARAR_CORES  2
#define CINZA_ATE_CERTO_PONTO 3
#define CORTAR  4
#define ASCII_ART_APARTIR_DA_IMAGEM 5
#define SAIR 6
#define VAZIO 0

//STRUCT PARA BMP
typedef struct{
    char magic[2]; //Identificação do arquivo BMP
    uint32_t file_size;
    uint16_t reserved1;  //NÃO USA
    uint16_t reserved2;  //NÃO USA

    uint32_t offset_of_img_data; // Ponto de partida para os pixels
    uint32_t DIBhdr_size; //Numero em byted deste ponto até o final do cabeçalho.
    uint32_t width; // Numero de pixels width
    uint32_t height; // Numero de pixels height
    uint16_t planes; //NÃO USA
    uint16_t bits_per_px; //quanto tem cada pixel em bits
    uint32_t compress; //NÃO USA
    uint32_t img_size_bytes; //Numero total de bytes da imagem
    uint32_t x_resolution;  //NÃO USA
    uint32_t y_resolution;  //NÃO USA
    uint16_t colors;  //NÃO USA
    uint32_t important_colors;  //NÃO USA
}__attribute__((packed)) BMP_HEADER;

typedef struct{
   char red, green, blue; 
}BMP_COLOR_TABLE;

//FUNÇÂO VERIFICA PADDING
int padding_teste(BMP_HEADER *p) {
    //Verificando paddings
    int verifica_padding = (p->width * 3)%4;
    return verifica_padding;
}

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
    printf("\n1) Selecionar Imagem ");
    printf("\n2) Separar Cores da Imagem '%s'",c);
    printf("\n3) Cinza até um ponto '%s'",c);
    printf("\n4) Cortar Imagem '%s'",c);
    printf("\n5) ASCII_ART_GERAR '%s'",c);
    printf("\n6) Sair");   
    printf("\n---------------------------------------------");                                                                                                                                   
}

void trocaEndereco(char *c){
    printf("\nEndereço atual: %s",c);
    printf("\nDigite Novo Endereço: ");
    scanf("%s", c);
    printf("Endereço atual Atualizado: %s",c);
    printf("\n");
}

void separarCores(char *c){
    printf("separar cores da imagem\n");
    FILE *lendo;
    BMP_HEADER img_header;
    BMP_COLOR_TABLE pixels;
    lendo = fopen(c, "rb");
    
    // //vai guardar em img_header o que ler
    fread(&img_header, sizeof(BMP_HEADER), 1, lendo);
    fread(&pixels, sizeof(BMP_COLOR_TABLE), 1, lendo);
    
    printf("\nmagic: %c%c", img_header.magic[0], img_header.magic[1]);
    printf("\nmagic: %c%c%c", img_header.magic[2], img_header.magic[3], img_header.magic[4]);
    printf("\nFile size: %i", img_header.file_size);
    printf("\nAltura: %d", img_header.height);
    printf("\nLargura: %d", img_header.width);
    
    fclose(lendo);
}

// FUNÇÂO PARA SEPARAR CORES
void cinzAteCertoPonto(char *c, int *x, int *y) {

    BMP_HEADER img_header_lido;
    BMP_HEADER img_header_escrita;

    //BLOCO DE LEITURA e BLOCO de ESCRITA
    FILE *LENDO;
    FILE *ESCREVENDO;
    
    //ESCREVENDO = fopen("saidas/CinzaAteCertoPonto.bmp","wb");
    LENDO = fopen(c,"rb");
    //======================== BLOCO LOGICA EDIÇÂO BMP ============================|
        fread(&img_header_lido, sizeof(BMP_HEADER),1,LENDO);

        //Printa padding testado.
        printf("width: %d | Padding: %d",img_header_lido.width,padding_teste(&img_header_lido));
        
        //Atualizando HEADER
        //img_header_escrita = img_header_lido;
        //fwrite(&img_header_escrita,sizeof(BMP_HEADER),1,ESCREVENDO);
    
    //=============================================================================|
    fclose(LENDO);
    //fclose(ESCREVENDO);
}

int main(){

    //Config
    setlocale(LC_ALL,"Portuguese");

    //Variaveis
    char endereco[50] = "images/bmp_24.bmp";
    int loop = 1;

    //Loop do Programa;
    while(loop){

        //Logica de Seleção de Opções;
        MENU(endereco);
        int op;
        printf("\nDigite o N° da Opção desejada: ");
        scanf("%d", &op);
        switch(op){
            //====================================================================|
            case EDITAR_ENDERECO: 
                trocaEndereco(endereco); 
            break;

            //====================================================================|
            case SEPARAR_CORES:
                separarCores(endereco);
            break;

            //====================================================================|
            case CINZA_ATE_CERTO_PONTO:
                int x = 0;
                int y = 0;
                cinzAteCertoPonto(endereco,&x,&y);
            break;

            //====================================================================|
            case CORTAR: 
                //cortarImagem(endereco); 
            break;

            //====================================================================|
            case ASCII_ART_APARTIR_DA_IMAGEM: 
                //asciiArt(endereco); 
            break;

            case SAIR: loop = 0; break;
            default: op = VAZIO; break;
        } 
    }
    return 0;
}