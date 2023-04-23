/**
* Developer: Dennis Dao
* Date: Jan 18, 2022
* Student Nunber: 110010116
*/

// Program to implement Bresenham's Line Algorithm to work with any slope

#define GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLint xStart, yStart, xEnd, yEnd, temp;

typedef void (*GLUTdisplayCB) (void);

// Function prototypes
void myInit();
void readCoordinates();
void bresenhamLine();

// Driver function
int main(int argc, char **argv) {
	// Initialize glfw
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// Create window
	GLFWwindow* window = glfwCreateWindow(640, 480, "a1.c", NULL, NULL);

	if (!window) {
		// Failing to initialize a window
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// OpenGL output onto the created window
	glfwMakeContextCurrent(window);
	//Swap buffer interval to 1, useful for faster computers
	glfwSwapInterval(1);

	myInit();

	// Main event loop
	while (!glfwWindowShouldClose(window)) {
		// Draw line
		bresenhamLine();
		// Display
		glfwSwapBuffers(window);
		// Handle potential user input
		glfwPollEvents();
	}

	// Destroy window that is no longer needed
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}

void myInit() {
	// Assume coordinates will be entered by the user.
	readCoordinates();

	// Clear buffer with white
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// Draw color to black
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(2.0);

	// Matrix definition for window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

// Function to read user's input for coordinates
void readCoordinates(void) {
	printf("Enter coordinates of the endpoints of the line:\n");
	printf("Enter starting endpoint (x0, y0): ");
	scanf("%d%d", &xStart, &yStart);
	printf("Enter ending endpoint (x1, y1): ");
	scanf("%d%d", &xEnd, &yEnd);
}

// Function to implement Bresenham's line algorithm
void bresenhamLine(void) {
	// Correct endpoint order (x1 < x0; if right endpoint given before left endpoint)
	if (xEnd < xStart) {
		temp = xEnd;
		xEnd = xStart;
		xStart = temp;
		temp = yEnd;
		yEnd = yStart;
		yStart = temp;
	}

	// Calculate constants 
	GLint dX = xEnd - xStart, dY = yEnd - yStart;
	GLint doubleDY = dY * 2, doubleDX = dX * 2;
	GLint doubleDiffDXDY = doubleDY - doubleDX, pk = doubleDY - dX;
	GLint step, x, y;
	float m = dY / (float)dX;

	step = m > 0 ? 1 : -1;

	x = xStart;
	y = yStart;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	// Vertical line; dX=0
	if (dX == 0) {
		for (int i = yStart; i <= yEnd; i++) {
			glVertex2i(x, i);
		}
	}

	// Horizontal line; dY=0
	else if (dY == 0) {
		for (int i = xStart; i <= xEnd; i++) {
			glVertex2i(i, y);
		}
	}

	// |m| is greater than 1
	else if (fabs(m) > 1) {
		// Recalculate constants - exchange x and y values
		pk = dX - doubleDY;
		doubleDiffDXDY = doubleDX - doubleDY;

		// Positive slope
		if (yEnd > y) {
			while (y <= yEnd) {
				glVertex2i(x, y);
				y++;

				if (pk < 0) {
					if (doubleDX < 0) {
						pk = pk + abs(doubleDX);
					}
					else {
						pk = pk + doubleDX;
					}
				}
				else {
					x += step;
					pk += doubleDiffDXDY;
				}
			}
		}

		// Negative slope (x must step positively in this case and y decrements)
		else {
			// Retrieved from deriving the formula from the slides with a negative slope (-m) and interchanging roles of x and y
			doubleDY = abs(doubleDY);
			doubleDiffDXDY = doubleDX - doubleDY, pk = dX - doubleDY;

			while (y >= yEnd) {
				glVertex2i(x, y);
				y--;

				if (pk < 0) {
					pk += doubleDX;
				}
				else {
					x += 1;
					pk += doubleDiffDXDY;
				}
			}
		}
	}

	// |m| is 1
	else if (fabs(m) == 1) {
		// From starting positions, step along the x and add appropriate step to y
		// yStart < yEnd when slope is positive, yStart > yEnd when slope is negative
		for (int i = xStart, j = yStart; i <= xEnd && (j <= yEnd || j >= yEnd); i++, j += step) {
			glVertex2i(i, j);
		}
	}

	// |m| is between 0 and 1 (m is 0 already covered in horziontal and vertical cases)
	else if (fabs(m) > 0 && fabs(m) < 1) {
		// Retrieved from deriving the formula from the slides with a negative slope (-m)
		if (m < 0) {
			doubleDY = abs(doubleDY);
			doubleDiffDXDY = doubleDY - doubleDX, pk = doubleDY - dX;
		}

		while (x <= xEnd) {
			glVertex2i(x, y);
			x++;

			if (pk < 0) {
				pk += doubleDY;
			}
			else {
				y += step;
				pk += doubleDiffDXDY;
			}
		}
	}

	glEnd();
	glFlush();
}