#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "ordenacao.h"
#define TAM 10000

// Cria sequ�ncia crescente
void ascending_sequence(TipoItem *vet, int n) {
    for (int i = 0; i < n; i++) {
        vet[i].chave = i + 1;
    }
}

// Cria sequ�ncia decrescente
void descending_sequence(TipoItem *vet, int n) {
    for (int i = n - 1; i > 0; i--) {
        vet[i].chave = n - i;
    }
}

// Aplica o algoritmo de Fisher-Yates para criar uma sequ�ncia aleat�ria
void fisherYates(TipoItem *vet, int n) {
    // Inicializa o gerador de n�meros aleat�rios
    srand(time(NULL));

    // Preenche o vetor vet com uma sequ�ncia crescente
    ascending_sequence(vet, n);

    for (int i = n - 1; i > 0; i--) {
        // Gera um �ndice aleat�rio j utilizando a fun��o rand().
        // O valor de j � calculado como o resto da divis�o de um n�mero aleat�rio
        // pelo valor i + 1. Isso garante que j estar� entre 0 e i, inclusive.
        int j = rand() % (i + 1);

        // Troca o elemento atual (i) com o elemento aleat�rio (j)
        TipoItem temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }
}

// Seleciona a sequ�ncia a ser criada com base na ordem de sequ�ncias
void select_sequence(TipoItem *vet, int n, char **str, int i) {
    switch (i) {
        case 0:
            ascending_sequence(vet, n);
            *str = "crescente";
            break;
        case 1:
            descending_sequence(vet, n);
            *str = "decrescente";
            break;
        default:
            fisherYates(vet, n);
            *str = "aleatorio";
            break;
    }
}

// Executa e mede o tempo de execu��o dos algoritmos de ordena��o para cada sequ�ncia
void runner_timer(FILE *arquivo, TipoItem *vet, int n) {
    int cp = 0, mv = 0;
    double tempo_execucao;
    char *str = NULL;
    clock_t t;

    for(int i = 0; i < 12; i++) {
        select_sequence(vet, n, &str, i);
        t = clock();
        select_sort(vet, n, &cp, &mv);
        t = clock() - t;
        tempo_execucao = (double) t / CLOCKS_PER_SEC;
        fprintf(arquivo, "select_sort,%d,%lf.4,%s\n", n, tempo_execucao, str);

        select_sequence(vet, n, &str, i);
        t = clock();
        insert_sort(vet, n, &cp, &mv);
        t = clock() - t;
        tempo_execucao = (double) t / CLOCKS_PER_SEC;
        fprintf(arquivo, "insert_sort,%d,%lf,%s\n", n, tempo_execucao, str);

        select_sequence(vet, n, &str, i);
        t = clock();
        bubble_sort(vet, n, &cp, &mv);
        t = clock() - t;
        tempo_execucao = (double) t / CLOCKS_PER_SEC;
        fprintf(arquivo, "bubble_sort,%d,%lf,%s\n", n, tempo_execucao, str);

        select_sequence(vet, n, &str, i);
        t = clock();
        merge_sort(vet, n);
        t = clock() - t;
        tempo_execucao = (double) t / CLOCKS_PER_SEC;
        fprintf(arquivo, "merge_sort,%d,%lf,%s\n", n, tempo_execucao, str);

        select_sequence(vet, n, &str, i);
        t = clock();
        shell_sort(vet, n);
        t = clock() - t;
        tempo_execucao = (double) t / CLOCKS_PER_SEC;
        fprintf(arquivo, "shell_sort,%d,%lf,%s\n", n, tempo_execucao, str);

        select_sequence(vet, n, &str, i);
        t = clock();
        quick_sort(vet, n);
        t = clock() - t;
        tempo_execucao = (double) t / CLOCKS_PER_SEC;
        fprintf(arquivo, "quick_sort,%d,%lf,%s\n", n, tempo_execucao, str);

        select_sequence(vet, n, &str, i);
        t = clock();
        heap_sort(vet, n);
        t = clock() - t;
        tempo_execucao = (double) t / CLOCKS_PER_SEC;
        fprintf(arquivo, "heap_sort,%d,%lf,%s\n", n, tempo_execucao, str);

    }
}


int main(void) {
    setlocale(LC_ALL, "");

    FILE *arquivo;
    arquivo = fopen("dados.csv", "w");

    fprintf(arquivo, "tipo_ordenacao,tamanho_sequencia,tempo_execucao,tipo_sequencia\n");

    for(int i = 1; i <= 10; i++) {
        int tam = TAM * i;
        TipoItem *vet = malloc((tam + 1) * sizeof(TipoItem));
        runner_timer(arquivo, vet, tam);

        printf("%d\n", tam);

        free(vet);
    }

    fclose(arquivo);
    return 0;
}
