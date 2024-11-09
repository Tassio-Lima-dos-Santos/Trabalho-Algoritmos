/* Para executar em terminal, digitar gcc trabalho_cac3202_20242.c -o trabalho_cac3202_20242 -pthread */


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


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



//**** 	 ****/


/*int main() {
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
        printf("6. Imprimir o a distÃ¢ncia entre o Ãºltimo ponto ponto visitado e o ponto mais prÃ³ximo das coordenadas (0, 0)\n");
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
              break;*/
           /**** Implementar as opÃ§Ãµes 3 a 7 aqui ****/   

           /**** Fim da implementaÃ§Ã£o das opÃ§Ãµes 3 a 7  ****/
           /*case 9: 
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
}*/
