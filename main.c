#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "estruturas.h"


//Para fins de complementaridade, criei mais 3 parametros adicionais, como os pontos marcados,pontos, sofridos e contador de nos
// Para fins de desempate quando duas equipas têm o mesmo nº de pontos, a equipa que irá primeiro irá ser a com mais pontos marcados
// Utilizei um vetor de estruturas para ir armazenando e atualizando os valores das respetivas equipas
// e em seguida, ordenei-o de forma a criar a lista circular de forma ordenada
//Para output, irei ter 2 ficheiros binarios, um com a tabela da classificação total e outra com as 2 primeiras e 2 ultimas equipas
// que depois irão ser lidos e convertidos em ficheiros txt por um programa externo a este

int contador_nos=0;
int numero_equipas=0;

int main() {

    char scan_ficheiro1[MAX];
    char scan_ficheiro2[MAX];
    char nome_binario_tabela[MAX];
    char nome_binario_promo[MAX];
    int scan_menu;
    

    printf("\nIntroduza o nome do ficheiro de entrada: ");
    scanf("%s",scan_ficheiro1);

    printf("\nIntroduza o nome do ficheiro dos resultados: ");
    scanf("%s",scan_ficheiro2);

    inicializar(); // vai inicializar a lista

    le_ficheiro(scan_ficheiro1,scan_ficheiro2); // vai ler o que esta no ficheiro de entrada

    //print_vetor();
    ordena_vetor();
    coloca_lista_ordenada();

    //print_lista();

    while(1) {

        printf("\n1-Mostrar Lista Campeonato\n2-Mostrar Promovidas/Despromovidas\nOpção: ");

        scanf("%d", &scan_menu);

        if (scan_menu == 1) {

            printf("\nDe-me o nome do ficheiro de saída para a tabela: ");

            scanf("%s", nome_binario_tabela);
            assert((nome_binario_tabela != NULL));

            escreve_binario_tabela(nome_binario_tabela);


        } else if (scan_menu == 2) {

            printf("\nDe-me o nome do ficheiro de saída para a promocao/despromocao: ");
            scanf("%s", nome_binario_promo);
            assert((nome_binario_promo != NULL));

            escreve_ficheiro_binario_promovidas(nome_binario_promo);


        } else {
            printf("\nIntroduziu mal a opção!! Tente outra vez!! ");

        }
    }
    return 0;

}

