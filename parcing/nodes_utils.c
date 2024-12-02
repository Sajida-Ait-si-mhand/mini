/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:59:24 by salaoui           #+#    #+#             */
/*   Updated: 2024/11/22 15:13:33 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redi_add_back(t_redir **redirections, t_redir *new_redir)
{
	t_redir	*arrs;

	arrs = *redirections;
	if (!redirections || !new_redir)
		return ;
	if (*redirections == NULL)
	{
		*redirections = new_redir;
		return ;
	}
	while (arrs->next != NULL)
		arrs = arrs->next;
	arrs->next = new_redir;
}

t_node	*allocate_for_node(t_token *temp_tokens)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = malloc(sizeof(char *) * (cmd_count(temp_tokens) + 1));
	return (node);
}

int	cmd_count(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->data_type != PIPE)
	{
		if (tokens->data_type == OUT_REDIR || tokens->data_type == APPEND
			|| tokens->data_type == INP_REDIR || tokens->data_type == HER_DOC)
			tokens = tokens->next_token;
		else
		{
			i++;
		}
		tokens = tokens->next_token;
	}
	return (i);
}

int	count_pipe(t_token *tokens)
{
	t_token	*temp_tokens;
	int		count;

	temp_tokens = tokens;
	count = 0;
	while (temp_tokens)
	{
		if (temp_tokens->data_type == 1)
			count++;
		temp_tokens = temp_tokens->next_token;
	}
	count++;
	return (count);
}
