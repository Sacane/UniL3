/* tree.h */

#ifndef __TREE

#define __TREE

typedef enum {

  Prog,

  DeclVars,

  DeclFoncts,

  types,

  divstar,

  id,

  DeclFonct,

  EnTeteFonct,

  Corps,

  Void,

  Parametres,

  ListTypVar,

  SuiteInstr,

  Exp,

  LValue,

  Assign,

  Body,

  Instr,

  If,

  Else,

  While,

  Or,

  And,

  Eq,

  Plus,

  Minus,

  Order,

  Addsub,

  FunctionCall,

  Neg,

  Int,

  Character,

  Arguments,

  ListExp,

  Return,

  EmptyInstr

  /* list all other node labels, if any */

  /* The list must coincide with the string array in tree.c */

  /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */

} label_t;

typedef struct Node {

  label_t label;

  struct Node *firstChild, *nextSibling;

  int lineno;

} Node;

Node *makeNode(label_t label);

void addSibling(Node *node, Node *sibling);

void addChild(Node *parent, Node *child);

void deleteTree(Node*node);

void printTree(Node *node);

#define FIRSTCHILD(node) node->firstChild

#define SECONDCHILD(node) node->firstChild->nextSibling

#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling

#endif