#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LEN 100

int main() {
    while (1) {
        char command[MAX_LEN];
        printf("$ ");
        fgets(command, MAX_LEN, stdin);
        command[strlen(command) - 1] = '\0';
        system(command);
    }
    return 0;
}