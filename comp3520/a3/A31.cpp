/**
* Developer: Dennis Dao
* Date: March 2, 2023
* Student Number: 110010116
*/

// Program to create a 3D model of a meeting room

#define GLFW_INCLUDE_GLU
constexpr auto room = 20;

#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "draw.h";

// Function prototypes
void keyManager(GLFWwindow*, int, int, int, int);
void drawFrame(void);

// Lighting variables
float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
float diffuse[] = { 0.9f, 0.8f, 0.5f, 1.0f };
float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
float spot_dir[] = { 0, -1, 0 };

// First light source
float light0_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
float light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//float light0_position[] = { 0,6,0, 1.0 };
float light0_position[] = { 0, 10, 0, 1.0 };

const GLfloat eyeXMax = room, eyeZMax = room, eyeXMin = -room, eyeZMin = -room;
GLfloat eyeX = -room, eyeY = 9.0, eyeZ = room;

int main(int argc, const char* argv[]) {
    if (!glfwInit())
        exit(EXIT_FAILURE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Meeting Room Model (COMP3520 Assignment 3)", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, keyManager);

    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, (GLsizei)640, (GLsizei)480);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0, 0, 0);
    glPointSize(1.0);

    /* Add perspective, adjust camera position */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 640 / (float)480, 1, 60);
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0);

    /* Apply information for first light */
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    /* Apply global ambient lighting */
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    /* More options as needed */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.001f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0018f);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);

    /* Enable lighting */
    glEnable(GL_LIGHTING);

    /* Enable first light */
    glEnable(GL_LIGHT0);

    /* Set the shader to smooth */
    glShadeModel(GL_SMOOTH);

    // The main event loop
    while (!glfwWindowShouldClose(window))
    {
        // Keep running and drawing
        drawFrame();

        //Display
        glfwSwapBuffers(window);

        //Handle the possible user input etc.
        glfwPollEvents();
    }

    //Destroy the window that you are no longer needed
    glfwDestroyWindow(window);

    //terminate glfw
    //Just before exiting the your program, you should shut down glfw
    glfwTerminate();
    return 0;
}

void drawFrame() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 640 / (float)480, 1, 60);
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0); // Used to "point the eye" based on camera position / center view / up direction

    // GL_MODELVIEW defines how your objects are transformed (meaning translation, rotation and scaling) in the world coordinate frame
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef((GLfloat)0, 1, 0, 0);
    glRotatef((GLfloat)0, 0, 1, 0);

    drawOffice(room);
    drawDoor(room, 0);
    drawDoor(room, 1);
    drawWhiteboard(room);
    drawTable();
    drawCube();
    drawPaper(1, -1, 1, 90);
    drawPaper(5, -1, 3, 45);
    drawPaper(-1, -1, 2, 60);
    drawPaper(-4, -1, -2, 20);
    drawLaptop(0, -1, 2, 90);
    drawLaptop(10, -1, 9, 15);

    drawChair(-12, -10, 5, 0);
    drawChair(-12, -10, -5, 0);
    drawChair(12, -10, -5, 180);
    drawChair(12, -10, 5, 180);
    drawChair(3, -10, 3, -90);
    drawChair(4, -10, 6, 90);

    drawSecCam(room);
    drawLightFixture();
    glPopMatrix();
    glFlush();
}

/* Keyboard Controls:        */
/* ------------------------- */
// Assuming the user starts at the front of the room (keys 1-4 required):
// Press 1 to go to front left camera (Front's left side)
// Press 2 to go to front right camera (front's right side)
// Press 3 to go to back left camera (back's right side)
// Press 4 to go to back right camera (back's left side)
// Press 5 or S to increase eyeZ
// Press 6 or W to decrease eyeZ
// Press 7 or D to increase eyeX
// Press 8 or A to decrease eyeX
// Press ESC to exit the program

/**
* For context:
* (-X, -Z) x--------D---------x (+X, -Z)
*          |3                4|
*          |                  |
*          |        T         WB
*          |                  |
*          |1                2|
* (-X, +Z) x--------D---------x (+X, +Z)
*/

// Manage keyboard input from user
void keyManager(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    /**
        We only process keyboard keys when they are pressed or repeated.
    **/
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
        return;

    switch (key) {
    case GLFW_KEY_1:
        eyeX = -room;
        eyeZ = room;
        break;
    case GLFW_KEY_2:
        eyeX = room;
        eyeZ = room;
        break;
    case GLFW_KEY_3:
        eyeX = -room;
        eyeZ = -room;
        break;
    case GLFW_KEY_4:
        eyeX = room;
        eyeZ = -room;
        break;
    case GLFW_KEY_5:
    case GLFW_KEY_S:
        if (eyeZ < eyeZMax) {
            if (++eyeZ == 0) { eyeZ = 1; }
        }
        break;
    case GLFW_KEY_6:
    case GLFW_KEY_W:
        if (eyeZ > eyeZMin) {
            if (--eyeZ == 0) { eyeZ = -1; }
        }
        break;
    case GLFW_KEY_7:
    case GLFW_KEY_D:
        if (eyeX < eyeXMax) {
            eyeX++;
        }
        break;
    case GLFW_KEY_8:
    case GLFW_KEY_A:
        if (eyeX > eyeXMin) {
            eyeX--;
        }
        break;
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    }
}
