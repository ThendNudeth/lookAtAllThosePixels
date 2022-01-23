# lookAtAllThosePixels
My framebuffer and graphics journey in C.

# Running the program
The application directly alters the system's framebuffer.
If you have any gui or window manager running, any output from the program will most likely be overwritten.
In order to use the app we have to disable the gui.

On my (ubuntu) machine I use:
```console
foo@bar:~$ sudo service gdm stop
```

This will result in a blank screen. Now we need to start a new shell.
Again, on my machine I use <kbd>CTRL</kbd>+<kbd>ALT</kbd>+<kbd>F2</kbd>

Now navigate to the root project directory and compile the program with:
```console
foo@bar:~\lookAtAllThosePixels$ make
```

and to run the program:
```console
foo@bar:~\lookAtAllThosePixels$ sudo ./bar
```
