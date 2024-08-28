#include "listas.h"
#include <strings.h>


Paluno cria() {  //cria a lista de alunos com uma estrutura Aluno e um ponteiro para um NoAluno e devolve o ponteiro para esse nó que criou (cabeçalho)
    Paluno aux;
    struct Aluno p1 = {"", "", 0, "", 0, 0};
    aux = (Paluno) malloc(sizeof(NoAluno)); //aloca espaço para o nó da lista (cabeçalho)

    if (aux) {
        aux->aluno = p1;
        aux->prox = NULL;
    }
    return aux;
}

Psaldo cria_saldo() { //cria a lista de ordenamento de saldos com um ponteiro para um NoAluno e outro para um NoSaldo e devolve o ponteiro para esse nó que criou (cabeçalho)
    Psaldo aux;
    aux = (Psaldo) malloc(sizeof(NoSaldo)); //aloca espaço para o nó da lista (cabeçalho)
    if (aux) {
        aux->no_aluno = NULL;
        aux->prox = NULL;
    }
    return aux;
}

Pdespesas cria_despesa() { //cria a lista de despesas com uma estrutura Despesa e um ponteiro para um NoDespesa e devolve o ponteiro para esse nó que criou (cabeçalho)
    Pdespesas aux;
    struct Despesa p1 = {0, 0, "", ""};
    aux = (Pdespesas) malloc(sizeof(NoDespesas)); //aloca espaço para o nó da lista (cabeçalho)

    if (aux) {
        aux->despesa = p1;
        aux->no__aluno = NULL;
        aux->prox = NULL;
    }
    return aux;
}

int le_ficheiro_alunos(Paluno lista) { //le a informação guardada no ficheiro Alunos e guarda-a na nós na lista_alunos
    char linha[MAX], nome[MAX], Data_nascimento[MAX], turma[MAX];
    int numero, ano, count = 1;
    float saldo = 0;

    FILE *ficheiro_alunos = fopen("C:\\Users\\tikit\\CLionProject\\Projeto PPP\\Alunos", "r"); //abre o ficheiro Alunos em modo leitura

    if (ficheiro_alunos == NULL) {
        printf("\n-----------------------------\nFicheiro de Alunos Nao Encontrado.\n-----------------------------\n");
        return 1;
    } else
        printf("\n-----------------------------\nFicheiro de Aluno Encontrado.\n-----------------------------\n");

    while (fgets(linha, MAX - 1, ficheiro_alunos) != NULL) { //ler as linhas todas do ficheiro

        if (count == 1) {
            strcpy(nome, linha);
            int len = (int) strlen(nome);
            if (nome[len - 1] == '\n') //substitui o último caracter lido pela funcção "strcpy" por "\0" caso este seja um "\n"
                nome[len - 1] = '\0';
        }

        if (count == 2)
            if (sscanf(linha, "%s %d %s %d %f", &Data_nascimento, &ano, &turma, &numero, &saldo) != 5) {
                printf("Erro no Sscanf\n---------------------\n");
                return 1;
            }

        if (count == 3) {
            insere(lista, nome, Data_nascimento, ano, turma, numero, saldo); //insere os dados lidos num NoAluno
            count = 0;
        }
        count++;
    }
    fclose(ficheiro_alunos); //fecha o ficheiro Despesas
    return 0;
}

int le_ficheiro_despesas(Pdespesas lista_despesas, Paluno lista_alunos) { //le a informação guardada no ficheiro Despesas e guarda-a em nós na lista_despesas
    char linha[MAX], descricao[MAX], data[MAX];
    int numero, count = 1;
    float valor = 0;

    FILE *ficheiro_despesas = fopen("C:\\Users\\tikit\\CLionProject\\Projeto PPP\\Despesas", "r"); //abre o ficheiro Alunos em modo leitura

    if (ficheiro_despesas == NULL) {
        printf("\n------------------------------------\nFicheiro de Despesas Nao Encontrado.\n------------------------------------\n");
        return 1;
    }

    else
        printf("\n--------------------------------\nFicheiro de Despesas Encontrado.\n--------------------------------\n");

    while (fgets(linha, MAX - 1, ficheiro_despesas) != NULL) { //ler as linhas todas do ficheiro

        if (count == 1) {
            strcpy(descricao, linha);
            int len = (int) strlen(descricao);
            if(descricao[len - 1] == '\n') //substitui o último caracter lido pela funcção "strcpy" por "\0" caso este seja um "\n"
                descricao[len - 1] = '\0';
        }

        if (count == 2)
            if(sscanf(linha, "%d %f %s", &numero, &valor, &data)!=3) {
                printf("\n---------------------\nErro no Sscanf\n---------------------\n");
                return 1;
            }

        if (count == 3) {
            insere_despesa(lista_despesas, lista_alunos, descricao, data, numero, valor); //insere os dados lidos num NoDespesas
            count = 0;
        }
        count++;
    }
    fclose(ficheiro_despesas); //fecha o ficheiro Despesas
    return 0;
}

