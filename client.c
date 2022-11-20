/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 19:44:58 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/20 13:08:37 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <string.h> // replace for the ft_atoi

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
           usleep(400); 
     
        i++;    
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
    
    pid = atoi(argv[1]);    
    str = strdup(argv[2]);   
    signal(SIGUSR1, &bit_confirmation);
	signal(SIGUSR2, &bit_confirmation_error);

    send_string(str, pid);
   
                
       


    
}


