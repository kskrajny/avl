#ifndef AVL_MYAVL_H
#define AVL_MYAVL_H

#include<bits/stdc++.h>
using namespace std;

namespace normalavl {
    class Node {
    public:
        int key;
        Node *left;
        Node *right;
        int height;
        int size;
    };

    // A utility function to get maximum
    // of two integers
    int max(int a, int b);

    // A utility function to get height
    // of the tree
    int height(Node *N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int size(Node *N) {
        if (N == nullptr)
            return 0;
        return N->size;
    }

    void update(Node *N) {
        if (N != nullptr) {
            N->height = max(height(N->left),height(N->right))+1;
            N->size = size(N->left)+size(N->right)+1;
        }
    }

    // A utility function to get maximum
    // of two integers
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    /* Helper function that allocates a
    new node with the given key and
    nullptr left and right pointers. */
    Node *newNode(int key) {
        Node *node = new Node();
        node->key = key;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1; // new node is initially
        node->size = 1;
        // added at leaf
        return (node);
    }

    // brings x to root
    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        update(y);
        update(x);
        // Return new root
        return x;
    }

    // brings y to root
    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        update(x);
        update(y);
        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(Node *N) {
        if (N == nullptr)
            return 0;
        return height(N->left) -
               height(N->right);
    }

    Node *insert(Node *node, int key) {
        /* 1. Perform the normal BST rotation */
        if (node == nullptr)
            return (newNode(key));

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else // Equal keys not allowed
            return node;

       update(node);

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    /* Given a non-empty binary search tree,
    return the node with minimum key value
    found in that tree.*/
    Node *minValueNode(Node *node) {
        Node *current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    // Recursive function to delete a node
    // with given key from subtree with
    // given root. It returns root of the
    // modified subtree.
    Node *deleteNode(Node *root, int key) {

        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);

        else if (key > root->key)
            root->right = deleteNode(root->right, key);

            // This is the node to be deleted
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node *temp = root->left ?
                             root->left :
                             root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else // One child case
                    *root = *temp; // Copy the contents of
                // the non-empty child
                free(temp);
            } else {
                // node with two children
                Node *temp = minValueNode(root->right);

                // Copy data
                root->key = temp->key;

                // Delete the inorder successor
                root->right = deleteNode(root->right,
                                         temp->key);
            }
        }

        // If the tree had only one node
        // then return
        if (root == nullptr)
            return root;

        update(root);

        int balance = getBalance(root);

        // Left Left Case
        if (balance > 1 &&
            getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 &&
            getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 &&
            getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 &&
            getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // A utility function to print preorder
    // traversal of the tree.
    void preOrder(Node *root) {
        if (root != nullptr) {
            cout << root->key << " :" << root->size << " , ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
}

#endif //AVL_MYAVL_H
