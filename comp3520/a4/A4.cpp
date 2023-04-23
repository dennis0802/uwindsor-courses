/**
* Developer: Dennis Dao
* Date: March 14, 2023
* Student Number: 110010116
*/

// Program to create a 3D model of a meeting room, now extended with 3 lights, one being distant and can be toggled on/off by the user
// Texture will be added where possible

#define GLFW_INCLUDE_GLU
constexpr auto room = 20;
unsigned char *woodData, *carpetData;
int woodWidth, woodHeight, carpetWidth, carpetHeight, nrChannelsW, nrChannelsC;

#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "draw.h";

// From sources:
// https://learnopengl.com/Getting-started/Textures
// https://github.com/nothings/stb/blob/master/stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Image sources
// Wood: https://opengameart.org/content/seamless-wood-textures-wood01png
// Carpet: https://opengameart.org/content/arcade-carpet-textures-carpet2512png

// Function prototypes
void keyManager(GLFWwindow*, int, int, int, int);
void drawFrame(void);

// Lighting variables
float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
float diffuse[] = { 0.9f, 0.8f, 0.5f, 1.0f };
float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
float spot_dir[] = { 0, -1, 0 };

// Light source info
float light0_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
float light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float light0_position[] = { 0, 10, 0, 1.0 };

float light1_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
float light1_diffuse[] = { 0.3f, 1.0f, 1.0f, 1.0f };
float light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float light1_position[] = { 0, 10, 0, 1.0 };

float light2_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
float light2_diffuse[] = { 0.1, 0.1f, 0.1f, 1.0f };
float light2_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float light2_position[] = { 0, 10, 0, 1.0 };

const GLfloat eyeXMax = room, eyeZMax = room, eyeXMin = -room, eyeZMin = -room;
GLfloat eyeX = -room, eyeY = 9.0, eyeZ = room;
GLint light0Flag = 0, light1Flag = 0, light2Flag = 0;

int main(int argc, const char* argv[]) {
    if (!glfwInit())
        exit(EXIT_FAILURE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Meeting Room Model Extended (COMP3520 Assignment 4)", NULL, NULL);

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

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

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

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.001f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0018f);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);

    /* Enable lighting */
    glEnable(GL_LIGHTING);

    /* Enable first light */
    glEnable(GL_LIGHT0);
    light0Flag = 1;

    /* Set the shader to smooth */
    glShadeModel(GL_SMOOTH);

    // Load wood texture
    woodData = stbi_load("Wood01.png", &woodWidth, &woodHeight, &nrChannelsW, 0);
    carpetData = stbi_load("Carpet.png", &carpetWidth, &carpetHeight, &nrChannelsC, 0);

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
// For lights, only 1 light will be enabled at a time (ie. turn on light 0 will disable 1 and 2)
// Press I to toggle light 0 (normal spotlight)
// Press O to toggle light 1 (cyan-ish spotlight)
// Press P to toggle light 2 (distant light)
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
    case GLFW_KEY_I:
        if (light0Flag) {
            light0Flag = 0;
            glDisable(GL_LIGHT0);
        }
        else {
            light0Flag = 1;
            light1Flag = 0;
            light2Flag = 0;
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
            glEnable(GL_LIGHT0);
        }
        break;
    case GLFW_KEY_O:
        if (light1Flag) {
            light1Flag = 0;
            glDisable(GL_LIGHT1);
        }
        else {
            light0Flag = 0;
            light2Flag = 0;
            light1Flag = 1;
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT2);
            glEnable(GL_LIGHT1);
        }
        break;
    case GLFW_KEY_P:
        if (light2Flag) {
            light2Flag = 0;
            glDisable(GL_LIGHT2);
        }
        else {
            light0Flag = 0;
            light1Flag = 0;
            light2Flag = 1;
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            glEnable(GL_LIGHT2);
        }
        break;
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    }
}
