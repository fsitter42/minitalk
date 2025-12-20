/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_server.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:02:14 by fsitter           #+#    #+#             */
/*   Updated: 2025/12/14 13:50:33 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	f_signal_handeling(int sig, siginfo_t *info, void *content);

void	f_signal_handeling(int sig, siginfo_t *info, void *content)
{
	static int				i = 0;
	static unsigned char	bit = 0;
	static unsigned char	byte = 0;
	static unsigned char	message[131072];

	(void)content;
	if (sig == SIGUSR1)
		byte = (byte << 1) | 1;
	else
		byte = byte << 1;
	bit++;
	if (bit == 8)
	{
		message[i++] = byte;
		if (!byte)
		{
			i = 0;
			ft_printf("%s\n", message);
			kill(info->si_pid, SIGUSR1);
		}
		bit = 0;
		byte = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	chimpanzini_bananini;

	chimpanzini_bananini.sa_sigaction = &f_signal_handeling;
	chimpanzini_bananini.sa_flags = SA_SIGINFO;
	sigemptyset(&chimpanzini_bananini.sa_mask);
	sigaction(SIGUSR1, &chimpanzini_bananini, NULL);
	sigaction(SIGUSR2, &chimpanzini_bananini, NULL);
	ft_printf("Server PID: %i\n", getpid());
	if (sigaction(SIGUSR1, &chimpanzini_bananini, NULL) == -1)
		ft_printf("ERROR: Receiving signal 1!\n");
	if (sigaction(SIGUSR2, &chimpanzini_bananini, NULL) == -1)
		ft_printf("ERROR: Receiving signal 2!\n");
	while (1)
		pause();
	return (0);
}
