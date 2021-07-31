#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <random>

using namespace std;

// Verifica se um número é primo, recebe o número lido pelo consumidor
bool e_primo(int x){
    int count = 0;
    int i;
    for (i = 2; i <= x; i++){
        if (x%i==0){
            count++;
        }
    }
    if(count==1){
        return true;
    }
    else{
        return false;
    }
    return 0;
}

// Gera um número aleatório delta pedido no trabalho
int ran(){
   
    /*srand(time(NULL));
    int r = rand() % 100;
    return r;*/

    //Faz o número gerado ser diferente a cada vez que o programa roda    
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1000(1,1000);
    
    //Gera um número aleatório
    return dist1000(rng);

    //Peguei esse método do link a seguir:
        //https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
    //Tinha utilizado antes o método rand() %1000, mas sempre gerava os mesmos 5 valores independentemente de quantas vezes eu rodasse a aplicação, então procurei uma forma de resolver esse problema.

   
}  

// Printa o número que o produtor gerou, recebe o número gerado e printa
void cria_num(int i){

    printf("Produtor gerou o número %d\n", i);
    
}