/* Para executar em terminal, digitar gcc trabalho_cac3202_20242.c -o trabalho_cac3202_20242 -pthread */


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//Struct que representa uma coordenada (X,Y)
typedef struct ponto{
   int x; //coordenada X
   int y; // coordenada Y
}Ponto;


//Struct que representa uma visita a um determinado ponto em uma determinada hora
typedef struct visita{
   Ponto coordenada;
   struct tm *hora; //hora em que a visita aconteceu   
}Visita;


int thread_status = 1;
Visita v; //variÃ¡vel global que armazena a Ãºltima visita realizada
float distancia; //variÃ¡vel global que armazena a distÃ¢ncia para o obstÃ¡culo mais prÃ³ximo

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


//funÃ§Ã£o que retorna os dados da Ãºltima visita
Visita ultima_visita(){
   return v;
}


//funÃ§Ã£o que retorna a distÃ¢ncia atual para o obstÃ¡culo mais prÃ³ximo
float distancia_obstaculo(){
   return distancia;
}


// FunÃ§Ã£o que simula a geraÃ§Ã£o de valores de sensores
void* gerar_valores_de_sensores(void* arg) {

    while (thread_status==1) {
        //*** gerar valores aleatÃ³rios para distÃ¢ncia do obstÃ¡culo e coordenadas X,Y:
        srand(time(NULL));
        int x = rand() % 100;    // Inteiro entre 0 e 99
        int y = rand() % 100;    // Inteiro entre 0 e 99
        distancia = (float)rand() / (float)(RAND_MAX) * 100.0;  // Float entre 0.0 e 100.0


        // *** capturar a hora atual *** 
        time_t agora;
        time(&agora); //obter o tempo atual



        v.coordenada.x = x;
        v.coordenada.y = y;
        v.hora = localtime(&agora);  

        // Sinaliza a thread de leitura de sensores pode executar
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);


        sleep(1);  // Aguarda um segundo atÃ© a prÃ³xima leitura de sensores
    }
    return NULL;
}



