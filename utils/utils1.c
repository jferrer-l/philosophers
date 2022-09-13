/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrer- <jferrer-@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 03:37:00 by jferrer-          #+#    #+#             */
/*   Updated: 2022/06/09 03:37:02 by jferrer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			j;
	long		sum;

	i = 0;
	j = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i++] == '-')
		j = -1;
	else if (str[i] == '+')
		i++;
	sum = 0;
	while (str[i] > 47 && str[i] < 58)
	{
		sum = (sum * 10) + (str[i] - 48);
		i++;
		if (sum > 2147483647 && j == 1)
			return (-1);
		else if (sum > 2147483648 && j == -1)
			return (0);
	}
	return (sum * j);
}

int	ft_argv_isdigit(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	if (!argv)
		return (-1);
	while (++j < argc)
	{
		if (!argv[j] || !argv[j][0])
			return (-1);
		i = -1;
		while (argv[j][++i])
			if (!(argv[j][i] >= '0' && argv[j][i] <= '9'))
				return (-1);
	}
	return (1);
}

long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_usec / 1000 + t.tv_sec * 1000);
}

long	get_time2(t_data *d)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (((t.tv_usec) / 1000 + (t.tv_sec) * 1000) - d->start_at);
}
