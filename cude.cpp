//
// File:        cude.cpp
// Author:      Oliver Hennigh
// Created:     6/1/2013
// Project:     Diffution simulator
// Description: Creates an OpenGL window and object
//              
// 
// Controls:    Left Arrow  - Rotate Left
//              Right Arrow - Rotate Right
//              Up Arrow    - Rotate Up
//              Down Arrow  - Rotate Down     
//
//
//

// ----------------------------------------------------------
// Includes
// ----------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "temp.h"


#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib,"glut32.lib")      


using namespace std;



double scale = 1;
 room test("q");
// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();
 
// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;
double xtranslate = 0;
double ytranslate = 0;
double ztranslate = 0;

int width = 200;
int height = 400;

int lastX = 150;
int lastY = 150;

double scale_change = .1;

bool in_full_screen = 0;

string file_name;

void drawStrokeText(char*string,int x,int y,int z);

string to_string(int number);

void drawText(const char * message, double x, double y, double z);

string heat = "temp ";
string timey = "time in milli seconds = 0";
const char *mess = timey.c_str();
const char *temp = heat.c_str();
// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){
 //  Clear screen and Z-buffer
 
  // Reset transformations
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
/*   
  glBegin(GL_QUADS);
	glColor3f(1,1,1);
	glVertex3f(0,0,-.4);
	glVertex3f(.1,0,-.4);
	glVertex3f(.1,.1,-.4);
	glVertex3f(0,.1,-.4);
  glEnd();
*/
  glColor3f(1,1,1);
//  glPushMatrix();
//  glTranslatef(0,0,-4);
  drawText(mess,-.9,-.9,-1);
//  glPopMatrix();
  glLoadIdentity();    
  // Rotate when user changes rotate_x and rotate_y
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );
  // Movement
  glTranslatef(xtranslate,ytranslate,ztranslate);
  // Scale stuff
  glScalef(scale_change,scale_change,scale_change);
 
  //Multi-colored side - FRONT
  glPushMatrix();
  for (int i = 0; i < test.room_blocks.size(); i++)
  { 
  	glBegin(GL_QUADS);
  	glColor3f(   test.room_blocks[i].heat,  test.room_blocks[i].green, test.room_blocks[i].blue );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
 	glEnd(); 

	glBegin(GL_QUADS);
  	glColor3f(   test.room_blocks[i].heat,  test.room_blocks[i].green, test.room_blocks[i].blue );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
 	glEnd(); 



  	glBegin(GL_QUADS);
  	glColor3f(   test.room_blocks[i].heat,  test.room_blocks[i].green, test.room_blocks[i].blue );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
 	glEnd(); 
	 
  	glBegin(GL_QUADS);
  	glColor3f(   test.room_blocks[i].heat,  test.room_blocks[i].green, test.room_blocks[i].blue );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
 	glEnd(); 

  	glBegin(GL_QUADS);

  	glColor3f(   test.room_blocks[i].heat,  test.room_blocks[i].green, test.room_blocks[i].blue );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos,  dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
 	glEnd(); 

  	glBegin(GL_QUADS);
  	glColor3f(   test.room_blocks[i].heat,  test.room_blocks[i].green, test.room_blocks[i].blue );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f(  dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos,  dx + 2*dx*test.room_blocks[i].z_pos );
  	glVertex3f( -dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos );
 	glEnd(); 




  }
/*
  glPopMatrix();
  for (int i = 0; i < test.room_blocks.size(); i++)
  {

//	glScalef(10,10,10);	
	glColor3f(1,1,1);
	drawText(temp, -dx + 2*dx*test.room_blocks[i].x_pos, -dx + 2*dx*test.room_blocks[i].y_pos, -dx + 2*dx*test.room_blocks[i].z_pos - .001);
  }
*/
  glFlush();
  glutSwapBuffers();
 
}


void drawText(const char * message, double x, double y, double z)
{
	/* raster pos sets the current raster position
	 * mapped via the modelview and projection matrices
	 */
	glRasterPos3d((GLdouble)x, (GLdouble)y, (GLdouble)z);
	glColor3f(1,1,1);
	/*
	 * write using bitmap and stroke chars
	 */
	while (*message) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *message);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*message++);
	}
}

 
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys( int key, int x, int y ) {
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;
 
  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 5;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;
 
  //  Request display update
  glutPostRedisplay();
 
}

