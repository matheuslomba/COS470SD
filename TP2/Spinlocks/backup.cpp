#include <iostream>
#include <math.h>
#include <thread>
#include <vector>

#include "../FuncSup/suporte.cpp"

using namespace std;

//Compilador:
    //g++ somador.cpp -o run -pthread -std=c++11

//-----------------------------------------------------------------------------------------------------

//Variáveis Globais
vector<char> vetor;

//-----------------------------------------------------------------------------------------------------

void somaVetor (int &soma, int inicio, int fim) {

    soma = 0;

    for (int i = inicio; i < fim; i++) {

        int num = int(vetor[i]);
        soma = soma + num;

    }

}

//-----------------------------------------------------------------------------------------------------

int main () {

    //Quantidade N -> tamanho do array
    for (int i = 0; i < 3; i++) {

        int n = i;
        //int n = 10000000 * (pow(10, i));
        cout << "N = " << n << endl;

        //Definir valores do vetor
        cout << "Vetor: " << endl;
        for (int v = 0; v <= n; v++) {
            
            //Gera um número aleatório entre [-100,100] e o transforma em char para ocupar apenas 1 byte
            int num = ran() - 100;
            vetor.push_back(char(num));

            //O -'0' é devido à tabela ASCII, para nos permitir ver quais são os números mesmo em formato char
            cout << vetor[v] - '0' << "/";
        }
        cout << endl;


        //Quantidade K -> número de threads
        for (int j = 0; j < 9; j++) {

            int k = pow(2, j);
            cout << "K = " << k << endl;

            std::vector<std::thread> threads;
            std::vector<int> somas_parciais(k);
            int tamanho = n/k;

            for (int t = 0; t < k; t++) {
                threads.push_back(std::thread(somaVetor, std::ref(somas_parciais[t]), t * tamanho, (t + 1) * tamanho));
            }

            for (std::thread &th : threads) {
                if (th.joinable()) {
                    th.join();
                }
            }

            int total = std::accumulate(somas_parciais.begin(), somas_parciais.end(), int(0));
            for(int a=0; a<somas_parciais.size(); a++){
                std::cout << somas_parciais[a] << ' ';}
            cout << "total = " << total << endl;

        }

    }

    return 0;
}

/*
void somaVetor (int &soma, vector<char> &vetor, int inicio, int fim) {

    soma = 0;

    for (int i = inicio; i < fim; i++) {

        int num = int(vetor[i]);
        soma = soma + num;

    }

}

//-----------------------------------------------------------------------------------------------------

int main () {

    //Quantidade N -> tamanho do array
    for (int i = 0; i < 3; i++) {

        int n = i;
        //int n = 10000000 * (pow(10, i));
        cout << "N = " << n << endl;

        //Definir valores do vetor
        vector<char> vetor;
        cout << "Vetor: " << endl;
        for (int v = 0; v <= n; v++) {
            
            //Gera um número aleatório entre [-100,100] e o transforma em char para ocupar apenas 1 byte
            int num = ran() - 100;
            vetor.push_back(char(num));

            //O -'0' é devido à tabela ASCII, para nos permitir ver quais são os números mesmo em formato char
            cout << vetor[v] - '0' << "/";
        }
        cout << endl;


        //Quantidade K -> número de threads
        for (int j = 0; j < 9; j++) {

            int k = pow(2, j);
            cout << "K = " << k << endl;

            std::vector<std::thread> threads;
            std::vector<int> somas_parciais(k);
            int tamanho = n/k;

            for (int t = 0; t < k; t++) {
                threads.push_back(std::thread(somaVetor, std::ref(somas_parciais[t]), vetor, t * tamanho, (t + 1) * tamanho));
            }

            for (std::thread &th : threads) {
                if (th.joinable()) {
                    th.join();
                }
            }

            int total = std::accumulate(somas_parciais.begin(), somas_parciais.end(), int(0));
            for(int a=0; a<somas_parciais.size(); a++){
                std::cout << somas_parciais[a] << ' ';}
            cout << "total = " << total << endl;

        }

    }

    return 0;
}*/