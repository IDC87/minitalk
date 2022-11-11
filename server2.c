/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:00:29 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/11 21:01:06 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

static void signal_handler(int signum)
{
    static int i ;
    static char c;    

    if (i < 8)
    {
        c = ((signum == SIGUSR1) << i) | c;
        i++;       
        
    }
    if (i == 8)
    {
        write(1, &c, 1);
        i = 0; 
        c = 0;
        
    }   
    
}


int main(void)
{
    int pid;
    //struct sigaction test;

    pid = getpid();
    printf("%d\n", pid );
    signal(SIGUSR1, &signal_handler); 
    usleep(500); 
    signal(SIGUSR2, &signal_handler);

    while(1)
        pause();
    
   return (0);
}