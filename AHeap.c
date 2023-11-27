//Heap Tree

#include <stdio.h>
#include <stdlib.h>

typedef struct noArvore_
{
    int valor;
    struct noArvore_ *esq;
    struct noArvore_ *dir;
} noArvore;

noArvore *busca(noArvore *raiz, int k)
{
    if (raiz == NULL || raiz->valor == k)
    {
        return raiz;
    }
    if (k > raiz->valor)
    {
        return busca(raiz->dir, k);
    }
    else
    {
        return busca(raiz->esq, k);
    }
}

noArvore *buscaPai(noArvore *raiz, noArvore *n)
{
    if (raiz == NULL || raiz == n)
    {
        return NULL;
    }

    if (raiz->esq == n || raiz->dir == n)
    {
        return raiz;
    }
    if (n->valor > raiz->valor)
    {
        return buscaPai(raiz->dir, n);
    }
    else
    {
        return buscaPai(raiz->esq, n);
    }
}

noArvore *insere(noArvore *raiz, noArvore *n)
{
    if (raiz == NULL)
    {
        return n;
    }
    if (n->valor > raiz->valor)
    {
        raiz->dir = insere(raiz->dir, n);
    }
    else
    {
        raiz->esq = insere(raiz->esq, n);
    }
    return raiz;
}

noArvore *criaNo(int valor)
{
    noArvore *novo = (noArvore *)malloc(sizeof(noArvore));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}


void mostraArvorePreOrdem(noArvore *raiz) {
    //printf("%d \t", raiz->info);
    if(raiz != NULL) { //if (raiz)
        printf("%d \t", raiz->valor);
        mostraArvorePreOrdem(raiz->esq);
        mostraArvorePreOrdem(raiz->dir);
    }
}


void mostraArvoreEmOrdem(noArvore *raiz) {
    //printf("%d \t", raiz->info);
    if(raiz != NULL) { //if (raiz)
        mostraArvoreEmOrdem(raiz->esq);
        printf("%d \t", raiz->valor);
        mostraArvoreEmOrdem(raiz->dir);

    }
}


void mostraArvorePosOrdem(noArvore *raiz) {
    //printf("%d \t", raiz->info);
    if(raiz != NULL) { //if (raiz)
        mostraArvorePosOrdem(raiz->esq);
        mostraArvorePosOrdem(raiz->dir);
        printf("%d \t", raiz->valor);
    }
}
void imprime(noArvore *raiz)
{
    if (raiz != NULL)
    {
        imprime(raiz->esq);
        printf("%d\n", raiz->valor);
        imprime(raiz->dir);
    }
    printf("\n\n\n");
}

noArvore *removeRaiz(noArvore *raiz)
{
    noArvore *pai = NULL;
    noArvore *filho = NULL;
    if (raiz->esq == NULL)
    {
        filho = raiz->dir;
        free(raiz);
        return filho;
    }
    if (raiz->dir == NULL)
    {
        filho = raiz->esq;
        free(raiz);
        return filho;
    }
    pai = raiz;
    filho = raiz->esq;
    while (filho->dir != NULL)
    {
        pai = filho;
        filho = filho->dir;
    }
    if (pai != raiz)
    {
        pai->dir = filho->esq;
        filho->esq = raiz->esq;
    }
    filho->dir = raiz->dir;
    free(raiz);
    return filho;
}

noArvore *removeNaArvore(noArvore *raiz, int k)
{
    noArvore *pai = NULL;
    noArvore *n = raiz;
    while (n != NULL && n->valor != k)
    {
        pai = n;
        if (k > n->valor)
        {
            n = n->dir;
        }
        else
        {
            n = n->esq;
        }
    }
    if (n == NULL)
    {
        return raiz;
    }
    if (pai == NULL)
    {
        return removeRaiz(raiz);
    }
    if (pai->esq == n)
    {
        pai->esq = removeRaiz(n);
    }
    else
    {
        pai->dir = removeRaiz(n);
    }
    return raiz;
}

int main()
{
    noArvore *raiz = NULL;
    noArvore *novo = NULL;
    int opcao = 0;
    int valor = 0;
    do
    {
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Imprimir\n");
        printf("4 - Buscar\n");
        printf("5 - Sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Digite o valor a ser inserido: ");
            scanf("%d", &valor);
            novo = criaNo(valor);
            raiz = insere(raiz, novo);
            break;
        case 2:
            printf("Digite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = removeNaArvore(raiz, valor);
            break;
        case 3:
            mostraArvorePreOrdem(raiz);
            break;
        case 4:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            novo = busca(raiz, valor);
            if (novo != NULL)
            {
                printf("Valor encontrado: %d\n", novo->valor);
            }
            else
            {
                printf("Valor nao encontrado\n");
            }
            break;
        case 5:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    } while (opcao != 5);
    return 0;
}










/*
// Max-Heap data structure in C

#include <stdio.h>
int size = 0;
void swap(int *a, int *b)
{
  int temp = *b;
  *b = *a;
  *a = temp;
}
void heapify(int array[], int size, int i)
{
  if (size == 1)
  {
    printf("Single element in the heap");
  }
  else
  {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && array[l] > array[largest])
      largest = l;
    if (r < size && array[r] > array[largest])
      largest = r;
    if (largest != i)
    {
      swap(&array[i], &array[largest]);
      heapify(array, size, largest);
    }
  }
}
void insert(int array[], int newNum)
{
  if (size == 0)
  {
    array[0] = newNum;
    size += 1;
  }
  else
  {
    array[size] = newNum;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
      heapify(array, size, i);
    }
  }
}
void deleteRoot(int array[], int num)
{
  int i;
  for (i = 0; i < size; i++)
  {
    if (num == array[i])
      break;
  }

  swap(&array[i], &array[size - 1]);
  size -= 1;
  for (int i = size / 2 - 1; i >= 0; i--)
  {
    heapify(array, size, i);
  }
}
void printArray(int array[], int size)
{
  for (int i = 0; i < size; ++i)
    printf("%d ", array[i]);
  printf("\n");
}
int main()
{
  int array[10];

  insert(array, 3);
  insert(array, 4);
  insert(array, 9);
  insert(array, 5);
  insert(array, 2);

  printf("Max-Heap array: ");
  printArray(array, size);

  deleteRoot(array, 4);

  printf("After deleting an element: ");

  printArray(array, size);
}*/
















/*Para o i-esimo nó
vetor[i] = vetor[2*i+1] // filho esquerdo
vetor[i] = vetor[2*i+2] // filho direito
vetor[i] = vetor[(i-1)/2] // pais
*/


//Insers a new key 'k'
/*
void insertKey(int k)
{
    if (heap_size == capacity)
    {
        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    //First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    //Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}
*/



// Method to remove minimun element (or root) form min heap
/*

int extractMin()
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    //Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    MinHeapify(0);

    return root;
}
*/


// A recursive method to heapfy a strema with the rest at given index
// This method assumes that the subtrees are already heapfied
/*
void MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}
*/ 