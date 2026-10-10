#ifndef ANALEX

#define ANALEX

#define TAM_MAX_LEXEMA 31

//Categoria do token
enum TOKEN_CAT
{
    ID = 1,
    SN,
    CT_I,
    FIM_EXPR,
    FIM_ARQ
};

/* Onde: ID: Identificador, SN: Sinal; CT_I: Constante numérica inteira */

enum SINAIS
{
    ATRIB = 1,
    
    //Operadores aritiméticos
    ADICAO,
    SUBTRACAO,
    MULTIPLIC,
    DIVISAO,
    
    //Delimitadores
    ABRE_PAR,
    FECHA_PAR,
    ABRE_CHA,
    FECHA_CHA,
    ABRE_COL,
    FECHA_COL,
    PONTO_VIRGULA,
    VIRGULA,

    //Operador relacional
    MAIOR,
    MAIOR_OU_IGUAL,
    MENOR,
    MENOR_OU_IGUAL,
    IGUALDADE,
    DIFERENTE,

    //Operador lógico
    AND,
    OR,
    NOT
}; // Sinais válidos da linguagem

typedef

    struct
{

    enum TOKEN_CAT cat; // deve receber uma das constantes de enum TOKEN_CAT

    union
    { // parte variável do registro

        int codigo; // para tokens das categorias SN

        char lexema[TAM_MAX_LEXEMA]; // cadeia de caracteres que corresponde ao nome do token da cat. ID

        int valInt; // valor da constante inteira em tokens da cat. CT_I
        //int valReal; // valor da constante inteira em tokens da cat. CT_I
    };

} TOKEN; // Tipo TOKEN

#endif

/* Contador de linhas do código fonte */

int contLinha = 1;