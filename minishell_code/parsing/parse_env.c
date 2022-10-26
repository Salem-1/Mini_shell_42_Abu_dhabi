/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:54:37 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/26 13:18:03 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*parse_env(char **envp, t_list *head)
{
	t_list		*tmp_node;
	int			i;

	i = 0;
	head = NULL;
	if (!envp)
		return (NULL);
	head = ft_lstnew((char **)ft_split(envp[i], '='));
	while (envp[i])
	{
		tmp_node = ft_lstnew((char **)ft_split(envp[i], '='));
		ft_lstadd_back(&head, tmp_node);
		i++;
	}
	return (head);
}

char	**join_env(t_list *t_env)
{
	char	**envp;
	char	*tmp_join;
	t_list	*tmp;

	tmp = t_env;
	tmp_join = NULL;
	while (tmp != NULL)
	{
		tmp_join = env_strjoin(tmp_join, tmp->key_val[0],
				ft_strlen(tmp_join) + ft_strlen(tmp->key_val[0]));
		tmp_join = env_strjoin(tmp_join, "=", ft_strlen(tmp_join) + 1);
		tmp_join = env_strjoin(tmp_join, tmp->key_val[1],
				ft_strlen(tmp_join) + ft_strlen(tmp->key_val[1]));
		tmp_join = env_strjoin(tmp_join, "\n", ft_strlen(tmp_join) + 1);
		tmp = tmp->next;
	}
	envp = ft_split(tmp_join, '\n');
	free(tmp_join);
	return (envp);
}
