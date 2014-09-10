# Cude

This program is designed to visual heat transfer in objects. It uses an explicit approximation of the heat equation. When the program is run it will ask for a text file of the simulation. There are two tests text files included, Cup.txt and test.txt.

 
## Sample Tests

Here is an example of a txt file it would run

```
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
```

Here is the resulting simulation


![ScreenShot](https://github.com/loliverhennigh/Cude/blob/master/test.png)

Here is the simulation of the txt file Cup.txt

![ScreenShot](https://github.com/loliverhennigh/Cude/blob/master/Cup.png)


## Commands

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

## How to compile

Here are the steps,

```
make
```
and to exacute
```
./cude
```
you will need opengl 3.0 and glut. On Ubuntu all you need to do is run
```
sudo apt-get install freeglut3-dev
```








