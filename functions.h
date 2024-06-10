#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void inicializa(unsigned short *r0,unsigned short *r1,unsigned short *r2,unsigned short *r3);
// R0
void liga_desliga_display(unsigned short *r0, int display);
void modo_exibicao(unsigned short *r0, int modo);
void velocidade(unsigned short *r0, int velocidade);
void liga_desliga_led(unsigned short *r0, int led);
void status_led(unsigned short *r0, char status);
void reset(unsigned short *r0);

// R1 e R2
void cor_rgb(unsigned short *r1,unsigned short *r2,int num,int num2,int num3);
void bateria(unsigned short *r3,int num);

// R3  
void temperatura(unsigned short *r3,int num); 
void exibir_dados(char *string,unsigned short *dados[]);

#endif // FUNCTIONS_H