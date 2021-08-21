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
int8_t ran(){
   
    /*srand(time(NULL));
    int r = rand() % 100;
    return r;*/

    //Faz o número gerado ser diferente a cada vez que o programa roda    
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist200(1,200);
    
    //Gera um número aleatório
    return dist200(rng);

    //Peguei esse método do link a seguir:
        //https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
    //Tinha utilizado antes o método rand() %200, mas sempre gerava os mesmos valores independentemente de quantas vezes eu rodasse a aplicação, então procurei uma forma de resolver esse problema.

   
}  