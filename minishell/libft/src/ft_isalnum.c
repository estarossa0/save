/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arraji <arraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 00:48:52 by arraji            #+#    #+#             */
/*   Updated: 2019/10/20 22:45:30 by arraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int car)
{
	if ((car >= 65 && car <= 90) || (car >= 97 && car <= 122) ||
	(car >= 48 && car <= 57))
	{
		return (1);
	}
	else
		return (0);
}
