/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _char2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:25:21 by eelmoham          #+#    #+#             */
/*   Updated: 2022/05/12 11:32:59 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  cpy_var(char *str, char *var, char c)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i] && str[i] != c && ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
	{
		var[j] = str[i];
		i++;
		j++;
	}
	var[j] = '\0';
	return (i);
}

char	*ft_one_char_str(char c)
{
	char	*output;

	output = (char *) malloc(2 * sizeof(char));
	if (!output)
		return (NULL);
	output[0] = c;
	output[1] = 0;
	return (output);
}

char	*ft_charjoin(char *s1, char c)
{
	unsigned int	i;
	char			*output;

	if (!s1)
		return (ft_one_char_str(c));
	i = 0;
	output = (char *) malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!output)
		return (NULL);
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	output[i++] = c;
	output[i] = '\0';
	free(s1);
	s1 = NULL;
	return (output);
}

int sh_expand(char *str, char c)
{
	int i;
	int is;
	
	is = -1;
	i = 0;
	while(str[i])
	{
		if (str[i] == c)
		{
			if (is == -1)
				is = 0;
			else if (is == 0)
				is = 1;
			else if (is == 1)
				is = 0;
		}
		i++;
	}
	return (is);
}
char *get_var(t_data *dt, char *st)
{
    t_env *e;

    e = dt->enver;
    while (e)
    {
        if(!ft_strcmp(e->variable, st))
            return (e->value);
        e = e->next;
    }
    return ("");
}