/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct{  
   char nome[30];
   float n1, n2, n3;
} typedef Aluno;


struct hash {
   int TABLE_SIZE;
   Aluno **itens; //os itens são um vetor de ponteiros
} typedef Hash;*/



/* Funcoes para manipulacao da tabela hash */
/*Hash *criaHash(int TABLE_SIZE){
   Hash *h = malloc(sizeof(Hash));
   int i;
   Aluno *ptAluno;
   h->TABLE_SIZE = TABLE_SIZE;   
   h->itens = malloc(TABLE_SIZE*sizeof(ptAluno));
   //h->qtd = 0;
   for (i=0;i<h->TABLE_SIZE;i++){  
      h->itens[i]=NULL;      
   }
   return h;
}


int gera_hash(char* s, int TABLE_SIZE){
   int i, hash = 0;
   int len_s = strlen(s);
   for (i=0;i<len_s;i++){
      hash  = hash + s[i];        
    }
    return hash%TABLE_SIZE;
}


void liberaHash(Hash *h){
   if(h!=NULL){
      int i;
      for(i=0;i<h->TABLE_SIZE;i++){
         if(h->itens[i]!=NULL)
            free(h->itens[i]);
      }
      free(h->itens);
      free(h);
   }
}*/


/*
   Inserir um novo elemento na tabela hash.
*/
/*void insere(Hash *h, Aluno *a){
   if(h==NULL){
      printf("Não será possível inserir");
   }
   else{
      h->itens[gera_hash(a->nome, h->TABLE_SIZE)] = a;
   }

}*/


/*
   Remover da tabela hash o elemento com a chave passada no parâmetro.
*/
/*void remover(Hash *h, char *chave){
   if(h==NULL){
      printf("Não será possível remover");
   }
   else{
      h->itens[gera_hash(chave, h->TABLE_SIZE)] = NULL;
      free(h->itens[gera_hash(chave, h->TABLE_SIZE)]);
   }

}*/


/*
  Busca na tabela hash o elemento com a chave passada no parâmetro.
*/
/*Aluno *busca(Hash *h, char *nome){
   return h->itens[gera_hash(nome, h->TABLE_SIZE)];
}*/

/**********************************************************/



/********* Funcoes para manipulacao da struct Aluno ************/
/*Aluno *cria_aluno(){
   Aluno *a = malloc(sizeof(Aluno));
   printf("Nome: ");
   scanf("%s",a->nome);
   printf("Nota 1: ");
   scanf("%f", &(a->n1));
   printf("Nota 2: ");
   scanf("%f", &(a->n2));
   printf("Nota 3: ");
   scanf("%f", &(a->n3));
   return a;
}

void print_aluno(Aluno *a){
   printf("%s: %f, %f, %f\n", a->nome, a->n1, a->n2, a->n3);
}*/
/************************************************************************/

/*int main(){

   int tamanho = 0;
   printf("Informe o tamanho da tabela: ");
   scanf("%d",&tamanho);

   Hash *h = criaHash(tamanho);


   int opcao = 1;
   while(opcao!=9){   
      printf("Selecione uma opção\n");
      printf("1 - Inserir\n");
      printf("2 - Remover\n");
      printf("3 - Buscar\n");      
      printf("9 - Sair\n");
      scanf("%d",&opcao);

     if(opcao==1){
        Aluno *a = cria_aluno();
        insere(h, a);        
     }else
     if(opcao==2){
        char nome[30];
        printf("Digite o nome do aluno: ");
        scanf("%s",nome);
        remover(h,nome);

     } else 
     if(opcao==3){
        char nome[30];
        printf("Digite o nome do aluno: ");
        scanf("%s",nome);
        Aluno *a = busca(h,nome);
        if(a==NULL)
           printf("Chave não encontrada.\n");
        else
           print_aluno(a);
     } 
   }
}*/