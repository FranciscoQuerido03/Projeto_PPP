#ifndef PROJETO_PPP_LISTAS_H
#define PROJETO_PPP_LISTAS_H

#include "stdio.h"
#include "stdlib.h"
#include <strings.h>
#include <math.h>

#define MAX 100

struct Aluno{
    char Nome[MAX];
    char Data_nascimento[MAX] ;
    int ano;
    char turma[MAX];
    int numero;
    float saldo;
};

struct Despesa{
    int numero_aluno;
    float valor;
    char descricao [MAX];
    char data [MAX];
};

typedef struct NoAluno{
    struct Aluno aluno;
    struct NoAluno * prox;
}NoAluno;

typedef struct NoSaldo{
    struct NoAluno * no_aluno;
    struct NoSaldo * prox;
}NoSaldo;

typedef struct NoDespesas{
    struct Despesa despesa;
    struct NoAluno * no__aluno;
    struct NoDespesas * prox;
}NoDespesas;


typedef NoDespesas * Pdespesas;
typedef NoAluno * Paluno;
typedef NoSaldo * Psaldo;


Paluno cria();
Pdespesas cria_despesa();
Psaldo cria_saldo();

int le_ficheiro_alunos(Paluno aux);
int le_ficheiro_despesas(Pdespesas lista, Paluno lista_alunos);

void imprime(Paluno lista, int numero);
void imprime_saldo (Psaldo lista);

void ordena (Paluno lista, char * chave, Paluno *ant, Paluno *actual);
void ordena_saldo(Psaldo ,float numero,Psaldo *ant,Psaldo *inutil);
void ordena_despesas(Pdespesas lista ,int numero ,Pdespesas *ant,Pdespesas *actual);

void insere(Paluno lista,char nome[MAX],char Data_nascimento[MAX],int ano,char turma[MAX],int numero,float saldo);
void insere_saldo (Psaldo lista,Paluno lista_alunos, float chave);
void insere_despesa(Pdespesas lista, Paluno lista_alunos, char * descricao, char * data, int numero, float valor);

int procura (Paluno lista, int chave, Paluno *ant, Paluno *actual);
void procura_saldo (float chave, Paluno *ant, Paluno *actual, int count);

int elimina (Paluno lista, int numero);

void carregar (Paluno lista, int numero, float saldo);

void escreve_ficheiro_alunos(Paluno);
void escreve_ficheiro_despesas(Pdespesas);

#endif
