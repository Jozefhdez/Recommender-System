#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>

struct AVLNode {
    std::string name;  // Nombre del anime (producto).
    int index;         // Índice en el arreglo 'animesArray'.
    int height;        // Altura del nodo.
    AVLNode* left;     // Puntero al hijo izquierdo.
    AVLNode* right;    // Puntero al hijo derecho;

    AVLNode(std::string n, int i)
        : name(n), index(i), height(1), left(nullptr), right(nullptr) {}
};
class AVLTree {
private:
    AVLNode* root;

    // Función para obtener la altura de un nodo.
    int height(AVLNode* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    // Función para obtener el factor de balance de un nodo.
    int balanceFactor(AVLNode* node) {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

    // Función para rotar el subárbol a la derecha.
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Rotación
        x->right = y;
        y->left = T2;

        // Actualizamos las alturas
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    // Función para rotar el subárbol a la izquierda.
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Rotación
        y->left = x;
        x->right = T2;

        // Actualizamos las alturas
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // Función para insertar un nodo en el árbol.
    AVLNode* insert(AVLNode* node, const std::string& name, int index) {
        // Inserción normal en un árbol binario de búsqueda
        if (node == nullptr)
            return new AVLNode(name, index);

        if (name < node->name)
            node->left = insert(node->left, name, index);
        else if (name > node->name)
            node->right = insert(node->right, name, index);
        else  // Si el nombre ya existe, no insertamos el duplicado.
            return node;

        // Actualizamos la altura del nodo actual
        node->height = 1 + std::max(height(node->left), height(node->right));

        // Balanceamos el nodo y sus descendientes
        int balance = balanceFactor(node);

        // Rotaciones según el factor de balance
        if (balance > 1 && name < node->left->name) {
            return rotateRight(node);
        }

        if (balance < -1 && name > node->right->name) {
            return rotateLeft(node);
        }

        if (balance > 1 && name > node->left->name) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && name < node->right->name) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Función de búsqueda
    AVLNode* searchClosest(AVLNode* node, const std::string& name, AVLNode* closest) {
        if (node == nullptr) {
            // Regresa el nodo más cercano encontrado
            return closest;
        }

        // Actualiza el nodo más cercano si el actual está más cerca del query
        if (closest == nullptr || std::abs((int)(node->name.compare(name))) < std::abs((int)(closest->name.compare(name)))) {
            closest = node;
        }

        // Decide si recorrer el subárbol izquierdo o derecho
        if (name < node->name) {
            return searchClosest(node->left, name, closest);
        } else {
            return searchClosest(node->right, name, closest);
        }
    }

    

public:
    AVLTree() : root(nullptr) {}

    // Insertar un nodo
    void insert(const std::string& name, int index) {
        root = insert(root, name, index);
    }

    // Buscar un nodo
    AVLNode* search(const std::string& name) {
        return searchClosest(root, name, nullptr);
    }

    void hola(){
        std::cout << "Hola";
    }
};

#endif // AVLTREE_HPP
