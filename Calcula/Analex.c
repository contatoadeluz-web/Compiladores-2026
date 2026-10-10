#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <direct.h>

#include "Analex.h"

#define TAM_LEXEMA 50
#define TAM_NUM 20

void error(char msg[])
{
    printf("%s\n", msg);
    exit(1);
}

TOKEN AnaLex(FILE *fd)
{
    int estado;
    char lexema[TAM_LEXEMA] = "";
    int tamL = 0;

    char digitos[TAM_NUM] = "";
    int tamD = 0;

    TOKEN t;

    estado = 0;

    while (true)
    {
        char c = fgetc(fd);

        switch (estado)
        {
        case 0:

            if (c == ' ' || c == '\t')
            {
                estado = 0;
            }

            else if (c >= 'a' && c <= 'z')
            {
                // inicio de identificador - inicializa lexema
                estado = 1;

                lexema[tamL] = c;
                lexema[++tamL] = '\0';
            }

            else if (c >= '0' && c <= '9')
            {
                // inicio de constante inteira - inicializa digitos
                estado = 10;

                digitos[tamD] = c;
                digitos[++tamD] = '\0';
            }

            else if (c == '+')
            {
                // sinal de adicao - monta e devolve token
                estado = 3;

                t.cat = SN;
                t.codigo = ADICAO;

                return t;
            }

            else if (c == '-')
            {
                // sinal de subtracao - monta e devolve token
                estado = 4;

                t.cat = SN;
                t.codigo = SUBTRACAO;

                return t;
            }

            else if (c == '*')
            {
                // sinal de multiplicacao - monta e devolve token
                estado = 6;

                t.cat = SN;
                t.codigo = MULTIPLIC;

                return t;
            }

            else if (c == '/')
            {
                // sinal de divisao - monta e devolve token
                estado = 5;

                t.cat = SN;
                t.codigo = DIVISAO;

                return t;
            }

            else if (c == '=')
            {
                // sinal de atribuicao - monta e devolve token
                estado = 7;

                t.cat = SN;
                t.codigo = ATRIB;

                return t;
            }

            else if (c == '(')
            {
                // sinal de abre parenteses - monta e devolve token
                estado = 8;

                t.cat = SN;
                t.codigo = ABRE_PAR;

                return t;
            }

            else if (c == ')')
            {
                // sinal de fecha parenteses - monta e devolve token
                estado = 9;

                t.cat = SN;
                t.codigo = FECHA_PAR;

                return t;
            }

            else if (c == '\n')
            {
                estado = 0;

                t.cat = FIM_EXPR;

                // fim de linha (ou expressao) encontrado
                contLinha++;

                return t;
            }

            else if (c == EOF)
            {
                // fim do arquivo fonte encontrado
                t.cat = FIM_ARQ;

                return t;
            }

            else
            {
                // sem transicao valida no AFD
                error("Caracter invalido na expressao!");
            }

            break;

        case 1:

            if ((c >= 'a' && c <= 'z') ||
                (c >= '0' && c <= '9') ||
                (c == '_'))
            {
                estado = 1;

                // acumula caracteres lidos em lexema
                lexema[tamL] = c;
                lexema[++tamL] = '\0';
            }

            else
            {
                // transicao OUTRO* do estado 1 do AFD
                estado = 2;

                // monta token identificador e retorna
                ungetc(c, fd);

                t.cat = ID;
                strcpy(t.lexema, lexema);

                return t;
            }

            break;

        case 10:

            if (c >= '0' && c <= '9')
            {
                estado = 10;

                // acumula digitos lidos na variavel digitos
                digitos[tamD] = c;
                digitos[++tamD] = '\0';
            }

            else
            {
                // transicao OUTRO* do estado 10 do AFD
                estado = 11;

                // monta token constante inteira e retorna
                ungetc(c, fd);

                t.cat = CT_I;
                t.valInt = atoi(digitos);

                return t;
            }

            break;
        }
    }
}

int main()
{
    FILE *fd;
    TOKEN tk;

    printf("Diretorio atual: %s\n", _getcwd(NULL, 0));

    fd = fopen("expressao.dat", "r");

    if (fd == NULL)
    {
        perror("Erro ao abrir expressao.dat");
        return 1;
    }

    printf("Arquivo aberto com sucesso!\n");

    /*A primeira linha é impressa aqui*/
    printf("LINHA %d ", contLinha);

    while (1)
    {
        // laço infinito para processar a expressão até o fim de arquivo
        tk = AnaLex(fd);

        switch (tk.cat)
        {
        case ID:

            printf("<ID, %s> ", tk.lexema);

            break;

        case SN:

            switch (tk.codigo)
            {
            case ADICAO:
                printf("<SN, ADICAO> ");
                break;

            case SUBTRACAO:
                printf("<SN, SUBTRACAO> ");
                break;

            case MULTIPLIC:
                printf("<SN, MULTIPLICACAO> ");
                break;

            case DIVISAO:
                printf("<SN, DIVISAO> ");
                break;

            case ATRIB:
                printf("<SN, ATRIBUICAO> ");
                break;

            case ABRE_PAR:
                printf("<SN, ABRE_PARENTESES> ");
                break;

            case FECHA_PAR:
                printf("<SN, FECHA_PARENTESES> ");
                break;
            }

            break;

        case CT_I:

            printf("\nINTCON: %d>\n", tk.valInt);

            break;

        case FIM_EXPR:

            printf("<FIM_EXPR>\n");
            printf("\nLINHA %d \n", contLinha);

            break;

        case FIM_ARQ:

            printf(" <Fim do arquivo encontrado>\n");

            break;
        }

        if (tk.cat == FIM_ARQ)
        {
            break;
        }
    }

    fclose(fd);

    return 0;
}