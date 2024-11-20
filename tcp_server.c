#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;  
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    char *msg = "Hello from server";
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(0);
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(0);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(0);
    }
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(0);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(0);
    }
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Message from client: %s\n", buffer);
    send(new_socket, msg, strlen(msg), 0);
    printf("Message sent\n");
    close(new_socket);
    close(server_fd);

    return 0;
}
