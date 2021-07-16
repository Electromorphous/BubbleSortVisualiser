#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

using namespace std;

#define MAX 200	  // Number of values in the array
#define SPEED 201 // Speed of sorting, must be greater than MAX always

int a[MAX];		  // Array
int swapflag = 0; // Flag to check if swapping has occured
int i = 0, j = 0; // To iterate through the array
int sorting = 0;  // 1 if Sorted
char title[25];
int titleHeight = 800;

// Function to display text on screen
void bitmap_output(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// Function for converting integer to string
void int_str(int rad, char r[])
{
	sprintf(r, "%d", rad);
}

void display_text()
{
	glColor3f(1, 1, 1);
	strcpy(title, "BUBBLE SORT VISUALISER");

	char students[2][30];
	strcpy(students[0], "1AY18CS017 : Arthi Vinod");
	strcpy(students[1], "1AY18CS018 : Aseer Uz Zaman");
	bitmap_output(500, 65, students[0], GLUT_BITMAP_8_BY_13);
	bitmap_output(500, 45, students[1], GLUT_BITMAP_8_BY_13);

	if (sorting == 0)
	{
		char messages[3][25];
		strcpy(messages[0], "Press S to sort");
		strcpy(messages[1], "Press R to randomise");
		strcpy(messages[2], "Press Esc to quit");
		bitmap_output(20, 655, messages[0], GLUT_BITMAP_9_BY_15);
		bitmap_output(20, 625, messages[1], GLUT_BITMAP_9_BY_15);
		bitmap_output(20, 595, messages[2], GLUT_BITMAP_9_BY_15);
	}
	else if (sorting == 1)
	{
		char messages[2][25];
		strcpy(messages[0], "Sorting in progress...");
		strcpy(messages[1], "Press P to pause");
		bitmap_output(20, 655, messages[0], GLUT_BITMAP_9_BY_15);
		bitmap_output(20, 625, messages[1], GLUT_BITMAP_9_BY_15);
	}
}

void Initialize()
{
	for (int temp = 0; temp < MAX; temp++)
	{
		a[temp] = rand() % 100 + 1;
		// cout << a[temp] << " ";
	}
	// cout << endl;

	i = j = 0;

	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 699, 0, 799);
}

// Return 1 if not sorted
int notsorted()
{
	int q;
	for (q = 0; q < MAX - 1; q++)
	{
		if (a[q] > a[q + 1])
			return 1;
	}
	return 0;
}

void display()
{
	int ix, temp;
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	display_text();

	if (titleHeight > 700)
	{
		bitmap_output(275, titleHeight, title, GLUT_BITMAP_HELVETICA_18);
		titleHeight -= 7;
	}
	else
	{
		bitmap_output(275, 700, title, GLUT_BITMAP_HELVETICA_18);
	}

	char text[10];
	for (ix = 0; ix < MAX; ix++)
	{
		float red = 1.4 * a[ix] / 100.0;
		float blue = 25.0 / a[ix];
		float green = (0.1 / abs(0.5 - a[ix] / 100.0) - 0.15) * 2.0;
		if (red > 1.0)
			red = 1.0;
		if (green > 1.0)
			green = 1.0;
		if (blue > 1.0)
			blue = 1.0;
		// cout << red << " " << green << " " << blue << endl;
		glColor3f(red, green, blue);
		glBegin(GL_POLYGON);
		glVertex2f(50 + (700 / (MAX + 1)) * ix, 150);
		glVertex2f(50 + (700 / (MAX + 1)) * (ix + 1), 150);
		glVertex2f(50 + (700 / (MAX + 1)) * (ix + 1), 150 + a[ix] * 4);
		glVertex2f(50 + (700 / (MAX + 1)) * ix, 150 + a[ix] * 4);
		glEnd();

		// int_str(a[ix], text);
		// glColor3f(1, 1, 1);
		// bitmap_output(13 + (700 / (MAX + 1)) * ix, 135, text, GLUT_BITMAP_HELVETICA_10);
	}

	if (swapflag || sorting == 0)
	{
		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		glVertex2f(50 + (700 / (MAX + 1)) * j, 150);
		glVertex2f(50 + (700 / (MAX + 1)) * (j + 1), 150);
		glVertex2f(50 + (700 / (MAX + 1)) * (j + 1), 150 + a[j] * 4);
		glVertex2f(50 + (700 / (MAX + 1)) * j, 150 + a[j] * 4);
		glEnd();
		swapflag = 0;
	}
	glFlush();
}

void bubblesort()
{
	int temp;
	while (notsorted())
	{
		while (j < MAX - 1)
		{
			if (a[j] > a[j + 1])
			{
				swapflag = 1;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				goto A;
			}
			j++;
			if (j == MAX - 1)
				j = 0;
			// cout << "swap " << a[j] << " and " << a[j + 1] << endl;
		}
	}
	sorting = 0;
A:
	cout << "";
}

void makedelay(int)
{
	if (sorting)
		bubblesort();

	glutPostRedisplay();
	glutTimerFunc(SPEED / MAX, makedelay, 1);
}

void keyboard(unsigned char key, int x, int y)
{
	if (sorting != 1)
	{
		switch (key)
		{
		case 27:
			exit(0);
		case 's':
			sorting = 1;
			break;
		case 'r':
			Initialize();
			break;
		}
	}
	if (sorting == 1)
		if (key == 'p')
			sorting = 0;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bubble sort visualiser");
	Initialize();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000, makedelay, 1);
	glutMainLoop();

	return 0;
}
