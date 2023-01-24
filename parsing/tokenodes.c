#include "../includes/shell.h"



int tokencolector(char **tokens)
{
    t_token *head = NULL;
	t_token *tail = NULL;
	int	i;
	i = 0;


    while (tokens[i]) 
	{
        t_token *new_node = (t_token *)malloc(sizeof(t_token));
        new_node->data = tokens[i];
        new_node->next = NULL;
		tokenrecon(tokens[i], new_node);

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
		i++;
    }

    t_token *current = head;
    while (current != NULL) 
	{
		printf("%s\n", current->data);
        current = current->next;
    }

    return 0;
}

/*int main(int ac, char **av)
{
	tokencolector(av);
}*/