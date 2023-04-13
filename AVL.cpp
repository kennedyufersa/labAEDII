#include <stdio.h>
#include<stdlib.h>
#include<time.h>

struct NoAVL
{
    int valor;
    int altura;
    NoAVL *esquerda;
    NoAVL *direita;

    NoAVL(int v)
    {
        valor = v;
        altura = 1;
        esquerda = NULL;
        direita = NULL;
    }
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int altura(NoAVL *no)
{
    if (no == NULL)
        return 0;
    else
        return no->altura;
}

int fator_balanceamento(NoAVL *no)
{
    if (no == NULL)
        return 0;
    else
        return altura(no->esquerda) - altura(no->direita);
}

NoAVL *rotacao_direita(NoAVL *no)
{
    NoAVL *novo_raiz = no->esquerda;
    NoAVL *temp = novo_raiz->direita;

    novo_raiz->direita = no;
    no->esquerda = temp;

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    novo_raiz->altura = max(altura(novo_raiz->esquerda), altura(novo_raiz->direita)) + 1;

    return novo_raiz;
}

NoAVL *rotacao_esquerda(NoAVL *no)
{
    NoAVL *novo_raiz = no->direita;
    NoAVL *temp = novo_raiz->esquerda;

    novo_raiz->esquerda = no;
    no->direita = temp;

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    novo_raiz->altura = max(altura(novo_raiz->esquerda), altura(novo_raiz->direita)) + 1;

    return novo_raiz;
}

NoAVL *rotacao_dupla_direita(NoAVL *no)
{
    no->esquerda = rotacao_esquerda(no->esquerda);
    return rotacao_direita(no);
}

NoAVL *rotacao_dupla_esquerda(NoAVL *no)
{
    no->direita = rotacao_direita(no->direita);
    return rotacao_esquerda(no);
}

NoAVL *inserir(NoAVL *raiz, int valor)
{

    if (raiz == NULL)
        return new NoAVL(valor);

    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);
    else
        return raiz;

    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;

    int fb = fator_balanceamento(raiz);

    switch (fb)
    {
    case 2:
        if (fator_balanceamento(raiz->esquerda) == 1)
            return rotacao_direita(raiz);
        else
            return rotacao_dupla_direita(raiz);
        break;

    case -2:
        if (fator_balanceamento(raiz->direita) == -1)
            return rotacao_esquerda(raiz);
        else
            return rotacao_dupla_esquerda(raiz);
        break;

    default:
        break;
    }

    return raiz;
}

void inOrdem(NoAVL *raiz)
{
    if (raiz == NULL)
        return;

    inOrdem(raiz->esquerda);
    printf("%d", raiz->valor);
    inOrdem(raiz->direita);
}

int main()
{
    NoAVL *raiz = NULL;
    int tam = 1000;
    srand(time(NULL));
    for (int i = 0; i < tam; i++)
    {
        raiz = inserir(raiz, rand() % (tam/4) + 1);
    }

    printf("InOrdem: ");
    inOrdem(raiz);

    return 0;
}
