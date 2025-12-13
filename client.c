/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:42:24 by fsitter           #+#    #+#             */
/*   Updated: 2025/12/13 13:59:00 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	message(char *msg, int pid);
void	f_acknowledge_client(int i);
void	f_end_of_line(int pid);

int		g_wait;

void	f_end_of_line(int pid)
{
	size_t	i;

	i = 8;
	while (i > 0)
	{
		g_wait = 1;
		kill(pid, SIGUSR2);
		while (g_wait)
			pause();
	}
}

void	f_acknowledge_client2(int i)
{
	if (i == SIGUSR1)
		ft_printf(".");
	g_wait = 0;
}

void	f_acknowledge_client(int i)
{
	static size_t	eol_count = 0;

	if (i == SIGUSR1)
		ft_printf(".");
	else if (i == SIGUSR2)
	{
		eol_count++;
		if (eol_count == 8)
		{
			ft_printf("sent!\n");
			eol_count = 0;
		}
	}
	g_wait = 0;
}

void	message(char *msg, int pid)
{
	size_t			i;
	unsigned int	bit;

	while (*msg)
	{
		i = 0;
		bit = (unsigned char)*msg;
		while (i < 8)
		{
			g_wait = 1;
			if ((bit << i) & 0x80)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i++;
			while (g_wait)
				pause();
		}
		msg++;
	}
	f_end_of_line(pid);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_printf("Instruction: ./filename server-PID message\n");
		exit(1);
	}
	if (ft_atoi(av[1]) <= 0 || av[1][0] == '+' || ft_atoi(av[1]) > 4194304)
		return (ft_printf("Invalid server-PID\n"), -1);
	signal(SIGUSR1, &f_acknowledge_client);
	signal(SIGUSR2, &f_acknowledge_client);
	message(av[2], ft_atoi(av[1]));
	return (0);
}
