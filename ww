#include "includes/shell.h"


int ft_malloc(char *s1)
{
	int i;
	int j;

	j = 1;
	i = 0;
	while (s1[i] != '\0')
	{
		if ((s1[i] == '|') || (s1[i] == '>') || (s1[i] == '<'))
		{
			i++;
			j++;
			if (check_vide(s1, i) == 1)
				j++;
		}
		i++;
	}
	return (j);
}

int main(int ac, char **av)
{
	int i = 0;
	ft_malloc(av[i]);
}