/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_smasher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:07:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/01 15:04:54 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//manipulate counting word to count "" or '' as one word
static int	*word_data(char const *s, char c, int i);
static int	*word_data_helper(char const *s, int *arr, char c, int j);
static char	**nuller(char **arr);
static int	splitter_core(int *all_data, char **arr, int i, const char *s);

t_pipes	*ft_cmd_split(char *raw_cmd, int c)
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
	all_data = word_data(raw_cmd, c, i);
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
static int	*word_data(char const *s, char c, int i)
{
	int	word_counter;
	int	*arr;
	int	j;

	j = 1;
	word_counter = 0;
	if (s[i] != c)
		word_counter++;
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1]))
			word_counter++;
		i++;
	}
	arr = ft_calloc(sizeof(int *), (word_counter + 2) + 1);
	if (!arr)
		return (NULL);
	//assinging first item as number of words
	arr[0] = word_counter;
	//check if first char is a valid word or delimimeter (special case)
	if (s[0] != c)
	{	
		//if it's first char then the location of first word is 0
		arr[j] = 0;
		j++;
	}
	return (word_data_helper(s, arr, c, j));
}


//norminette function
//continue the word data workout
static int	*word_data_helper(const char *s, int *arr, char c, int j)
{
	int	i;

	i = 0;
	//looping over the string to extract the needed data
	while (s[i])
	{
		//if current char = delimeter, 
		//and next char is not delimeter
		//and there is a next char, not null I mean
		if ((s[i] == c && (s[i + 1] != c) && s[i + 1]))
		{
			//then fill the word data
			//this is a valid word, 
			//arr[j], which we assigned j in last function to 0 or 1 according
			//to the occurance of first word
			arr[j] = i + 1;
			//i + 1 because teh first item in the array is the number of words, 
			//I didn't know how to work with linked lists back then
			j++;
			//incremented j to fill the next item in arr[];
		}
		//if current char is not delimeter, but
		//next char is delimeter
		//or next char is the end of str (null)
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
		{
			//then fill the word data with where the word ends
			arr[j] = i + 1;
//i + 1 because teh first item in the array is the number of words, 
			//I didn't know how to work with linked lists back then
			j++;
			//incremented j to fill the next item in arr[];
		}
		//let's check the next char if there is one
		i++;
	}
	//return the lovely word data, that has all reciepies for success
	return (arr);
}

static char	**nuller(char **arr)
{
	arr = ft_calloc(sizeof(char *), 1);
	if (!arr)
		return (NULL);
	arr[0] = NULL;
	return (arr);
}