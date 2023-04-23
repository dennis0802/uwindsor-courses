/**
 * Developer: Dennis Dao
 * Date: February 12, 2023
 * Student Number: 110010116
 */

// Graphics program to simulate predator and prey

#define GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLint preyPresent = 0, predatorPresent = 0, windowLength = 640, windowHeight = 480, predatorScale = 10;
GLint preyDx, preyDy, predatorDx, predatorDy, tookEscape = 0;
GLint outerPer[6][2] = { {50,100}, {550, 100}, {550, 225}, {550, 275}, {550, 400}, {50, 400} };
GLint innerPer[4][2] = { {100,150}, {500, 150}, {500, 350}, {100, 350} };
GLdouble preyX, preyY, predatorX, predatorY;

// For this program, assume the path will be divided into 5 sections as follows:
/*
*      L T T T T T R
*      L           R
*      L           R E E E
*      L           R
*      L B B B B B R
* 
*	L = left path
*	R = right path
*	T = top path
*	B = bottom path
*	E = escape route (no spawning prey here)
*   Clicking anywhere outside of the L, R, T, and B pathways will not spawn anything
*/

// Function prototypes
void myInit();
void mouseManager(GLFWwindow*, int, int, int);
void drawMap(void);
void drawPrey(void);
void drawPredator(void);
void preyIdle(void);
void predatorIdle(void);
int withinClickBoundary(GLdouble, GLdouble);

