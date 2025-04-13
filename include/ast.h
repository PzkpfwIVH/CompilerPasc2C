// ast.h
#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdlib.h>

// ------------------------- AST 节点类型枚举 -------------------------
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    PROGRAMSTRUCT,
    PROGRAM_HEAD,
    PROGRAM_BODY,
    IDLIST,
    CONST_DECLARATIONS,
    CONST_DECLARATION,
    CONST_VALUE,
    VAR_DECLARATIONS,
    VAR_DECLARATION,
    TYPE,
    BASIC_TYPE,
    PERIOD,
    SUBPROGRAM_DECLARATIONS,
    SUBPROGRAM,
    SUBPROGRAM_HEAD,
    FORMAL_PARAMETER,
    PARAMETER_LIST,
    PARAMETER,
    VAR_PARAMETER,
    VALUE_PARAMETER,
    SUBPROGRAM_BODY,
    COMPOUND_STATEMENT,
    STATEMENT_LIST,
    STATEMENT,
    VARIABLE_LIST,
    VARIABLE,
    ID_VARPART,
    PROCEDURE_CALL,
    ELSE_PART,
    EXPRESSION_LIST,
    EXPRESSION,
    SIMPLE_EXPRESSION,
    TERM,
    FACTOR
} NodeType;

// ------------------------- 关键字类型枚举 -------------------------
typedef enum {
    PROGRAM,
    CONST,
    VAR,
    ARRAY,
    OF,
    INTEGER,
    REAL,
    BOOLEAN,
    CHAR,
    PROCEDURE,
    FUNCTION,
    BEGIN,
    END,
    IF,
    THEN,
    FOR,
    TO,
    DO,
    READ,
    WRITE,
    ELSE,
    NOT,
    TRUE,
    FALSE
} KeywordType;

// ------------------------- 操作符类型枚举 -------------------------
typedef enum {
    OP_EQ, OP_NE, OP_L, OP_LE, OP_G, OP_GE,     //RELOP运算符
    OP_ADD, OP_SUB, OP_OR,                      //ADDOP运算符
    OP_MUL, OP_D, OP_DIV, OP_MOD, OP_AND,       //MULOP运算符
    OP_ASSIGN                                   //ASSIGNOP运算符
} OperatorType;

// ------------------------- 字面量类型枚举 -------------------------
typedef enum {
    LIT_INTEGER,    // 整数字面量
    LIT_REAL,       // 实数字面量
    LIT_CHAR,        // 字符字面量
    LIT_BOOLEAN      // 布尔字面量
} LiteralType;

typedef enum{
    INTEGER_TYPE,
    REAL_TYPE,
    BOOLEAN_TYPE,
    CHAR_TYPE
}BasicType;

typedef enum{
    ARRAY_TYPE
}AdvancedType;

// ------------------------- AST 节点结构定义 -------------------------
typedef struct ASTNode {
    NodeType node_type;
    union{
        KeywordType key_type;
        OperatorType op_type;
        LiteralType lit_type;
        BasicType bas_type;
        AdvancedType adv_type;
    }val_type;
    union{
        char * str;
        int val;
        float fval;
    }value;
    int lineno;
    struct ASTNode * parent;
    struct ASTNode * brother;
    struct ASTNode * child;
} ASTNode;

// ------------------------- AST 接口定义 -------------------------
ASTNode * root = NULL;


// ------------------------- AST 接口定义 -------------------------
ASTNode *create_astnode(NodeType node_type);

void free_astnode(ASTNode *root);

bool check_node_type(ASTNode *Node1, ASTNode *Node2);

#endif // AST_H