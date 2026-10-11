#ifndef ANALEX

#define ANALEX

#define TAM_MAX_LEXEMA 31

// Categoria do token
enum TOKEN_CAT
{
    ID = 1,        // IDENTIFICADOR

    PR, //PALAVRA RESERVADA

    CT_INTCON,     // INTCON
    CT_REALCON,    // REALCON
    CT_CARACCON,   // CHARCCON
    CT_CADEIACON,  //
    CT_COMENTARIO, // COMENTÁRO

    SN, // todos os outros carateres
        // válidos não enquadrados acima, são sinal, por eliminação

    OPERADORES,

    // Finaliazação
    FIM_EXPR,
    FIM_ARQ
};

enum SINAIS
{
    ATRIB = 1,

    // Operadores aritiméticos
    ADICAO,
    SUBTRACAO,
    MULTIPLIC,
    DIVISAO,

    // Delimitadores
    ABRE_PARENTESES,
    FECHA_PARENTESES,
    ABRE_CHAVES,
    FECHA_CHAVES,
    ABRE_COLCHETES,
    FECHA_COLCHETES,
    PONTO_VIRGULA,
    VIRGULA,
    
    // Operador relacional
    MAIOR,
    MAIOR_OU_IGUAL,
    MENOR,
    MENOR_OU_IGUAL,
    IGUALDADE,
    DIFERENTE,


}; // Sinais válidos da linguagem

// Operador lógico
enum OPERADORES
{   AND,
    OR,
    NOT
};

const char *definicao[] = {
    ".and.",   // Posição 1 (AND)
    ".or.",    // Posição 2 (OR)
    ".not."    // Posição 3 (NOT)
};

//Palavras reservadas

enum PALAVRAS_RESERVADAS
{
    PROG = 1,
    ENDPROG,
    VAR,
    ENDVAR,

    FUNC,
    ENDFUNC,
    PROC,
    ENDPROC,
    FWD,
    NOPARAM,

    CHAR,
    INT,
    REAL,
    BOOL,

    IF,
    ELSE,
    ENDIF,
    WHILE,
    ENDWHILE,
    RETURN,
    CALL,

    KEYBOARD,
    DISPLAY,
    DUP
};

const char *definicaoPR[] = {
    "",          // Posição 0 (não utilizada)

    "prog",      // 1  - PROG
    "endprog",   // 2  - ENDPROG
    "var",       // 3  - VAR
    "endvar",    // 4  - ENDVAR

    "func",      // 5  - FUNC
    "endfunc",   // 6  - ENDFUNC
    "proc",      // 7  - PROC
    "endproc",   // 8  - ENDPROC
    "fwd",       // 9  - FWD
    "noparam",   // 10 - NOPARAM

    "char",      // 11 - CHAR
    "int",       // 12 - INT
    "real",      // 13 - REAL
    "bool",      // 14 - BOOL

    "if",        // 15 - IF
    "else",      // 16 - ELSE
    "endif",     // 17 - ENDIF
    "while",     // 18 - WHILE
    "endwhile",  // 19 - ENDWHILE
    "return",    // 20 - RETURN
    "call",      // 21 - CALL

    "keyboard",  // 22 - KEYBOARD
    "display",   // 23 - DISPLAY
    "dup"        // 24 - DUP
};


typedef

    struct
{

    enum TOKEN_CAT cat; // deve receber uma das constantes de enum TOKEN_CAT

    union
    { // parte variável do registro

        int codigo; // para tokens das categorias SN

        char lexema[TAM_MAX_LEXEMA]; // cadeia de caracteres que corresponde ao nome do token da cat. ID

        int valInt; // valor da constante inteira em tokens da cat. CT_I
        // int valReal; // valor da constante inteira em tokens da cat. CT_I
    };

} TOKEN; // Tipo TOKEN

#endif

/* Contador de linhas do código fonte */

int contLinha = 1;