int main(void) {
	// Initialize glfw
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// Create window
	GLFWwindow* window = glfwCreateWindow(windowLength, windowHeight, "Predator-Prey Simulation (COMP3520 Assignment 2)", NULL, NULL);
	glfwSetWindowPos(window, 100, 150);

	if (!window) {
		// Failing to initialize a window
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// OpenGL output onto the created window
	glfwMakeContextCurrent(window);
	//Swap buffer interval to 1, useful for faster computers
	glfwSwapInterval(1);
	glfwSetMouseButtonCallback(window, mouseManager);

	myInit();

	// Main event loop
	while (!glfwWindowShouldClose(window)) {
		// Drawing functions
		drawMap();

		if (preyPresent) {
			drawPrey();
			preyIdle();
		}
		if (predatorPresent) {
			drawPredator();
			predatorIdle();
		}

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

// Initialize glfw
void myInit() {
	// Clear buffer with white
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(2.0);

	// Matrix definition for window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

// Handle mouse input
void mouseManager(GLFWwindow* window, int button, int action, int mods) 
{
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		// Only when left click is pressed, NOT released
		if (action == GLFW_PRESS) {

			// Spawn prey if none exist
			if (!preyPresent) {
				// Get cursor coordinate and check within the pathway
				glfwGetCursorPos(window, &preyX, &preyY);
				if (withinClickBoundary(preyX, preyY)) {
					preyPresent = 1;

					// Left path
					if (preyX >= 50 && preyX <= 100 && preyY >= 85 && preyY <= 385) {
						preyX = 70;
						preyDy = 3;
						// Corner cases
						if (preyY > 360) {
							preyY = 350;
						}
						else if (preyY < 105) {
							preyY = 105;
						}
					}
					// Right path
					else if (preyX >= 490 && preyX <= 550 && preyY >= 85 && preyY <= 400) {
						preyX = 525;
						preyDy = -3;
						// Corner cases
						if (preyY > 360) {
							preyY = 350;
						}
						else if (preyY < 105) {
							preyY = 105;
						}
					}
					// Bottom path
					else if (preyX >= 100 && preyX <= 500 && preyY >= 335 && preyY <= 380) {
						preyY = 350;
						preyDx = 3;
					}
					// Top path
					else if (preyX >= 100 && preyX <= 500 && preyY >= 85 && preyY <= 130) {
						preyY = 105;
						preyDx = -3;
					}
				}
			}

			// Spawn predator if none exist
			else if(preyPresent && !predatorPresent) {
				// Get cursor coordinate and check within the pathway
				glfwGetCursorPos(window, &predatorX, &predatorY);
				if (withinClickBoundary(predatorX, predatorY)) {
					predatorPresent = 1;

					// Left path
					if (predatorX >= 50 && predatorX <= 100 && predatorY >= 85 && predatorY <= 385) {
						predatorX = 80;
						predatorDy = 6;
						// Corner cases
						if (predatorY > 345) {
							predatorY = 345;
						}
						else if (predatorY < 105) {
							predatorY = 105;
						}
					}
					// Right path
					else if (predatorX >= 490 && predatorX <= 550 && predatorY >= 85 && predatorY <= 400) {
						predatorX = 525;
						predatorDy = -6;
						// Corner cases
						if (predatorY > 345) {
							predatorY = 345;
						}
						else if (predatorY < 105) {
							predatorY = 105;
						}
					}
					// Bottom path
					else if (predatorX >= 100 && predatorX <= 500 && predatorY >= 335 && predatorY <= 380) {
						predatorY = 350;
						predatorDx = 6;
					}
					// Top path
					else if (predatorX >= 100 && predatorX <= 500 && predatorY >= 85 && predatorY <= 130) {
						predatorY = 105;
						predatorDx = -6;
					}
				}
			}
		}
		break;
	default:;
	}
}

// Draw the map
void drawMap(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	// Pathway drawing
	// Outer perimeter  - assume a 500x300 layout
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);

	for (int i = 0; i < 6; i++) {
		// Prevent (550, 225) to (550, 275) from being drawn in the loop, aka the exit
		if (i == 2) {
			continue;
		}
		// Segment connecting back to start
		else if (i == 5) {
			glVertex2i(outerPer[i][0], outerPer[i][1]);
			glVertex2i(outerPer[0][0], outerPer[0][1]);
		}
		// General case
		else {
			glVertex2i(outerPer[i][0], outerPer[i][1]);
			glVertex2i(outerPer[i + 1][0], outerPer[i + 1][1]);
		}
	}

	// Exit path
	glVertex2i(550, 225);
	glVertex2i(640, 225);

	glVertex2i(550, 275);
	glVertex2i(640, 275);
	
	glEnd();

	// Inner perimeter - assume a 400x200 rectangle
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < 4; i++) {
		glVertex2i(innerPer[i][0], innerPer[i][1]);
	}

	glEnd();
	glFlush();
}

// Draw prey
void drawPrey(void) {
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);

	// The centroid of the prey is (preyX, windowHeight-preyY)
	// Vertical orientation
	if(preyDy != 0){
		glVertex2i(preyX - 5, windowHeight - preyY - 10);
		glVertex2i(preyX + 5, windowHeight - preyY - 10);
		glVertex2i(preyX + 5, windowHeight - preyY + 10);
		glVertex2i(preyX - 5, windowHeight - preyY + 10);
	}
	// Horizontal orientation
	else {
		glVertex2i(preyX - 10, windowHeight - preyY - 5);
		glVertex2i(preyX + 10, windowHeight - preyY - 5);
		glVertex2i(preyX + 10, windowHeight - preyY + 5);
		glVertex2i(preyX - 10, windowHeight - preyY + 5);
	}

	glEnd();
	glFlush();
}

// Prey behaviour
void preyIdle(void){
	// Movement behaviour
	preyX += preyDx;
	preyY += preyDy;

	// Collision behaviour
	// Left wall
	if (preyX < 75 && preyDx == -3) {
		preyDx = 0;
		preyDy = 3;
	}

	// Bottom wall
	else if (preyY > 350 && preyDy == 3) {
		preyDx = 3;
		preyDy = 0;
	}

	// Top wall, no predator
	else if (preyY < 110 && preyDy == -3 && !tookEscape) {
		preyDx = -3;
		preyDy = 0;
	}

	// Top wall, predator present, and strictly the bottom right area
	// Assume it is forced to go through the counter-clockwise path
	else if (preyY > 225 && preyY < 235 && preyDy == -3 && predatorPresent) {
		preyDx = 3;
		preyDy = 0;
		tookEscape = 1;
	}

	// Escaped to the right
	else if (preyX > 665 && preyPresent) {
		tookEscape = 0;
		preyPresent = 0;
		preyDx = 0;
		// Scale down the predator by 10% (multiply current by 90%)
		predatorScale *= 0.9;

		// Extra - if predator becomes too small, it vanishes, simulating that it starved
		if (predatorScale <= 5) {
			predatorPresent = 0;
			predatorScale = 10;
			predatorDx = 0;
			predatorDy = 0;
		}
	}

	// Right wall - not escaping
	else if (preyX > 525 && preyDx == 3 && !tookEscape) {
		preyDx = 0;
		preyDy = -3;
	}
}

