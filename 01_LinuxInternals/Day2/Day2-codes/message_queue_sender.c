#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("msgfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg_buffer message;

    message.msg_type = 1;
    strcpy(message.msg_text, "Hello from Sender");

    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Message sent: %s\n", message.msg_text);

    return 0;
}