void le_ficheiro(char scan_ficheiro1[],char scan_ficheiro2[]) {


    FILE *f, *f_resultados;


    f = fopen("lista_equipas.txt", "r");
    f_resultados = fopen("entrada.txt", "r");

    if (f == NULL) {
        printf("Erro, não consegui abrir o ficheiro lista_equipas!");
        exit(1);
    }
    if (f_resultados == NULL) {
        printf("Erro, não consegui abrir o ficheiro resultados.txt!");
        exit(1);
    }
    char equipa[MAX];

    char pontos_marcadosVetor[MAX];
    char pontos_sofridosVetor[MAX];
    int pontos_marcados = 0;
    int pontos_sofridos = 0;


    int i = 0;
    int k = 0;
    int z = 0;
    int x=0;

    char aux[MAX_TAM];
    char aux_resultado[MAX];
    char equipaVefCasa[MAX];
    char equipaVefAdv[MAX];

    char c;

    int index=0;
    char string_lida[MAX_TAM];

    char string_aux[MAX_TAM];

    int tamanho;

    while ((c = fgetc(f)) != EOF) {

        aux[i] = c;

        i++;

    }

    string_aux[0]='\0';

    while(fscanf(f_resultados, "   %s   ", string_lida) != EOF) {

        strcat(string_aux,string_lida);

        tamanho = strlen(string_aux);
        string_aux[tamanho] = '\n';
        string_aux[tamanho+1] = '\0';

    }

    aux[i] = '\0';

    aux_resultado[z] = '\0';

    int contador_char = 0;


    if (f) {
        int ind=0;

        for (int i = 0; i < strlen(aux) + 1; i++) {

            if(aux[i] != '\t' && aux[i] != '\0') {

                equipa[ind] = aux[i];
                ind++;
            }


            if (aux[i] == '\t' || aux[i] == '\0') { // PARA O FICHEIRO DA LISTA DE EQUIPAS SEPARADAS POR UM TAB


                equipa[ind] = '\0';


                strcat(vetor_dados[index].nome_equipa,equipa);


                vetor_dados[index].pontos = 0;
                vetor_dados[index].contador_pontos_marcados = 0;
                vetor_dados[index].contador_pontos_sofridos = 0;


                equipa[0] = '\0';


                contador_char = 0;
                index++;
                ind=0;
                numero_equipas++;

            }
            contador_char++;


        }
        fclose(f);
    }

    //------ IR OBTER OS RESULTADOS DE CADA EQUIPA PARA O FICHEIRO DOS RESULTADOS

    if (f_resultados) {

        for (int y = 0; y < strlen(string_aux); y++) {
            aux_resultado[x] = string_aux[y];


            if(aux_resultado[x] == '\n') {

                aux_resultado[x+1]='\0';

                x=0;

                for (int i = 0; i < strlen(aux_resultado); i++) {
                    k=0;

                    if (aux_resultado[i] == '-') {


                        if (isalpha(aux_resultado[i + 1]) ) { // sabemos se é o hiffen entre equipas

                            for (int z = i -2; z >= 0; z--) {

                                equipaVefCasa[i - z-2 ] = aux_resultado[i - z -1]; // verificar se nao esta em ordem invertida
                                //printf("\nVEF: %c AUX: %c I: %d Z: %d",equipaVefCasa[i-z-2],aux_resultado[i-z-1],i,z);

                            }

                            equipaVefCasa[i]='\0';

                            //printf("\nEQUIPA CASA: %s", equipaVefCasa);
                            i++;
                            //printf("\nI DEPOIS: %d",i);
                            while (aux_resultado[i] != '-') {
                                equipaVefAdv[k] = aux_resultado[i];
                                i++;
                                k++;

                            }

                            equipaVefAdv[k]='\0';

                            //printf("\nEQUIPA ADVERSARIA: %s", equipaVefAdv);

                            //printf("\n-----------------");

                        }
                    }

                    if (isdigit(aux_resultado[i + 1]) && aux_resultado[i] == '-') { // sabemos que é o '-' antes dos golos, vamos ao 1ºs pontos
                        i++;
                        k = 0;

                        while (aux_resultado[i] != '.') {

                            pontos_marcadosVetor[k] = aux_resultado[i]; // cada posicao do vetor vai ser cada numero dos pontos marcados
                            i++;
                            k++;

                        }

                        pontos_marcadosVetor[k] = '\0';


                        pontos_marcados = soma_pontos(pontos_marcadosVetor);

                    }

                    if (isdigit(aux_resultado[i + 1]) && aux_resultado[i] == '.') { // vamos aceder aos 2º pontos

                        k = 0;
                        i++;
                        while (aux_resultado[i] != '\0') {

                            pontos_sofridosVetor[k] = aux_resultado[i]; // cada posicao do vetor vai ser cada numero dos pontos marcados

                            k++;
                            i++;

                        }

                        pontos_sofridosVetor[k] = '\0';

                        pontos_sofridos = soma_pontos(pontos_sofridosVetor);


                    }
                    coloca_vetor(equipaVefCasa,equipaVefAdv,pontos_marcados,pontos_sofridos);
                    memset(equipaVefCasa,0,strlen(equipaVefCasa));
                    memset(equipaVefAdv,0,strlen(equipaVefAdv));
                }

            }

            x++;

        }

    }

    fclose(f_resultados);

}

void print_vetor(){

    for(int i=0;i<numero_equipas;i++){
        printf("\nNOME: %s PONTOS: %d MARCADOS: %d SOFRIDOS:%d",vetor_dados[i].nome_equipa,vetor_dados[i].pontos,vetor_dados[i].contador_pontos_marcados,vetor_dados[i].contador_pontos_sofridos);
    }

}


