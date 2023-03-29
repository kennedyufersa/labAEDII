#include "arvoreBinaria.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int *geradadorSequencia(int seed, int N);

int main() {
    // Init
    int tam = 0;
    int N[100];
    for (float p = 3; p <= 6; p = p + 0.1) {
        N[tam] = (int)pow(10., p);
        tam++;
    }
    int *v;
    int mat = 5;
    int tentativas = 3;
    FILE *f;
    Node *raiz;
    clock_t t, total;
    for (int k = 0; k < tam; k++) {
        total = 0.;
        printf("Tamanho: %d (%d/%d)\n", N[k], k + 1,tam+1);
        for (int m = 0; m < tentativas; m++) {
            // Gerando Sequência
            printf("\tGerando a sequencia: %d/%d\n", m + 1, tentativas);
            v = geradadorSequencia(mat, N[k]);

            // Inicializando árvore
            raiz = 0;

            // Marcando o tempo da INSERCAO
            t = clock();

            // Inserindo os elementos
            inserirVetor(raiz, v, N[k]);

            // Marcando o tempo (Acumulando)
            t = clock() - t;
            // Acumulando o tempo (milisegundos)
            total += ((float)t * 1000000) / CLOCKS_PER_SEC;

            // Apagar árvore
            removerTodos(raiz);
        }
        // Salvando os resultados
        f = fopen("resultados.dat", "a+");
        fprintf(f, "%d\t%d\n", N[k], (int)(total / tentativas));
        fflush(f);
        fclose(f);
    }
}

int *geradadorSequencia(int seed, int N) {
    srand(seed);
    int *res = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        res[i] = random() % N;
    }
    return res;
}

bool apagarArquivo(const char *caminhoArquivo) {
    int resultado = remove(caminhoArquivo);
    if (resultado != 0) {
        return false;
    }
    return true;
}