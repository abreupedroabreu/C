
#define MAX 700
#define MAX_TAM 99999

struct dados{
    int pontos;
    int contador_pontos_marcados;
    int contador_pontos_sofridos;
    char nome_equipa[MAX];
    int contador_nos;
}vetor_dados[MAX];

struct elem_fila {
    struct dados equipa;
    struct elem_fila * equipa_seguinte;

}*raiz;



void inicializar();
void le_ficheiro(char scan_ficheiro1[],char scan_ficheiro2[]);
int colocar(struct dados mens);
int soma_pontos(char pontos[]);
void print_lista();
void ordena_vetor();
void coloca_lista_ordenada();
void escreve_binario_tabela(char nome[]);
void coloca_vetor(char equipaCasa[], char equipaAdv[], int pontos_marcados,int pontos_sofridos);
void print_vetor();

void escreve_ficheiro_binario_promovidas(char nome_ficheiro[]);