void coloca_vetor(char equipaCasa[], char equipaAdv[], int pontos_marcados,int pontos_sofridos){

    //printf("\n EQUIPA VEF CASA: %s\nEQUIPA VEF ADV: %s",equipaVefCasa,equipaVefAdv);

    for(int i=0;i<numero_equipas;i++){
        if(strcmp(equipaCasa,vetor_dados[i].nome_equipa)==0){
            //printf("\nCASA: %s PONTOS CASA: %d",vetor_dados[i].nome_equipa,vetor_dados[i].pontos);
            vetor_dados[i].contador_pontos_marcados += pontos_marcados;
            vetor_dados[i].contador_pontos_sofridos += pontos_sofridos;
            if(pontos_marcados>pontos_sofridos) {
                vetor_dados[i].pontos += 2;
            }
            else{
                vetor_dados[i].pontos+=1;
            }

        }
        else{
            if(strcmp(equipaAdv,vetor_dados[i].nome_equipa)==0){
                vetor_dados[i].pontos+=1;
                vetor_dados[i].contador_pontos_marcados += pontos_sofridos;
                vetor_dados[i].contador_pontos_sofridos += pontos_marcados;
                if(pontos_sofridos>pontos_marcados) {
                    vetor_dados[i].pontos += 2;
                }
                else{
                    vetor_dados[i].pontos+=1;
                }

            }
        }


    }

}

void ordena_vetor(){


    struct dados aux;

    for (int i = 0; i < numero_equipas; ++i)
    {
        for (int j = i + 1; j < numero_equipas; ++j)
        {
            if (vetor_dados[i].pontos > vetor_dados[j].pontos)
            {
                aux = vetor_dados[i];
                vetor_dados[i] = vetor_dados[j];
                vetor_dados[j] = aux;
            }
        }
    }

}


void inicializar(){
    raiz = NULL;
}

void coloca_lista_ordenada(){

    int vef;

    for(int i=0;i<numero_equipas;i++){


        vef = colocar(vetor_dados[i]);

        if(vef ==0){
            printf("\nNão consegui colocar!!");
            exit(1);
        }

    }

}
int colocar(struct dados mens) {
    struct elem_fila * aux;

    mens.contador_nos=0;
    contador_nos++;

    //Obter espaço para um novo nó
    aux = (struct elem_fila *) malloc(sizeof(struct elem_fila));

    if (aux == NULL) {
        //não há espaço
        printf("\nNão Há mais espaço");
        return 0;

    }

    // inserir à entrada da lista sendo uma lista circular
    aux->equipa = mens;

    aux->equipa.contador_nos = contador_nos;

    aux->equipa_seguinte = raiz;

    raiz = aux;

    return 1;


}



int soma_pontos(char pontos[]){
    char soma[MAX];

    for(int i=0;i<strlen(pontos);i++){
        soma[i] = pontos[i];

    }
    soma[strlen(pontos)] ='\0';


    return atoi(soma);
}

void escreve_binario_tabela(char nome_ficheiro_tabela[]){

    char buffer[MAX_TAM];
    buffer[0]='\0';

    char str[10000];
    

    struct elem_fila *aux;
    FILE *ptr;

    ptr = fopen(nome_ficheiro_tabela,"wb");

    strcat(buffer,"TABELA CLASSIFICATIVA");
    strcat(buffer,"\n\n");




    for(aux = raiz; aux->equipa_seguinte != NULL; aux = aux->equipa_seguinte){

        strcat(buffer, "NOME: ");

        strcat(buffer, aux->equipa.nome_equipa);
        strcat(buffer, " PONTOS: ");

        sprintf(str, "%d", aux->equipa.pontos);
        strcat(buffer, str);

        strcat(buffer, " PONTOS MARCADOS: ");
        sprintf(str, "%d", aux->equipa.contador_pontos_marcados);
        strcat(buffer, str);


        strcat(buffer, " PONTOS SOFRIDOS: ");
        sprintf(str, "%d", aux->equipa.contador_pontos_sofridos);
        strcat(buffer, str);

        strcat(buffer, "\n");

    }


    fwrite(buffer,sizeof(buffer),1,ptr);



    buffer[0]='\0';


    fflush(ptr);

    fclose(ptr);

}


