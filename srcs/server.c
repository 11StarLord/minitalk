/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:39:27 by djoao             #+#    #+#             */
/*   Updated: 2024/09/18 17:39:38 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	convert_dec(char *str)
{
	int		bit_pos;
	int		result;
	char	bit;

	result = 0;
	bit_pos = 0;
	while (bit_pos < 8)
	{
		bit = str[bit_pos];
		if (bit == '1')
			result = result + (1 << (7 - bit_pos));
		bit_pos++;
	}
	ft_printf("%c", result);
}

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	bit_array[8];

	(void)context;
	if (signal == SIGUSR1)
		bit_array[i] = '1';
	else if (signal == SIGUSR2)
		bit_array[i] = '0';
	i++;
	if (i == 8)
	{
		i = 0;
		convert_dec(bit_array);
	}
	if (info != NULL)
		kill(info -> si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	ft_printf("----------------\n");
	ft_printf("  Server: %d \n", pid);
	ft_printf("----------------\n");
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
