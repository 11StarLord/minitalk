/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:39:12 by djoao             #+#    #+#             */
/*   Updated: 2024/09/18 17:39:15 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_control;

void	handler_signal(int signal)
{
	(void)signal;
	g_control = 1;
}

void	convert_bin(char *str, pid_t pid)
{
	int	bit;

	while (*str)
	{
		bit = 7;
		while (bit >= 0)
		{
			g_control = 0;
			if (*str & (1 << bit))
			{
				if(kill(pid, SIGUSR1)== -1)
					exit(1);
			}
			else
			{
				if(kill(pid, SIGUSR2) == -1)
					exit(1);
			}
			while (g_control == 0)
				pause();
			bit--;
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("ERROR! Correct: %s PID_SERVER message\n", argv[0]);
		return (-1);
	}
	if (argv[2][0] == '\0')
	{
		ft_printf("Empty message!\n");
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Invalid PID!\n");
		return (-1);
	}
	signal(SIGUSR1, handler_signal);
	convert_bin(argv[2], pid);
	return (0);
}
