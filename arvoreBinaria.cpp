#include <iostream>
using namespace std;

struct Node {
    int valor;
    Node *esquerda;
    Node *direita;
};

Node *novoNo(int valor) {
    Node *no = new Node();
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

Node *inserir(Node *raiz, int valor) {
    if (raiz == NULL) {
        return novoNo(valor);
    } else {
        if (valor <= raiz->valor) {
            raiz->esquerda = inserir(raiz->esquerda, valor);
        } else {
            raiz->direita = inserir(raiz->direita, valor);
        }
        return raiz;
    }
}

Node *buscar(Node *raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    } else if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    } else {
        return buscar(raiz->direita, valor);
    }
}

Node *encontrarMinimo(Node *raiz) {
    Node *atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

Node *remover(Node *raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    } else if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            Node *temp = raiz->direita;
            delete raiz;
            return temp;
        } else if (raiz->direita == NULL) {
            Node *temp = raiz->esquerda;
            delete raiz;
            return temp;
        } else {
            Node *temp = encontrarMinimo(raiz->direita);
            raiz->valor = temp->valor;
            raiz->direita = remover(raiz->direita, temp->valor);
        }
    }
    return raiz;
}

void inserirVetor(Node*& raiz, int *vetor, int N) {
    for (int i = 0; i < N; i++) {
        raiz = inserir(raiz, vetor[i]);
    }
}

void removerTodos(Node *raiz) {
    if (raiz != NULL) {
        removerTodos(raiz->esquerda);
        removerTodos(raiz->direita);
        delete raiz;
    }
}