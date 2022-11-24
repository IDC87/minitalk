# minitalk
<b>small data exchange program using UNIX signals</b>

The objective of this project is to use the signal library in order to be able to send data from a client to a server.


Since Signals were not made to be the main source of data stream communication both the client and server need to be made in a way the information
can be send flawlessly.

We can only use two signals from the library, SIGUSR1 and SIGUSR2 with the help of the kill system call. 
Data needs to be translated in binary with the help of the bitwise operations in c.
In the other end, server side, binary data needs to be converted again in order to be displayed in the standart output.

- <tt>125% completed (main and bonus)</tt>

- <tt>acknowledge response from client and return confirmation of all bytes read!</tt>

- <tt>Unicode support!</tt>

- <tt>Works with 100kb strings size</tt>
