
Man page client and server 
------------------------------
Programs from the getaddrinfo man page https://man7.org/linux/man-pages/man3/getaddrinfo.3.html.
Run them like this.  The server just mirrors the information that it receives back to the client.

gcc manpage_server.c && ./a.out 3490
gcc manpage_client.c && ./a.out 127.0.0.1 3490 hello

