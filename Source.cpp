/*==================================================================================================
/*=================================================================
COURSE: CSC 525, assignment# project 3
PROGRAMMERS:
	Noah McQuerter ~33%
		-Design idea
		-Code cleanup
		-Debugging
		-text
	Mohammed Hanash ~33%
		-Displaying cylinder
		-views
	Christian Leslie ~33%
		-Debugging
		-Menu System
 MODIFIED BY:			N/A

 LAST MODIFIED DATE:	12/09/2022

 DESCRIPTION:			Demo: drawing a soda can


 NOTE:					Should be stored in C:/Temp for proper execution of the program

 FILES:					main.cpp, (OpenGL_GLUT.sln, ...)

 IDE/COMPILER:			MicroSoft Visual Studio 2022

 INSTRUCTION FOR COMPILATION AND EXECUTION:

	1.		Double click on OpenGL_GLUT.sln	to OPEN the project

	2.      Click on the Local Windows Debugger Text or Button (Text in White) and Button is Trianguler in Green on the top menus second row

			centre to execute the program

==================================================================================================*/
/*========================================================================
1) The design should contain at least one 3D object and the objects in the design should
not come from only the previous labs.
2) All objects should be placed in a 3D space.
3) A user should be able to see different views of the objects/scene by moving either the
objects or the viewer through some interactive methods, such as mouse, keyboard, or
menu, etc.
4) All interactions between a user and the program should be through a graphics window,
rather than a CMD window.======================================================*/



#include <iostream>					// include iostream library

#include <GL/glut.h>				// include GLUT library

#include <GL/freeglut.h>

#include <string>					// include string class

#include <vector>					// include vector class

#include <math.h>

#include <stdio.h>

#include <stdlib.h> 





using namespace std;				// use namespace std



//********* Prototypes **************************************************************  

void myMenuCallback(int);



GLvoid* font = GLUT_BITMAP_8_BY_13; //default font 



//********* Predefined Variables ****************************************************  

int ViewId = 1;





// cylinder 



#define PI 3.1415927

void draw_cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B);

void displayCylinder(int view);

void displayCallback();

void reshape(int width, int height);



//Can Cocacola Dimensions - It is usually 6 centimeters in diameter and 12 centimeters in height for a content of 330 milliliters of liquid.

float radius = 0.25;  //3cm

float height = 1.00;   // 12 cm

float R = 190;

float G = 1;

float B = 27;

float logo_x = -0.25;

float logo_y = 0.70;



void displayHelpMessage(string);

vector <unsigned char> messages, helpMessage; // a vector to store the message

GLvoid* textFont = GLUT_BITMAP_TIMES_ROMAN_24;



//********* Subroutines *************************************************************

int main(int argc, char** argv)

{

	/** Initialize glut */



	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(640, 480);

	glutCreateWindow("Cocacola Cylinder");



	// prepare and display menu 

	// dispaly view type, Orthogonal or Perspective

	int view = glutCreateMenu(myMenuCallback);

	glutAddMenuEntry("Orthogonal", 1);

	glutAddMenuEntry("Perspective", 2);

	glutCreateMenu(myMenuCallback);



	glutAddSubMenu("View", view);

	glutAddMenuEntry("Reset", 3);

	glutAddMenuEntry("Exit", 4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);



	glClearColor(1.0, 1.0, 1.0, 0.0);

	glutDisplayFunc(displayCallback);

	glutReshapeFunc(reshape);



	glutMainLoop();



	return 0;

}



//*****************************************************************************

void myMenuCallback(int id)

{

	switch (id)

	{

	case 1:

	{

		displayCylinder(1);
		ViewId = 1;

	}

	break;



	case 2:

	{

		displayCylinder(2);
		ViewId = 2;

	}

	break;



	case 3:

	{

		displayCylinder(1);
		ViewId = 1;

	}

	break;



	case 4:

	{

		exit(0);

	}

	break;



	default:

		break;

	}

}





//************************************************************************************

