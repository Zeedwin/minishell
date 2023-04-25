#include "../includes/shell.h"

/*char	*ft_realloc(char *map, int i)
{
	char	*map_tp;
	int		x;

	x = 0;
	map_tp = malloc(i * sizeof(char *));
	while (map[x])
	{
		map_tp[x] = map[x];
		x++;
	}
	free(map);
	map_tp[x] = '\0';
	return (map_tp);
}*/

char *appl_chang(char *so, char *sc, int k, int o)
{
	int i;
	int j;
	char *sf;

	i = 0;
	j = 0;
	sf = malloc(sizeof(char) * (ft_strlen(so) + ft_strlen(sc) - (o - k) + 1));
	while (i < k)
	{
		sf[i] = so[i];
		i++;
	}
	if (sc != NULL)
	{
		//sf[i] = '"';
		//i++;
		while (sc[j] != '\0')
		{
			sf[i] = sc[j];
			i++;
			j++;
		}
		//sf[i] = '"';
		//i++;
		while (so[o] != '\0')
		{
			sf[i] = so[o];
			o++;
			i++;
		}
		sf[i] = '\0';
		return (sf);
	}
	else
	{
		while (so[i] != '$')
		{
			sf[i] = so[i];
			i++;
		}
		while (so[o] != '\0')
		{
			sf[i] = so[o];
			o++;
			i++;
		}
		sf[i] = '\0';
		return (sf);
	}
}

char *change_value(char *s, char **envp)
{
	int i;
	int j;
	int o;
	char *s2;

	o = ft_strlen(s);
	i = 0;
	s2 = NULL;
	while(envp[i])
	{
		j = 0;
		if (ft_strncmp(envp[i], s, ft_strlen(s)) == 0)
		{
			s2 = malloc(sizeof(char) * (ft_strlen(envp[i]) - ft_strlen(s) + 1));
			while (envp[i][o] != '\0')
			{
				s2[j] = envp[i][o];
				j++;
				o++;
			}
			s2[j] = '\0';
		}
		i++;
	}
	return (s2);
}

char *replace_dol(char *s, char **envp)
{
	int i;
	int j;
	int o;
	char *sf;
	char *s1;

	i = 0;
	j = 0;
	o = 0;
	while(s[i] != '$' && s[i] != '\0')
	{
		i++;
	}
	sf = malloc(sizeof(char) * (i + 1));
	i = 0;
	while(s[i] != '$' && s[i] != '\0')
	{
		sf[j] = s[i];
		i++;
		j++;
	}
	sf[j] = '\0';
	i++;
	s1 = malloc(sizeof(char) * (ft_strlen(s) - i + 2));
	while (s[i] != '\0')
	{
		s1[o] = s[i];
		o++;
		i++;
	}
	s1[o] = '\0';
	s1 = change_value(s1, envp);
	i = 0;
	if (s1 != NULL)
	{
		sf = ft_realloc(sf, (ft_strlen(s1) + j + 1));
		while(s1[i] != '\0')
		{
			sf[j] = s1[i];
			i++;
			j++;
		}
		sf[j] = '\0';
	}
	return (sf);
}

char *dollars_ch(char *s, char **envp)
{
	char *s2;
	int i;
	//int l;
	int j;
	int o;
	int k;

	j = 0;
	i = 0;
	k = 0;
	//l = ft_strlen(s);
	while(i <= ft_strlen(s) && s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				i++;
			i++;
		}
		if (s[i] == '$')
		{
			o = 0;
			while(s[i] != ' ' && i > 0 && s[i] != '"')
				i--;
			k = i;
			i++;
			j = i;
			while(s[i] != ' ' && s[i] != '\0' && s[i] != '"')
				i++;
			s2 = malloc(sizeof(char) * (i - j + 2));
			while (j < i)
			{
				s2[o] = s[j];
				o++;
				j++;
			}
			s2[o] = '=';
			o++;
			s2[o] = '\0';
 			s2 = replace_dol(s2, envp);
			s = appl_chang(s, s2, k + 1, i);
		}
		i++;
	}
	return (s);
}

char *replace_dol_(char *s, int i)
{
	char *sf;
	char *res;
	int j;
	int o;
	int k;

	j = 0;
	k = 0;
	o = 0;
	res = ft_itoa(i);
	sf = malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[j] != '\0')
	{
		if (s[j] == '$' && s[j + 1] == '?')
		{
			sf = realloc(sf, ft_strlen(s) + ft_strlen(res));
			while (res[k] != '\0')
			{
				sf[o] = res[k];
				o++;
				k++;
			}
			j += 2;
		}
		else
		{
			sf[o] = s[j];
			j++;
			o++;
		}
	}
	sf[o] = '\0';
	return (sf);
}

char ***del_brak(char ***s)
{
	int i;
	int j;
	int k;

	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		while (s[i][j] != NULL)
		{
			if (s[i][j][0] == '"' || s[i][j][0] == '\'')
			{
				k = 1;
				s[i][j] = ft_realloc(s[i][j], ft_strlen(s[i][j]) - 2);
				while(k < ft_strlen(s[i][j]) - 1)
				{
					s[i][j][k - 1] = s[i][j][k];
					k++;
				}
				s[i][j][k - 1] = '\0';
			}
			j++;
		}
		i++;
	}
	return (s);
}


/*int main(int ac, char **av, char **envp)
{
	char *s;
	(void)ac;
	(void)av;

	s = readline(">");
	//s = replace_dol_(s, 0);
	s = dollars_ch(s, envp);
	printf("s = %s\n", s);
	return (0);
}*/