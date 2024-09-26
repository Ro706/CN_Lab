#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUCKET_SIZE 10
#define PACKET_RATE 4

int bucket = 0;
void addTokens(int tokens) {
    bucket += tokens;
    if (bucket > BUCKET_SIZE) {
        bucket = BUCKET_SIZE;
    }
}

void processPacket(int packet_size) {
    if (packet_size <= bucket) {
        bucket -= packet_size;
        printf("Processed packet of size %d. Tokens left: %d\n", packet_size, bucket);
    } else {
        printf("Not enough tokens to process packet of size %d. Tokens left: %d\n", packet_size, bucket);
    }
}

int main() {
    int incomingPackets[] = {2, 3, 5, 7, 1, 4};
    int n = sizeof(incomingPackets) / sizeof(incomingPackets[0]);
    for (int i = 0; i < n; i++) {
        printf("\nTime %d seconds:\n", i + 1);
        addTokens(PACKET_RATE);
        printf("Added %d tokens. Bucket now contains %d tokens.\n", PACKET_RATE, bucket);
        processPacket(incomingPackets[i]);
        sleep(1);
    }
    return 0;
}
