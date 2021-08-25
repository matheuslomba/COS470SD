#include <iostream>
#include <cstdlib>
#include <thread>
#include <semaphore.h>
#include <queue>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <random>

#include "aux"


using namespace std;
//Definição de semáforos 
sem_t controlSemaphore;
sem_t control_1_Semaphore;
sem_t countSemaphore;
//Definição da fila
queue<int> fila;
int ii;

//As threads vão gerar 100000 números e vão botar na fila. O wait(countSempahore) vai diminuir 1 de N. O wait(controlSemaphore) vai garantir que apenas uma thread esteja em contato com a fila. O post(control_1_Semaphore) vai garantir que a thread nenhuma thread consumidora vai tentar puxar da fila sem ter nenhum número
void Produtor() {
    
    for(int i=0;i<100000;i++){
        //escrever numero na memoria 
        sem_wait(&countSemaphore);
        
        sem_wait(&controlSemaphore);
        int r=ran();
        fila.push(r);
        sem_post(&control_1_Semaphore);
    
        sem_post(&controlSemaphore);
    }
}


//As threads vão gerar ler os números e tirá-los da fila. O post(countSempahore) vai aumentar 1 de N. O wait(controlSemaphore) vai garantir que apenas uma thread esteja em contato com a fila. O wait(control_1_Semaphore) vai garantir que a thread nenhuma thread consumidora vai tentar puxar da fila sem ter nenhum número

void Consumidor() {    
    
    while( ii<100000){
    
        sem_wait(&control_1_Semaphore);

        sem_post(&countSemaphore);
        
        sem_wait(&controlSemaphore);
        int pr=fila.front();
        fila.pop();
        cout<<"AQUI: " << ii;
        
        bool verif = e_primo(pr);
        ii++;
        if(verif==true){
            cout << "O número " << pr << " é primo!" << endl;
            sem_post(&controlSemaphore);
        }
        else{
            cout << "O número " << pr << " não é primo!" << endl;;
            sem_post(&controlSemaphore);
        }
    }
    
    exit(-1);
}


int main () {

    long tempo_inicial = time(NULL);
    int N;
    //Iniciando os semáforos
    printf("Defina o tamanho da fila: ");
    scanf("%d", &N);
    sem_init(&countSemaphore, 1, N);
    sem_init(&control_1_Semaphore, 1, 0);
    sem_init(&controlSemaphore, 1, 1);
    
    cout << N << endl;;
    //escrevendo a quantidade de threads produtoras
    int Np;
    printf("Selecione a quantidade de threads produtoras a serem gerados: ");
    scanf("%d", &Np);
    //escrevendo a quantidade de threads consumidoras
    int Nc;
    printf("Selecione a quantidade de threads consumidores a serem gerados: ");
    scanf("%d", &Nc);
    //Definindo o tamanho dessas threads
    std::thread threadsP[Np];
    std::thread threadsC[Nc];
    //Criando cada uma dessas threads
    long tempo_medio = 0.000;
    for (int tp = 0; tp < Np; tp++) {
        threadsP[tp] = std::thread(Produtor);
    }
    for (int tc = 0; tc < Nc; tc++) {
        threadsC[tc] = std::thread(Consumidor);
    }
    
    
    //Ativando cada uma dessas threads
    for (int tp = 0; tp < Np; tp++) {
        threadsP[tp].join();
    }
    for (int tc = 0; tc < Nc; tc++) {
        threadsC[tc].join();
    }
    
    cout << "-------------------------------------------" << endl;
    //}

    long tempo_final = time(NULL);
    tempo_medio = difftime(tempo_final,tempo_inicial);
    cout<<"O tempo é: "<<tempo_medio;
    return 0;
}
