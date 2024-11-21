#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct frame {
    char ack;
    int data;
} Frm[10];

int n, r;

void sender();
void recvack();
void resend_sr();

int main() {
    printf("\n--- Selective Repeat ARQ ---\n");
    sender();
    recvack();
    resend_sr();
    printf("\nAll frames sent successfully using Selective Repeat ARQ.\n");
    return 0;
}

void sender() {
    printf("\nEnter the number of frames to be sent: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("\nEnter data for frame [%d]: ", i);
        scanf("%d", &Frm[i].data);
        Frm[i].ack = 'y';
    }
}

void recvack() {
    r = rand() % n + 1;
    Frm[r].ack = 'n';
    printf("\nThe frame number %d was not received.\n", r);
}

void resend_sr() {
    printf("\nResending frame %d...\n", r);
    sleep(2);
    Frm[r].ack = 'y';
    printf("The received frame is %d.\n", Frm[r].data);
}
