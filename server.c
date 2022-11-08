/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 19:45:06 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/08 20:20:39 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

void signal_handler(int signum)
{
         
    
}


int main(void)
{
    int pid;
    //struct sigaction test;

    pid = getpid();
    printf("%d\n", pid );
    signal(SIGUSR1, &signal_handler);  

    while(1)
        pause();
    
   return (0);
}