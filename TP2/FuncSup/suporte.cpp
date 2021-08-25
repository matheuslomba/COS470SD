#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <random>

using namespace std;

// Gera um número aleatório delta pedido no trabalho
int8_t ran200(){

    //Faz o número gerado ser diferente a cada vez que o programa roda    
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist200(1,200);
    
    //Gera um número aleatório
    return dist200(rng);

    //Peguei esse método do link a seguir:
        //https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c

   
}

int ran107(){
    //Faz o número gerado ser diferente a cada vez que o programa roda    
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist107(1,10000000);
    
    //Gera um número aleatório
    return dist107(rng);

    //Peguei esse método do link a seguir:
        //https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
 
}    

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