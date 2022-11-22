/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:51:07 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/22 15:51:25 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*print_string(char c, char *client_str)
{
	char	*new_string;
	size_t	str_len;

	new_string = NULL;
	str_len = 0;
	if (client_str)
		str_len = ft_strlen(client_str);
	new_string = (char *)malloc(sizeof(char) * (str_len + 1 + 1));
	if (new_string)
	{
		new_string = ft_memcpy(new_string, client_str, str_len);
		new_string[str_len] = c;
		new_string[str_len + 1] = '\0';
	}
	if (client_str)
		free(client_str);
	return (new_string);
}

static void	signal_handler(int signum, siginfo_t *pid, void *palha)
{
	static int				i;
	static unsigned char	c;
	static pid_t			client_pid;
	static char				*client_str;

	(void)palha;
	client_pid = pid->si_pid;
	c = ((signum == SIGUSR1) << i) | c;
	i++;
	if (i == 8)
	{
		if (c)
			client_str = print_string(c, client_str);
		else if (client_str)
		{
			ft_putendl_fd(client_str, STDOUT_FILENO);
			kill(client_pid, SIGUSR2);
			client_str = NULL;
		}
		i = 0;
		c = 0;
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sig;

	pid = getpid();
	ft_putstr_fd("SERVER PID: ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putchar('\n');
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = &signal_handler;
	sigemptyset(&sig.sa_mask);
	while (1)
	{
		if (!SIGUSR1 && !SIGUSR2)
			pause();
		else
		{
			sigaction(SIGUSR1, &sig, NULL);
			sigaction(SIGUSR2, &sig, NULL);
		}
	}
	return (0);
}