void insere(Paluno lista, char * nome,char * Data_nascimento,int ano,char * turma,int numero,float saldo) {//adiciona um NoAluno à lista_alunos
    Paluno no, ant, actual;
    no = (Paluno) malloc(sizeof(NoAluno));

    if (no != NULL) {
        strcpy(no->aluno.Nome, nome);
        strcpy(no->aluno.Data_nascimento, Data_nascimento);
        no->aluno.ano = ano;
        strcpy(no->aluno.turma, turma);
        no->aluno.numero = numero;
        no->aluno.saldo = saldo;
        ordena(lista, nome, &ant, &actual);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

void insere_saldo (Psaldo lista_saldo,Paluno lista_alunos,float numero) { //insere um NoSaldo na lista_saldo
    Paluno actual, anterior;
    int count = 0;
    anterior = lista_alunos;
    actual = lista_alunos->prox;
    while (actual) {
        procura_saldo(numero, &anterior, &actual, count);
        if (actual) {
            float numero_no = actual->aluno.saldo;
            Psaldo no, ant, inutil;
            no = (Psaldo) malloc(sizeof(NoSaldo));
            if (no) { //Ordena os saldos (inferiores a um determinado valor) por ordem decrescente
                no->no_aluno = actual;
                ordena_saldo(lista_saldo, numero_no, &ant, &inutil);
                no->prox = ant->prox;
                ant->prox = no;
            }
        }
        count++; //incrementado o contador utilizado na função procura_saldo.
    }
}

void insere_despesa(Pdespesas lista_despesas, Paluno lista_alunos, char * descricao, char * data, int numero, float valor){ //adiciona um NoDespesa à lista_despesas
    Paluno anterior, atual;
    Pdespesas no, ant, act;
    no = (Pdespesas) malloc(sizeof(NoDespesas)); //aloca espaço na memória para um novo NoDespesas

    if (no != NULL) {
        strcpy(no->despesa.descricao, descricao);
        strcpy(no->despesa.data, data);
        no->despesa.valor = valor;
        no->despesa.numero_aluno = numero;
        procura(lista_alunos,numero,&anterior,&atual);
        no->no__aluno=atual;
        ordena_despesas(lista_despesas, numero, &ant, &act);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

void carregar (Paluno aux, int numero, float saldo){ //adiciona um determinado valor pertendido ao valor do saldo do aluno
    Paluno ant, actual;
    char resposta [100];
    procura(aux, numero, &ant, &actual);

    if (actual==NULL) //segurança no caso de o aluno nao constar na lista_alunos
        printf("\n--------------------------------------------\n----ERRO CARREGAR - Aluno nao encontrado----\n--------------------------------------------\n\n");

    else {
        printf("---CARREGAR %.2f EUROS A %s [S/N]---\n",saldo, actual->aluno.Nome);
        scanf("%s",resposta);
        if (strcasecmp(resposta, "S") == 0) {
            actual->aluno.saldo = (actual->aluno.saldo) + saldo; //incrementa ao saldo do aluno, o valor desejado.
            printf("-----------------------------------\n----SALDO CARREGADO COM SUCESSO----\n---SALDO DISPONIVEL: %.2f EUROS---\n-----------------------------------\n\n",actual->aluno.saldo);
        }
        else
            printf("------------------------\n---OPERACAO CANCELADA---\n------------------------\n\n");
    }
}

int elimina (Paluno lista, int numero) { //elimina um aluno
    Paluno ant, actual;
    char resposta[100];
    procura(lista, numero, &ant, &actual);
    if (actual != NULL) {
        printf("---------------------------------------------------\n----ELIMINAR %s NUMERO %d [S/N]----\n---------------------------------------------------\n", actual->aluno.Nome,actual->aluno.numero);
        scanf(" %s", resposta);
        if (strcasecmp(resposta, "S") == 0) {
            ant->prox = actual->prox;
            free(actual); //liberta a memória do no que continha a informação do aluno a eliminar
        }
        return 1;
    }
    else{
        printf("--------------------------------------------\n----ERRO ELIMINAR - Aluno nao encontrado----\n--------------------------------------------\n\n");
        return 0;
    }
}

void imprime (Paluno aux, int numero) { //apresenta os dados presentes num NoAluno que contenha as informações do aluno desejado
    Paluno ant, actual;
    procura(aux, numero, &ant, &actual); //encontra o aluno desejado
    aux = actual;
    if (aux==NULL)
        printf("----------------------------------------------------\n----ERRO APRESENTAR DADOS - Aluno nao encontrado----\n----------------------------------------------------\n\n");
    else
        printf("\n-------------------------------\n%s\n%s %d %s %d %.2f\n-------------------------------\n\n", aux->aluno.Nome, aux->aluno.Data_nascimento, aux->aluno.ano, aux->aluno.turma,aux->aluno.numero, aux->aluno.saldo);
}

void imprime_saldo (Psaldo lista_saldo){ //apresenta os dados dos alunos que tenham saldo inferior a um determinado valor, imprimindo a lista_saldo na íntegra.
    Psaldo aux = lista_saldo->prox; //salta o cabeçalho da lista_saldo
    while (aux) {
        printf("\n-------------------------------\n%s\n%s %d %s %d %.2f\n-------------------------------\n\n",aux->no_aluno->aluno.Nome, aux->no_aluno->aluno.Data_nascimento, aux->no_aluno->aluno.ano,aux->no_aluno->aluno.turma, aux->no_aluno->aluno.numero, aux->no_aluno->aluno.saldo);
        aux = aux->prox;
    }
}

void ordena (Paluno lista, char * chave, Paluno *ant, Paluno *actual) { //ordena os alunos por ordem alfabetica
    *ant = lista;
    *actual = lista->prox;

    while (((*actual) != NULL) && (strcasecmp((*actual)->aluno.Nome, chave) < 0)) {
        *ant = *actual;
        *actual = (*actual)->prox;
    }

    if (((*actual) != NULL) && (strcasecmp((*actual)->aluno.Nome, chave) != 0))
        *actual = NULL;

}

void ordena_saldo(Psaldo lista ,float numero ,Psaldo *ant,Psaldo *actual){  //encontra o primeiro NoSaldo com menor valor de saldo do que o valor fornecido
    *ant = lista;
    *actual = lista->prox;

    while (((*actual) != NULL) && ((*actual)->no_aluno->aluno.saldo)>=numero) {
        *ant = *actual;
        *actual = (*actual)->prox;
    }
}

void ordena_despesas(Pdespesas lista ,int numero ,Pdespesas *ant,Pdespesas *actual) { //ordena as depesas de forma que as realizadas pelos mesmos alunos fiquem juntas
    *ant = lista;
    *actual = lista->prox;

    while (((*actual) != NULL) && ((*actual)->despesa.numero_aluno) != numero) {
        *ant = *actual;
        *actual = (*actual)->prox;
    }

    while (((*actual) != NULL) && ((*actual)->despesa.numero_aluno) == numero) {
        *ant = *actual;
        *actual = (*actual)->prox;
    }
}

int procura (Paluno lista, int chave, Paluno *ant, Paluno *actual) { //procura o aluno com o número pretendido
    *ant = lista;
    *actual = lista->prox;

    while (((*actual) != NULL) && (chave!=((*actual)->aluno.numero))) {
        *ant = *actual;
        *actual = (*actual)->prox;
    }

    return 0;
}

void procura_saldo (float chave, Paluno *ant, Paluno *actual, int count) { //procura alunos que tenham saldo inferior a um determinado valor

    if (((*actual) != NULL) && (chave >= ((*actual)->aluno.saldo))&&count!=0) { //count serve para quando o primeiro aluno da lista de alunos, satisfaz a condição do if. Logo o aluno nunca seria inserido na lista_saldo.
        *ant = *actual;
        *actual = (*actual)->prox;
    }

    while (((*actual) != NULL) && (chave <= ((*actual)->aluno.saldo))) { //só acaba o while quando encontrar um aluno com saldo inferior ao da chave.
        *ant = *actual;
        *actual = (*actual)->prox;
    }
}

void escreve_ficheiro_alunos(Paluno lista_alunos) { //guarda os dados dos alunos no ficheiro Alunos
    FILE *ficheiro_alunos = fopen("C:\\Users\\tikit\\CLionProject\\Projeto PPP\\Alunos", "w"); //abre o ficheiro Alunos em modo escrita
    Paluno aux = lista_alunos->prox; // Salta o cabeçalho da lista_alunos
    while (aux) {
        fprintf(ficheiro_alunos, "%s\n%s %d %s %d %.2f\n\n", aux->aluno.Nome, aux->aluno.Data_nascimento, aux->aluno.ano, aux->aluno.turma, aux->aluno.numero, aux->aluno.saldo);
        aux=aux->prox;
    }
    fclose(ficheiro_alunos);//fecha o ficheiro alunos
}

void escreve_ficheiro_despesas(Pdespesas lista_despesas) { //guarda os dados dos alunos no ficheiro Despesas
    FILE *ficheiro_alunos = fopen("C:\\Users\\tikit\\CLionProject\\Projeto PPP\\Despesas", "w"); //abre o ficheiro Despesas em modo escrita
    Pdespesas aux = lista_despesas->prox; // Salta o cabeçalho da lista_despesas
    while (aux) {
        fprintf(ficheiro_alunos, "%s\n%d %.2f %s\n\n", aux->despesa.descricao, aux->despesa.numero_aluno, aux->despesa.valor, aux->despesa.data);
        aux=aux->prox;
    }
    fclose(ficheiro_alunos);//fecha o ficheiro alunos
}
