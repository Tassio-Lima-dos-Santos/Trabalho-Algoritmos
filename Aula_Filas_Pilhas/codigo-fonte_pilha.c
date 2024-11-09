#include <stdio.h>
#include <stdlib.h>


typedef struct lstItem{
   int dado;
   struct lstItem *next;
}pilhaItem;


typedef struct{
   pilhaItem *top;	
}pilha;



pilha *criaPilha(){
   pilha *p = malloc(sizeof(pilha));
   p->top = NULL;
   return p;
}


/* Inserir um novo elemento na pilha */
void *push(pilha *p, int dado){
   pilhaItem *novo = malloc(sizeof(pilhaItem));
   novo->dado = dado;
   novo->next = p->top;
   p->top = novo;
}


/* Remover um elemento da pilha */
void *pop(pilha *p){
   if(p->top!=NULL){
      pilhaItem *tmp = p->top;
      p->top = p->top->next;
      free(tmp);
   }
}


/* Retornar o dado que se encontra na cabeça da pilha */
int peek(pilha *p){
   if(p->top!=NULL){
      return p->top->dado;
   }else{
      return -1;
   }
}

void print(pilha *p){
   pilhaItem *item = p->top;
   while(item!=NULL){
      printf("%d --- ",item->dado);
      item = item->next;
   }
   printf("\n\n");
}



/*int main(){*/
   /*int opcao = 1, i; 

   while(opcao!=5){
      printf("\n1 - Empilhar\n");
      printf("2 - Desempilhar\n");
      printf("3 - Consultar cabeça (peek)\n");
      printf("4 - Imprimir a pilha\n");
      printf("5 - Sair\n");
      printf("\nDigite uma opcao: ");
      scanf("%d",&opcao);
      if(opcao==1){
         printf("Digite um número inteiro: ");
         scanf("%d",&i);
         push(p,i) ;
      }else
      if(opcao==2){
         pop(p);
         printf("Item removido com sucesso");
      }else
      if(opcao==3)  {
         printf("%d\n",peek(p));
      }else
      if(opcao==4)  {
         print(p);
      }
   }*/
   /*int input = 0;
   while(input>-1){
      printf("\nDigite um número: ");
      scanf("%d", &input);
      if(input>-1){
         pilha *p = criaPilha();
         int buffer = input;
         while(buffer>1){
            push(p, buffer%2);
            buffer = buffer/2;
         }
         push(p, buffer);
         printf("\nNumero em decimal : %d\nNumero em binario: ", input);
         while(p->top!=NULL){
            printf("%d", peek(p));
            pop(p);
         }
         printf("\n");
      }
   }*/
   /*char input[64];
   pilha *p = criaPilha();
   printf("Escreva uma sequencia de parentesis: ");
   fgets(input, 60, stdin);
   char buffer = ' ';
   for(int i = 0; buffer != '\0'; i++){
      buffer = input[i];
      if(buffer=='('){
         push(p, 1);
      }else if(buffer==')'){
         if(p->top!=NULL){
            pop(p);
         }else{
            printf("Sequencia invalida");
            return 0;
         }
      }
   }
   if(peek(p)==1){
      printf("Sequencia invalida");
      return 0;
   }else{
      printf("Sequencia valida");
      return 0;
   }
}*/
