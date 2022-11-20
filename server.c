/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 19:45:06 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/20 13:06:43 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
//#define _GNU_SOURCE

//c = ((signum == SIGUSR1) << i) | c; 
/* #include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h> */


static void signal_handler(int signum, siginfo_t *pid, void *palha)
{
    static int i ;
    static unsigned char c;  
    static pid_t			client_pid;  

   
        (void)palha;
        client_pid = pid->si_pid;    
        if (signum == SIGUSR1)
        {
            c = 1 << i | c;
            i++;
        }
        else if (signum == SIGUSR2)
        {
            c = 0 << i | c;
            i++;            
        }  
        
    
    if (i == 8)
    {   
        if (!c)
        {
            kill(client_pid, SIGUSR2); 
            printf("\n\nerror comes from here!\n\n");    
            exit(0);
        }  
        
        write(1, &c, 1);
        i = 0; 
        c = 0;         
            
    } 
    kill(client_pid, SIGUSR1);
    
    
}  

int main(void)
{
    int pid;
   struct sigaction sig;
     
    pid = getpid();
    printf("%d\n", pid);
    sig.sa_flags = SA_SIGINFO;   
    sig.sa_sigaction = &signal_handler;
    sigemptyset(&sig.sa_mask);
    while(1)
    {
            if(!SIGUSR1 && !SIGUSR2)
                pause();                
            else
            {               
                sigaction(SIGUSR1, &sig, NULL);
                sigaction(SIGUSR2, &sig, NULL); 
                     
            }
          
    }

    
   return (0);
}