//cylinder



void draw_cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B)

{

	/************************** draw_cylinder() **************************

	 * This function will draw the cylinder

	 *

	 *   @parameter1: radius = The radius of cylinder

	 *   @parameter2: height = Height of the cylinder

	 *   @parameter3: R = Red value of the cylinder's color

	 *   @parameter4: G = Green value of the cylinder's color

	 *   @parameter5: B = Blue value of the cylinder's color

	 *

	 *   @return: Nothing

	 */



	GLfloat x = 0.0;

	GLfloat y = 0.0;

	GLfloat angle = 0.0;

	GLfloat angle_stepsize = 0.1;



	/** Draw the tube */

	// red color for tube 



	glColor3ub(R, G, B);

	glBegin(GL_QUAD_STRIP);

	angle = 0.0;

	while (angle < 2 * PI) {

		x = radius * cos(angle);

		y = radius * sin(angle);

		glVertex3f(x, y, height);

		glVertex3f(x, y, 0.0);

		angle = angle + angle_stepsize;

	}

	glVertex3f(radius, 0.0, height);

	glVertex3f(radius, 0.0, 0.0);

	glEnd();



	/** Draw the circle on top of cylinder */

	//Use silver color for top

	R = 242; // 187;

	G = 245; // 194;

	B = 255; // 204;



	glColor3ub(R, G, B);

	glBegin(GL_POLYGON);

	angle = 0.0;

	while (angle < 2 * PI) {

		x = radius * cos(angle);

		y = radius * sin(angle);

		glVertex3f(x, y, height);

		angle = angle + angle_stepsize;

	}

	glVertex3f(radius, 0.0, height);

	glEnd();



	glRasterPos2f(logo_x + 0.1, logo_y + 0.2);

	glColor3ub(R, G, B);

	displayHelpMessage("Drink");



	glRasterPos2f(logo_x, logo_y - 0.1);

	glColor3ub(R, G, B);

	displayHelpMessage("Cocacola");

}





/**************************** display() ******************************

 * The glut callback function to draw the polygons on the screen.

 *

 *   @parameter1: Nothing

 *

 *   @return: Nothing

 */





void displayCylinder(int view)

{

	if (view == 1) {



		// show the cocacola display in Orthogonal view



		glClear(GL_COLOR_BUFFER_BIT);

		glLoadIdentity();



		glTranslatef(0.0, -0.4, -3.0);

		glRotatef(-60, 1.0, 0.0, 0.0);



		logo_x = -0.25;

		textFont = GLUT_BITMAP_TIMES_ROMAN_24;

		draw_cylinder(radius, height, R, G, B);



		glFlush();

	}

	else {



		// show the cocacola display in Perspective view



		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();



		gluLookAt(0, 0, 1, 0.0, 0.0, 0, 0, 1, 0);

		glPushMatrix();



		glTranslatef(0.0, -0.4, -3.0);

		glRotatef(-60, 1.0, 0.0, 0.0);



		logo_x = -0.20;

		textFont = GLUT_BITMAP_8_BY_13;



		draw_cylinder(radius, height, R, G, B);



		glPopMatrix();



		glFlush();

	}



}



void displayCallback() {

	displayCylinder(ViewId);

}





/**************************** reshape() ******************************

 * The glut callback function that responsible when the window is

 * resized.

 *

 *   @parameter1: width  = Current window's width

 *   @parameter2: height = Current window's height

 *

 *   @return: Nothing

 */

void reshape(int width, int height)

{

	if (width == 0 || height == 0) return;



	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(40.0, (GLdouble)width / (GLdouble)height, 0.5, 20.0);



	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, width, height);

}





void displayHelpMessage(string helpString)

{





	for (int i = 0; i < helpString.length(); i++)

	{

		helpMessage.push_back(helpString[i]);

	}





	for (int i = 0; i < helpMessage.size(); i++)

	{

		glutBitmapCharacter(textFont, helpMessage[i]);

	}



	helpMessage.clear();



}