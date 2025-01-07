#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    ord.order_type = 1;  // Order type

    for (int i = 1; i <= 5; i++) {
        sprintf(ord.order_details, "Order #%d: Item%d", i, i);
        msgsnd(msgid, &ord, sizeof(ord), 0);
        printf("Order Sent: %s\n", ord.order_details);
        sleep(1);
    }

    return 0;
}
