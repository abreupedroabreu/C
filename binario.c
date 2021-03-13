#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define MAX_TAM 10000

int main()
{
    char nome[MAX];
    int vef=0;
    char buffer[MAX_TAM];
    FILE *ptr;

    FILE *fpTXT;

    while(1) {

        do {
            vef = 0;
            printf("Nome do ficheiro binario: ");
            scanf("%s", nome);
            for (int i = 0; i < strlen(nome); i++) {
                if (((nome[i] >= '0' && nome[i] <= '9') || (nome[i] >= 'A' && nome[i] <= 'Z') ||
                     (nome[i] >= 'a' && nome[i] <= 'z')) || nome[i] == '.') {
                    continue;
                } else {
                    vef = 1;
                }
            }
            if (vef == 1) {
                printf("Introduziu caracteres invalidos no nome do ficheiro");
            }
        } while (vef == 1);

        ptr = fopen(nome, "r+b"); // ler ficheiro binario

        fread(buffer, sizeof(buffer) - 1, 1, ptr);

        buffer[sizeof(buffer) - 1] = '\0';

        fflush(ptr);

        fclose(ptr);

        do {
            vef = 0;
            printf("Nome de saida para o ficheiro de texto: ");
            scanf("%s", nome);
            for (int i = 0; i < strlen(nome); i++) {
                if (((nome[i] >= '0' && nome[i] <= '9') || (nome[i] >= 'A' && nome[i] <= 'Z') ||
                     (nome[i] >= 'a' && nome[i] <= 'z')) || nome[i] == '.') {
                    continue;
                } else {
                    vef = 1;
                }
            }
            if (vef == 1) {
                printf("Introduziu caracteres invalidos no nome do ficheiro");
            }
        } while (vef == 1);

        fpTXT = fopen(nome, "w+");


        printf("\n%s\n", buffer);

        fprintf(fpTXT, "%s", buffer);   //vai escrever no ficheiro de texto

        fclose(fpTXT);
    }


}
