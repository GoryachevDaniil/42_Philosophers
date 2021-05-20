#include "philosophers.h"

int ft_inicializate_semaphor(t_m *mn)
{
	sem_unlink("print");
	sem_unlink("semaphor");
	if ((mn->sem = sem_open("semaphor", O_CREAT, 0777, mn->nbr)) == SEM_FAILED)
		return (ft_error("Semaphor open failed"));
	if ((mn->sem_print = sem_open("print", O_CREAT, 0777, 1)) == SEM_FAILED)
		return (ft_error("Semaphor open failed"));
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
	if (ft_inicializate_semaphor(mn) == -1)
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
	if (pthread_join(mn->death, NULL))
		return (ft_error("Thread join failed."));
	free(ph);
	sem_unlink("print");
	sem_unlink("semaphor");
	return (0);
}