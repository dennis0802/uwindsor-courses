/**
* Developer: Dennis Dao 
* Date: March 25, 2023
* Student Number: 110010116
*/

// Graphics program to draw B-Spline curves
// Using the provided Bezier and editing to fit B-Spline

#define GLFW_INCLUDE_GLU

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLFW/glfw3.h>

// Function prototypes
void myInit();
void mouseManager(GLFWwindow*, int, int, int);
void displayFunc(void);
void makeMatrix(float**, float**);

GLint xc, yc, radius;
int i = 0;
float** A, ** c;  // matrix c is for the polynomial coefficients
float** points, u, x, y;
GLdouble selectedX, selectedY;
int drawCurve = 0, next = -3;

void displayFunc(void) {
    float u;
    int j, k;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    for (j = 1; j <= i; j++)
        glVertex2i((int)points[j][1], (int)points[j][2]);

    if (drawCurve) {
        glColor3f(0.0f, 1.0f, 1.0f); // set the drawing color to cyan
        // From Bezier - change to step by 1's to avoid missing sections
        for (j = 0; j <= next; j += 1) {
            if ((j + 4) <= i) {
                makeMatrix(c, points + j);

                for (u = 0.001; u < 1; u += 0.001) {
                    x = c[1][1] + c[2][1] * u + c[3][1] * u*u + c[4][1] * u*u*u;
                    y = c[1][2] + c[2][2] * u + c[3][2] * u*u + c[4][2] * u*u*u;

                    glVertex2i((int)(x + 0.5), (int)(y + 0.5));
                }
            }
        }
    }

    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    int i;

    // Initialize GLFW
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(640, 640, "B-Spline Curves Program (COMP3520 Project)", NULL, NULL);
    
    if (!window) {
        // Fail to initialize a window
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // OpenGL output onto the created window
    glfwMakeContextCurrent(window);
    // Swap buffer interval to 1
    glfwSwapInterval(1);
    glfwSetMouseButtonCallback(window, mouseManager);

    myInit();

    c = (float**)malloc(5 * sizeof(float*)); // create matrices c and points
    for (i = 1; i <= 4; i++)
        c[i] = (float*)malloc(5 * sizeof(float));
    points = (float**)malloc(100 * sizeof(float*));
    for (i = 1; i <= 99; i++)
        points[i] = (float*)malloc(3 * sizeof(float));

    // Main event loop
    while (!glfwWindowShouldClose(window)) {
        // Draw
        displayFunc();
        // Display
        glfwSwapBuffers(window);
        // Handle user input
        glfwPollEvents();
    }

    // Destroy window that is no longer needed
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set clear color to white 
    glColor3f(0.0f, 1.0f, 1.0f);      // set the drawing color to cyan
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);   // virtual camera 
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 640.0);
}

void mouseManager(GLFWwindow* window, int button, int action, int mods) {
    glfwGetCursorPos(window, &selectedX, &selectedY);
    y = 640 - selectedY;
    x = selectedX;

    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            if (drawCurve) {
                drawCurve = 0;
                next = -3;
                i = 0;
            }
            i++;
            points[i][1] = x;   // input coorinates of clicked control points
            points[i][2] = y;
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if (action == GLFW_PRESS) {
            drawCurve = 1;
            next += 3;
        }
        break;
    defaut:
        ;
    }
    displayFunc();
}

void makeMatrix(float** c, float** points) { // Use B-Spline Geometry Matrix
                                            // to calculate coefficients c                 
    // Using this, the midpoints will be drawn
    // ie. given control points 1,2,3,4; curve will go from 2-3
    c[1][1] = (points[1][1] + 4 * points[2][1] + points[3][1])/6;
    c[1][2] = (points[1][2] + 4 * points[2][2] + points[3][2])/6;

    c[2][1] = (3 * (points[3][1] - points[1][1]))/6;
    c[2][2] = (3 * (points[3][2] - points[1][2]))/6;

    c[3][1] = (3 * points[1][1] - 6 * points[2][1] + 3 * points[3][1])/6;
    c[3][2] = (3 * points[1][2] - 6 * points[2][2] + 3 * points[3][2])/6;

    c[4][1] = (-points[1][1] + 3 * points[2][1] - 3 * points[3][1] + points[4][1])/6;
    c[4][2] = (-points[1][2] + 3 * points[2][2] - 3 * points[3][2] + points[4][2])/6;
}
