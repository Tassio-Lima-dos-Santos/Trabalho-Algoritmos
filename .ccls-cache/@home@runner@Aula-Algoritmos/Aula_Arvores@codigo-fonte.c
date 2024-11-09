#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>




struct tree{
   int dado;
   struct tree *left, *right;
} typedef Tree;



Tree *create_tree(){
   return NULL;
}



Tree *insert(Tree *t, int dado){
   if(t==NULL){
      t = malloc(sizeof(Tree));
      (*t).dado = dado;
      (*t).left = NULL;
      (*t).right = NULL; 
   }else{
      if(dado<(*t).dado)
         (*t).left = insert((*t).left,dado);     
      else
         (*t).right = insert((*t).right,dado); 
   } 
   return t;
}


/* imprimir o conteudo dos nodos percorrendo a arvore em pre-ordem*/
void imprimir_preorder(Tree *root){
   if(root != NULL){
      printf("%d ", root->dado);
      imprimir_preorder(root->left);
      imprimir_preorder(root->right);
   }
}

/* imprimir o conteudo dos nodos percorrendo a arvore em pos-ordem*/
void imprimir_postorder(Tree *root){
   if(root != NULL){
      imprimir_postorder(root->left);
      imprimir_postorder(root->right);
      printf("%d ", root->dado);
   }
}

/* imprimir o conteudo dos nodos percorrendo a arvore em-ordem (in-order)*/
void imprimir_inorder(Tree *root){
   if(root != NULL){
      imprimir_inorder(root->left);
      printf("%d ", root->dado);
      imprimir_inorder(root->right);
   }
}


/* retorna o menor nodo entre os nodos maiores que t */
Tree *menor_maior(Tree *t){
   if((*t).right==NULL){
     return NULL;
   }else{
      Tree *temp = (*t).right;
      while((*temp).left!=NULL){
         temp = (*temp).left;
      } 
      return temp;
   }   
}


/* retorna o predecessor do nodo que armazena value */
Tree *predecessor(Tree *t, int value){ 
   if(t==NULL||(t->left==NULL&&t->right==NULL))
      return NULL;
   if((t->left!=NULL&&t->left->dado==value)||(t->right!=NULL&&t->right->dado==value))
      return t;
   else{
        if(value<t->dado)
           return predecessor(t->left,value);
        else 
           return predecessor(t->right,value);
   }
}


/* percorre a árvore t em busca do valor value. Retorna o nodo encontrado */
Tree *search_value(Tree *t, int value){
   if(t==NULL||(*t).dado==value){
      return t;
   }else{
      if(value<(*t).dado)
         return search_value((*t).left, value);
      else
         return search_value((*t).right, value);
   }    
}




/* Remover da arvore "t" o nodo "nodo" passado como parametro */
void remover(Tree *t, Tree *nodo){
   if(nodo->left == NULL && nodo->right == NULL){
      Tree *pred = predecessor(t, nodo->dado);
      if(pred->left == nodo){
         pred->left = NULL;
      }else if(pred->right == nodo){
         pred->right = NULL;
      }
      free(nodo);
   }else if(nodo->left != NULL && nodo->right != NULL){
      
   }else if(nodo->left != NULL){
      Tree *pred = predecessor(t, nodo->dado);
      if(pred->left == nodo){
         pred->left = nodo->left;
      }else if(pred->right == nodo){
         pred->right = nodo->left;
      }
      free(nodo);
   }else if(nodo->right != NULL){
      Tree *pred = predecessor(t, nodo->dado);
      if(pred->left == nodo){
         pred->left = nodo->right;
      }else if(pred->right == nodo){
         pred->right = nodo->right;
      }
      free(nodo);
   }
}

/* 
   Imprime a arvore "t" na tela a partir da profundidade passada como parametro.
   Para imprimir a arvore a partir da raiz, informar profundidade zero.
*/
void mostra_arvore(Tree *t, int profundidade, char lado){
   int i;
   if (t != NULL){
      for (i = 0; i < profundidade*5; i++){
         if (i > profundidade*5 -5){
      printf("-");
         } else {
     printf(" ");
  }
      }
      printf(">%d (%c)\n", t->dado, lado);
      profundidade++;
      mostra_arvore(t->left, profundidade, 'L');
      mostra_arvore(t->right, profundidade, 'R');
   }
}

/*int main(){
  Tree *T = create_tree();*/ /* ponteiro para a raiz da arbore */

  /*int option, x;
  while(true){
    printf("Opções: \n <1> - Inserir \n <2> - Imprimir Preorder\n <3> - Imprimir Postorder\n <4> - Imprimir Inorder\n <5> - Remover\n <6> - Mostrar árvore\n");
    printf("\nDigite uma opção: ");
      scanf("%d", &option);
      switch(option){
        case 1: 
                printf("Digite um numero inteiro: ");
                scanf("%d",&x);
                T = insert(T,x); 
        break;
        case 2: imprimir_preorder(T);        
                printf("\n");
        break;    
        case 3: imprimir_postorder(T);        
                printf("\n");
        break;
        case 4: imprimir_inorder(T);        
                printf("\n");
        break;
        case 5: printf("Digite o número a ser localizado: \n");
                scanf("%d", &x);     
                Tree *to_remove = search_value(T,x);
                if(to_remove==NULL){
                  printf("Dado não localizado na árvore.\n");
                }else{
                  remover(T, to_remove);
                }
                printf("\n");
        break;
        case 6: mostra_arvore(T,0, 'T');        
                printf("\n"); 
        break;    
      }   



  }


}*/