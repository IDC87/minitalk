/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:00:52 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/11 22:47:43 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


// client receives two arguments:
    // the server PID
    // the string to send

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int		ft_check_base(char *base)
{
	int		i;
	int		j;

	if (ft_strlen(base) < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+' || base[i] < 32 || base[i] > 126)
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long	nbr_l;
	char	nbr_c[32];
	int		base_divider;
	int		i;

	if (!ft_check_base(base))
		return ;
	base_divider = ft_strlen(base);
	if (nbr < 0)
	{
		nbr_l = nbr;
		nbr_l = -nbr_l;
		ft_putchar('-');
	}
	else
		nbr_l = nbr;
	i = 0;
	while (nbr_l > 0)
	{
		nbr_c[i] = base[nbr_l % base_divider];
		nbr_l /= base_divider;
		i++;
	}
	while (--i >= 0)
		ft_putchar(nbr_c[i]);
}


void send_bit(char c, int pid)
{
    int binary[8];
    int i = 0;
    //printf("c in dec is %c\n", c);
    c = c - 48;
   // printf("%c in dec is %d\n", c, c);    
    
    while (c > 0) 
    {
        binary[i] = c % 2;
        c = c / 2;
        i++;
    }
        usleep(50);
        i = 0;
        while(i < 8)
        {
            if ((binary[i]) & 1)
            kill(pid, SIGUSR1);
            else
            kill(pid, SIGUSR2);

           i++; 
        }
        
     
    
}


int main (int argc, char **argv)
{
    int pid;
    int ret;
    char *str;
    int i;

    //i = 01101001
    i = 0;
    
    pid = atoi(argv[1]);    
    str = argv[2];

    printf("ARGS \n%d\n%s\n", pid, str);

    //send_bit(str[0], pid);
    
    while(str[i])
    {
        send_bit(str[i], pid);
        i++;
        //usleep(300);
    }



    
}