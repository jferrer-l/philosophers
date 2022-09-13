/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrer- <jferrer-@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:15:51 by jferrer-          #+#    #+#             */
/*   Updated: 2022/06/21 19:15:52 by jferrer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*get_new_mutex(int *f_return)
{
	pthread_mutex_t	*new_mutex;

	new_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(new_mutex, NULL) == 0)
		return (new_mutex);
	*f_return = -1;
	write(2, MT_CREATE, 27);
	return (new_mutex);
}

int	create_forks(t_philo	**pss)
{
	int				i;
	int				err;

	i = -1;
	err = 1;
	while (++i < pss[0]->num_philo)
	{
		pss[i]->right = get_new_mutex(&err);
		if (i < pss[0]->num_philo - 1)
			pss[i + 1]->left = pss[i]->right;
		else
			pss[0]->left = pss[i]->right;
		if (err == -1)
			return (-1);
	}
	return (err);
}

void	leaks_checker(void)
{
	system("leaks philo");
}

int	all_finished(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->num_philo)
		if (d->pss[i]->fin == 0)
			return (0);
	return (1);
}
