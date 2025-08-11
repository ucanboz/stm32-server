#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define VERSION "1.0"
#define AUTHOR "ucanboz"
#define DESCRIPTION "A simple TCP server that echoes back received messages."

void print_info() {
    printf("TCP Server Version: %s\n", VERSION);
    printf("Author: %s\n", AUTHOR);
    printf("Description: %s\n", DESCRIPTION);
}


int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    print_info();
    printf("Server listening on port %d...\n", PORT);

    // Accept
    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (client_fd < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read and echo
    int valread = read(client_fd, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);
    send(client_fd, buffer, valread, 0);

    close(client_fd);
    close(server_fd);
    return 0;
}