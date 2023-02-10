#include "server.h"

int main(int argc, char const* argv[]) {
    int client;
    int server;

    struct sockaddr_in server_address;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        std::cerr 
            << ERROR_S 
            << "Sockets cannot be generated. Error code - " 
            << client 
            << "\n";
        
            return -1;
    } 
    std::cout 
            << "SERVER: "
            << "Socket for server was successfully created\n";

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr =  htons(INADDR_ANY);

    int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_address), 
            sizeof(server_address));

    if (ret < 0) {
        std::cerr 
            << ERROR_S 
            << "binding connection. Socket has alredy been establishing. Error code - "
            << ret
            << std::endl;

            return -2;
    }

    socklen_t size_address = sizeof(server_address);
    std::cout 
            << "SERVER: "
            << "Listening client...\n";
    listen(client, 1);

    server = accept(client, 
            reinterpret_cast<struct sockaddr*>(&server_address), 
            &size_address);
    if (server < 0) {
        std::cerr
            << ERROR_S
            << "Can't accepting client. Error code - "
            << server
            << std::endl;

    }
    char buffer[BUFFER_SIZE];
    bool ifExit = false;
    while (server > 0) {
        strcpy(buffer, "=> Server connected!\n");
        send(server, buffer, BUFFER_SIZE, 0);
        std::cout 
            << "=> Connected to the client #1" 
            << std::endl
            << "Enter"
            << EXIT_SYMBOL
            << "to end the connection\n\n";

        std::cout 
            << "Client: ";
        recv(server, buffer, BUFFER_SIZE, 0);
        std::cout 
            << buffer 
            << std::endl;
        
        ifExit = is_client_connection_close(buffer);
            
        while (!ifExit) {
            std::cout 
                << "Server: ";
            std::cin.getline(buffer, BUFFER_SIZE);
            send(server, buffer, BUFFER_SIZE, 0);
            if (is_client_connection_close(buffer))
                break;
            
            std::cout
                << "Client: ";
            recv(server, buffer, BUFFER_SIZE, 0);
            std::cout
                << buffer
                << std::endl;
            if (is_client_connection_close(buffer))
                break;
        }
        ifExit = false;
        break;
    }
    std::cout 
        << "\n Have a nice day!"
        << std::endl;
    ifExit = false;
    close(server);
    close(client);
    return 0;
}

bool is_client_connection_close(const char* msg) {
    for (int i = 0; i < strlen(msg); ++i) {
        if (msg[i] == EXIT_SYMBOL) {
            return true;
        }
    }
    return false;
}