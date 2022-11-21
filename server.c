/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 19:45:06 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/21 12:08:35 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
//#define _GNU_SOURCE
#include <string.h>

//c = ((signum == SIGUSR1) << i) | c; 
/* #include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h> */

void	ft_putendl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}


void	ft_putchar(char c)
{
	write(1, &c, 1);
}


static char *print_string(char c, char *client_str)
{
    char *new_string; 
    size_t str_len;
    
    // string = "mensagem que vem do cliente"
    new_string = NULL;
    str_len = 0;
    if(client_str)
        str_len = strlen(client_str);

    new_string = (char *)malloc(sizeof(char) * (str_len + 1 + 1));  
          
    if(new_string)
    {
        new_string = strncpy(new_string, client_str, str_len);
        new_string[str_len] = c;
        new_string[str_len + 1] = '\0';
        
    }
    if(client_str)
        free(client_str);

    return (new_string);
    
    
}


static void signal_handler(int signum, siginfo_t *pid, void *palha)
{
    static int i ;
    static unsigned char c;  
    static pid_t			client_pid;  
    static char     *client_str;

   
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
        if (c)
            client_str = print_string(c, client_str); 
        else if(client_str)
            ft_putendl(client_str);
            
         
        /* if (!c)
        {
            kill(client_pid, SIGUSR2); 
            printf("\n\nerror comes from here!\n\n");    
            exit(0);
        }   */

        
        
          // write(1, &c, 1);
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