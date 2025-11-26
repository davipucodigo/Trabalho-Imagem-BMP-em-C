#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdint.h>
#include <time.h>

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
    uint32_t colors;  //NÃO USA
    uint32_t important_colors;  //NÃO USA
}__attribute__((packed)) BMP_HEADER;

typedef struct{
    unsigned char blue, green, red;
}__attribute__((packed)) BMP_COLOR_TABLE;

//FUNÇÂO VERIFICA PADDING
int padding_teste(BMP_HEADER *p) {
    //Verificando paddings
    int verifica_padding = (4-(p->width*3)%4)%4;
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
    printf("\n DAVI SANT'ANNA VIEIRA                       ");
    printf("\n HENRIQUE AZEREDO PELTZ                      ");
    printf("\n 4324 - 2025                                 ");
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
    FILE *lendo, *escrevendo;
    BMP_HEADER img_header;
    BMP_COLOR_TABLE pixels;
    int linha, pixel, cor;
    lendo = fopen(c, "rb");
    for(cor=0; cor<=2; cor++){
        fseek(lendo, 0, SEEK_SET);
        switch(cor){
            case 0:
                escrevendo = fopen("vermelho.bmp","wb");
            break;
            case 1:
                escrevendo = fopen("verde.bmp","wb");
            break;
            case 2:
                escrevendo = fopen("azul.bmp","wb");
            break;
        }     

        fread(&img_header, sizeof(BMP_HEADER), 1, lendo);
        fwrite(&img_header, sizeof(BMP_HEADER), 1, escrevendo);

        int paddingbytes = (4-(img_header.width*3)%4)%4;

        linha=0;
        while(linha!=img_header.height){
            pixel=0;
            while(pixel!=img_header.width){
                fread(&pixels, sizeof(BMP_COLOR_TABLE), 1, lendo);
                switch(cor){
                    case 0:
                        pixels.red = pixels.red;
                        pixels.green = 0;
                        pixels.blue = 0;
                    break;
                    case 1:
                        pixels.red = 0;
                        pixels.green = pixels.green;
                        pixels.blue = 0;
                    break;
                    case 2:
                        pixels.red = 0;
                        pixels.green = 0;
                        pixels.blue = pixels.blue;
                    break;
                }   
                fwrite(&pixels, sizeof(BMP_COLOR_TABLE), 1, escrevendo);
                pixel++;
            }
            fseek(lendo, paddingbytes, SEEK_CUR);
            fwrite("00", 1, paddingbytes, escrevendo);
            linha++;
        }
        fclose(escrevendo);
    }
    fclose(lendo);
}

// FUNÇÂO PARA SEPARAR CORES
void cinzAteCertoPonto(char *c) {

    int x1, x2, y1, y2, linha, pixel;
    printf("\ndigite o valor de X inicial: ");
    scanf("%d", &x1);
    printf("\ndigite o valor de X final: ");
    scanf("%d", &x2);
    printf("\ndigite o valor de Y inicial: ");
    scanf("%d", &y1);
    printf("\ndigite o valor de Y final: ");
    scanf("%d", &y2);

    BMP_HEADER img_header;
    BMP_COLOR_TABLE pixels;

    FILE *lendo, *escrevendo;
    
    lendo = fopen(c,"rb");
    escrevendo = fopen("cinza.bmp","wb");
    fread(&img_header, sizeof(BMP_HEADER), 1, lendo);
    fwrite(&img_header, sizeof(BMP_HEADER), 1, escrevendo);
    int paddingbytes = (4-(img_header.width*3)%4)%4;

    linha=1;
    while(linha<=img_header.height){
        pixel=1;
        while(pixel<=img_header.width){
            fread(&pixels, sizeof(BMP_COLOR_TABLE), 1, lendo);
            if((pixel >= x1) && (pixel <= x2) && (linha >= y1) && (linha <= y2)){
                unsigned char gray = (0.299*pixels.red + 0.587*pixels.green + 0.114*pixels.blue);
                pixels.red = gray;
                pixels.green = gray;
                pixels.blue = gray; 
            }
            fwrite(&pixels, sizeof(BMP_COLOR_TABLE), 1, escrevendo);
            pixel++;
        }
        fseek(lendo, paddingbytes, SEEK_CUR);
        fwrite("00", 1, paddingbytes, escrevendo);
        linha++;
    }
    fclose(lendo);
    fclose(escrevendo);
}

void cortarImagem(char *c){
    int x1, x2, y1, y2, linha, pixel;
    int largura_original, largura_cortada, altura_original, altura_cortada;


    printf("\ndigite o valor de X inicial: ");
    scanf("%d", &x1);
    printf("\ndigite o valor de X final: ");
    scanf("%d", &x2);
    printf("\ndigite o valor de Y inicial: ");
    scanf("%d", &y1);
    printf("\ndigite o valor de Y final: ");
    scanf("%d", &y2);

    largura_cortada = x2-x1+1;
    altura_cortada = y2-y1+1;

    int paddingbytes_cortado = (4-(largura_cortada*3)%4)%4;

    BMP_HEADER img_header;
    BMP_COLOR_TABLE pixels;

    FILE *lendo, *escrevendo;
    
    lendo = fopen(c,"rb");
    escrevendo = fopen("cortado.bmp","wb");
    fread(&img_header, sizeof(BMP_HEADER), 1, lendo);

    largura_original = img_header.width;
    img_header.width = largura_cortada;

    altura_original = img_header.height;
    img_header.height = altura_cortada;

    fwrite(&img_header, sizeof(BMP_HEADER), 1, escrevendo);

    img_header.width = largura_original;
    img_header.height = altura_original;

    int paddingbytes = (4-(img_header.width*3)%4)%4;

    linha=1;
    while(linha<=img_header.height){
        pixel=1;
        while(pixel<=img_header.width){
            printf("%d %d\n", linha, pixel);
            fread(&pixels, sizeof(BMP_COLOR_TABLE), 1, lendo);
            if((pixel >= x1) && (pixel <= x2) && (linha >= y1) && (linha <= y2)){
                printf("cor: %d %d %d\n", pixels.blue, pixels.green, pixels.red);
                fwrite(&pixels, sizeof(BMP_COLOR_TABLE), 1, escrevendo);
            }
            pixel++;
        }
        fseek(lendo, paddingbytes, SEEK_CUR);
        if((linha >= y1) && (linha <= y2)){ //apenas escreve padding na area cortada
            fwrite("00", 1, paddingbytes_cortado, escrevendo);
        }
        linha++;
    }
    fclose(lendo);
    fclose(escrevendo);
}

int main(){

    //Config
    setlocale(LC_ALL,"Portuguese");

    //Variaveis
    char endereco[50] = "images/teste4x4.bmp";
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
                cinzAteCertoPonto(endereco);
            break;

            //====================================================================|
            case CORTAR: 
                cortarImagem(endereco); 
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