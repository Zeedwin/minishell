#include "../includes/shell.h"



/*t_token *tokencolector(char **tokens)
{
    t_token *head = NULL;
	t_token *tail = NULL;
    t_token *tok = NULL;
    t_token *new_node = (t_token *)malloc(sizeof(t_token));
	t_token *curr = new_node;
	int	i; 
	int j;
	i = 0;


    while (tokens[i]) 
	{

        new_node->data = tokens[i];
        new_node->next = NULL;
		//tokenrecon(ew_node);

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        while (new_node->next != NULL) 
	    {
			j = 0;
	    	if (new_node->data[j] == '|')
	    	{
	    		new_node->type = TOKEN_PIPE;
	    	}
	    	else if (new_node->data[j] == '>' || new_node->data[j] == '<')
	    	{
	    		new_node->type = TOKEN_REDIR;
	    	}
	    	else 
	    	{
	    		new_node->type = TOKEN_WORD;
	    	}
	    	printf("arg: %s type: %d\n", new_node->data, new_node->type);
            new_node = new_node->next;
            j++;
        }
		i++;
        tok = new_node;
    }
    return (curr);
}

*/