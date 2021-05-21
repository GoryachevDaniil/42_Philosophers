#include "philosophers.h"

void	ft_validate(char *argv, t_m *mn)
{
	int	i;

	i = -1;
	while (argv[++i])
		if (ft_isdigit(argv[i]) == 0)
			mn->invalid = 1;
}

void	ft_check_arg(t_m *mn, char **argv, int argc)
{
	int	i;

	i = 0;
	mn->invalid = 0;
	while (++i < argc)
		ft_validate(argv[i], mn);
	if (mn->nbr < 2 || mn->nbr > 200)
		mn->invalid = 1;
	if (mn->ttd < 60 || mn->ttd > 2147483647)
		mn->invalid = 1;
	if (mn->tte < 60 || mn->tte > 2147483647)
		mn->invalid = 1;
	if (mn->tts < 60 || mn->tts > 2147483647)
		mn->invalid = 1;
	if (mn->six == 1)
		if (mn->tmte < 0 || mn->tmte > 2147483647)
			mn->invalid = 1;
}

int	ft_parser(t_m *mn, char **argv, int argc)
{
	if (argc == 6)
		mn->six = 1;
	else
		mn->six = 0;
	mn->tmte = 0;
	mn->nbr = ft_atoi(argv[1]);
	mn->ttd = ft_atoi(argv[2]);
	mn->tte = ft_atoi(argv[3]);
	mn->tts = ft_atoi(argv[4]);
	if (mn->six == 1)
		mn->tmte = ft_atoi(argv[5]);
	ft_check_arg(mn, argv, argc);
	if (mn->invalid == 1)
		return (ft_error("Invalid one or any arguments."));
	mn->die = 0;
	mn->end = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_m	mn;

	if (argc >= 5 && argc <= 6)
	{
		if (ft_parser(&mn, argv, argc) == -1)
			return (0);
		ft_inicializate_threads(&mn);
	}
	else
		printf("%s\n", "Invalid nbr of arguments.");
	return (0);
}
