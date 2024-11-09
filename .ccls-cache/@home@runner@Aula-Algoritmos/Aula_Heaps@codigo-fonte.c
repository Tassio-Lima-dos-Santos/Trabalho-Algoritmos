#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Tarefa{
   char nome[30];
   int prioridade;
} Tarefa;



typedef struct {
   int comprimento; //número de elementos no vetor
   int tamanho_do_heap; //número de elementos no heap
   Tarefa *v; //ponteiro para o primeiro elemento do vetor
}Heap;


Heap *criaHeap(int comprimento){
   Heap *h = malloc(sizeof(Heap));
   h->tamanho_do_heap = 0;
   h->comprimento = comprimento;
   h->v = malloc(sizeof(Tarefa)*comprimento);
   
   return h;
}


Tarefa *cria_tarefa(){
   Tarefa *t = malloc(sizeof(Tarefa));
   printf("Nome: ");
   scanf("%s",t->nome);
   while ((getchar()!='\n') && (getchar()!=EOF) );
   printf("Prioridade: ");
   scanf("%d", &(t->prioridade));
   while ((getchar()!='\n') && (getchar()!=EOF) );
   return t;
}


void imprime_tarefa(Tarefa t){
   printf("Nome: %s - Prioridade: %d\n", t.nome, t.prioridade);
}


/*
   Retorna o índice do elemento "pai" daquele que tem o índice "i" passado no parÃ¢metro.

   Baseado em 
   Cormen, Thomas H., Charles E. Leiserson, Ronald L. Rivest and Clifford Stein. 
   Algoritmos: Teoria E Prática. 3 ed.: Campus, 2012. ISBN: 9788535236996.
*/
int parent(int i){
   return i/2;
} 

void troca(Tarefa *v, int posicao1, int posicao2){
   Tarefa *buffer = malloc(sizeof(Tarefa));
   *buffer = v[posicao1-1];
   v[posicao1-1] = v[posicao2-1];
   v[posicao2-1] = *buffer;
   free(buffer);
}

/*
   Mantém a propriedade de heap máximo para o vetor cujo elemento é apontado por v, 
   de tamanho "tamanho_heap", a partir da posição "posicao".

   Considera-se que "v" aponte para um max_heap mas v[posicao], pode ser menor que seus dois 
   filhos, violando a propriedade do heap. Esta função faz com que v[posicao] "flutue" para baixo 
   para manter essa propriedade.

   Considerar a "posicao" do heap (comeÃ§ando em 1) e nÃ£o do vetor (que começa em 0)

   Baseado em 
   Cormen, Thomas H., Charles E. Leiserson, Ronald L. Rivest and Clifford Stein. 
   Algoritmos: Teoria E Prática. 3 ed.: Campus, 2012. ISBN: 9788535236996.
*/
Tarefa *max_heapify(Tarefa *v, int posicao, int tamanho_heap){
   int left = 2*posicao, right = left+1, maior = posicao;
   if(left <= tamanho_heap && v[left-1].prioridade > v[maior-1].prioridade){
      maior = left;
   }
   if(right <= tamanho_heap && v[right-1].prioridade > v[maior-1].prioridade){
      maior = right;
   }
   if(maior != posicao){
      troca(v, maior, posicao);
      return max_heapify(v, maior, tamanho_heap);
   }else{
      return v;
   }
}


/*
   Converte um vetor v em um heap.

   Baseado em 
   Cormen, Thomas H., Charles E. Leiserson, Ronald L. Rivest and Clifford Stein. 
   Algoritmos: Teoria E Prática. 3 ed.: Campus, 2012. ISBN: 9788535236996.
*/
Tarefa *build_max_heap(Tarefa *v, int tamanho_vetor){
   int i;
   for(i=tamanho_vetor/2;i>0;i--){
      printf("Max heapify x %d\n", i);
      max_heapify(v,i,tamanho_vetor);
   }
}


void heap_increase_key(Heap *h, int i, int prioridade){
   if(h->v[i-1].prioridade < prioridade){
      h->v[i-1].prioridade = prioridade;
      while(i>1 & h->v[parent(i)-1].prioridade<h->v[i-1].prioridade){
         Tarefa t = h->v[parent(i)-1];
         h->v[parent(i)-1] = h->v[i-1];
         h->v[i-1] = t;
         i = parent(i);
      }
   }
}

/*
   Baseado em 
   Cormen, Thomas H., Charles E. Leiserson, Ronald L. Rivest and Clifford Stein. 
   Algoritmos: Teoria E Prática. 3 ed.: Campus, 2012. ISBN: 9788535236996.
*/   
Tarefa extract_max(Heap *h){
   if(h->tamanho_do_heap>1){
      Tarefa removido = h->v[0];
      h->v[0] = h->v[h->tamanho_do_heap-1];
      h->tamanho_do_heap--;
      max_heapify(h->v, 1, h->tamanho_do_heap);
      return removido;
   }
}







/* Insere o valor x no heap h. Retorna 1 em caso de sucesso e 0 em caso de falha.

   Baseado em 
   Cormen, Thomas H., Charles E. Leiserson, Ronald L. Rivest and Clifford Stein. 
   Algoritmos: Teoria E Prática. 3 ed.: Campus, 2012. ISBN: 9788535236996.
*/ 
int insert_max(Heap *h, Tarefa x){
    if(h->tamanho_do_heap<h->comprimento){
       h->tamanho_do_heap++;
       h->v[h->tamanho_do_heap-1] = x;
       h->v[h->tamanho_do_heap-1].prioridade = -1;
       heap_increase_key(h, h->tamanho_do_heap, x.prioridade);
       return 1;
    }
    else
       return 0;
}


void imprimeHeap(Heap *h){
    int i;
    for(i=0;i<h->tamanho_do_heap;i++)
       imprime_tarefa(h->v[i]);
    printf("\n");
}



int main(){

    Heap *h = criaHeap(10);

      int opcao = 0;
    while(opcao!=9){
       printf("1 - Inserir no heap\n");
       printf("2 - Consultar prioridade\n");
       printf("3 - Remover\n");
       printf("4 - Imprimir\n");
       printf("9 - Sair\n");
       printf("\n\nDigite uma opÃ§Ã£o: ");
       scanf("%d", &opcao);

       if(opcao==1){
          Tarefa *t = cria_tarefa();
          insert_max(h,*t);         
          free(t); t = NULL; 
       }else
       if(opcao==2){
          imprime_tarefa(h->v[0]);
       }else
       if(opcao==3){
          Tarefa t = extract_max(h);
          printf("Excluiu "); imprime_tarefa(t); printf("\n");
       }else
       if(opcao==4){
          imprimeHeap(h);
       }
       else
       if(opcao==5){
          int i;
          printf("Indice: ");
          scanf("%d",&i);
          imprime_tarefa(h->v[i]);
       }
    }



}