// Draw predator
void drawPredator(void) {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);

	// The centroid of the predator is (predatorX, windowHeight-predatorY)
	// Facing left
	if (predatorDx == -6) {
		glVertex2i(predatorX - predatorScale, windowHeight - predatorY);
		glVertex2i(predatorX + predatorScale, windowHeight - predatorY + predatorScale);
		glVertex2i(predatorX + predatorScale, windowHeight - predatorY - predatorScale);
	}
	// Facing right
	else if (predatorDx == 6) {
		glVertex2i(predatorX + predatorScale, windowHeight - predatorY);
		glVertex2i(predatorX - predatorScale, windowHeight - predatorY + predatorScale);
		glVertex2i(predatorX - predatorScale, windowHeight - predatorY - predatorScale);
	}
	// Facing down
	else if (predatorDy == 6) {
		glVertex2i(predatorX, windowHeight - predatorY - predatorScale);
		glVertex2i(predatorX + predatorScale, windowHeight - predatorY + predatorScale);
		glVertex2i(predatorX - predatorScale, windowHeight - predatorY + predatorScale);
	}
	// Facing up
	else if (predatorDy == -6) {
		glVertex2i(predatorX, windowHeight - predatorY + predatorScale);
		glVertex2i(predatorX - predatorScale, windowHeight - predatorY - predatorScale);
		glVertex2i(predatorX + predatorScale, windowHeight - predatorY - predatorScale);
	}

	glEnd();
	glFlush();
}

// Predator behaviour
void predatorIdle(void) {

	// Move only if prey exists
	if (preyPresent) {
		predatorX += predatorDx;
		predatorY += predatorDy;
	}

	// Colliding with walls
	// Left wall
	if (predatorX < 80 && predatorDx == -6) {
		predatorDx = 0;
		predatorDy = 6;
	}

	// Bottom wall
	else if (predatorY > 355 && predatorDy == 6) {
		predatorDx = 6;
		predatorDy = 0;
	}

	// Right wall
	else if (predatorX > 520 && predatorDx == 6) {
		predatorDx = 0;
		predatorDy = -6;
	}

	// Top wall
	else if (predatorY < 110 && predatorDy == -6) {
		predatorDx = -6;
		predatorDy = 0;
	}

	// Eating the prey (given that getting exact coordinates will be difficult, allow the predator's scale to be the buffer in front of the predator)
	if (abs(predatorX - preyX) <= predatorScale && abs(predatorY - preyY) <= predatorScale && preyPresent) {
		preyPresent = 0;
		preyDx = 0;
		preyDy = 0;
		// Scale up the predator by 25%
		if (predatorScale < 25) {
			predatorScale *= 1.25f;
		}
	}
}

// Utility function to check if coordinate clicked is in within the path
int withinClickBoundary(GLdouble coordX, GLdouble coordY) {

	// Left path
	return (coordX >= 50 && coordX <= 100 && coordY >= 85 && coordY <= 380) ||
		// Right path
		(coordX >= 490 && coordX <= 550 && coordY >= 85 && coordY <= 380) ||
		// Bottom path
		(coordX >= 100 && coordX <= 500 && coordY >= 335 && coordY <= 380) || 
		// Top path
		(coordX >= 100 && coordX <= 500 && coordY >= 85 && coordY <= 130) 
	? 1 : 0;
}

/*
* 	glTranslatef(175 + tx, 125.0 + ty, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(-(175 + tx), -(125.0 + ty), 0.0);
*/