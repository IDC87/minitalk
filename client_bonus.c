/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:50:42 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/22 16:14:43 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(char *message)
{
	ft_putstr_fd("Error!", STDOUT_FILENO);
	ft_putendl_fd(message, STDOUT_FILENO);
	exit(0);
}

static void	send_bit(char c, int pid)
{
	__uint8_t	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
		i++;
	}
}

static void	send_string(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_bit(str[i], pid);
		i++;
	}
	if (str[i] == '\0')
		send_bit(str[i], pid);
}

static void	bit_confirmation(int signum)
{
	static int	beeps_count;

	if (signum == SIGUSR1)
		beeps_count++;
	if (signum == SIGUSR2)
	{
		beeps_count = (beeps_count + 1) / 8;
		ft_putchar('\n');
		ft_putnbr_fd(beeps_count, STDOUT_FILENO);
		ft_putendl_fd(" Bytes received with sucess!", STDOUT_FILENO);
		ft_putchar('\n');
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc != 3)
		error(" invalid arguments! Ending Client");
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) < 0)
		error(" PID is Invalid! Ending Client!");
	str = ft_strdup(argv[2]);
	if (!str || ft_strlen(str) == 0)
	{
		free(str);
		error(" Empty string");
	}
	signal(SIGUSR1, &bit_confirmation);
	signal(SIGUSR2, &bit_confirmation);
	send_string(str, pid);
	free(str);
	while (1)
		pause();
	return (0);
}
