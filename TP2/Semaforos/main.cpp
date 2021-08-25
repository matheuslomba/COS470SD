#include <iostream>
#include <cstdlib>
#include <thread>
#include <semaphore.h>
#include <queue>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/types.h>
#include <string>
#include <sys/wait.h>
#include <time.h>
#include <random>

#include "../FuncSup/suporte.cpp"

using namespace std;

//Compilador:
    //g++ somador.cpp -o run -pthread -std=c++11

//-----------------------------------------------------------------------------------------------------

//Variáveis Globais
sem_t controlSemaphore;
sem_t control_1_Semaphore;
sem_t countSemaphore;
queue <int> fila;

//-----------------------------------------------------------------------------------------------------

void Produtor(int tamanhoP) {

    for (int i = 0; i < tamanhoP; i++) {
        int r=ran107();

        //escrever numero na memoria 
        sem_wait(&countSemaphore);
        sem_wait(&controlSemaphore);

        fila.push(r);

        sem_post(&control_1_Semaphore);
        sem_post(&controlSemaphore);
    }
}

void Consumidor(int tamanhoC) {

    int ii = 0;

    for (ii = 0; ii < tamanhoC; ii++) {

        //ler na memoria
        cout << ii << endl;
        
        sem_wait(&control_1_Semaphore);
        sem_post(&countSemaphore);
        sem_wait(&controlSemaphore);
        
        int pr = fila.front();
        fila.pop();

        bool verif = e_primo(pr);

        if(verif==true){
            cout << "O número " << pr << " é primo!" << endl;
            sem_post(&controlSemaphore);
        }
        else{
            cout << "O número " << pr << " não é primo!" << endl;;
            sem_post(&controlSemaphore);
        }

    }

}

int main () {

    FILE *rsemaforo = fopen("r_semaforo.csv", "w");
    fprintf(rsemaforo,"N, Np, Nc, Tempo médio\n");

    /*int N;
    printf("Defina o tamanho da fila: ");
    scanf("%d", &N);
    sem_init(&countSemaphore, 2, N);
    sem_init(&controlSemaphore, 0, 1);

    int Np;
    printf("Selecione a quantidade de threads produtoras a serem gerados: ");
    scanf("%d", &Np);

    int Nc;
    printf("Selecione a quantidade de threads consumidores a serem gerados: ");
    scanf("%d", &Nc);*/
    
    int valN[5] = {1,2,4,16,32};
    int valNpc[9][2] = {{1,1},{1,2},{1,4},{1,8},{1,16},{2,1},{4,1},{8,1},{16,1}};

    for (int nn = 0; nn < 5; nn++) {
        
        int N = valN[nn];
        sem_init(&countSemaphore, 2, N);
        sem_init(&controlSemaphore, 0, 1);
        sem_init(&control_1_Semaphore, 1, 0);

        for (int npc = 0; npc < 9; npc++) {
            
            int Np = valNpc[npc][0];
            int Nc = valNpc[npc][1];

            cout << N << "---------------------------------------------------" << endl;
            cout << Np << "---------------------------------------------------" << endl;
            cout << Nc << "---------------------------------------------------" << endl;

            int tamanhoP = ceil(100/double(Np));
            int tamanhoC = ceil(100/double(Nc));
            std::thread threadsP[Np];
            std::thread threadsC[Nc];

            for (int m = 0; m < 10; m++) {
                int tempo_medio = 0;
                for (int tp = 0; tp < Np; tp++) {
                    threadsP[tp] = std::thread(Produtor, tamanhoP);
                }
                for (int tc = 0; tc < Nc; tc++) {
                    threadsC[tc] = std::thread(Consumidor, tamanhoC);
                }

                int tempo_inicial = clock();

                for (int tp = 0; tp < Np; tp++) {
                    threadsP[tp].join();
                }
                for (int tc = 0; tc < Nc; tc++) {
                    threadsC[tc].join();
                }

                int tempo_final = clock();
                tempo_medio += tempo_final - tempo_inicial;

                //Envia os dados para um arquivo csv, para facilitar o estudo de caso 
                fprintf(rsemaforo,"%d, %d, %d, %lf\n", N, Np, Nc, double(tempo_medio)/CLOCKS_PER_SEC);

                cout << "Em N = " << N << ", com " << Np << " threads produtor e " << Nc << " threads consumidor, o programa foi executado em " << double(tempo_medio)/CLOCKS_PER_SEC << " segundos." << endl;

                cout << "-------------------------------------------" << endl;
            }

        }

    }
    
    return 0;
}