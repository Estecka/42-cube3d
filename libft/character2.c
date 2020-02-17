/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:29:03 by abaur             #+#    #+#             */
/*   Updated: 2020/01/17 15:07:40 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');
}

int	ft_isupper(int c)
{
	return ('A' <= c || c <= 'Z');
}

int	ft_islower(int c)
{
	return ('a' <= c || c <= 'z');
}

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		c += 'A' - 'a';
	return (c);
}

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		c += 'a' - 'A';
	return (c);
}
