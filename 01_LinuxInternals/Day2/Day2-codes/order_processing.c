#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 100

struct order {
    long order_type;
    char order_details[MAX_TEXT];
};

int main() {
    key_t key = ftok("orderfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct order ord;

    for (int i = 0; i < 5; i++) {
        msgrcv(msgid, &ord, sizeof(ord), 1, 0);
        printf("Processing Order: %s\n", ord.order_details);
    }

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