void escreve_ficheiro_binario_promovidas(char nome_ficheiro[]){

    char buffer[MAX];
    buffer[0]='\0';

    char str[30];
    struct elem_fila *aux;
    FILE *ptr_promovidas;

    ptr_promovidas = fopen(nome_ficheiro,"wb");

    strcat(buffer,"EQUIPAS PROMOVIDAS");
    strcat(buffer,"\n\n");
    int i=0;

    for(aux = raiz; i<2; aux = aux->equipa_seguinte){


        strcat(buffer,"NOME: ");
        strcat(buffer,aux->equipa.nome_equipa);



        strcat(buffer," PONTOS : ");
        sprintf(str, "%d", aux->equipa.pontos);
        strcat(buffer, str);

        strcat(buffer," PONTOS MARCADOS: ");
        sprintf(str, "%d", aux->equipa.contador_pontos_marcados);
        strcat(buffer, str);

        strcat(buffer," PONTOS SOFRIDOS: ");
        sprintf(str, "%d", aux->equipa.contador_pontos_sofridos);
        strcat(buffer, str);


        i++;

    }
    //printf("\nBUFFER ANTES: %s",buffer);


    strcat(buffer,"\n\nEQUIPAS ZONA DESPROMOÇÃO");
    strcat(buffer,"\n\n");



    for(aux = raiz; aux->equipa_seguinte != NULL; aux = aux->equipa_seguinte){
       // printf("\nCONTADORES: %d",aux->equipa.contador_nos);

        if(aux->equipa.contador_nos==2) {


            strcat(buffer, "NOME: ");
            strcat(buffer, aux->equipa.nome_equipa);
            strcat(buffer,"PONTOS : ");
            sprintf(str, "%d", aux->equipa.pontos);
            strcat(buffer, str);

            strcat(buffer,"PONTOS MARCADOS: ");
            sprintf(str, "%d", aux->equipa.contador_pontos_marcados);
            strcat(buffer, str);

            strcat(buffer,"PONTOS SOFRIDOS: ");
            sprintf(str, "%d", aux->equipa.contador_pontos_sofridos);
            strcat(buffer, str);

            strcat(buffer, "\n\n");
            aux = aux->equipa_seguinte;

            //printf("\nCONTADORES 33 : %d",aux->equipa.contador_nos);
            //printf("\nCONTADORES 33: %d",aux->equipa.contador_nos);
            strcat(buffer,"NOME: ");
            strcat(buffer,aux->equipa.nome_equipa);
            strcat(buffer,"PONTOS : ");
            sprintf(str, "%d", aux->equipa.pontos);
            strcat(buffer, str);

            strcat(buffer,"PONTOS MARCADOS: ");
            sprintf(str, "%d", aux->equipa.contador_pontos_marcados);
            strcat(buffer, str);

            strcat(buffer,"PONTOS SOFRIDOS: ");
            sprintf(str, "%d", aux->equipa.contador_pontos_sofridos);
            strcat(buffer, str);
            strcat(buffer,"\n");

            break;

        }

    }




    fwrite(buffer,sizeof(buffer),1,ptr_promovidas);


    fflush(ptr_promovidas);
    fclose(ptr_promovidas);

}

void print_lista(){
    struct elem_fila * aux;
    aux=raiz;
    for(int i=0;i<contador_nos;i++){
        printf("\n%s : %d CONTADOR: %d",aux->equipa.nome_equipa,aux->equipa.pontos,aux->equipa.contador_nos);
        aux = aux->equipa_seguinte;
    }
}



