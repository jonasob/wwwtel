# wwwtel

In 1995, I was 18 years old and working the summer at Ericsson Telecom AB
in Norrköping. With a background from using and running BBS systems,
together with an interest in role playing games, I'd gotten hooked on
text based role playing adventures online over the past year.

All of them required you to connect to them using a normal TCP/IP connection
on a non-standard port. Typically a non-privileged port, 5000, or 5678, or
something easily recognizable.

Being an extraordinarily slow summer (I believe it was the last summer I
worked for Ericsson), most of us summer workers had plenty of time to spare
in any given working day. Unfortunately, the firewall at Ericsson only allowed
you to connect to the outside world using a proxy, which in itself only
allowed connections on port 80 (HTTP).

This software was my way to escape that prison. It's a telnet gateway for
the web. It constituted a number of CGI scripts which ran server side at
my home. When browsing the server, you're faced with a web page divided into
two frames, an upper part which contains the output from the telnet connction,
and a lower part with an input field and submit button.

Entering something in the input field and submitting it, sends it to a CGI
script on the server side which communicates over a pipe to the process managing
the telnet connection, and then sending whatever you typed into there to the
telnet connection.
