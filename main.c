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

//DEFINES TONS DE CINZA
#define PRETO_PURO 0x00
#define CINZA_MUITO_ESCURO 0x32
#define CINZA_ESCURO 0x64
#define CINZA_MEDIO 0x80
#define CINZA_CLARO 0xc8
#define CINZA_MUITO_CLARO 0xdc
#define BRANCO_PURO 0xff

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

//FUNÇÃO CALCULA PIXEL CINZA retorna o pixel equivalente a cinza.
unsigned char CinzaPixel(BMP_COLOR_TABLE *px) { //BMP_COLOR_TABLE *px
    int soma = px->red+px->blue+px->green;
    unsigned char media = (unsigned char)(soma/3);
    return media;
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
                escrevendo = fopen("Cores_Separadas/vermelho.bmp","wb");
            break;
            case 1:
                escrevendo = fopen("Cores_Separadas/verde.bmp","wb");
            break;
            case 2:
                escrevendo = fopen("Cores_Separadas/azul.bmp","wb");
            break;
        }     

        fread(&img_header, sizeof(BMP_HEADER), 1, lendo);
        fwrite(&img_header, sizeof(BMP_HEADER), 1, escrevendo);

        int paddingbytes = padding_teste(&img_header);

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

void asciiArt(char *c) {
    //                                              0 -------> 128 ------> 225
    char vetor_de_Caracteres_de_substituição[7] = {' ','.','o','O','&','#','@'};
    
    BMP_HEADER img_header;
    BMP_COLOR_TABLE pixels;

    FILE * LENDO;
    FILE * ESCREVENDO;

    LENDO = fopen(c,"rb");
    ESCREVENDO = fopen("ASCII/ascii_img.txt","wb");

        fread(&img_header,sizeof(img_header),1,LENDO);

        int padding = padding_teste(&img_header);
        int L;
        int PX;

        for (L = (img_header.height - 1); L >= 0; L--) {
            //posiciona o ponteiro na linha de baixo e vai subindo;
            fseek(LENDO,  img_header.offset_of_img_data + L*(img_header.width*sizeof(pixels)+padding), SEEK_SET);

            for (PX = 0; PX < img_header.width; PX++) {
                //Le a linha, sequencia de pixel delas.
                fread(&pixels,sizeof(pixels),1,LENDO);
                unsigned char cinza = CinzaPixel(&pixels);

                if (cinza >= PRETO_PURO && cinza < CINZA_MUITO_ESCURO) 
                    fprintf(ESCREVENDO, "%c", vetor_de_Caracteres_de_substituição[0]);

                if (cinza >= CINZA_MUITO_ESCURO && cinza < CINZA_ESCURO) 
                    fprintf(ESCREVENDO, "%c", vetor_de_Caracteres_de_substituição[1]);

                if (cinza >= CINZA_ESCURO && cinza < CINZA_MEDIO) 
                    fprintf(ESCREVENDO, "%c", vetor_de_Caracteres_de_substituição[2]);

                if (cinza >= CINZA_MEDIO && cinza < CINZA_CLARO) 
                    fprintf(ESCREVENDO, "%c", vetor_de_Caracteres_de_substituição[3]);

                if (cinza >= CINZA_CLARO && cinza < CINZA_MUITO_CLARO) 
                    fprintf(ESCREVENDO, "%c", vetor_de_Caracteres_de_substituição[4]);

                if (cinza >= CINZA_MUITO_CLARO && cinza < BRANCO_PURO) 
                    fprintf(ESCREVENDO, "%c", vetor_de_Caracteres_de_substituição[5]);

                if (cinza >= BRANCO_PURO) 
                    fprintf(ESCREVENDO, "%c", vetor_de_Caracteres_de_substituição[6]);
            }
            fprintf(ESCREVENDO, "\n");
        }
    fclose(LENDO);
    fclose(ESCREVENDO);
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
                asciiArt(endereco); 
            break;

            case SAIR: loop = 0; break;
            default: op = VAZIO; break;
        } 
    }
    return 0;
}