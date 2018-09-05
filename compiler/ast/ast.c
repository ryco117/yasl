#include <debug.h>
#include "ast.h"

Node *node_clone(const Node *const node) {
    if (node == NULL) return NULL;
    Node *clone = malloc(sizeof(Node));
    clone->nodetype = node->nodetype;
    clone->type = node->type;
    clone->children_len = node->children_len;
    clone->children = malloc(clone->children_len * sizeof(Node));
    for (int i = 0; i < clone->children_len; i++) {
        clone->children[i] = node_clone(node->children[i]);
    }
    clone->name_len = node->name_len;
    clone->name = malloc(node->name_len);
    memcpy(clone->name, node->name, clone->name_len);
    clone->line = node->line;
    return clone;
}


static Node *new_Node_0(AST nodetype, Token type, char *name /* OWN */, int64_t name_len, int line) {
    Node *node = malloc(sizeof(Node));
    node->nodetype = nodetype;
    node->type = type;
    node->children = NULL;
    node->children_len = 0;
    node->name_len = name_len;
    node->name = name;
    node->line = line;
    return node;
}

static Node *new_Node_1(AST nodetype, Token type, Node *child /* OWN */, char *name /* OWN */, int64_t name_len, int line) {
    Node *node = malloc(sizeof(Node));
    node->nodetype = nodetype;
    node->type = type;
    node->children = malloc(1 * sizeof(Node*));
    node->children[0] = child;
    node->children_len = 1;
    node->name_len = name_len;
    node->name = name;
    node->line = line;
    return node;
}

static Node *new_Node_2(AST nodetype, Token type, Node *child1 /* OWN */, Node *child2 /* OWN */, char *name /* OWN */, int64_t name_len, int line) {
    Node *node = malloc(sizeof(Node));
    node->nodetype = nodetype;
    node->type = type;
    node->children = malloc(2 * sizeof(Node*));
    node->children[0] = child1;
    node->children[1] = child2;
    node->children_len = 2;
    node->name_len = name_len;
    node->name = name;
    node->line = line;
    return node;
}

static Node *new_Node_3(AST nodetype, Token type, Node *child1 /* OWN */, Node *child2 /* OWN */, Node *child3 /* OWN */, char *name /* OWN */, int64_t name_len, int line) {
    Node *node = malloc(sizeof(Node));
    node->nodetype = nodetype;
    node->type = type;
    node->children = malloc(3 * sizeof(Node*));
    node->children[0] = child1;
    node->children[1] = child2;
    node->children[2] = child3;
    node->children_len = 3;
    node->name_len = name_len;
    node->name = name;
    node->line = line;
    return node;
}


Node *new_ExprStmt(Node *child, int line) {
    return new_Node_1(N_EXPRSTMT, T_UNKNOWN, child, NULL, 0, line);
}

Node *new_Block(Node *body, int line) {
    return new_Node_1(N_BLOCK, T_UNKNOWN, body, NULL, 0, line);
}

Node *new_Body(int line) {
    return new_Node_0(N_BODY, T_UNKNOWN, NULL, 0, line);
}

void body_append(Node *const node, Node *const child) {
    YASL_TRACE_LOG("%s\n", "appending to block");
    node->children = realloc(node->children, (++node->children_len)*sizeof(Node*));
    node->children[node->children_len-1] = child;
}


Node *new_FnDecl(Node *params, Node *body, char *name, int64_t name_len, int line) {
    return new_Node_2(N_FNDECL, T_UNKNOWN, params, body, name, name_len, line);
}

Node *new_Return(Node *expr, int line) {
    return new_Node_1(N_RET, T_UNKNOWN, expr, NULL, 0, line);
}

Node *new_Call(Node *params, Node *object, int line) {
    return new_Node_2(N_CALL, T_UNKNOWN, params, object, NULL, 0, line);
}

Node *new_Set(Node *collection, Node *key, Node *value, int line) {
    return new_Node_3(N_SET, T_UNKNOWN, collection, key, value, NULL, 0, line);
}

Node *new_Get(Node *collection, Node *value, int line) {
    return new_Node_2(N_GET, T_UNKNOWN, collection, value, NULL, 0, line);
}

Node *ListComp_get_expr(const Node *const node) {
    return node->children[0];
}

Node *ListComp_get_var(const Node *const node) {
    return node->children[1];
}

Node *ListComp_get_collection(const Node *const node) {
    return node->children[2];
}

Node *new_ListComp(Node *expr, Node *var, Node *collection, int line) {
    return new_Node_3(N_LISTCOMP, T_UNKNOWN, expr, var, collection, NULL, 0, line);
}

Node *TableComp_get_key_value(const Node *const node) {
    return node->children[0];
}

