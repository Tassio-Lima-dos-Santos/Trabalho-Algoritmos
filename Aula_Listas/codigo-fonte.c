/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
   char nome[30];
   float preco; 
} produto;


typedef struct lstItem{
   produto dado;
   struct lstItem *next;
} lstProduto;*/



/* Criação da lista: retorna uma lista vazia */
/*lstProduto *cria_lista(){
   return NULL;
}


*/
/* 
   Imprime a lista.
   Esta função é um exemplo de como percorrer uma lista encadeada.
*/
//void print(lstProduto *lista){
   /* "atual" é um ponteiro para o elemento da lista que está sendo examinado. Inicialmente, aponta para o primeiro elemento */
   /*lstProduto *atual = lista; 

   while(atual!=NULL){
      printf(">>Nome: %s; Preco: %f\n", (*atual).dado.nome, atual->dado.preco);
      atual = atual->next;
   }
}


*/
/* 
   Procura, em lstProduto, um elemento cujos dados sejam igual ao "dado" passado como parâmetro .
   Retorna um ponteiro para o elemento da lista que contém o referido dado.
*/
/*lstProduto *busca(lstProduto *lista, produto dado){
   lstProduto *item = lista;
   while(!( item->dado.preco == dado.preco && !strcmp(item->dado.nome, dado.nome)) ){
      item = (*item).next;
      if(item==NULL){
         return item;
      }
   }

   return item;
}

*/
/* 
   Insere um novo elemento no inicio na lista.
   Retorna um ponteiro para a cabeça da lista.
*/
/*lstProduto* insere_no_inicio(lstProduto *lista, produto dado){ 
   lstProduto* novo = malloc(sizeof(lstProduto));
   (*novo).dado = dado;
   (*novo).next = lista;
   lista = novo;   
   return lista;
}*/




/* 
   Insere um novo elemento no final na lista.
   Retorna um ponteiro para a cabeça da lista.

*/
/*lstProduto* insere_no_fim(lstProduto *lista, produto dado){
   if(lista==NULL){
      lista = insere_no_inicio(lista, dado);
      return lista;
   }
   lstProduto *item = lista;
   while(item->next!=NULL){
      item = (*item).next;
   }
   item->next = insere_no_inicio((*item).next, dado);

   return lista;
}*/




/* 
   Inserção do produto passado no parâmetro "dado" após a posicao que armazena o produto passado no parâmero "posicao".
   Retorna um ponteiro para a cabeça da lista.
*/
/*lstProduto *insere_apos(lstProduto *lista, produto dado, produto posicao){
   if(lista==NULL){
      lista = insere_no_inicio(lista, dado);
      return lista;
   }
   lstProduto *item = busca(lista, posicao);
   item->next = insere_no_inicio(item->next, dado);
   return lista;
}

void excluir(lstProduto *lista, produto dado){
   if(lista==NULL){
      printf("Não há itens");
   }else{
      lstProduto *item = lista, *itemAnt = lista;
      while(!( item->dado.preco == dado.preco && !strcmp(item->dado.nome, dado.nome)) ){
         itemAnt = item;
         item = (*item).next;
         if(item==NULL){
            break;
         }
      }
      if(itemAnt==lista){
         lista = item->next;
      }else{
         itemAnt->next = item->next;
      }
      free(item);
   }
}




*/
/* Execução das rotinas necessárias para ler os dados de um novo produto */
/*produto *novo_produto(){
   produto *novo = malloc(sizeof(produto));
   printf("Nome do produto: ");
   scanf("%s",(*novo).nome);
   printf("Preço: ");
   scanf("%f",&((*novo).preco));
   return novo;
}

int main(){

   lstProduto *lista = cria_lista();

   int opcao = 0;   

   while(opcao!=9){  */ 
      /* Imprime o menu de opcoes */
      /*printf("1 - Inserir no início da lista\n"); 
      printf("2 - Inserir no meio da lista\n");
      printf("3 - Inserir no fim da lista\n");
      printf("4 - Excluir elemento da lista\n");
      printf("5 - Imprimir a lista\n");
      printf("6 - Pesquisar\n");
      printf("9 - Encerrar o programa\n");
      printf("\nDigite a opção desejada: ");
      scanf("%d",&opcao);
      printf("Opcao selecionada %d\n", opcao);
   
      if(opcao==1){
         produto *novo = novo_produto(); 
         lista = insere_no_inicio(lista, *novo);
      }else 
      if(opcao==2){        
         produto *novo = novo_produto();          
         printf("Informe a posição que o novo elemento deve ocupar:\n");    
         produto *posicao = novo_produto();
         lista = insere_apos(lista, *novo, *posicao);
      }else
      if(opcao==3){
         produto *novo = novo_produto(); 
         lista = insere_no_fim(lista, *novo);
      }else
      if(opcao==4){
         produto *selecionado = novo_produto();
         excluir(lista, *selecionado);
      }else
      if(opcao==5){
         print(lista);
         getchar();
      }else
      if(opcao==6){
         produto *novo = novo_produto();          
         lstProduto *p = busca(lista, *novo);       
         if(p==NULL)
            printf("Produto não encontrado.\n"); 
         else
           printf("Produto encontrado.\n"); 
           printf(">>Nome: %s; Preco: %f\n", (*p).dado.nome, p->dado.preco);
         printf("\n pressione qualquer tecla para continuar\n"  );
         getchar();
         getchar();
      }   



   }

}*/