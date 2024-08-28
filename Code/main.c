#include <stdio.h>
#include "listas.h"


int main() {
    printf("\n-----------A inicializar programa - por favor aguarde-----------\n");
    Paluno lista_alunos;
    Pdespesas lista_despesas;
    char funcionalidade[MAX], resposta[MAX], data[MAX];
    lista_alunos = cria();                      //cria o cabeçalho da lista de alunos
    lista_despesas = cria_despesa(); //cria o cabeçalho da lista de despesas
    if (le_ficheiro_alunos(lista_alunos) == 1){ //le os dados do ficheiro que contem os dados dos alunos e guarda-os em nós da lista de alunos
        printf("\n-----ERRO A INICIALIZAR PROGRAMA - ficheiro alunos -----\n");
        return 1;
    }
    if (le_ficheiro_despesas(lista_despesas, lista_alunos) == 1){ //le os dados do ficheiro que contem os dados dos alunos e guarda-os em nós da lista de alunos
        printf("\n-----ERRO A INICIALIZAR PROGRAMA - ficheiro despesas -----\n");
        return 1;
    }
    printf("\n-----------INTRODUZA A DATA DE HOJE (dd/mm/aaaa):"); //Na lista de despesas, cada despesa tem uma data associada a sua realização. É então pedido ao utilizador assim que inicia o programa que indique a data de hoje para que todas as despesas realizadas nesse dia tenham a mesma data sem ter de pedir ao utilizador que a indique a cada compra.
    scanf("%s", data);
    fflush(stdin);
    printf("\n-----------Programa pronto a usar-----------\n\n");

    do { //pergunta ao utilizador que funcionalidade deseja realizar e compara o input do utilizador com as funcionalidades disponiveis do programa, até o utilizador terminar o programa.

        printf("---Digite a funcionalidade deseja realizar - Inserir, Eliminar, Carregar Saldo, Realizar Compra, Apresentar Dados, Saldo Inferior ---\n---(ou digite -Terminar- para terminar o programa)---\n\n");
        gets(funcionalidade);

        if (strcasecmp(funcionalidade, "Inserir") == 0) {
            printf("----INSERIR NOVO ALUNO [S/N]----\n");
            gets(resposta);
            if (strcasecmp(resposta, "S") == 0) {
                char nome[MAX], data_nascimento[MAX], turma[MAX];
                Paluno ant, actual;
                int ano, numero;
                float saldo;
                printf("Introduza o nome do aluno:");
                gets(nome);
                printf("Introduza a data de nascimento do aluno (dd/mm/aaaa):");
                gets(data_nascimento);
                printf("Introduza a turma do aluno:");
                gets(turma);
                printf("Introduza o ano do aluno:");
                if (scanf("%d", &ano) != 1) {
                    printf("\n--------------------------------------------\nERRO NO SCANF\n--------------------------------------------\n");
                    break;
                }
                printf("Introduza o numero do aluno:");
                if (scanf("%d", &numero) != 1) {
                    printf("\n--------------------------------------------\nERRO NO SCANF\n--------------------------------------------\n");
                    break;
                }
                procura(lista_alunos, numero, &ant, &actual);
                if (actual) {
                    printf("\n-------------------------------------------------\n-----ERRO - NUMERO ATRIBUIDO A OUTRO ALUNO-----\n-------------------------------------------------\n\n");
                    break;
                } else {
                    printf("Introduza o saldo do aluno:");
                    if (scanf("%f", &saldo) != 1) {
                        printf("\n--------------------------------------------\nERRO NO SCANF\n--------------------------------------------\n");
                        break;
                    }
                    insere(lista_alunos, nome, data_nascimento, ano, turma, numero, saldo);
                    procura(lista_alunos, numero, &ant, &actual);
                    if (actual != NULL)
                        printf("\n--------------------------------------------\n---------Aluno inserido com sucesso---------\n--------------------------------------------\n\n");
                }
            }
        }

        if (strcasecmp(funcionalidade, "Realizar Compra") == 0) {

            char descricao[MAX];
            Paluno ant, actual;
            int numero;
            float valor;
            printf("Produto Adquirido:");
            gets(descricao);
            printf("Introduza o numero do aluno:");
            if (scanf("%d", &numero) != 1) {
                printf("\n--------------------------------------------\nERRO NO SCANF\n--------------------------------------------\n");
                break;
            }

            printf("Introduza o valor da compra:");
            if (scanf("%f", &valor) != 1) {
                printf("\n--------------------------------------------\nERRO NO SCANF\n--------------------------------------------\n");
                break;
            }

            printf("----REALIZAR DESPESA: %s - %.2f EUROS [S/N]----\n",descricao,valor);
            scanf("%s",resposta);
            if (strcasecmp(resposta, "S") == 0) {
                procura(lista_alunos, numero, &ant, &actual);
                if (actual->aluno.saldo < valor) {  //compara o saldo do aluno com o valor da compra e se for menor imprime um aviso
                    fflush(stdin);
                    printf("\n--------------------------------------------\n-------------SALDO INSUFICIENTE-------------\n");
                    printf("--------------------%.2f--------------------\n--------------------------------------------\n\n",actual->aluno.saldo);
                } else {
                    insere_despesa(lista_despesas, lista_alunos, descricao, data, numero, valor);
                    actual->aluno.saldo = (actual->aluno.saldo) - valor;
                    if (actual != NULL)
                        printf("\n-----------------------------------------------\n---------Despesa realizada com sucesso---------\n--------------Saldo actual: %.2f---------------\n-----------------------------------------------\n\n",actual->aluno.saldo);
                }
            }
        }

        if (strcasecmp(funcionalidade, "Eliminar") == 0) {
            printf("----ELIMINAR ALUNO [S/N]----\n");
            gets(resposta);
            if (strcasecmp(resposta, "S") == 0) {
                int numero;
                Paluno anterior, atual;
                printf("Introduza o numero do aluno:");
                if (scanf("%d", &numero) != 1) {
                    printf("ERRO NO SCANF\n--------------------------------------------\n");
                    break;
                }
                if (elimina(lista_alunos, numero) != 0) {
                    procura(lista_alunos, numero, &anterior, &atual);
                    if (atual == NULL)
                        printf("--------------------------------------------\n--------Aluno eliminado com sucesso---------\n--------------------------------------------\n\n");
                }
            }
        }

        if (strcasecmp(funcionalidade, "Apresentar dados") == 0) {
            printf("----APRESNTAR DADOS DE ALUNO [S/N]----\n");
            gets(resposta);
            if (strcasecmp(resposta, "S") == 0) {
                int numero;
                printf("Introduza o numero do aluno:");
                if (scanf("%d", &numero) != 1) {
                    printf("ERRO NO SCANF\n--------------------------------------------\n");
                    break;
                }
                imprime(lista_alunos, numero);
            }
        }

        if (strcasecmp(funcionalidade, "Carregar Saldo") == 0) {
            printf("----CARREGAR SALDO DE ALUNO [S/N]----\n");
            gets(resposta);
            if (strcasecmp(resposta, "S") == 0) {
                float saldo;
                int numero;
                printf("Introduza o numero do aluno:");
                if (scanf("%d", &numero) != 1) {
                    printf("ERRO NO SCANF\n--------------------------------------------\n");
                    break;
                }
                printf("Introduza o valor a carregar:");
                if (scanf("%f", &saldo) != 1) {
                    printf("ERRO NO SCANF\n--------------------------------------------\n");
                    break;
                }
                carregar(lista_alunos, numero, saldo);
            }
        }

        if (strcasecmp(funcionalidade, "Saldo Inferior") == 0) {
            Psaldo lista_saldo;
            float valor_max = 0;
            printf("Introduza o valor maximo:");
            scanf("%f", &valor_max);
            printf("\n----VER ALUNOS COM SALDO INFERIOR A %.2f [S/N]----\n",valor_max);
            scanf("%s",resposta);
            if (strcasecmp(resposta, "S") == 0) {
                lista_saldo = cria_saldo();
                insere_saldo(lista_saldo, lista_alunos, valor_max);
                imprime_saldo(lista_saldo);
            }
        }

        if (strcasecmp(funcionalidade, "Terminar") == 0) {
            escreve_ficheiro_alunos(lista_alunos); //guarda os dados de cada no da lista de alunos no ficheiro "Alunos"
            escreve_ficheiro_despesas(lista_despesas);  //guarda os dados de cada no da lista de despesas no ficheiro "Despesas"
            printf("---PROGRAMA TERMINADO---");
        }

        fflush(stdin);
    } while (strcasecmp(funcionalidade, "Terminar") != 0);

    return 0;
}