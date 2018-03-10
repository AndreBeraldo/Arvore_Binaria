/**      Desenvolvido por: Andre Vitor Beraldo
*   Instituicao: Universidade Federal de Itajuba (UNIFEI)
*           Curso: Ciencias da Computacao
*/

#include <stdio.h>
#include <stdlib.h>

        //////////////////
        /*  PROTOTIPOS  */
        //////////////////

struct arvore_binaria {
    int data;
    struct arvore_binaria *direita, *esquerda;
};

        //////////////////
        /*  PROTOTIPOS  */
        //////////////////
typedef struct arvore_binaria node;
void lerArquivo(node **tree);
void inserir(node **tree, int val);
void print_preordem(node * tree);
void print_inordem(node * tree);
void print_posordem(node * tree);
void deltree(node * tree);
node *MaiorDireita(node **no);
node *MenorEsquerda(node **no);
void remover(node **tree, int numero);
void main();

          ////////////
          /*  MAIN  */
          ////////////

void main()
{
    node *root;
    node *tmp;
    root = NULL;

    int escolha=0, valor=0;
    while(escolha!=7){
        printf("\n|-------------------------|");
        printf("\n\n\tOpcoes:");
		printf("\n\n1 - Receber Arquivos ");
		printf("\n2 - Printando pre-ordem ");
		printf("\n3 - Printando em-ordem ");
		printf("\n4 - Printando pos-ordem ");
		printf("\n5 - Incluir dados ");
		printf("\n6 - Remover dados ");
		printf("\n7 - Sair\n");
        printf("\n|-------------------------|");
        printf("\nEscolha: ");
		scanf("%d", &escolha);
		system("cls");
		if(escolha == 1){
            lerArquivo(&root);
		}
        else if(escolha == 2){
            printf("|-------------------------|");
            printf("\n\n\tPre - Ordem\n\n");
            print_preordem(root);

        }
        else if(escolha == 3){
            printf("|-------------------------|");
            printf("\n\n\tEm - Ordem\n\n");
            print_inordem(root);

        }
        else if(escolha == 4){
            printf("|-------------------------|");
            printf("\n\n\tPos - Ordem\n\n");
            print_posordem(root);

        }
        else if(escolha == 5){
            printf("|-------------------------|");
            printf("\nValor a inserir: ");
            scanf("%d", &valor);
            inserir(&root, valor);
        }
        else if(escolha == 6){
            printf("|-------------------------|");
            printf("\nValor a deletar: ");
            scanf("%d", &valor);
            remover(&root, valor);
        }

    }
}

        //////////////////
        /*   METODOS    */
        //////////////////

void lerArquivo(node **tree)
{
        FILE* arq;
        char* nomeArq;
        node tmp;

        // NOME DO ARQUIVO DE DADOS
        nomeArq = (char*) calloc ( 50, sizeof (char));
        printf ( "Nome do arquivo a ser lido:\n" );
        scanf ( "%s", nomeArq );

        arq = fopen ( nomeArq, "rt" );

        if ( !arq ) {
            printf ( "arquivo %s nao existe\n", nomeArq );
            exit(0);
        }
                // LEITURA DOS DADOS
        while ( !feof ( arq )){
              fscanf (arq, "%d", &tmp.data );
              inserir( &(*tree), tmp.data );
        }
     }

void inserir(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->esquerda = temp->direita = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)
    {
        inserir(&(*tree)->esquerda, val);
    }
    else if(val > (*tree)->data)
    {
        inserir(&(*tree)->direita, val);
    }

}

void print_preordem(node * tree)
{
    if (tree)
    {
        printf("%d  ",tree->data);
        print_preordem(tree->esquerda);
        print_preordem(tree->direita);
    }
}

void print_inordem(node * tree)
{
    if (tree)
    {
        print_inordem(tree->esquerda);
        printf("%d  ",tree->data);
        print_inordem(tree->direita);
    }
}

void print_posordem(node * tree)
{
    if (tree)
    {
        print_posordem(tree->esquerda);
        print_posordem(tree->direita);
        printf("%d  ",tree->data);
    }
}

void deltree(node * tree){
    if (tree)
    {
        deltree(tree->esquerda);
        deltree(tree->direita);
        free(tree);
    }
}

node *MaiorDireita(node **no){
    if((*no)->direita != NULL)
       return MaiorDireita(&(*no)->direita);
    else{
       node *aux = *no;
       if((*no)->esquerda != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da esquerda!
          *no = (*no)->esquerda;
       else
          *no = NULL;
       return aux;
       }
}

node *MenorEsquerda(node **no){
    if((*no)->esquerda != NULL)
       return MenorEsquerda(&(*no)->esquerda);
    else{
       node *aux = *no;
       if((*no)->direita != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da direita!
          *no = (*no)->direita;
       else
          *no = NULL;
       return aux;
       }
}

void remover(node **tree, int numero){
    if(*tree == NULL){   // esta verificacao serve para caso o numero nao exista na arvore.
       printf("Numero nao existe na arvore!");
       getch();
       return;
    }
    if(numero < (*tree)->data)
       remover(&(*tree)->esquerda, numero);
	else if(numero > (*tree)->data)
       remover(&(*tree)->direita, numero);

       else{    // se nao eh menor nem maior, logo, é o numero que estou procurando! :)
          node *pAux = *tree;
          if (((*tree)->esquerda == NULL) && ((*tree)->direita == NULL)){         // se nao houver filhos...
                free(pAux);
                (*tree) = NULL;
               }
          else{
             if ((*tree)->esquerda == NULL){
                (*tree) = (*tree)->direita;
                pAux->direita = NULL;
                free(pAux); pAux = NULL;
                }
             else{
                if ((*tree)->direita == NULL){
                    (*tree) = (*tree)->esquerda;
                    pAux->esquerda = NULL;
                    free(pAux); pAux = NULL;
                    }
                else{
                   pAux = MaiorDireita(&(*tree)->esquerda);
                   pAux->esquerda = (*tree)->esquerda;
                   pAux->direita = (*tree)->direita;
                   (*tree)->esquerda = (*tree)->direita = NULL;
                   free((*tree));  *tree= pAux;  pAux = NULL;
                   }
                }
             }
          }
}

node* search(node ** tree, int val){
    if(!(*tree))
    {
        return NULL;
    }

    if(val < (*tree)->data)
    {
        search(&((*tree)->esquerda), val);
    }
    else if(val > (*tree)->data)
    {
        search(&((*tree)->direita), val);
    }
    else if(val == (*tree)->data)
    {
        return *tree;
    }
}
