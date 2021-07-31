#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../../FuncSup/suporte.cpp"

using namespace std;

void error (const char *msg) {
    perror(msg);
    exit(1);
}

//-----------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {

    //Verifica quantidade de argumentos inseridos ao iniciar o programa
    if (argc < 2) {
        cerr << "Nenhuma porta foi indicada." << endl;
        exit(1);
    }

    //Criar socket
    int conexao, porta;
    struct sockaddr_in addr_serv;
    int t_serv = sizeof(addr_serv);

    conexao = socket(AF_INET, SOCK_STREAM, 0);
    if (conexao < 0) {
        cerr << "Erro ao criar socket.";
        return -1;
    }

    //Limpa o buffer (pois pode conter dados indesejados) para usar a seguir
    bzero((char *) &addr_serv, t_serv);

    //O valor da porta que será utilizada é o segundo argumento inserido ao rodar a aplicação.
    porta = atoi(argv[1]);

    //Conectar socket ao IP/porta
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = INADDR_ANY;
    addr_serv.sin_port = htons(porta);

    if (bind(conexao, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0) {
        cerr << "Não foi possível conectar ao IP/porta inseridos.";
        return -2; 
    }

    //Server em espera pelo cliente. Máximo de 5 conexões.
    if (listen(conexao, 5) < 0) {
        cerr << "Não foi possível conectar ao cliente.";
        return -3;
    }

    //Server aceita conexão com cliente
    int novaconexao;
    struct sockaddr_in addr_cliente;
    socklen_t t_cliente = sizeof(addr_cliente);

    novaconexao = accept(conexao, (struct sockaddr *) &addr_cliente, &t_cliente);
    if (novaconexao < 0) {
        cerr << "Ocorreu algum erro ao tentar se conectar com o cliente.";
        return -4;
    }

    //Informa que a conexão foi realizada com sucesso
    printf("Conexão realizada com sucesso em IP:%s e Porta:%d\n", inet_ntoa(addr_cliente.sin_addr), ntohs(addr_cliente.sin_port));

//-----------------------------------------------------------------------------------------------------
    
    //apenas para melhorar a visualização das informações printadas no terminal
    cout << "-----------------------------------" << endl; 

    //Gera número aleatório, envia para consumidor e recebe resposta se é primo ou não. Roda 5 vezes para 5 números diferentes
    int num, isprimo;
    char buffer [32];

    for (int i = 0; i < 5; i++) {

        //gera número aleatório
        num = ran();
           
        //Transforma o int num em string para poder enviá-lo pelo socket
        const char * msg = (to_string(num)).c_str();

        //Envia número pro cliente
        send(novaconexao, msg, strlen(msg), 0);
        cout << "Número " << num << " enviado para o consumidor." << endl;

        //Recebe a resposta do consumidor
        read(novaconexao, buffer, 32);
        int isprimo = atoi(buffer);

        if (isprimo == 1) {
            cout << "Número " << num << " é primo!" << endl;
            cout << "-----------------------------------" << endl; 
        } else {
            cout << "Número " << num << " não é primo!" << endl;
            cout << "-----------------------------------" << endl; 
        }

        num = 0;
    }

    cout << "O programa está sendo encerrado. Enviando valor zero para o consumidor..." << endl;
    send(novaconexao, "0", strlen("0"), 0);

    return 0;
}