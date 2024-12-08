/* Para executar em terminal, digitar gcc codigo-fonte.c -o trabalho_cac3202_20242 -pthread */


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



//**** Implementar todas as funÃ§Ãµes e estruturas de dados aqui ****/

/************ Início - Lista das Distâncias de Obstáculo **************/

// Estrutura de um nó da lista encadeada de distância
typedef struct item_distancia {
    float distancia;          // Valor da leitura de distância
    struct item_distancia *proximo, *anterior;      // Ponteiros para o nó posterior e anterior
} Item_distancia;

// Estrutura da lista encadeada de distância
typedef struct {
    Item_distancia *inicio, *fim;                  // Ponteiros para o primeiro e último nó
    int tamanho;              // Número de elementos na lista
} ListaEncadeada_distancia;

// Função para criar uma lista encadeada de distância
ListaEncadeada_distancia* iniciar_lista_distancia() {
    ListaEncadeada_distancia* lista = malloc(sizeof(ListaEncadeada_distancia));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função para adicionar uma leitura à lista
void adicionar_distancia(ListaEncadeada_distancia* lista, float distancia) {
    Item_distancia* novo = malloc(sizeof(Item_distancia)); // Aloca um espaço na memória para um novo item da lista
    novo->distancia = distancia; // Grava a distância no novo item
    novo->proximo = NULL; // Seta o ponteiro do novo item para o próximo como NULL
    novo->anterior = lista->fim; // Seta o ponteiro do novo item para o anterior como o item apontado pelo ponteiro fim

    // Adiciona o novo nó no final da lista
    if (lista->fim == NULL) { // Lista vazia
        lista->inicio = novo; // Ponteiro início aponta para o novo item
    } else { // Caso a lista não for vazia
        lista->fim->proximo = novo; // Ponteiro próximo do item anterior aponta o novo item
    }
    lista->fim = novo;
    lista->tamanho++;
}

// Função para calcular a média das x leituras mais antigas
float calcular_media_antigas(ListaEncadeada_distancia* lista, int x) {
    if (x > lista->tamanho) {
        printf("Erro: não há leituras suficientes para calcular a média.\n");
        return -1.0;
    }

    Item_distancia *atual = lista->inicio; // Inicia do item apontado pelo ponteiro início
    float soma = 0.0;

    // Soma as distâncias das x leituras mais antigas
    for(int i = 0; atual != NULL && i < x; i++) {
        soma += atual->distancia;
        atual = atual->proximo; // Vai percorrendo a lista passando a cada passo para o proximo item
    }

    return soma / x;
}

float calcular_media_recentes(ListaEncadeada_distancia* lista, int x) {
    if (x > lista->tamanho) {
        printf("Erro: não há leituras suficientes para calcular a média.\n");
        return -1.0;
    }

    Item_distancia *atual = lista->fim; // Inicia do último item
    float soma = 0.0;

    // Soma as distâncias das x leituras mais antigas
    for(int i = 0; atual != NULL && i < x; i++) {
        soma += atual->distancia;
        atual = atual->anterior; // Percorre a lista passando para o item anterior a cada passo
    }

    return soma / x;
}

/************ Fim - Lista das Distâncias de Obstáculo **************/

/************ Início - Lista das Visitas do Veículo **************/

// Estrutura de um nó da lista encadeada de visita
typedef struct item_visita {
    Visita dado;          // Valor da leitura de visita
    struct item_visita *proximo;      // Ponteiros para o nó posterior e anterior
} Item_visita;

// Estrutura da lista encadeada de visita
typedef struct {
    Item_visita *inicio, *fim;                  // Ponteiros para o primeiro e último nó
    int tamanho;              // Número de elementos na lista
} ListaEncadeada_visita;

// Função para criar uma lista encadeada de visita
ListaEncadeada_visita* iniciar_lista_visita() {
    ListaEncadeada_visita* lista = malloc(sizeof(ListaEncadeada_visita));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função para adicionar uma leitura à lista de visitas
void adicionar_visita_lista(ListaEncadeada_visita* lista, Visita dado) {
    Item_visita* novo = malloc(sizeof(Item_visita)); // Aloca um espaço na memória para um novo item da lista
    novo->dado = dado; // Grava a visita no novo item
    novo->proximo = NULL; // Seta o ponteiro do novo item para o próximo como NULL

    // Adiciona o novo nó no final da lista
    if (lista->fim == NULL) { // Lista vazia
        lista->inicio = novo; // Ponteiro início aponta para o novo item
    } else { // Caso a lista não for vazia
        lista->fim->proximo = novo; // Ponteiro próximo do item anterior aponta o novo item
    }
    lista->fim = novo;
    lista->tamanho++;
}

/************ Fim - Lista das Visitas do Veículo **************/

/************ Início - Árvore das Visitas do Veículo **************/

struct no_tree{ // Struct dos nós da árvore
   ListaEncadeada_visita *lista_dado;
   struct no_tree *left, *right; // filho da esquerda e da direita
   int altura; // Altura do nó para a folha mais baixa
} typedef No_tree;

typedef struct{
   No_tree *raiz, *minimo, *maximo, *ultimo; // Nós importantes da árvore: A raiz da árvore, a visita mais
   // próxima de (0,0), a visita mais distante de (0,0) e a última visita feita
} Tree;

/************ Início - Funções necessárias para o funcionamento da árvore **************/
float dist_coords(int x1, int y1, int x2, int y2){ // Distância entre duas coordenadas
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
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
   }else if(visita1.coordenada.y > visita2.coordenada.y){
        return 1;
   }else if(visita1.coordenada.y < visita2.coordenada.y){
        return 2;
   }else{
        return 0;
   }
}

No_tree *criarNo(Visita dado_novo){
    // Inicia um nó que guarda o dado passado como argumento da função
    No_tree *novo_no = malloc(sizeof(No_tree));
    novo_no->lista_dado = iniciar_lista_visita();
    adicionar_visita_lista(novo_no->lista_dado, dado_novo);
    novo_no->left = NULL;
    novo_no->right = NULL;
    novo_no->altura = 1;
    return novo_no;
}

int getAltura(No_tree *n)
{
    // Serve para sempre obter a altura de um nó sem gerar erro, pois trata o caso do ponteiro apontar para NULL
    if(n == NULL){
        return 0;
    }
    return n->altura;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int updateAltura(No_tree *n){ // Atualiza a altura de um nó acrescentando 1 à altura do filho mais "alto"
    return max(getAltura(n->left), getAltura(n->right)) + 1;
}

int getBalanceFactor(No_tree *n){ 
    // Retorna o valor de balanço de um dado nó, que basicamente fala qual lado do nó está mais "pesado",
    // >0 = lado esquerdo mais pesado, <0 = lado direito mais pesado, =0 = nó equilibrado
    if (n == NULL)
        return 0;
    return getAltura(n->left) - getAltura(n->right);
}

No_tree *rightRotate(No_tree *y){ 
    // Faz o nó da esquerda de um dado nó se tornar seu pai e o dado nó ir para direita do outro nó

    No_tree *x = y->left;
    No_tree *T2 = x->right;

    // Performa a rotação
    x->right = y;
    y->left = T2;

    // Atualiza as alturas dos nós que foram trocados
    y->altura = updateAltura(y);
    x->altura = updateAltura(x);

    return x;
}

No_tree *leftRotate(No_tree *x){
    // Faz o nó da direita de um dado nó se tornar seu pai e o dado nó ir para esquerda do outro nó

    No_tree *y = x->right;
    No_tree *T2 = y->left;

    // Performa a rotação
    y->left = x;
    x->right = T2;

    // Atualiza as alturas dos nós que foram trocados
    x->altura = updateAltura(x);
    y->altura = updateAltura(y);

    return y;
}

/************ Fim - Funções necessárias para o funcionamento da árvore **************/

Tree *iniciar_arvore(){
   // Inicia uma variável Tree que vai gerenciar a estrutura de dados responsável 
   // pelas coordenadas
   Tree *tree = malloc(sizeof(Tree));
   tree->raiz = NULL;
   tree->minimo = NULL;
   tree->maximo = NULL;
   tree->ultimo = NULL;

   return tree;
}

No_tree *insert(No_tree *no_atual, Visita novo_dado){
    // 1. Inserção de árvore binária padrão
    if (no_atual == NULL){
        No_tree *novo_no = criarNo(novo_dado);
        return novo_no;
    }

    if(comparar_visitas(no_atual->lista_dado->inicio->dado, novo_dado) == 1){
        no_atual->left = insert(no_atual->left, novo_dado);
    }else if(comparar_visitas(no_atual->lista_dado->inicio->dado, novo_dado) == 2){
        no_atual->right = insert(no_atual->right, novo_dado);
    }else{
        adicionar_visita_lista(no_atual->lista_dado, novo_dado);
        return no_atual;
    }

    // 2. Atualiza recursivamente as alturas dos nós
    no_atual->altura = updateAltura(no_atual);

    // 3. Pega o valor de balanço do nó atual e checa se o nó está desbalanceado
    int balance = getBalanceFactor(no_atual);

    // 4. Se o nó está desbalanceado, há 4 casos desse desbalanço

    // Caso Left Left
    if (balance > 1 && (comparar_visitas(no_atual->left->lista_dado->inicio->dado, novo_dado) == 1))
        return rightRotate(no_atual);

    // Caso Right Right 
    if (balance < -1 && (comparar_visitas(no_atual->right->lista_dado->inicio->dado, novo_dado) == 2))
        return leftRotate(no_atual);

    // Caso Left Right
    if (balance > 1 && (comparar_visitas(no_atual->left->lista_dado->inicio->dado, novo_dado) == 2)) {
        no_atual->left = leftRotate(no_atual->left);
        return rightRotate(no_atual);
    }

    // Caso Right Left
    if (balance < -1 && (comparar_visitas(no_atual->right->lista_dado->inicio->dado, novo_dado) == 1)) {
        no_atual->right = rightRotate(no_atual->right);
        return leftRotate(no_atual);
    }

    // Retorna o endereço do nó atual
    return no_atual;

    // Fonte: https://www.geeksforgeeks.org/c-program-to-implement-avl-tree/
}

No_tree *buscar_visita(No_tree *t, Visita value){
   if(t==NULL || comparar_visitas(t->lista_dado->inicio->dado, value) == 0){
      // Caso o nó atual for NULL ou seu dado for igual ao procurado, então o nó atual é retornado
      return t;
   }else{
      if(comparar_visitas(t->lista_dado->inicio->dado, value) == 1){
         // Caso o nó atual tenha preferência na comparação com o dado procurado, procurar no nó a esquerda
         return buscar_visita(t->left, value);
      }
      else{
         // Caso o dado procurado tenha preferência na comparação com o nó atual, procurar no nó a direita
         return buscar_visita(t->right, value);
      }
   }    
}

void adicionar_visita_arvore(Tree *tree, Visita dado_novo){
    //printf("\n\nfuncao adicionar_visita_arvore chamada\n\n");
    tree->raiz = insert(tree->raiz, dado_novo); // Insere o novo nó na árvore
    //printf("\n\nno inserido\n\n");
    tree->ultimo = buscar_visita(tree->raiz, dado_novo);
    if(tree->maximo == NULL){
        tree->maximo = tree->ultimo;
    }else{
        if(comparar_visitas(dado_novo, tree->maximo->lista_dado->inicio->dado) == 1){
            // Se ao comparar as coordenadas da última visita e da visita mais distante do ponto (0,0)
            // a visita mais distante não tiver prioridade, o último nó se torna o nó máximo
            tree->maximo = tree->ultimo;
        }
    }if(tree->minimo == NULL){
        tree->minimo = tree->ultimo;
    }else{
        if(comparar_visitas(tree->minimo->lista_dado->inicio->dado, tree->ultimo->lista_dado->inicio->dado) == 1){
            // Se ao comparar as coordenadas da última visita e da visita mais próxima do ponto (0,0)
            // a última visita não tiver prioridade, o último nó se torna o nó mínimo
            tree->minimo = tree->ultimo;
        }
    }
}

/************ Fim - Árvore das Visitas do Veículo **************/

/************ Início - Criação das Estruturas **************/

ListaEncadeada_distancia *lista_de_distancias = NULL;
Tree *arvore_de_visitas = NULL;

/************ Fim - Criação das Estruturas **************/

//**** 	 ****/

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

        if(lista_de_distancias == NULL){
            lista_de_distancias = iniciar_lista_distancia();
        }if(arvore_de_visitas == NULL){
           arvore_de_visitas = iniciar_arvore();
        }
        adicionar_distancia(lista_de_distancias, distancia_obstaculo());
        adicionar_visita_arvore(arvore_de_visitas, ultima_visita());

        /**** Finalizar a leitura dos sensores aqui  ****/

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread_gerar, thread_ler;
    Visita visita; 
    int opcao=0;

    lista_de_distancias = iniciar_lista_distancia();
    arvore_de_visitas = iniciar_arvore();

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
        printf("Selecione uma das opcoes abaixo: \n");
        printf("1. Imprimir distancia para o obstaculo mais proximo\n");
        printf("2. Imprimir os dados do ultimo ponto visitado\n");
        printf("3. Imprimir a distancia media para o obstaculo mais proximo nas primeiras 'x' leituras\n");
        printf("4. Imprimir a distancia media para o obstaculo mais proximo nas ultimas 'x' leituras\n");
        printf("5. Imprimir o horario da primeira visita a um ponto.\n");
        printf("6. Imprimir o a distancia entre o ultimo ponto ponto visitado e o ponto mais distante das coordenadas (0, 0)\n");
        printf("7. Imprimir o a distancia entre o ultimo ponto ponto visitado e o ponto mais proximo das coordenadas (0, 0)\n");
        printf("9. Encerrar o programa\n");


        printf("\nDigite uma opcao: ");
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
           case 3: 
              printf("x: ");
              int x;
              scanf("%d", &x);
              printf("Distancia media para o obstaculo mais proximo nas primeiras %d leituras: %f\n\n", x, calcular_media_antigas(lista_de_distancias, x));
              break;
           case 4: 
              printf("x: ");
              int input;
              scanf("%d", &input);
              printf("Distancia media para o obstaculo mais proximo nas ultimas %d leituras: %f\n\n", input, calcular_media_recentes(lista_de_distancias, input));
              break;
           case 5: 
              int coordx, coordy;
              printf("Coordenada x do ponto: ");
              scanf("%d", &coordx);
              printf("Coordenada y do ponto: ");
              scanf("%d", &coordy);
              Visita ponto;
              ponto.coordenada.x = coordx;
              ponto.coordenada.y = coordy;
              No_tree *no_ponto = buscar_visita(arvore_de_visitas->raiz, ponto);
              if(no_ponto == NULL){
                printf("Ponto ainda nao visitado\n\n");
              }else{
                Visita primeira_visita = no_ponto->lista_dado->inicio->dado;
                printf("Horario que o ponto foi visitado pela primeira vez: %02d:%02d:%02d\n\n", primeira_visita.hora->tm_hour, primeira_visita.hora->tm_min, primeira_visita.hora->tm_sec);
              }
              break;
           case 6: 
              Visita ultimo_ponto = arvore_de_visitas->ultimo->lista_dado->fim->dado;
              Visita ponto_mais_distante = arvore_de_visitas->maximo->lista_dado->fim->dado;
              printf("Coordenadas do ultimo ponto lido: (%d,%d)\n", ultimo_ponto.coordenada.x, ultimo_ponto.coordenada.y);
              printf("Coordenadas do ponto visitado mais distante das coordenadas (0, 0): (%d,%d)\n", ponto_mais_distante.coordenada.x, ponto_mais_distante.coordenada.y);
              printf("Distancia entre esses dois pontos: %f\n\n", dist_coords(ultimo_ponto.coordenada.x, ultimo_ponto.coordenada.y, ponto_mais_distante.coordenada.x, ponto_mais_distante.coordenada.y));
              break;
           case 7: 
              Visita ultimo_pont = arvore_de_visitas->ultimo->lista_dado->fim->dado;
              Visita ponto_mais_proximo = arvore_de_visitas->minimo->lista_dado->fim->dado;
              printf("Coordenadas do ultimo ponto lido: (%d,%d)\n", ultimo_pont.coordenada.x, ultimo_pont.coordenada.y);
              printf("Coordenadas do ponto visitado mais proximo das coordenadas (0, 0): (%d,%d)\n", ponto_mais_proximo.coordenada.x, ponto_mais_proximo.coordenada.y);
              printf("Distancia entre esses dois pontos: %f\n\n", dist_coords(ultimo_pont.coordenada.x, ultimo_pont.coordenada.y, ponto_mais_proximo.coordenada.x, ponto_mais_proximo.coordenada.y));
              break;
           /**** Fim da implementaÃ§Ã£o das opÃ§Ãµes 3 a 7  ****/
           case 9: 
              pthread_mutex_lock(&mutex);
              thread_status = 0;
              pthread_cond_broadcast(&cond); // Sinalizar todas as threads
              pthread_mutex_unlock(&mutex);
              break;     
           default:
              printf("Opcao inválida\n");
        }
    }

    // Espera as threads finaizarem
    pthread_join(thread_gerar, NULL);
    pthread_join(thread_ler, NULL);

    return 0;
}