Node *new_TableComp(Node *expr, Node *iter, int line) {
    return new_Node_2(N_TABLECOMP, T_UNKNOWN, expr, iter, NULL, 0, line);
}

Node *new_LetIter(Node *var, Node *collection, int line) {
    return new_Node_2(N_LETITER, T_UNKNOWN, var, collection, NULL, 0, line);
}

Node *new_Iter(Node *var, Node *collection, int line) {
    return new_Node_2(N_ITER, T_UNKNOWN, var, collection, NULL, 0, line);
}

Node *ForIter_get_var(const Node *const node) {
    return node->children[0];
}

Node *ForIter_get_collection(const Node *const node) {
    return node->children[1];
}

Node *ForIter_get_body(const Node *const node) {
    return node->children[1];
}

Node *new_ForIter(Node *iter, Node *body, int line) {
    return new_Node_2(N_FORITER, T_UNKNOWN, iter, body, NULL, 0, line);
}

Node *While_get_cond(const Node *const node) {
    return node->children[0];
}

Node *While_get_body(const Node *const node) {
    return node->children[1];
}

Node *new_While(Node *cond, Node *body, Node *post, int line) {
    return new_Node_3(N_WHILE, T_UNKNOWN, cond, body, post, NULL, 0, line);
}

Node *new_Break(int line) {
    return new_Node_0(N_BREAK, T_UNKNOWN, NULL, 0, line);
}

Node *new_Continue(int line) {
    return new_Node_0(N_CONT, T_UNKNOWN, NULL, 0, line);
}

Node *new_If(Node *cond, Node *then_node, Node *else_node, int line) {
    return new_Node_3(N_IF, T_UNKNOWN, cond, then_node, else_node, NULL, 0, line);
}

Node *Print_get_expr(const Node *const node) {
    return node->children[0];
}

Node *new_Print(Node *expr, int line) {
    return new_Node_1(N_PRINT, T_UNKNOWN, expr, NULL, 0, line);
}

Node *Let_get_expr(const Node *const node) {
    return node->children[0];
}

Node *new_Let(char *name, int64_t name_len, Node *expr, int line) {
    return new_Node_1(N_LET, T_UNKNOWN, expr, name, name_len, line);
}

Node *Const_get_expr(Node *node) {
    return node->children[0];
}

Node *new_Const(char *name, int64_t name_len, Node *expr, int line) {
    return new_Node_1(N_CONST, T_UNKNOWN, expr, name, name_len, line);
}

Node *new_TriOp(Token op, Node *left, Node *middle, Node *right, int line) {
    return new_Node_3(N_TRIOP, op, left, middle, right, NULL, 0, line);
}

Node *new_BinOp(Token op, Node *left, Node *right, int line) {
    return new_Node_2(N_BINOP, op, left, right, NULL, 0, line);
}

Node *new_UnOp(Token op, Node *child, int line) {
    return new_Node_1(N_UNOP, op, child, NULL, 0, line);
}

Node *new_Assign(char *name, int64_t name_len, Node *child, int line) {
    return new_Node_1(N_ASSIGN, T_UNKNOWN, child, name, name_len, line);
}

Node *new_Var(char *name, int64_t name_len, int line) {
    return new_Node_0(N_VAR, T_UNKNOWN, name, name_len, line);
}

Node *new_Undef(int line) {
    return new_Node_0(N_UNDEF, T_UNKNOWN, NULL, 0, line);
}

Node *new_Float(char *value, int len, int line) {
    return new_Node_0(N_FLOAT64, T_UNKNOWN, value, len, line);
}

Node *new_Integer(char *value, int len, int line) {
    return new_Node_0(N_INT64, T_UNKNOWN, value, len, line);
}

Node *new_Boolean(char *value, int len, int line) {
    return new_Node_0(N_BOOL, T_UNKNOWN, value, len, line);
}

Node *new_String(char *value, int len, int line) {
    return new_Node_0(N_STR, T_UNKNOWN, value, len, line);
}

Node *List_get_values(const Node *const node) {
    return node->children[0];
}

Node *new_List(Node *values, int line) {
    return new_Node_1(N_LIST, T_UNKNOWN, values, NULL, 0, line);
}

Node *Table_get_values(const Node *const node) {
    return node->children[0];
}

Node *new_Table(Node *keys, int line) {
    return new_Node_1(N_TABLE, T_UNKNOWN, keys, NULL, 0, line);
}

void node_del(Node *node) {
    while(node->children_len-- > 0)
        if (node->children[node->children_len] != NULL)
            node_del(node->children[node->children_len]);
    free(node->name);
    free(node->children);
    free(node);

}
