/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrer- <jferrer-@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:15:45 by jferrer-          #+#    #+#             */
/*   Updated: 2022/06/09 18:15:47 by jferrer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	f1(void *p, int return_code)
{
	free(p);
	return (return_code);
}

int	fpss(t_philo **pss, int index)
{
	while (--index >= 0)
		free(pss[index]);
	return (-1);
}

int	ftss(pthread_t **trr, int index)
{
	while (--index >= 0)
		free(trr[index]);
	return (-1);
}

void	free_mutexs(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->num_philo)
		free(d->pss[i]->right);
	if (pthread_mutex_destroy(&d->writer) != 0)
		printf("error\n");
}
