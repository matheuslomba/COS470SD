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

sem_t controlSemaphore;
sem_t control_1_Semaphore;
sem_t countSemaphore;

queue<int> fila;
int ii;

void Produtor() {
    
    for(int i=0;i<1000;i++){
        //escrever numero na memoria 
        sem_wait(&countSemaphore);
        
        sem_wait(&controlSemaphore);
        int r=ran();
        fila.push(r);
        sem_post(&control_1_Semaphore);
    
        sem_post(&controlSemaphore);
    }
}

void Consumidor() {
    //ler na memoria
    
    
    while( ii<1000){
    
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
    printf("Defina o tamanho da fila: ");
    scanf("%d", &N);
    sem_init(&countSemaphore, 1, N);
    sem_init(&control_1_Semaphore, 1, 0);
    sem_init(&controlSemaphore, 1, 1);
    
    cout << N << endl;;

    int Np;
    printf("Selecione a quantidade de threads produtoras a serem gerados: ");
    scanf("%d", &Np);

    int Nc;
    printf("Selecione a quantidade de threads consumidores a serem gerados: ");
    scanf("%d", &Nc);
    
    std::thread threadsP[Np];
    std::thread threadsC[Nc];

    long tempo_medio = 0.000;
    for (int tp = 0; tp < Np; tp++) {
        threadsP[tp] = std::thread(Produtor);
    }
    for (int tc = 0; tc < Nc; tc++) {
        threadsC[tc] = std::thread(Consumidor);
    }
    
    
    
    for (int tp = 0; tp < Np; tp++) {
        threadsP[tp].join();
    }
    for (int tc = 0; tc < Nc; tc++) {
        threadsC[tc].join();
    }

    

    //Envia os dados para um arquivo csv, para facilitar o estudo de caso 
    //fprintf(rspinlock,"%d, %d, %d, %lf\n", n, k, somaTotal, double(tempo_medio)/CLOCKS_PER_SEC);

    //cout << "Em K = " << k << " foi encontrado um somatório final de " << int(somaTotal) << ", executado em " << double(tempo_medio)/CLOCKS_PER_SEC << " segundos." << endl;
    //somaTotal = 0;
    
    cout << "-------------------------------------------" << endl;
    //}

    long tempo_final = time(NULL);
    tempo_medio = difftime(tempo_final,tempo_inicial);
    cout<<"O tempo é: "<<tempo_medio;
    return 0;
}
