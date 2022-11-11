/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivda-cru <ivda-cru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 19:44:58 by ivda-cru          #+#    #+#             */
/*   Updated: 2022/11/11 23:02:55 by ivda-cru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// client receives two arguments:
    // the server PID
    // the string to send

void send_bit(char c, int pid)
{
    int i = 0;
    while(i < 8)
    {
        if((c >> i++) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2); 
            usleep(1000);  
            
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

    /* while(1)
        pause();
 */

    
}