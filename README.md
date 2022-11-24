# minitalk
small data exchange program using UNIX signals

The objective of this project is to use the signal library in order to be able to send data from a client to a server.
Since Signals were not made to be the main source of data stream communication both the client and server need to be made in a way the information
can be send flawless. 
We can only use two signals from the library, SIGUSR1 and SIGUSR2 with the help of the kill system call. 
Data needs to be translated in binary with the help of the bitwise operations in c.
