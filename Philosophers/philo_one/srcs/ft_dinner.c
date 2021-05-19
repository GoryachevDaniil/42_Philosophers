#include "philosophers.h"

void ft_eat(t_philo *ph) 
{ 
	if (ph->mn->die == 0)
	{
		pthread_mutex_lock(&ph->mn->mtx[ph->l_fork]);
		pthread_mutex_lock(&ph->mn->mtx_print);
		printf("\033[34m%d philo %d takes the right fork\033\n", ft_time_diff(ph->mn), ph->id);
		pthread_mutex_unlock(&ph->mn->mtx_print);
		pthread_mutex_lock(&ph->mn->mtx[ph->r_fork]);
	}
	if (ph->mn->die == 0)
	{
		pthread_mutex_lock(&ph->mn->mtx_print);
		printf("\033[34m%d philo %d takes the left fork\033\n", ft_time_diff(ph->mn), ph->id);
		pthread_mutex_unlock(&ph->mn->mtx_print);
	}
	if (ph->mn->die == 0)
	{
		pthread_mutex_lock(&ph->mn->mtx_print);
		printf("\033[32m%d philo %d eating\033\n", ft_time_diff(ph->mn), ph->id);
		pthread_mutex_unlock(&ph->mn->mtx_print);
		ph->last_eat = ft_get_time();
		ft_usleep(ph->mn->tte);
		pthread_mutex_unlock(&ph->mn->mtx[ph->r_fork]);
		pthread_mutex_unlock(&ph->mn->mtx[ph->l_fork]);
	}
}


void ft_sleep(t_philo *ph)
{
	if (ph->mn->die == 0)
	{
		pthread_mutex_lock(&ph->mn->mtx_print);
		printf("\033[36m%d philo %d sleeping\033\n", ft_time_diff(ph->mn), ph->id);
		pthread_mutex_unlock(&ph->mn->mtx_print);
		ft_usleep(ph->mn->tts);
	}
}

void ft_think(t_philo *ph)
{
	if (ph->mn->die == 0)
	{
		pthread_mutex_lock(&ph->mn->mtx_print);
		printf("\036[36m%d philo %d thinking\033\n", ft_time_diff(ph->mn), ph->id);
		pthread_mutex_unlock(&ph->mn->mtx_print);
	}
}

void *ft_die(void *buf)
{
	t_philo *ph;
	int i;
	int j;

	j = 0;
	ph = (t_philo *) buf;
	while(++j)
	{
		i = -1;
		while (++i < ph->mn->nbr)
			if (ft_get_time() - ph[i].last_eat > ph->mn->ttd)
			{
				pthread_mutex_lock(&ph->mn->mtx_print);
				printf("\033[31m%d philo %d die\033\n", ft_time_diff(ph->mn) - 1, ph[i].id);
				ph->mn->die = 1;
				return (0);
			}
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
		if (ph->mn->die == 1)
			return (0);
		ft_eat(ph);
		if (i == ph->mn->tmte)
		{
			ph->mn->end++;
			break ;
		}
		ft_sleep(ph);
		ft_think(ph);
	}
	return (0);
}