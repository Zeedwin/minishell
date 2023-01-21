#include	"../includes/shell.h"

int	export(char **envp)
{
	char **miniexp;
	int i;

	i = 1;
	while (envp[i] != NULL)
	{
		ft_strcpy(miniexp[i], envp[i]);
		printf("%s\n", miniexp[i]);
		i++;
	}
	return(1);
}

int main(int ac, char	**av, char **envp)
{
	export(envp);
}