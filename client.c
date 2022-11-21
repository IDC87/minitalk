/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 19:44:58 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/21 09:31:38 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <string.h> // replace for the ft_atoi

int		len(long nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char *str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

static void send_bit(char c, int pid)
{
    __uint8_t i;

    i = 0;    
    while(i < 8)
    {
        if((c >> i) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2); 
           usleep(200); 
     
        i++;    
    }     
}

static void send_str_len(char *str, int pid)
{
    int		shift;
	char	bit;
    int num;
    
    num = strlen(str);
	shift = (sizeof(int) * 8) - 1;
	while (shift >= 0)
	{
		bit = (num >> shift) & 1;
        if(bit == 1)
		    kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(200);
		shift--;
	}
    
    
}

static void send_string(char *str, int pid)
{
    int i;    
        
    i = 0;    
    while (str[i])
    {
        send_bit(str[i], pid);
        i++;
    }
    
}

static void bit_confirmation(int signum)
{   
    if (signum == SIGUSR1)
       // printf("BASED\n");  
    while(signum != SIGUSR1) 
        pause();   
        
}

static void bit_confirmation_error(int signum)
{     
    
    if (signum == SIGUSR2)
        {
            printf("\n\nNao aguentou a pujanca\n\n");
            exit(0);
        }
}

int main (int argc, char **argv)
{
    int pid;
    char *str;
    if (argc == 3)
    {
        pid = atoi(argv[1]);    
        str = strdup(argv[2]);   
        
    }
    signal(SIGUSR1, &bit_confirmation);
	signal(SIGUSR2, &bit_confirmation_error);

    send_str_len(str, pid);
    send_string(str, pid);
    
}

/* int i;
    int size_str;
    char *str_len;
    
    i = 0;
    size_str = (int)strlen(str);    
    str_len = ft_itoa(size_str);

    while (str_len[i])
    {
        send_bit(str_len[i], pid);
        i++;
    }
    if (!str_len[i])
        send_bit('\t', pid); */


