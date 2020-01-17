/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:52:49 by abaur             #+#    #+#             */
/*   Updated: 2019/11/07 15:28:48 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z'));
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	ft_isascii(int c)
{
	return (0x0 <= c && c <= 0x7f);
}

int	ft_isprint(int c)
{
	return ((' ' <= c && c <= '?')
		|| ('@' <= c && c <= '_')
		|| ('`' <= c && c <= '~'));
}
