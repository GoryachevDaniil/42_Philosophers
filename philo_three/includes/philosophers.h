#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct  s_m
{
	int				nbr;
	double			ttd;
	double			tte;
	double			tts;
	int				tmte;
	int				six;
	int				invalid;
	int				die;
	long			start_time;
	pthread_t		*t;
	pthread_t		death;
	pthread_t		killa;
	pthread_t		monitoring;
	sem_t			*sem;
	sem_t			*sem_print;
	sem_t			*sem_killa;
	sem_t			*sem_count;
	sem_t			*sem_stop;
	int				malloc_error;
	int             end;
}               t_m;

typedef struct  s_philo
{
    int				id;
    // int				l_fork;
    // int				r_fork;
    int 			last_eat;
    t_m             *mn;
	int				godmod;
	pid_t			pid;
}               t_philo;




int main(int argc, char **argv);

int ft_parser(t_m *main, char **argv, int argc);

void ft_check_arg(t_m *main, char **argv, int argc);
void ft_validate(char *argv, t_m *mn);

int	promezhutok(t_m *mn);

int ft_inicializate_threads(t_philo *ph);
t_philo *ft_inicializate_philo(t_m *mn);
// int ft_inicializate_mutex(t_m *mn);
int ft_inicializate_semafor(t_m *mn);

void *ft_on_the_table(void *buf);
void *ft_die(void *buf);
void ft_eat(t_philo *ph);
void ft_sleep(t_philo *ph);
void ft_think(t_philo *ph);

int ft_error(char *str);
void    ft_usleep(long time);
suseconds_t	ft_time_diff(t_m *mn);
suseconds_t	ft_get_time(void);


int	ft_atoi(const char *str);
int	ft_isdigit(int ch);
size_t	ft_strlen(const char *str);

#endif