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

int verificaPR(char lexema[TAM_LEXEMA])
{
    for (int i = 1; i <= DUP; i++)
    {
        if (strcmp(lexema, definicaoPR[i]) == 0)
        {
            return i;
        }
    }

    return 0;
}

TOKEN AnaLex(FILE *fd)
{
    int estado;
    char lexema[TAM_LEXEMA] = "";
    int tamL = 0;

    char digitos[TAM_NUM] = "";
    int tamD = 0;

    // Operadores lógicos

    // Lista de operadores
    // Tamanho dos operadores

    const enum OPERADORES logicos[] = {AND, OR, NOT};
    const int qtd_operadores = sizeof(logicos) / sizeof(logicos[0]);

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

            else if (c == '(')
            {
                // sinal de abre parenteses - monta e devolve token
                estado = 1;

                t.cat = SN;
                t.codigo = ABRE_PARENTESES;

                return t;
            }

            else if (c == ')')
            {
                // sinal de fecha parenteses - monta e devolve token
                estado = 2;

                t.cat = SN;
                t.codigo = FECHA_PARENTESES;

                return t;
            }

            else if (c == '[')
            {
                // sinal de abre cholchetes
                estado = 3;

                t.cat = SN;
                t.codigo = ABRE_COLCHETES;

                return t;
            }

            else if (c == ']')
            {
                // sinal de fecha colchetes
                estado = 4;

                t.cat = SN;
                t.codigo = FECHA_COLCHETES;

                return t;
            }

            else if (c == '{')
            {
                // sinal de abre chaves
                estado = 4;
                t.cat = SN;
                t.codigo = ABRE_CHAVES;

                return t;
            }

            else if (c == '}')
            {
                // sinal de fecha chaves
                estado = 6;

                t.cat = SN;
                t.codigo = FECHA_CHAVES;

                return t;
            }

            else if (c == '#')
            {
                // Diferente
                estado = 7;

                t.cat = SN;
                t.codigo = DIFERENTE;

                return t;
            }

            else if (c == '.')
            {
                estado = 8;

                lexema[tamL] = c;
                lexema[++tamL] = '\0';
            }

            else if (c == ',')
            {
                // sinal de divisao - monta e devolve token
                estado = 11;

                t.cat = SN;
                t.codigo = VIRGULA;

                return t;
            }

            else if (c == '*')
            {
                // sinal de multiplicacao - monta e devolve token
                estado = 12;

                t.cat = SN;
                t.codigo = MULTIPLIC;

                return t;
            }

            else if (c == '+')
            {
                // sinal de adicao - monta e devolve token
                estado = 13;

                t.cat = SN;
                t.codigo = ADICAO;

                return t;
            }

            else if (c == '-')
            {
                // sinal de subtracao - monta e devolve token
                estado = 14;

                t.cat = SN;
                t.codigo = SUBTRACAO;

                return t;
            }

            else if (c == ';')
            {
                // PONTO e VÍRGULA
                estado = 15;

                t.cat = SN;
                t.codigo = PONTO_VIRGULA;

                return t;
            }

            else if (c == '>')
            {
                estado = 16;
            }

            else if (c == '<')
            {
                estado = 19;
            }

            else if (c == '/')
            {
                estado = 22;
            }

            else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
            {
                // inicio de identificador - inicializa lexema
                estado = 25;

                lexema[tamL] = c;
                lexema[++tamL] = '\0';
            }

            else if (c >= '0' && c <= '9')
            {
                estado = 27;

                // acumula digitos lidos na variavel digitos
                digitos[tamD] = c;
                digitos[++tamD] = '\0';

                // return t;
            }

            // Char: aspas simples
            else if (c == '\'')
            {
                estado = 31;

                lexema[tamL] = c;
                lexema[++tamL] = '\0';
            }

            // String: aspas duplas
            else if (c == '"')
            {
                estado = 36;

                lexema[tamL] = c;
                lexema[++tamL] = '\0';
            }

            else if (c == '=')
            {
                // sinal de atribuicao - monta e devolve token
                estado = 41;
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
        case 8:

            if (c >= 'a' && c <= 'z')
            {
                lexema[tamL] = c;
                lexema[++tamL] = '\0';
            }
            else if (c == '.')
            {
                lexema[tamL] = c;
                lexema[++tamL] = '\0';

                for (int i = 0; i < qtd_operadores; i++)
                {
                    if (strcmp(lexema, definicao[i]) == 0)
                    {
                        t.cat = OPERADORES;
                        t.codigo = logicos[i];

                        switch (t.codigo)
                        {
                        case AND:
                            // continua 8
                            break;

                        case NOT:
                            estado = 9;
                            break;

                        case OR:
                            estado = 10;
                            break;

                        default:
                            break;
                        }

                        return t;
                    }
                }

                error("Operador logico invalido!");
            }

            break;
        case 16:

            if (c == '=')
            {
                estado = 18;
                t.cat = SN;
                t.codigo = MAIOR_OU_IGUAL;
                return t;
            }
            else
            {
                estado = 17;
                t.cat = SN;
                t.codigo = MAIOR;
                return t;
            }

            break;
        case 19:

            if (c == '=')
            {
                estado = 21;
                t.cat = SN;
                t.codigo = MENOR_OU_IGUAL;
                return t;
            }
            else
            {
                estado = 20;
                t.cat = SN;
                t.codigo = MENOR;
                return t;
            }

            break;
        case 25:

            if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) || isdigit((unsigned char)c))
            {

                // Acumula caracteres em lexema
                lexema[tamL] = c;
                lexema[++tamL] = '\0';
            }
            else
            {
                // Transição para o estado final do identificador
                ungetc(c, fd);
                estado = 26;

                // Verifica palavras reservadas
                int codigoPR = verificaPR(lexema);

                if (codigoPR != 0)
                {
                    t.cat = PR;
                    t.codigo = codigoPR;
                    strcpy(t.lexema, lexema);
                    return t;
                }

                // Se não for palavra reservada, retorna ID
                t.cat = ID;
                strcpy(t.lexema, lexema);

                return t;
            }

            break;

        case 27:

            if (c >= '0' && c <= '9')
            {
                // acumula digitos lidos na variavel digitos
                digitos[tamD] = c;
                digitos[++tamD] = '\0';
            }

            else
            {
                // transicao OUTRO* do estado 10 do AFD
                estado = 29;

                // monta token constante inteira e retorna
                ungetc(c, fd);

                t.cat = CT_INTCON;
                t.valInt = atoi(digitos);

                return t;
            }

            break;

        case 31:

            //char
            break;

        case 36:

            
            //Caractere
            break;

        case 41:

            if (c == '=')
            {
                estado = 42;
                t.cat = SN;
                t.codigo = COMPARACAO;
                return t;
            }
            else
            {
                estado = 43;
                t.cat = SN;
                t.codigo = ATRIB;
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
        case PR:
            printf("<PR, %s> ", tk.lexema);
            break;
        case CT_INTCON:
            printf("\nINTCON: %d>\n", tk.valInt);
            break;
        case CT_REALCON:

            break;
        case CT_CARACCON:

            break;
        case CT_CADEIACON:

            break;
        case CT_COMENTARIO:

            break;
        case OPERADORES:
            switch (tk.codigo)
            {
            case AND:
                printf("<OPERADOR LÓGICO, AND> ");
                break;

            case NOT:
                printf("<OPERADOR LÓGICO, NOT> ");
                break;

            case OR:
                printf("<OPERADOR LÓGICO, OR> ");
                break;
            }

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

            case ABRE_PARENTESES:
                printf("<SN, ABRE_PARENTESES> ");
                break;

            case FECHA_PARENTESES:
                printf("<SN, FECHA_PARENTESES> ");
                break;

            case ABRE_COLCHETES:
                printf("<SN, ABRE_COLCHETES> ");
                break;

            case FECHA_COLCHETES:
                printf("<SN, FECHA_COLCHETES> ");
                break;

            case ABRE_CHAVES:
                printf("<SN, ABRE_CHAVES> ");
                break;

            case FECHA_CHAVES:
                printf("<SN, FECHA_CHAVES> ");
                break;

            case DIFERENTE:
                printf("<SN, DIFERENTE> ");
                break;

            case COMPARACAO:
                printf("<SN, COMPARAÇÃO> ");
                break;

            case MENOR:
                printf("<SN, MENOR> ");
                break;

            case MENOR_OU_IGUAL:
                printf("<SN, MENOR OUR IGUAL> ");
                break;

            case MAIOR:
                printf("<SN, MAIOR> ");
                break;

            case MAIOR_OU_IGUAL:
                printf("<SN, MAIOR OUR IGUAL> ");
                break;
            }
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
