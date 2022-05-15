#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//トークンの種類
typedef enum {
    TK_RESERVED, //記号
    TK_IDENT, //識別子
    TK_NUM, //整数トークン
    TK_EOF, //入力の終わりを表わすトークン
} TokenKind;

typedef struct Token Token;
//トークン型
struct Token {
    TokenKind kind; //トークンの型
    Token *next; //次の入力のトークン
    int val; //kindがTK_NUMの場合、その数値
    char *str; //トークン文字列
    int len; //トークンの長さ
};

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);
char *strndup(char *p, int len);
Token *consume_ident();
void expect(char *op);
int expect_number();
bool at_eof();
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
Token *tokenize();

extern char *user_input;
extern Token *token;


typedef struct Var Var;
struct Var {
    Var *next;
    char *name;
    int offset;
};

//抽象構文木のノードの種類
typedef enum {
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_EQ, // ==
    ND_NE, // !=
    ND_LT, // <
    ND_LE, // <= 
    ND_NUM, //整数
    ND_ASSIGN, // =
    ND_VAR, //ローカル変数
    ND_RETURN,
    ND_EXPR_STMT,
} NodeKind;

typedef struct Node Node;
//抽象構文木のノードの型
struct Node {
    NodeKind kind; //ノードの型
    Node *next;
    Node *lhs; //左辺
    Node *rhs; //右辺
    Var *var;
    int val; //kindがND_NUMの場合のみ
};

typedef struct {
    Node *node;
    Var *locals;
    int stack_size;    
} Program;

Program *program();

void codegen(Program *prog);
