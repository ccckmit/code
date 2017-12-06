#include <stdio.h>
#include "Tree.h"

Tree *TreeNew(char *type, char *value) {
  ASSERT(type != NULL && value != NULL);
  Tree *rzTree = ObjNew(Tree, 1);
  rzTree->type = (void*) newStr(type);
  rzTree->value = (void*) newStr(value);
  rzTree->childs = NULL;
//  printf("TreeNew(%s,%s)\n", type, value);
//  printf("address of tree->type=%d, tree->value=%d\n", rzTree->type, rzTree->value);
  return rzTree;
}

void TreeFree(Tree *tree) {
  if (tree == NULL) return;
  freeMemory(tree->type);
  freeMemory(tree->value);
  if (tree->childs != NULL) {
    int i;
    for (i=0; i<tree->childs->count; i++)
      TreeFree(tree->childs->item[i]);
    ArrayFree(tree->childs, NULL);
  }
  ObjFree(tree);
}

void TreeAddChild(Tree *tree, Tree *child) {        // �b�𤤥[�J�@�ӷs���l��C
  ASSERT(tree != NULL && child != NULL);
  if (tree->childs == NULL)
    tree->childs = ArrayNew(1);
  ArrayAdd(tree->childs, child);
}

void TreePrintLevel(Tree *tree, int level) { // �N�Ӿ�C�L�X�ӡC
  ASSERT(tree != NULL && tree->type != NULL);
//  printf("address of tree->type=%d, tree->value=%d\n", tree->type, tree->value);
  printf("%s+%s\t = %s\n", strSpaces(level), tree->type, tree->value);
  if (tree->childs != NULL) {
    int i;
    for (i=0; i<tree->childs->count; i++)
      TreePrintLevel(tree->childs->item[i], level + 1);
    printf("%s-%s\n", strSpaces(level), tree->type);
  }
}

void TreePrint(Tree *tree) {
  TreePrintLevel(tree, 0);
}
