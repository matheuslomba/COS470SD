#include <iostream>
#include <unistd.h>
#include <csignal>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "../../FuncSup/suporte.cpp"

using namespace std;

void error (const char *msg) {
    perror(msg);
    exit(1);
}

//-----------------------------------------------------------------------------------------------------

/*bool primo(int num) {

    if (num <= 1) {
        return false;
    } else if (num == 2) {
        return true;
    } else {
        for (int i = 2; i < num; i++) {
            if (num%i == 0) {
                return false;
            }
        }
        return true;
    }
}*/

//-----------------------------------------------------------------------------------------------------

int main (int argc, char *argv[]) { 
    
    //Verifica se o programa recebeu todos os argumentos necessários.
    if (argc < 3) {
        cerr << "Favor inserir todos os argumentos necessários. (nome do programa; nome do servidor; e porta a ser utilizada." << endl;
        exit(0);
    }

    //Criar socket
    int conexao;
    struct sockaddr_in addr_serv;
    conexao = socket(AF_INET, SOCK_STREAM, 0);
    if (conexao < 0) {
        cerr << "Erro ao criar socket";
        return -1;
    }

    //Identifica o nome do servidor que será usado
    struct hostent *servidor;
    servidor = gethostbyname(argv[1]);
    if (servidor == NULL) {
        cerr << "O servidor indicado para uso não existe. Favor inserir um servidor válido (ex: localhost)." << endl;
        exit(0);
    }

    //Realiza as configurações do servidor para poder realizar a comunicação cliente-servidor
    bzero((char *) &addr_serv, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    bcopy((char *)servidor->h_addr, (char *)&addr_serv.sin_addr.s_addr, servidor->h_length);

    //Pega o valor da porta inserido e conecta ao servidor
    int porta;
    porta = atoi(argv[2]);
    addr_serv.sin_port = htons(porta);

    //Tenta se conectar ao servidor
    if(connect(conexao, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0) {
        cerr << "Não foi possível conectar ao servidor " << servidor << endl;
    }

//-----------------------------------------------------------------------------------------------------

    //apenas para melhorar a visualização das informações printadas no terminal
    cout << "-----------------------------------" << endl; 

    //Recebe o número enviado pelo programa produtor e verifica se o número é primo.
    int num;
    char buffer[32] = {0};
    const char * msg;

    while (true) {

        read(conexao, buffer, 32);

        num = atoi(buffer);

        if (num == 0) {
            cout << "Produtor enviou valor zero. Encerrando programa..." << endl;
            return 0;
        }

        //Esvazia o buffer para poder receber um novo valor
        memset(buffer, 0, sizeof(buffer));

        if(e_primo(num)) {
            
            //Se o número for primo, retorna valor 1, que será atribuído à variável isprimo no programa produtor, imprimindo no terminal que o número é primo.
            msg = (to_string(1)).c_str();
            send(conexao, msg, strlen(msg), 0);
        
        } else {
            
            //Se o número for primo, retorna valor 0, que será atribuído à variável isprimo no programa produtor, imprimindo no terminal que o número não é primo.
            msg = (to_string(0)).c_str();
            send(conexao, msg, strlen(msg), 0);

        }

        cout << "Número " << num << " recebido.\nCalculando se é primo... " << endl;
        cout << "-----------------------------------" << endl; 

    }

}