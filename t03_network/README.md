# t03_network
SERVER BUILD PROGRAM @ v1.0  
Created by Sebastian Dichler, 2017  
  
Code snippets by M. Horauer, UAS Technikum Wien  
  
Server running on a preprocessor defined port (6778).  
It runs a user made program and makes it possible for networking.  

To build it use:
<pre>
make
</pre>
or
<pre>
clang -Wall --pedantic -D_POSIX_C_SOURCE=200809L server.c
clang -Wall --pedantic -D_POSIX_C_SOURCE=200809L serverprogram.c
clang -Wall --pedantic -D_POSIX_C_SOURCE=200809L client.c
</pre>

