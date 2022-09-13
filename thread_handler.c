/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrer- <jferrer-@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:51:50 by jferrer-          #+#    #+#             */
/*   Updated: 2022/06/21 18:51:51 by jferrer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static void	i_loop(t_philo	*philo, t_data	*data);
static void	i_loop_2(t_philo	*philo, t_data	*data);

void	*thread_handler(void *pssi)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)pssi;
	data = (t_data *)philo->idata;
	pthread_mutex_lock(&philo->w2);
	philo->last_eat = 0;
	pthread_mutex_unlock(&philo->w2);
	while (get_time() < data->start_at)
		usleep(10);
	if (philo->id % 2 == 0)
		nsleep(data->tto_eat);
	i_loop(philo, data);
	return (philo);
}

static void	i_loop(t_philo	*philo, t_data	*data)
{
	int	i;

	i = 0;
	while (data->death != 1
		&& (data->num_of_eats == -1 || i < data->num_of_eats))
	{
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(&data->writer);
		if (data->death != 1)
			printf("%ld %d has taken right fork\n", get_time2(data), philo->id);
		pthread_mutex_unlock(&data->writer);
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(&data->writer);
		if (data->death != 1)
		{
			printf("%ld %d has taken left fork\n", get_time2(data), philo->id);
			printf("%ld %d is eating\n", get_time2(data), philo->id);
		}
		pthread_mutex_unlock(&data->writer);
		nsleep(data->tto_eat);
		pthread_mutex_lock(&philo->w2);
		i_loop_2(philo, data);
		i++;
	}
	philo->fin = 1;
}

static void	i_loop_2(t_philo	*philo, t_data	*data)
{
	if (data->death != 1)
		philo->last_eat = get_time2(data);
	pthread_mutex_unlock(&philo->w2);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_lock(&data->writer);
	if (data->death != 1)
		printf("%ld %d is sleeping\n", get_time2(data), philo->id);
	pthread_mutex_unlock(&data->writer);
	nsleep(data->tto_sleep);
	pthread_mutex_lock(&data->writer);
	if (data->death != 1)
		printf("%ld %d is thinking\n", get_time2(data), philo->id);
	pthread_mutex_unlock(&data->writer);
}

int	check_death(t_data *d)
{
	int		i;
	long	temp;

	while (get_time() < d->start_at)
		usleep(10);
	i = 0;
	while (!d->death && !all_finished(d))
	{
		temp = get_time2(d);
		if (temp - d->pss[i]->last_eat > d->tto_die)
		{
			pthread_mutex_lock(&d->writer);
			printf("%ld %d died\n", temp, i + 1);
			d->death = 1;
			pthread_mutex_unlock(&d->writer);
		}
		if (++i == d->num_philo)
			i = 0;
		usleep(50);
	}
	i = 0;
	free_mutexs(d);
	while (i < d->num_philo)
		pthread_detach(*d->trr[i++]);
	return (0);
}
