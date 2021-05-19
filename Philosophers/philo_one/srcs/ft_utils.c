#include "philosophers.h"

suseconds_t	ft_get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

suseconds_t	ft_time_diff(t_m *mn)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000 - mn->start_time);
}

void		ft_usleep(long time)
{
	long t;

	t = ft_get_time();
	while (ft_get_time() - t < time)
		usleep(1);
}

int 		ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (-1);
}
