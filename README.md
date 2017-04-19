# Programming SS17  

###### Everything appearing red is debug information  
  
## Uebungstasks  
------
### t01_semaphore  
Created by Sebastian Dichler, 2017  
  
Compiler input:  
<pre>
clang -Wall 016_semaphore_shared_memory_P2.c -o server.out  
clang -Wall 015_semaphore_shared_memory_P1.c -o client.out  
</pre>
  
Start server first before client!  
------
### t02_matrix_thread  
Created by Sebastian Dichler, 2017  
Change between Task with Preprocessor Varibales  
<pre>
./matrix -n MATRIXLENGTH  
</pre>
------
### t03_network  
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
clang -Wall --pedantic -D_POSIX_C_SOURCE=200809L demo.c
</pre>
