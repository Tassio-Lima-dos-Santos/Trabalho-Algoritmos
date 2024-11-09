/*#include <stdio.h>
#include <stdlib.h>


typedef struct lstItem{
   int dado;
   struct lstItem *next;
}filaItem;


typedef struct{
   filaItem *inicio;	
   filaItem *fim;
}fila;



fila *criaFila(){
   fila *f = malloc(sizeof(fila	));
   f->inicio = f->fim = NULL;
   return f;
}*/


/* Inserir um novo dado na fila f*/
/*void push(fila *f, int dado){
   filaItem *novo = malloc(sizeof(filaItem));   
   novo->dado = dado;
   novo->next = NULL;
   if(f->inicio==NULL){
      f->inicio = novo;
   }else{
      f->fim->next = novo;
   }
   f->fim = novo;
}*/


/* Remover um elemento da fila f */
/*void pop(fila *f){
   if(f->inicio==NULL){
      printf("Fila vazia.\n");   
   }
   else{
      filaItem *tmp = f->inicio;
      if(f->inicio->next==NULL){
         f->fim = NULL;
      }
      f->inicio = tmp->next;
      free(tmp);
   }
}*/


/* Retornar o dado que se encontra na cabeça da fila. */
/*int peek(fila *f){
   if(f->inicio!=NULL){
      return f->inicio->dado;
   }else{
      return (-1);
   }
}


void print(fila *f){
   filaItem *item = f->inicio;
   while(item!=NULL){
      printf("%d --- ",item->dado);
      item = item->next;
   }
   printf("\n\n");
}*/

/*int main(){

   fila *f = criaFila(); 
   int opcao = 1, i; 

   while(opcao!=9){
      printf("1 - Inserir\n");
      printf("2 - Remover\n");
      printf("3 - Consultar cabeça (peek)\n");
      printf("4 - Imprimir a fila\n");
      printf("9 - Sair\n");
      printf("\nDigite uma opcao: ");
      scanf("%d",&opcao);
      if(opcao==1){
         printf("Digite um número inteiro: ");
         scanf("%d",&i);
         push(f,i);
      }else
      if(opcao==2){
         pop(f);
         printf("Item removido com sucesso\n"); 
      }
      if(opcao==3){
         printf("%d\n", peek(f));
      }else
      if(opcao==4){
         print(f);
      }
   }
}*/