
#include	"../includes/shell.h"

token	*ft_lstnew(char **content)
{
	token	*lst;

	lst = malloc(sizeof(token));
	if (!lst)
		return (0);
	lst->c = content;
	lst->next = NULL;
	return (lst);
}
