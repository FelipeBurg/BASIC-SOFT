#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024 // Mesmo tamanho usado no primeiro programa
#include "functions.h"

// Função para abrir ou criar o arquivo e mapear na memória
char *registers_map(const char *file_path, int file_size, int *fd)
{
    *fd = open(file_path, O_RDWR | O_CREAT, 0666);
    if (*fd == -1)
    {
        perror("Erro ao abrir ou criar arquivo");
        return NULL;
    }

    // Garante que o arquivo tenha o tamanho correto
    if (ftruncate(*fd, file_size) == -1)
    {
        perror("Erro ao definir o tamanho do arquivo");
        close(*fd);
        return NULL;
    }

    // Mapeia o arquivo na memória
    char *map = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED)
    {
        perror("Erro no mapeamento de arquivo");
        close(*fd);
        return NULL;
    }
    return map;
}

// Função para liberar a memória mapeada e o descritor de arquivo
int registers_release(void *map, int file_size, int fd)
{
    if (munmap(map, file_size) == -1)
    {
        perror("Erro ao desmapear a memória");
        close(fd);
        return -1;
    }

    if (close(fd) == -1)
    {
        perror("Erro ao fechar o arquivo");
        return -1;
    }
    return 0;
}

void menu()
{
    printf("Menu:\n");
    printf("1. Ligar/Desligar o display\n");
    printf("2. Definir modo de exibição\n");
    printf("3. Definir velocidade de atualização do display\n");
    printf("4. Ligar/Desligar o LED de operação\n");
    printf("5. Definir cor do LED de status\n");
    printf("6. Resetar registradores\n");
    printf("7. Definir cor do display\n");
    printf("8. Definir nível da bateria (0-255)\n");
    printf("9. Definir temperatura\n");
    printf("10. Definir caractere a ser exibido\n");
    printf("11. Sair\n");
}

int main()
{
    int fd;
    // Abre o arquivo e mapeia na memória
    char *map = registers_map(FILE_PATH, FILE_SIZE, &fd);
    if (map == NULL)
    {
        return EXIT_FAILURE;
    }

    unsigned short *base_address = (unsigned short *)map;
    unsigned short *r0 = base_address + 0x00;
    unsigned short *r1 = base_address + 0x01;
    unsigned short *r2 = base_address + 0x02;
    unsigned short *r3 = base_address + 0x03;
    unsigned short *r4 = base_address + 0x04;
    unsigned short *r5 = base_address + 0x05;
    unsigned short *r6 = base_address + 0x06;
    unsigned short *r7 = base_address + 0x07;
    unsigned short *r8 = base_address + 0x08;
    unsigned short *r9 = base_address + 0x09;
    unsigned short *r10 = base_address + 0x0A;
    unsigned short *r11 = base_address + 0x0B;
    unsigned short *r12 = base_address + 0x0C;
    unsigned short *r13 = base_address + 0x0D;
    unsigned short *r14 = base_address + 0x0E;
    unsigned short *r15 = base_address + 0x0F;
    // Registradores de modo de exibição R4-R15
    unsigned short *dados[] = {r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15};
    int escolha;
    int var1, var2, var3;
    char character;
    char string[200];
    inicializa(r0, r1, r2, r3);
    
    do
    {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            printf("Digite 0 para desligar ou 1 para ligar o display: \n");
            scanf("%d", &var1);
            liga_desliga_display(r0, var1);
            break;
        case 2:
            printf("Digite o modo de exibição (0: estático, 1: deslizante, 2: piscante, 3: deslizante/piscante): \n");
            scanf("%d", &var1);
            modo_exibicao(r0, var1);
            break;
        case 3:
            printf("Define velocidade de atualização do display em valores múltiplos de 100 milisegundos para modo de exibição não estático (0-255): \n");
            scanf("%d", &var1);
            velocidade_display(r0, var1);
        case 4:
            printf("Digite 0 para desligar ou 1 para ligar o LED de operação: \n");
            scanf("%d", &var1);
            liga_desliga_led(r0, var1);
            break;
        case 5:
            printf("Digite o LED de status (R, G, B): \n");
            scanf(" %c", &character);
            status_led(r0, character);
            break;
        case 6:
            printf("Resetar registradores\n");
            reseta_register(r0);
            break;
        case 7:
            printf("Digite a quantidade de cor para alterar respectivamente(Red, Green, Blue): \n");
            printf("Digite o valor da cor RED (0-255): \n");
            scanf("%d", &var1);
            printf("Digite o valor da cor GREEN (0-255): \n");
            scanf("%d", &var2);
            printf("Digite o valor da cor BLUE (0-255): \n");
            scanf("%d", &var3);
            cor_display(r0, r2, var1, var2, var3);
            break;
        case 8:
            printf("Digite a opçao de nivel de bateria(1-crítico,2-baixo,3-medio,4-alto)\n");
            scanf("%d", &var1);
            liga_desliga_led(r3, var1);
            break;
        case 9:
            printf("Digite a temperatura que deseja(lembrando valor  323 representa 32,2 graus)\n");
            scanf("%d", &var1);
            temperatura(r1, var1);
            break;
        case 10:
            printf("Digite a o conteudo que deseja exibir no display\n");
            scanf("%s", &string);
            exibir_dados(string, &dados);
            break;
        case 11:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }
    } while (escolha != 11);

    printf("Current value of R0: 0x%02x\n", *r0);
    printf("Current value of R1: 0x%02x\n", *r1);
    printf("Current value of R2: 0x%02x\n", *r2); 
    printf("Current value of R3: 0x%02x\n", *r3);
    printf("Current value of R4: %c\n", *r4); 
    printf("O valor ASCII de r4 é: %d\n", *r4);   

    // Libera a memória e o descritor de arquivo
    if (registers_release(map, FILE_SIZE, fd) == -1)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}