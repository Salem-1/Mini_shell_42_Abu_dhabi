/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_smasher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:07:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/01 18:13:54 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//manipulate counting word to count "" or '' as one word
static int	*word_data(char const *s, int i);
static int	*word_data_helper(char const *s, int *arr, int j);
static char	**nuller(char **arr);
static int	splitter_core(int *all_data, char **arr, int i, const char *s);
int			is_delimi(char s, char quote);
char		quote_update(char s, char quote, int flag);

char	**ft_cmd_split(char *raw_cmd)
{
	//the output char **
	char	**arr;
	int		*all_data;
	int		i;
	int		j;

	arr = NULL;
	//checking that the input is not null
	if (!*raw_cmd)
		return (nuller(arr));
	i = 0;
	//all = [n_words, firstword[0], first_word[len(word)] ...]
	all_data = word_data(raw_cmd, i);
	if (!all_data)
		return (NULL);
	//mallocing the char ** with places of char * according to the number of words
	arr = (char **)ft_calloc(sizeof(char *), (all_data[i] + 1));
	if (!arr)
	{
		free(all_data);
		return (NULL);
	}
	i++;
	//i = 1;
	j = splitter_core(all_data, arr, i, raw_cmd);
	//no need for all data now let's free it
	free(all_data);
	//nulling last item in the arr char *
	arr[j] = NULL;
	return (arr);
}


static int	splitter_core(int *all_data, char **arr, int i, const char *s)
{
	int	j;

	j = 0;
	while (j < all_data[0])
	{
		//fill each char * with the word data start and end using ft_substr
		arr[j] = ft_substr(s, all_data[i], (all_data[i + 1] - all_data[i]));
		//loop to the next char * in the char **arr
		j++;
		//jump 2 steps to get the data of the next word
		i += 2;
	}
	//returning the j to use it to null the char **arr
	return (j);
}

//get int * data =[
				//n_words, 
				// location first char in first word, 
				// location of last char in first word,
				// ....
				//]
static int	*word_data(char const *s, int i)
{
	int				word_counter;
	int				*arr;
	int				j;
	char			quote;
	static int		flag = 0;

	quote = '\0';
	j = 1;
	word_counter = 0;
	i = 0;
	quote = quote_update(s[i], quote, flag);
	if (is_delimi(s[i], quote))
		word_counter++;
	while (s[i])
	{
		quote = quote_update(s[i], quote, flag);
		if (quote == '\0')
			flag = 0;
		if (is_delimi(s[i], quote) && !is_delimi(s[i + 1], quote) && s[i + 1])
			word_counter++;
		i++;
	}
	arr = ft_calloc(sizeof(int *), (word_counter + 2) + 1);
	if (!arr)
		return (NULL);
	arr[0] = word_counter;
	quote = quote_update(s[i], quote, flag);
	if (quote == '\0')
		flag = 0;
	if (!is_delimi(s[i + 1], quote))
	{	
		arr[j] = 0;
		j++;
	}
	return (word_data_helper(s, arr, j));
}

//continue the word data workout
static int	*word_data_helper(const char *s, int *arr, int char_index)
{
	int				i;
	char			quote;
	static int		flag = 0;

	quote = '\0';
	i = 0;
	while (s[i])
	{
		quote = quote_update(s[i], quote, flag);
		if (quote == '\0')
			flag = 0;
		if ((is_delimi(s[i], quote)
				&& !is_delimi(s[i + 1], quote) && s[i + 1]))
		{
			if (quote != '\0')
				flag++;
			arr[char_index] = i + 1;
			char_index++;
		}
		if (!(is_delimi(s[i], quote)
				&& (is_delimi(s[i + 1], quote) || !s[i + 1])))
		{
			if (quote != '\0')
				flag++;
			arr[char_index] = i + 1;
			char_index++;
		}
		i++;
	}
	return (arr);
}

char	quote_update(char s, char quote, int flag)
{
	if (flag == 2)
		return ('\0');
	if (s == '\'' && quote != '"')
		quote = '\'';
	else if (s == '\"' && quote != '\'')
		quote = '"';
	return (quote);
}
int	is_delimi(char s, char quote)
{
	if (quote == '\0')
	{
		if (s == ' ')
			return (1);
	}
	else if (s == quote)
		return (1);
	else
		return (0);
	return (0);
}

static char	**nuller(char **arr)
{
	arr = ft_calloc(sizeof(char *), 1);
	if (!arr)
		return (NULL);
	arr[0] = NULL;
	return (arr);
}