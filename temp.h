

//
// This is my file with the heart of the diffution simulator. 
// It is where the explicit finite difference method is implemented
//





#include <stdio.h>
#include <stdlib.h>
//#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

// what i need

#include <iostream>
#include <vector>
#include <fstream>



using namespace std;

double dx = 1;
double dt = .01;
double r = .01;
double time_elapsed = 0;

class block
{

public:

//constructor
block(int x, int y, int z, double temp, double cgreen, double cblue, double diff);
//print block data
void print();
// draw block
void draw_one_cube();
//

// Position
int x_pos;
int y_pos;
int z_pos;

// blocks near it

int plus_z;
int minus_z;
int plus_y;
int minus_y;
int plus_x;
int minus_x;

int number_of_connections;

// HEAT

double heat;
double new_heat;

// Color (want to add up to .4 probably) 
double green;
double blue;

// K constant (diffition constant)
double diffution_rate;

};

//----------- functions for block ---------------
//constructor
block::block(int x, int y, int z, double temp, double cgreen, double cblue, double diff)
{
	x_pos = x; 
	y_pos = y;
	z_pos = z;
	
	// -1 is saying there is no block on that side
	plus_z = -1;
	minus_z = -1;
	plus_y = -1;
	minus_y = -1;
	plus_x = -1;
	minus_x = -1;
	
	number_of_connections = 0;

	heat = temp;
	new_heat = 0;

	green = cgreen;
	blue = cblue;
	diffution_rate = diff;
}

void block::print()
{
	cout << "x_pos = " << x_pos << ", y_pos = " << y_pos << ", z_pos = " << z_pos << ", temp = " << heat << ", new temp = " << new_heat << ",    plus_x = " << plus_x << ", minus_x = " << minus_x << ", plus_y = " << plus_y << ", minus_y = " << minus_y << ", plus_z = " << plus_z << ", minus_z = " << minus_z << ",    connections = " << number_of_connections << "\n";	
}

class room
{

public:
	
//constructor
room(string file_name);
//print room 
void veiw();
// check to see if overlapping positions
void check();
// look up position and see if block in it. return number of block
int look_up_pos(int x, int y, int z);
// calc bools
void find_bools();
// calc new heat for one block in vector
void new_heat(int i);
// calc temp for entire vector (easyer to break it up i thought)
void run_new_heat();
// make old temp new temp and new temp 0
void run_once();
// run one time step
void one_step();
// print to file
void print(string file_name);
// testing ----------------------------
void draw();
// testing ----------------------------
void setupDrawCallback();
// double testing
//static void test();

// vector of blocks
vector<block> room_blocks;



};