void timeMaker(unsigned char key, int x, int y)
{
	if (key ==  't')
	{
		test.one_step();
		time_elapsed += dt;
		timey = "time in milli sec = ";
		timey.append(to_string(time_elapsed*1000000));
		
		mess = timey.c_str();
	}
	if (key == 'f')
	{
		for (int i = 0; i < 10; i++)
		{
			test.one_step();
			time_elapsed += dt;
		}	
		
		timey = "time in milli sec = ";
		timey.append(to_string(time_elapsed*1000000));
		mess = timey.c_str();

	}
	if (key == 'g')
	{
		for (int i = 0; i < 100; i++)
		{
			test.one_step();
			time_elapsed += dt;
		}	
		
		timey = "time in milli sec = ";
		timey.append(to_string(time_elapsed*1000000));
		mess = timey.c_str();

	}

	if(key == 'w') 
	{
		ztranslate += 0.02*cos(rotate_y*M_PI/180);
		xtranslate -= 0.02*sin(rotate_y*M_PI/180);	
	}
	if(key == 's')
	{
		ztranslate -= 0.02*cos(rotate_y*M_PI/180);
		xtranslate += 0.02*sin(rotate_y*M_PI/180);
	}
	if(key == 'a')
	{
		xtranslate += 0.02*cos(rotate_y*M_PI/180);
		ztranslate += 0.02*sin(rotate_y*M_PI/180);	
	}
	if(key == 'd')
	{
		xtranslate -= 0.02*cos(rotate_y*M_PI/180);
		ztranslate -= 0.02*sin(rotate_y*M_PI/180);
	}

	if (rotate_y > 360) rotate_y -= 360;
	else if (rotate_y < -360) rotate_y += 360;

	if(key == 'e')
	{
		scale_change += .001;
	}
	if(key == 'r')
	{
		scale_change -= .001;
	}

	glutPostRedisplay();
	if(key == '1')
	{
		glutFullScreen();
		in_full_screen = 1;
	}
	if(key == '2')
	{
		glutPositionWindow(0,0);
		in_full_screen = 0;
	}
	if(key == 'p')
	{
		string p = file_name; 
		p.append("_");
		string str = to_string(time_elapsed*1000000);
		p.append(str);
		p.append(".txt");
		test.print(p);
		timey.append("   printed to ");
		timey.append(p);
		mess = timey.c_str();
	}
	// text stuff
//	glFontBegin(font);
//  	glScalef(8.0, 8.0, 8.0);
//  	glTranslatef(30, 30, 0);
//  	glFontTextOut("Test", 5, 5, 0);




  glFlush();

}

string to_string(int number){
    string number_string = "";
    char ones_char;
    int ones = 0;
    while(true){
        ones = number % 10;
        switch(ones){
            case 0: ones_char = '0'; break;
            case 1: ones_char = '1'; break;
            case 2: ones_char = '2'; break;
            case 3: ones_char = '3'; break;
            case 4: ones_char = '4'; break;
            case 5: ones_char = '5'; break;
            case 6: ones_char = '6'; break;
            case 7: ones_char = '7'; break;
            case 8: ones_char = '8'; break;
            case 9: ones_char = '9'; break;
        }
        number -= ones;
        number_string = ones_char + number_string;
        if(number == 0){
            break;
        }
        number = number/10;
    }
    return number_string;
}


void prompt()
{
	cout << "Hi there, This is Eddy youre ship board computer! Just follow my directions \n";
	cout << "Enter the text file you want to read data from \n";
	cin >> file_name;
	cout << "Hope that works, I have no error checking :) \n";
	cout << "if its blank then you probably didnt enter the correct file. Have a Great Day ;) \n";
	room makeing(file_name);
	test = makeing;
}
 
void mouse_movements(int x, int y)
{

	int deltaX = x - lastX;
	int deltaY = y - lastY;

	lastX = x;
	lastY = y;

	if( deltaX == 0 && deltaY == 0 ) return;

	int windowX		= glutGet( GLUT_WINDOW_X );
	int windowY		= glutGet( GLUT_WINDOW_Y );
	int screenWidth		= glutGet( GLUT_SCREEN_WIDTH );
	int screenHeight	= glutGet( GLUT_SCREEN_HEIGHT );

	int screenLeft = -windowX;
	int screenTop = -windowY;
	int screenRight = screenWidth - windowX;
	int screenBottom = screenHeight - windowY;

	if( x <= screenLeft+10 || (y) <= screenTop+10 || x >= screenRight-10 || y >= screenBottom - 10) {
		lastX = 150;
		lastY = 150;
		glutWarpPointer( lastX, lastY );
		//	If on Mac OS X, the following will also work (and CGwarpMouseCursorPosition seems faster than glutWarpPointer).
		//	CGPoint centerPos = CGPointMake( windowX + lastX, windowY + lastY );
		//	CGWarpMouseCursorPosition( centerPos );
		// Have to re-hide if the user touched any UI element with the invisible pointer, like the Dock.
		//	CGDisplayHideCursor(kCGDirectMainDisplay);
	}

	rotate_x += deltaX;
	rotate_y -= deltaY;

	/*
	glutWarpPointer(150,150);	


	cout << "x is " << x << "\n";
	cout << "y is " << y << "\n";;
	rotate_x += x*.001;
	rotate_y += y*.001;	

        glutPostRedisplay();
	*/
}




void drawStrokeText(char*string,int x,int y,int z)
{
          char *c; 
          glPushMatrix();
          glTranslatef(x, y,z);
          glScalef(0.09f,-0.08f,z);
  
          for (c=string; *c != '\0'; c++)
          {   
                glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
          }   
          glPopMatrix();
}

// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){

  //  Prompt function
  prompt(); 

  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Create window
  glutCreateWindow("Awesome Cube");

  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);
 
  glutSetCursor(GLUT_CURSOR_CROSSHAIR);
  // Callback functions
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
  glutKeyboardFunc(timeMaker);
//  glutMotionFunc(mouse_movements); 

  //  Pass control to GLUT for events
  glutMainLoop();
 
  //  Return to OS
  return 0;
 
}
