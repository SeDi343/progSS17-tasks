# t04_gui_greeter
  
This is a simple GUI Program using GTK+3 libs, it asks for name and welcomes,  
you after pressing the OK Button.  
  
Compile the Program using  
<pre>
make
</pre>
or  
<pre>
glib-compile-resources --sourcedir=. greeter_res.gresource.xml --generate-source
gcc greeter_application.c greeter_res.c -lm `pkg-config --cflags --libs gtk+-3.0` -Wall -g -o greeter
</pre>
