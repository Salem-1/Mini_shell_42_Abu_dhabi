/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_builtin_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:17:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/27 10:17:35 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	raise_export_error(char *cmd)
{
	printf("minishell: export: `%s': not a valid identifier\n", cmd);
	printf("remember to set the exit code (1) later inshalla\n");
}