// FunÃ§Ã£o que simula a leitura de valores de sensores
void* ler_valores_de_sensores(void* arg) {
    Visita visita;     
    while (thread_status == 1) {
        // Espera atÃ© receber o sinal da thread de geraÃ§Ã£o de valores
        pthread_mutex_lock(&mutex);

        // Verifica se o programa ainda deve continuar antes de esperar pelo sinal
        if (thread_status == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_cond_wait(&cond, &mutex);

        if (thread_status == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        //*** As trÃªs linhas abaixo ilustram a leitura de sensores. Descomentar para testar 
        //printf("DistÃ¢ncia para o obstÃ¡culo mais prÃ³ximo: %f\n", distancia_obstaculo());
        //Visita visita = ultima_visita();
        //printf("(%d,%d) - %02d:%02d:%02d\n",visita.coordenada.x, visita.coordenada.y, visita.hora->tm_hour, visita.hora->tm_min, visita.hora->tm_sec);

        /**** Implementar a leitura dos sensores aqui ****/


        /**** Finalizar a leitura dos sensores aqui  ****/

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


//**** Implementar todas as funÃ§Ãµes e estruturas de dados aqui ****/

/************ Início - Lista das distâncias de obstáculo **************/

// Estrutura de um nó da lista encadeada
typedef struct item {
    float distancia;          // Valor da leitura de distância
    struct item *proximo, *anterior;      // Ponteiros para o nó posterior e anterior
} Item;

// Estrutura da lista encadeada
typedef struct {
    Item *inicio, *fim;                  // Ponteiros para o primeiro e último nó
    int tamanho;              // Número de elementos na lista
} ListaEncadeada;

// Função para criar uma lista encadeada
ListaEncadeada* criar_lista() {
    ListaEncadeada* lista = malloc(sizeof(ListaEncadeada));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função para adicionar uma leitura à lista
void adicionar_distancia(ListaEncadeada* lista, float distancia) {
    Item* novo = malloc(sizeof(Item));
    novo->distancia = distancia;
    novo->proximo = NULL;
    novo->anterior = lista->fim;

    // Adiciona o novo nó no final da lista
    if (lista->fim == NULL) { // Lista vazia
        lista->inicio = novo;
    } else {
        lista->fim->proximo = novo;
    }
    lista->fim = novo;
    lista->tamanho++;
}

// Função para calcular a média das x leituras mais antigas
float calcular_media_antigas(ListaEncadeada* lista, int x) {
    if (x > lista->tamanho) {
        printf("Erro: não há leituras suficientes para calcular a média.\n");
        return -1.0;
    }

    Item *atual = lista->inicio;
    float soma = 0.0;

    // Soma as distâncias das x leituras mais antigas
    for(int i = 0; atual != NULL && i < x; i++) {
        soma += atual->distancia;
        atual = atual->proximo;
    }

    return soma / x;
}

float calcular_media_recentes(ListaEncadeada* lista, int x) {
    if (x > lista->tamanho) {
        printf("Erro: não há leituras suficientes para calcular a média.\n");
        return -1.0;
    }

    Item *atual = lista->fim;
    float soma = 0.0;

    // Soma as distâncias das x leituras mais antigas
    for(int i = 0; atual != NULL && i < x; i++) {
        soma += atual->distancia;
        atual = atual->anterior;
    }

    return soma / x;
}

/************ Fim - Lista das distâncias de obstáculo **************/

/************ Início - Árvore das Visitas do Veículo **************/

float dist_coords(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

struct no_tree{
   Visita dado;
   struct no_tree *left, *right; //filho da esquerda e da direita
} typedef No_tree;

typedef struct{
   No_tree *raiz, *minimo, *maximo, *ultimo; // Nós importantes da árvore: A raiz da árvore, a visita mais
   // próxima de (0,0), a visita mais distante de (0,0) e a última visita feita
} Tree;

Tree *iniciar_arvore(){ // Inicia uma variável Tree que vai gerenciar a estrutura de dados responsável 
                        // pelas coordenadas
   Tree *tree = malloc(sizeof(Tree));
   tree->raiz = NULL;
   tree->minimo = NULL;
   tree->maximo = NULL;
   tree->ultimo = NULL;

   return tree;
}

int comparar_visitas(Visita visita1, Visita visita2){

    /* A função cria uma ordem para as coordenadas, na qual coordenadas mais distantes da origem
    tem prioridade sobre as menos distantes, e entre as equidistantes, as mais distantes da origem
    no eixo x tem prioridade sobre as menos distantes. O valor que a função retorna informa qual
    dos dois nós comparados tem prioridade nessa ordem, caso a função retorne 1, o primeiro nó
    tem prioridade, caso a função retorne 2, o segundo nó tem prioridade, e caso as duas coordenadas
    sejam iguais, a função retorna 0.*/

   float dist[2] = {dist_coords(visita1.coordenada.x, visita1.coordenada.y, 0, 0),
                    dist_coords(visita2.coordenada.x, visita2.coordenada.y, 0, 0)};
    // As distâncias das coordenadas dos nós até a origem
   if(dist[0] > dist[1]){
        return 1;
   }else if(dist[0] < dist[1]){
        return 2;
   }else if(visita1.coordenada.x > visita2.coordenada.x){
        return 1;
   }else if(visita1.coordenada.x < visita2.coordenada.x){
        return 2;
   }else{
        return 0;
   }
}

void adicionar_visita(Tree *tree, Visita dado_novo){
    tree->ultimo = insert(tree->raiz, dado_novo);
    if(tree->raiz == NULL){
        tree->raiz = tree->ultimo;
    }
    if(dist_coords(tree->ultimo->dado.coordenada.x, tree->ultimo->dado.coordenada.y, 0, 0) >= dist_coords(tree->maximo->dado.coordenada.x, tree->maximo->dado.coordenada.y, 0, 0)){
        tree->maximo = tree->ultimo;
    }if(dist_coords(tree->ultimo->dado.coordenada.x, tree->ultimo->dado.coordenada.y, 0, 0) <= dist_coords(tree->minimo->dado.coordenada.x, tree->minimo->dado.coordenada.y, 0, 0)){
        tree->minimo = tree->ultimo;
    }
}

No_tree *insert(No_tree *t, Visita dado){
    No_tree *noAtual = t;
    while(noAtual != NULL){
      if(comparar_visitas(noAtual->dado, dado) == 2)
         noAtual = noAtual->left;     
      else
         noAtual = noAtual->right;
    }
    noAtual = malloc(sizeof(No_tree));
    noAtual->dado = dado;
    noAtual->left = NULL;
    noAtual->right = NULL; 
    return noAtual;
   /*if(t==NULL){
      t = malloc(sizeof(No_tree));
      t->dado = dado;
      t->left = NULL;
      t->right = NULL; 
   }else{
      if(comparar_visitas(t->dado, dado) == 1)
         (*t).left = insert((*t).left,dado);     
      else
         (*t).right = insert((*t).right,dado); 
   }*/
}

No_tree *buscar_visita(No_tree *t, Visita value){
   if(t==NULL || comparar_visitas(t->dado, value) == 0){
      return t;
   }else{
      if(comparar_visitas(t->dado, value) == 1)
         return search_value(t->left, value);
      else
         return search_value(t->right, value);
   }    
}

/************ Fim - Árvore das Visitas do Veículo **************/

//**** 	 ****/


int main() {
    pthread_t thread_gerar, thread_ler;
    Visita visita; 
    int opcao=0;

    // CriaÃ§Ã£o da thread que simula geraÃ§Ã£o de valores de sensores
    if (pthread_create(&thread_gerar, NULL, gerar_valores_de_sensores, NULL) != 0) {
        perror("Erro ao criar thread");
        return 1;
    }

    // CriaÃ§Ã£o da thread que lÃª de valores de sensores simulados
    if (pthread_create(&thread_ler, NULL, ler_valores_de_sensores, NULL) != 0) {
        perror("Erro ao criar thread");
        return 1;
    }

    // FunÃ§Ã£o principal aguarda a tecla ENTER para imprimir o contador
    while (opcao!=9) {
        printf("Selecione uma das opÃ§Ãµes abaixo: \n");
        printf("1. Imprimir distÃ¢ncia para o obstÃ¡culo mais prÃ³ximo\n");
        printf("2. Imprimir os dados do Ãºltimo ponto visitado\n");
        printf("3. Imprimir a distÃ¢ncia mÃ©dia para o obstÃ¡culo mais prÃ³ximo nas primeiras 'x' leituras\n");
        printf("4. Imprimir a distÃ¢ncia mÃ©dia para o obstÃ¡culo mais prÃ³ximo nas Ãºltimas 'x' leituras\n");
        printf("5. Imprimir o horÃ¡rio da primeira visita a um ponto.\n");
        printf("6. Imprimir o a distÃ¢ncia entre o Ãºltimo ponto ponto visitado e o ponto mais distante das coordenadas (0, 0)\n");
        printf("7. Imprimir o a distÃ¢ncia entre o Ãºltimo ponto ponto visitado e o ponto mais prÃ³ximo das coordenadas (0, 0)\n");
        printf("9. Encerrar o programa\n");


        printf("\nDigite uma opÃ§Ã£o: ");
        scanf("%d",&opcao);
        switch(opcao){
           case 1: 
              printf("%f\n", distancia_obstaculo()); 
              break;
           case 2: 
              visita = ultima_visita();
              printf("(%d,%d) - %02d:%02d:%02d\n",visita.coordenada.x, visita.coordenada.y, visita.hora->tm_hour, visita.hora->tm_min, visita.hora->tm_sec);
              break;
           /**** Implementar as opÃ§Ãµes 3 a 7 aqui ****/   

           /**** Fim da implementaÃ§Ã£o das opÃ§Ãµes 3 a 7  ****/
           case 9: 
              pthread_mutex_lock(&mutex);
              thread_status = 0;
              pthread_cond_broadcast(&cond); // Sinalizar todas as threads
              pthread_mutex_unlock(&mutex);
              break;     
           default:
              printf("OpÃ§Ã£o invÃ¡lida\n");
        }





    }

    // Espera as threads finaizarem
    pthread_join(thread_gerar, NULL);
    pthread_join(thread_ler, NULL);

    return 0;
}
