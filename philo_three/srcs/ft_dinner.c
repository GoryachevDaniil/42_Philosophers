#include "philosophers.h"

void ft_eat(t_philo *ph) 
{ 
	sem_wait(ph->mn->sem);
	sem_wait(ph->mn->sem_print);
	printf("\033[34m%d philo %d takes the right fork\033\n", ft_time_diff(ph->mn), ph->id);
	sem_post(ph->mn->sem_print);
	sem_wait(ph->mn->sem);
	sem_wait(ph->mn->sem_print);
	printf("\033[34m%d philo %d takes the left fork\033\n", ft_time_diff(ph->mn), ph->id);
	sem_post(ph->mn->sem_print);
	sem_wait(ph->mn->sem_print);
	printf("\033[32m%d philo %d eating\033\n", ft_time_diff(ph->mn), ph->id);
	sem_post(ph->mn->sem_print);
	ph->last_eat = ft_get_time();
	ft_usleep(ph->mn->tte);
	sem_post(ph->mn->sem);
	sem_post(ph->mn->sem);
}

void ft_sleep(t_philo *ph)
{
	sem_wait(ph->mn->sem_print);
	printf("\033[36m%d philo %d sleeping\033\n", ft_time_diff(ph->mn), ph->id);
	sem_post(ph->mn->sem_print);
	ft_usleep(ph->mn->tts);
}

void ft_think(t_philo *ph)
{
	sem_wait(ph->mn->sem_print);
	printf("\036[36m%d philo %d thinking\033\n", ft_time_diff(ph->mn), ph->id);
	sem_post(ph->mn->sem_print);
}

void *ft_die(void *buf)
{
	t_philo *ph;

	ph = (t_philo *) buf;
	while(1)
	{
		sem_wait(ph->mn->sem_print);
		if (ft_get_time() - ph->last_eat > ph->mn->ttd)
		{
			printf("\033[31m%d philo %d die\033\n", ft_time_diff(ph->mn) - 1, ph->id);
			// ph->mn->die = 1;
			sem_post(ph->mn->sem_killa);
			exit (0);
		}
		sem_post(ph->mn->sem_print);
		if (ph->mn->end == ph->mn->nbr)
			break ;
	}
	return (0);
}

void *ft_on_the_table(void *buf)
{
	t_philo *ph;
	int i;
	
	i = 0;
	ph = (t_philo *) buf;
	if (ph->id % 2 != 0)
		ft_usleep(ph->mn->tte);
	while (++i)
	{
		ft_eat(ph);
		if (i == ph->mn->tmte)
		{
			sem_post(ph->mn->sem_print);
			exit (0);
			// sem_post(ph->mn->sem_count);
		}
		ft_sleep(ph);
		ft_think(ph);
	}
	return (0);
}