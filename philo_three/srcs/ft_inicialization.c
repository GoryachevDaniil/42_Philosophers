#include "philosophers.h"

// void *ft_monitoring(void *buf)
// {
// 	t_philo *ph;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = -1;
// 	ph = (t_philo *) buf;
// 	while (1)
// 	{
// 		sem_wait(ph->mn->sem_count);
// 		++i;
// 		if (i == ph->mn->nbr)
// 		{
// 			// sem_post(ph->mn->sem_killa);
// 			while(++j < ph->mn->nbr)
// 				kill(ph[j].id, SIGTERM);
// 			exit (0);
// 		}
// 		else
// 			sem_post(ph->mn->sem_print);
// 	}
// 	return (0);
// }

void *ft_monitoring_death(void *buf)
{
	t_philo *ph;

	ph = (t_philo *) buf;
	while (1)
	{
		usleep(10);
		sem_wait(ph->mn->sem_killa);
		sem_post(ph->mn->sem_killa);
		exit (0);
	}
	return (0);
}

int ft_inicializate_semaphor(t_m *mn)
{
	sem_unlink("semaphor");
	sem_unlink("print");
	sem_unlink("killa");
	// sem_unlink("count");
	if ((mn->sem = sem_open("semaphor", O_CREAT, 0777, mn->nbr)) == SEM_FAILED)
		return (ft_error("Semaphor open failed"));
	if ((mn->sem_print = sem_open("print", O_CREAT, 0777, 1)) == SEM_FAILED)
		return (ft_error("Semaphor open failed"));
	if ((mn->sem_killa = sem_open("killa", O_CREAT, 0777, 0)) == SEM_FAILED)
		return (ft_error("Semaphor open failed"));
	// if ((mn->sem_count = sem_open("count", O_CREAT, 0777, 0)) == SEM_FAILED)
	// 	return (ft_error("Semaphor open failed"));
	return (0);
}

t_philo *ft_inicializate_philo(t_m *mn)
{
	int i;
	t_philo *ph;

	ph = malloc(sizeof(t_philo) * mn->nbr);
	if (ph == NULL)
		return (NULL);
	i = -1;
	while(++i < mn->nbr)
	{
		ph[i].id = i + 1;
		// ph[i].r_fork = 0;
		// ph[i].l_fork = 0;
		ph[i].last_eat = ft_get_time();
		ph[i].mn = mn;
	}
	return (ph);
}

int ft_inicializate_threads(t_philo *ph)
{
	int i;

	i = -1;
	if (pthread_create(&ph->mn->killa, NULL, ft_monitoring_death, ph))
		return (ft_error("Thread create failed."));
	if (pthread_create(&ph->mn->death, NULL, ft_die, ph))
		return (ft_error("Thread create failed."));
	ft_on_the_table(ph);
	if (pthread_join(ph->mn->killa, NULL))
		return (ft_error("Thread join failed."));
	if (pthread_join(ph->mn->death, NULL))
		return (ft_error("Thread join failed."));
	return (0);
}

int	promezhutok(t_m *mn)
{
	int i;
	t_philo *ph;

	// mn->t = malloc(sizeof(pthread_t) * 2);
	if (ft_inicializate_semaphor(mn) == -1)
		return (0);
	ph = ft_inicializate_philo(mn);	
	if (ph == NULL)
		return (ft_error("Philofophers inicializate failed."));
	mn->start_time = ft_get_time();


	i = -1;
	while (++i < mn->nbr)
	{
		ph[i].pid = fork();
		if (ph[i].pid < 0)
			return (0);
		else if (ph[i].pid == 0)
		{
			printf("i ============ %d\n", i);
			ft_inicializate_threads(&ph[i]);
		}
	}
	// if (pthread_create(&ph->mn->monitoring, NULL, ft_monitoring, ph))
	// 	return (ft_error("Thread create failed."));	
	// pthread_detach(ph->mn->monitoring);
	i = -1;
	while (++i < mn->nbr)
		waitpid(ph[i].pid, NULL, WUNTRACED);


	sem_unlink("semaphor");
	sem_unlink("print");
	sem_unlink("killa");
	free(ph);
	return (0);
}