#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVERADDR "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(0);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVERADDR, &server_address.sin_addr) <= 0) {
        perror("Invalid address");
        exit(0);
    }
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(0);
    }
    char *msg = "Hello from client";
    send(sock, msg, strlen(msg), 0);
    printf("Message sent\n");
    bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
    buffer[bytes_received] = '\0';
    printf("Message from server: %s\n", buffer);

    // Close the socket
    close(sock);

    return 0;
}
