#include "../includes/shell.h"


typedef struct Node {
    char *data;
    struct Node *next;
} Node;

int tokencolector(char **tokens)
{
    Node *head = NULL;
    Node *tail = NULL;
	int	i;
	i = 1;


    while (tokens[i]) 
	{
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->data = tokens[i];
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
		i++;
    }

    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    return 0;
}

int main(int ac, char **av)
{
	tokencolector(av);
}