//----------- functions for room -----------------
// constructor
room::room(string file_name)
{
	// create stream to file
	ifstream reading;
	reading.open(file_name.c_str());
	// create vector	
	
	int x = 0;
	int y = 0;
	int z = 0;
	double heat = 0.0;
	double green = .2;
	double blue = .2;
	double diffution_rate = 1;
	reading >> dx >> dt;
	while(reading >> x >> y >> z >> heat >> green >> blue >> diffution_rate)
	{
	block f(x,y,z,heat, green, blue, diffution_rate);
	room_blocks.push_back(f);
	}
		
	reading.close();
	
	find_bools();
}
// prints position of data of blocks
void room::veiw()
{
	for(int i = 0; i < room_blocks.size(); i++)
	{
		room_blocks[i].print();
	}
}
// checks overlapping position of blocks
void room::check()
{	
	// not yet :P
}
// look up a position and return the number block in it. if none return -1
int room::look_up_pos(int x, int y, int z)
{
	for(int i = 0; i < room_blocks.size(); i++)
	{
		if((room_blocks[i].x_pos == x) && (room_blocks[i].y_pos == y) && (room_blocks[i].z_pos == z))
		{
			return i;
		}
	}
	return -1;
}
// finds the correct bool values
void room::find_bools()
{
	for(int i = 0; i < room_blocks.size(); i++)
	{
		room_blocks[i].plus_z = look_up_pos(room_blocks[i].x_pos, room_blocks[i].y_pos, room_blocks[i].z_pos + 1);
		room_blocks[i].minus_z = look_up_pos(room_blocks[i].x_pos, room_blocks[i].y_pos, room_blocks[i].z_pos - 1);
		room_blocks[i].plus_y = look_up_pos(room_blocks[i].x_pos, room_blocks[i].y_pos + 1, room_blocks[i].z_pos);
		room_blocks[i].minus_y = look_up_pos(room_blocks[i].x_pos, room_blocks[i].y_pos - 1, room_blocks[i].z_pos);
		room_blocks[i].plus_x = look_up_pos(room_blocks[i].x_pos + 1, room_blocks[i].y_pos, room_blocks[i].z_pos);
		room_blocks[i].minus_x = look_up_pos(room_blocks[i].x_pos - 1, room_blocks[i].y_pos, room_blocks[i].z_pos);
		
		if(room_blocks[i].plus_z != -1) {room_blocks[i].number_of_connections = room_blocks[i].number_of_connections + 1;}
		if(room_blocks[i].minus_z != -1) {room_blocks[i].number_of_connections = room_blocks[i].number_of_connections + 1;}
		if(room_blocks[i].plus_y != -1) {room_blocks[i].number_of_connections = room_blocks[i].number_of_connections + 1;}
		if(room_blocks[i].minus_y != -1) {room_blocks[i].number_of_connections = room_blocks[i].number_of_connections + 1;}
		if(room_blocks[i].plus_x != -1) {room_blocks[i].number_of_connections = room_blocks[i].number_of_connections + 1;}
		if(room_blocks[i].minus_x != -1) {room_blocks[i].number_of_connections = room_blocks[i].number_of_connections + 1;}
	}
}
// calc new heat for a given block
void room::new_heat(int i)
{
	r = room_blocks[i].diffution_rate*dt/(dx*dx);
	room_blocks[i].new_heat = 0;
	room_blocks[i].new_heat = room_blocks[i].heat * (1 - (room_blocks[i].number_of_connections * r));
	if(room_blocks[i].plus_z != -1) {room_blocks[i].new_heat = room_blocks[i].new_heat + (room_blocks[room_blocks[i].plus_z].heat * r);}
	if(room_blocks[i].minus_z != -1) {room_blocks[i].new_heat = room_blocks[i].new_heat + (room_blocks[room_blocks[i].minus_z].heat * r);}
	if(room_blocks[i].plus_y != -1) {room_blocks[i].new_heat = room_blocks[i].new_heat + (room_blocks[room_blocks[i].plus_y].heat * r);}
	if(room_blocks[i].minus_y != -1) {room_blocks[i].new_heat = room_blocks[i].new_heat + (room_blocks[room_blocks[i].minus_y].heat * r);}
	if(room_blocks[i].plus_x != -1) {room_blocks[i].new_heat = room_blocks[i].new_heat + (room_blocks[room_blocks[i].plus_x].heat * r);}
	if(room_blocks[i].minus_x != -1) {room_blocks[i].new_heat = room_blocks[i].new_heat + (room_blocks[room_blocks[i].minus_x].heat * r);}
	 
}
// running the new heat for the whole thing
void room::run_new_heat()
{
	for(int i = 0; i < room_blocks.size(); i++)
	{
		new_heat(i);
	}
}
// make new temp old temp and new temp 0
void room::run_once()
{
	for(int i = 0; i < room_blocks.size(); i++)
	{
		room_blocks[i].heat = room_blocks[i].new_heat;
		room_blocks[i].new_heat = 0;
	}
}
// run one time step
void room::one_step()
{
	run_new_heat();
	run_once();
}
//print it to a file
void room::print(string file_name)
{
	// create stream to file
	ofstream reading;
	reading.open(file_name.c_str());
	// create vector	
	reading << dx << " " << dt << "\n";
	for(int i = 0; i < room_blocks.size(); i++)
	{
		reading << room_blocks[i].x_pos << " " << room_blocks[i].y_pos << " " << room_blocks[i].z_pos << " " << room_blocks[i].heat << " " << room_blocks[i].green << " " << room_blocks[i].blue << " " << room_blocks[i].diffution_rate << "\n";
	}	
		
	reading.close();
}








