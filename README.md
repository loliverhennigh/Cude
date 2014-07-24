

To compile my code you should just run the make script I sent with it.
Thats right, its a scrip and not a make file haha. You will need the 
install opengl 3.0 as well as glut for the libraries. This shouldn't be
to hard and there is lots of support for this.

When you run my program it will prompt you to input the name of a txt file.
I have included several that should work for testing purposes. The txt 
file are structured so the first line is dx spacing then the dt time
steps. The next rows have three ints as x y z coordinates followed by the current 
temp and blue and green values. The last digit of the line is the diffusion 
constant of that block. A higher constant means it will heat and cool 
faster. Be careful to keep these values fairly low or the simulation
will become unstable. Here is an example of a text file with comments

(dx) 1 (dt).001
(x,y,z)0 0 0 (temp)0.0 (green, blue).2 .2 (diffusion constant)1
0 0 1 0.0 .2 .2 1
0 1 0 0.0 .2 .2 1
0 1 1 0.0 .2 .2 1
1 0 0 0.0 .2 .2 1
1 0 1 0.0 .2 .2 1
1 1 0 0.0 .2 .2 1
1 1 1 0.0 .2 .2 1
0 0 -1 0.0 .2 .2 1
0 -1 0 0.0 .2 .2 1
0 -1 -1 0.0 .2 .2 1
-1 0 0 0.0 .2 .2 1
-1 0 -1 0.0 .2 .2 1
-1 -1 0 0.0 .2 .2 1
-1 -1 -1 10.0 .2 .2 1


My program uses an explicit approximation of the heat equation. This is 
very simple and I highly encourage you to look it up Online. 

Here is a list of commands my program supports

```
t = one time step

f = ten time steps

r = zoom out (need to do this to see Cup.txt clearly)

e = zoom in

p = print file with current temps (prints to file name ending in the current time)

1 = full screen

2 = exit full screen

arrows = rotate

w,a,s,d = move around (doesn't work well, stick with arrow keys)

```

good luck :)







