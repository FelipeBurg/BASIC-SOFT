#include "functions.h"
#include <stdio.h>

void inicializa(unsigned short *r0,unsigned short *r1,unsigned short *r2,unsigned short *r3)
{
    *r0 = 0;
    *r1 = 0;
    *r2 = 0;
    *r3 = 0;
}

//R0 R0
void liga_desliga_display(unsigned short *r0, int display)
{
    if (display == 0)
    {
        *r0 = *r0 | 0x01;
    }
    else
    {
        *r0 = *r0 & ~0x01;
    }
}

void modo_exibicao(unsigned short *r0, int modo)
{
    *r0 &= ~((1 << 1) | (1 << 2));
    switch (modo)
    {
    case 1:

        break;
    case 2:
        *r0 |= (1 << 1);
        break;

    case 3:;
        *r0 |= (1 << 2);
        break;

    case 4:
        *r0 |= (1 << 1) | (1 << 2);
        break;
    default:
        printf("modo invalido");
        break;
    }
}

void velocidade_display(unsigned short *r0, int velocidade)
{
    if (velocidade <= 63)
    {
        *r0 &= ~(0x3F << 3);
        *r0 |= (velocidade << 3);
    }
    else
    {
        printf("velocidade invalida");
    }
}

void liga_desliga_led(unsigned short *r0, int led)
{
    if (led == 0)
    {
        *r0 = *r0 | 0x10;
    }
    else
    {
        *r0 = *r0 & ~0x10;
    }
}

void status_led(unsigned short *r0, char status)
{
    switch (status)
    {
    case 'B':
        *r0 |= (1 << 10);
        break;
    case 'G':
        *r0 |= (1 << 11);
        break;
    case 'R':
        *r0 |= (1 << 12);
        break;

    default:
        printf("Opção invalida");
        break;
    }
}

void reseta_register(unsigned short *r0)
{
    *r0 = 0;
}

//  R1 e R2
void cor_rgb(unsigned short *r1, unsigned short *r2, int num, int num2, int num3)
{
    if (num <= 255)
    {
        *r1 &= ~0xFF;
        *r1 |= num;
    }
    else
    {
        printf("Numero invalido para quantidade de bits ");
    }
    if (num2 <= 255)
    {
        *r1 &= ~(0xFF << 8);
        *r1 |= num2 << 8;
    }
    else
    {
        printf("Numero invalido para quantidade de bits ");
    }
    if (num3 <= 255)
    {
        *r2 &= ~0xFF;
        *r2 |= num3;
        *r2 &= ~(0xFF << 8);
    }
    else
    {
        printf("Numero invalido para quantidade de bits ");
    }
}

void bateria(unsigned short *r3, int num)
{
    *r3 &= ~((1 << 1) | (1 << 2));
    switch (num)
    {
    case 1:

        break;
    case 2:
        *r3 |= (1 << 0);
        break;

    case 3:
        *r3 |= (1 << 1);
        break;

    case 4:
        *r3 |= (1 << 1) | (1 << 0);
        break;
    }
}

void temperatura(unsigned short *r3, int num)
{
    unsigned short mask = ~((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
    *r3 &= mask;

    if (num <= 511)
    {
        *r3 &= ~(0x3FF << 6);
        *r3 |= (num << 6);
    }
    else
    {
        printf("Erro na temperatura");
    }
}

void exibir_dados(char *string,unsigned short *dados[])
{
    int i;
    for (i = 0; i < 10 && string[i] != '\0'; i++) {
        if(dados[i] != NULL){
            printf("O caractere '%c' foi colocado corretamente no registrador r%d\n", string[i], i+4);   
        }else{
            printf("Erro na alocação de memória para o registrador");
            
        }
    
    }
    for (; i < 10; i++) {
        if(dados[i]!=NULL){
        *dados[i] = '\0';
    }else{
        printf("Erro na alocação de memória\n");
       

        }    }
}


