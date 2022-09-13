/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrer- <jferrer-@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:06:02 by jferrer-          #+#    #+#             */
/*   Updated: 2022/06/09 17:06:03 by jferrer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	sanitize_input(int argc, char **argv, t_data *data)
{
	struct timeval	init_time;

	if (check_args(argc, argv) == -1 || ft_atoi(argv[1]) == 0)
		return ((0 * write(2, "Invalid input\n", 15)) - 1);
	if (gettimeofday(&init_time, NULL) == -1)
		return ((0 * write(2, "Error in gettimeofday\n", 23)) - 1);
	data->num_philo = ft_atoi(argv[1]);
	data->tto_die = ft_atoi(argv[2]);
	data->tto_eat = ft_atoi(argv[3]);
	data->tto_sleep = ft_atoi(argv[4]);
	data->num_of_eats = 1;
	data->init_time = init_time;
	data->death = 0;
	if (argc == 6)
		data->num_of_eats = ft_atoi(argv[5]);
	if (data->num_philo == -1 || data->tto_die == -1 || data->tto_eat == -1
		|| data->tto_sleep == -1 || data->num_of_eats == -1)
		return ((0 * write(2, "Invalid input\n", 15)) - 1);
	if (argc != 6)
		data->num_of_eats = -1;
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (-1);
	if (ft_argv_isdigit(argc, argv) == -1)
		return (-1);
	return (1);
}
