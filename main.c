/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrer- <jferrer-@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:50:07 by jferrer-          #+#    #+#             */
/*   Updated: 2022/06/09 03:22:41 by jferrer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	create_t_array2(t_data *d, t_philo	**pss);

/*
atexit(leaks_checker);
implementar un filosofo
*/

/*void	leaks_checker()
{
	system("leaks philo");
}*/

int	main(int argc, char **argv)
{
	t_data			*data;
	int				err;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return ((0 * write(2, MALL_FAIL, 15)) - 1);
	pthread_mutex_init(&data->writer, NULL);
	data->death = 0;
	err = 0;
	if (err == -1)
		return (f1(data, -1));
	if (sanitize_input(argc, argv, data) == -1)
		return (f1(data, -1));
	return (f1(data, create_array(data)));
}

int	create_array(t_data *data)
{
	t_philo	**pss;
	int		i;

	pss = (t_philo **)malloc(sizeof(t_philo *) * data->num_philo);
	if (!pss)
		return ((0 * write(2, MALL_FAIL, 15)) - 1);
	i = -1;
	while (++i < data->num_philo)
	{
		pss[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!pss[i])
			return (f1(pss, fpss(pss, i)) + (0 * write(2, MALL_FAIL, 15)));
		pss[i]->id = i + 1;
		pss[i]->init_time = data->init_time;
		pss[i]->num_philo = data->num_philo;
		pss[i]->idata = data;
		pss[i]->fin = 0;
	}
	data->pss = pss;
	if (create_forks(data->pss) == -1)
		return (f1(pss, fpss(pss, data->num_philo)));
	return (create_t_array(data, pss)
		+ (0 * f1(pss, fpss(pss, data->num_philo))));
}

int	create_t_array(t_data *d, t_philo	**pss)
{
	int			i;

	d->trr = (pthread_t **)malloc(sizeof(pthread_t *) * d->num_philo);
	if (!d->trr)
		return ((0 * write(2, MALL_FAIL, 15)) - 1);
	if (create_t_array2(d, pss) == -1)
		return (f1(d->trr, -1));
	i = -1;
	d->start_at = get_time() + d->num_philo * 5;
	while (++i < pss[0]->num_philo)
	{
		d->pss[i]->tid = d->trr[i];
		pthread_mutex_init(&d->pss[i]->w2, NULL);
		if (pthread_create(d->trr[i], NULL, thread_handler, d->pss[i]) != 0)
			return (f1(d->trr, ftss(d->trr, d->num_philo))
				+ (0 * write(2, PT_CREATE, 23)));
		usleep(10);
	}
	check_death(d);
	return (0 * f1(d->trr, ftss(d->trr, pss[0]->num_philo)));
}

static int	create_t_array2(t_data *d, t_philo	**pss)
{
	int	i;

	i = -1;
	while (++i < pss[0]->num_philo)
	{
		d->trr[i] = (pthread_t *)malloc(sizeof(pthread_t));
		if (!d->trr[i])
			return (f1(d->trr, ftss(d->trr, i))
				+ (0 * write(2, MALL_FAIL, 15)));
	}
	return (0);
}

void	nsleep(long time)
{
	long	itime;

	itime = get_time();
	while (get_time() < itime + time)
		usleep(time / 2);
}
