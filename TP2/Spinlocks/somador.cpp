#include <iostream>
#include <math.h>
#include <thread>
#include <time.h>

#include "../FuncSup/suporte.cpp"

using namespace std;

//Compilador:
    //g++ somador.cpp -o run -pthread -std=c++11

//-----------------------------------------------------------------------------------------------------

//Variável Global
int8_t somaTotal = 0;

//-----------------------------------------------------------------------------------------------------

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;

void acquire (std::atomic_flag *lock_stream){
    while(lock_stream -> test_and_set());
}

void release (std::atomic_flag * lock_stream){
    lock_stream -> clear();
}

//-----------------------------------------------------------------------------------------------------

void somaVetor (int8_t *vetor, int inicio, int fim) {

    acquire(&lock_stream);

    for (int i = inicio; i < fim; i++) {
        somaTotal += vetor[i];
    }

    release(&lock_stream);

}

//-----------------------------------------------------------------------------------------------------

int main () {

    FILE *rspinlock = fopen("r_spinlock.csv", "w");
    fprintf(rspinlock,"N, K, Somatório, Tempo médio\n");

    //const int n = 10000000;
    //const int n = 100000000;
    const int n = 1000000000;

    cout << "N = 10^" << log10(n) << endl;

    //Definir valores do vetor
    int8_t *vetor;
    vetor = (int8_t *) malloc(n * sizeof(int8_t));

    for (int v = 0; v < n; v++) {
        
        //Gera um número aleatório entre [ -100,100 ]
        vetor[v] = ran200() - 100;

    }

//-----------------------------------------------------------------------------------------------------

    //Define número de threads a serem usadas
    for (int j = 0; j < 9; j++) {

        int k = pow(2, j);

        int tamanho = ceil(n/double(k));
        std::thread threads[k];

        
        for (int m = 0; m < 10; m++) {
            int tempo_medio = 0;
            for (int t = 0; t < k; t++) {
                threads[t] = std::thread(somaVetor, vetor, (t*tamanho), ((t+1)*tamanho));
            }
            
            int tempo_inicial = clock();
            
            for (int t = 0; t < k; t++) {
                threads[t].join();
            }

            int tempo_final = clock();
            tempo_medio += tempo_final - tempo_inicial;

            //Envia os dados para um arquivo csv, para facilitar o estudo de caso 
            fprintf(rspinlock,"%d, %d, %d, %lf\n", n, k, somaTotal, double(tempo_medio)/CLOCKS_PER_SEC);

            cout << "Em K = " << k << " foi encontrado um somatório final de " << int(somaTotal) << ", executado em " << double(tempo_medio)/CLOCKS_PER_SEC << " segundos." << endl;
            somaTotal = 0;

        }
        
        cout << "-------------------------------------------" << endl;
    }

    free(vetor);
    fclose(rspinlock);
    return 0;
}