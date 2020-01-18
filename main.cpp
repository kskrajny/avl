#include "Myavl.h"
using namespace normalavl;
int main()
{
    Node *root = nullptrptr;

    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    preOrder(root);

    root = deleteNode(root, 10);
    root = deleteNode(root, 9);

    preOrder(root);

    return 0;
}
