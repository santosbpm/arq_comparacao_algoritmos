#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "ordenacao.h"
#define TAM 10000

// Cria sequência crescente
void ascending_sequence(TipoItem *vet, int n) {
    for (int i = 0; i < n; i++) {
        vet[i].chave = i + 1;
    }
}

// Cria sequência decrescente
void descending_sequence(TipoItem *vet, int n) {
    for (int i = n - 1; i > 0; i--) {
        vet[i].chave = n - i;
    }
}

// Aplica o algoritmo de Fisher-Yates para criar uma sequência aleatória
void fisherYates(TipoItem *vet, int n) {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Preenche o vetor vet com uma sequência crescente
    ascending_sequence(vet, n);

    for (int i = n - 1; i > 0; i--) {
        // Gera um índice aleatório j utilizando a função rand().
        // O valor de j é calculado como o resto da divisão de um número aleatório
        // pelo valor i + 1. Isso garante que j estará entre 0 e i, inclusive.
        int j = rand() % (i + 1);

        // Troca o elemento atual (i) com o elemento aleatório (j)
        TipoItem temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }
}

// Seleciona a sequência a ser criada com base na ordem de sequências
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

// Executa e mede o tempo de execução dos algoritmos de ordenação para cada sequência
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
