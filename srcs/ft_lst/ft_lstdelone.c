/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:00:19 by samajat           #+#    #+#             */
/*   Updated: 2022/05/24 19:47:33 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone(t_list **lst, int free_content)
{
	if (!lst || !(*lst)->content)
		return ;
	if (free_content)
		free((*lst)->content);
	(*lst)->content = NULL;
	free (*lst);
	lst = NULL;
}

// void	ft_tokendelone(t_token **token, int  free_content)
// {
// 	if (!token || !(*token)->sep)
// 		return ;
//     // printf ("about to free %s\n", (*token)->content);
//     if (free_content)
//         free((*token)->content);
//     (*token)->content = NULL;
// 	free (*token);
// 	token = NULL;
// }
