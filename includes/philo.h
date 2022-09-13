/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrer- <jferrer-@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:51:27 by jferrer-          #+#    #+#             */
/*   Updated: 2022/06/09 02:51:28 by jferrer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

/*
# define MAX_INT 2147483647
*/

# define MALL_FAIL "Malloc failed\n"
# define PT_CREATE "pthread_create failed\n"
# define MT_CREATE "failed creating the mutex\n"

typedef struct s_philo
{
	int				id;
	pthread_t		*tid;
	struct timeval	init_time;
	int				num_philo;
	long			last_eat;
	void			*idata;
	int				fin;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_mutex_t	w2;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				tto_die;
	int				tto_eat;
	int				tto_sleep;
	int				num_of_eats;
	int				death;
	long			start_at;
	struct timeval	init_time;
	pthread_t		**trr;
	t_philo			**pss;
	pthread_mutex_t	writer;
}	t_data;

int				create_array(t_data *data);
int				create_t_array(t_data *data, t_philo **pss);
int				check_death(t_data *data);
void			nsleep(long time);

/*
SANITIZE_INPUT.C
*/

int				check_args(int argc, char **argv);
int				sanitize_input(int argc, char **argv, t_data *data);

/*
FREE_FUNCS.C
*/

int				f1(void *p, int return_code);
int				fpss(t_philo **pss, int index);
int				ftss(pthread_t **trr, int index);
void			free_mutexs(t_data *d);

/*
UTILS1.C
*/

size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
int				ft_argv_isdigit(int argc, char **argv);
long			get_time(void);
long			get_time2(t_data *d);

/*
UTILS2.C
*/

pthread_mutex_t	*get_new_mutex(int *f_return);
int				create_forks(t_philo **pss);
void			leaks_checker(void);
int				all_finished(t_data *d);

/*
THREAD_HANDLER.C
*/

void			*thread_handler(void *philo);

#endif