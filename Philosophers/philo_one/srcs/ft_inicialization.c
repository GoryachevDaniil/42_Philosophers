#include "philosophers.h"

int ft_inicializate_mutex(t_m *mn)
{
	int i;

	mn->mtx = malloc(sizeof(pthread_mutex_t) * mn->nbr + 1);
	if (mn->mtx == NULL)
		return (ft_error("Mutex malloc failed"));
	i = -1;
	while (++i < mn->nbr)
		if (pthread_mutex_init(&mn->mtx[i], NULL))
			return (ft_error("Mutex init failed"));
	if (pthread_mutex_init(&mn->mtx_print, NULL))
		return (ft_error("Mutex init failed"));
	return (0);
}

t_philo *ft_inicializate_philo(t_m *mn)
{
	int i;
	t_philo *ph;

	ph = malloc(sizeof(t_philo *) * mn->nbr);
	if (ph == NULL)
		return (NULL);
	i = -1;
	while(++i < mn->nbr)
	{
		ph[i].id = i + 1;
		ph[i].r_fork = i;
		ph[i].l_fork = (i + 1) % mn->nbr;
		ph[i].last_eat = ft_get_time();
		ph[i].mn = mn;
	}
	return (ph);
}

int ft_inicializate_threads(t_m *mn)
{
	int i;
	t_philo *ph;

	mn->t = malloc(sizeof(pthread_t) * mn->nbr + 1);
	if (ft_inicializate_mutex(mn) == -1)
		return (0);
	ph = ft_inicializate_philo(mn);	
	if (ph == NULL)
		return (ft_error("Philofophers inicializate failed."));
	i = -1;
	mn->start_time = ft_get_time();
	if (pthread_create(&mn->death, NULL, ft_die, ph))
		return (ft_error("Thread create failed."));
	while (++i < mn->nbr)
		if (pthread_create(&mn->t[i], NULL, ft_on_the_table, &ph[i]))
			return (ft_error("Thread create failed."));
	i = -1;
	while (++i < mn->nbr)
		pthread_detach(mn->t[i]);
	// i = -1;
	// while (++i < mn->nbr)
	// 	if (pthread_join(mn->t[i], NULL))
	// 		return (ft_error("Thread join failed."));
	pthread_mutex_unlock(&ph->mn->mtx_print);
	if (pthread_join(mn->death, NULL))
		return (ft_error("Thread join failed."));
	free(ph);
	return (0);
}