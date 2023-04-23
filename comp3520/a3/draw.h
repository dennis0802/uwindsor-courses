void normalize(float* v);
void crossProduct(float* a, float* b, float* c, float* n);
void changeColor(float cx, float cy, float cz);
void drawPlane(float* a, float* b, float* c, float* d);
void drawOffice(float roomLength);
void drawTable(void);
void drawCube(void);
void drawLightFixture(void);
void drawPaper(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);
void drawLaptop(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);
void drawChair(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);
void drawDoor(float room, int flag);
void rotationVertex(GLfloat x, GLfloat y, GLfloat z, GLfloat xrot, GLfloat zrot, GLfloat angle);

/*
    Normalize function for the cross product below
*/
void normalize(float* v) {
    float mg;
    int i;

    // Length of vector
    mg = (float)(sqrt(pow((double)v[0], 2.0) + pow((double)v[1], 2.0) + pow((double)v[2], 2.0)));

    if (mg != 0)
        // Divide by length to normalize
        for (i = 0; i < 3; i++)
            v[i] /= mg;
    else {
        printf("division by Zero\n");
        exit(0);
    }
}

/*
    Cross product to find the normal,
    then saved in n after we normalize.
*/
void crossProduct(float* a, float* b, float* c, float* n) {

    n[0] = (b[1] - a[1]) * (c[2] - a[2]) - (b[2] - a[2]) * (c[1] - a[1]);
    n[1] = (b[2] - a[2]) * (c[0] - a[0]) - (b[0] - a[0]) * (c[2] - a[2]);
    n[2] = (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]);

    normalize(n);
}

/*
    Draw a quadrilateral and apply the normals for shading.
    This function takes 4 verticles (a, b, c and d)
    each with 3 components (x, y, z).
*/
void drawPlane(float* a, float* b, float* c, float* d) {
    float n[3];
    crossProduct(a, b, c, n);
    glNormal3fv(n);

    glBegin(GL_POLYGON);

    glVertex3fv(a); /* half the quadrilateral (Triangle) */
    glVertex3fv(b);
    glVertex3fv(c);

    glEnd();

    crossProduct(a, c, d, n);
    glNormal3fv(n);

    glBegin(GL_POLYGON);

    glVertex3fv(a); /* Other half of quadrilateral */
    glVertex3fv(c);
    glVertex3fv(d);

    glEnd();
}

/*
    This function applies colour to your lighting
    by changing the diffuse colour.
*/
void changeColor(float cx, float cy, float cz) {

    float amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diff[] = { cx, cy, cz, 1.0f };
    float spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Specify reflection parameters
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

// Utility function to place a vertex after applying it in a rotation matrix around the y-axis
void rotationVertex(GLfloat x, GLfloat y, GLfloat z, GLfloat xrot, GLfloat zrot, GLfloat angle) {
    GLfloat tempAngle = angle * 3.14159265 / 180;

    // Draw (x,y,z) with an angle rotation around the y-axis, using xrot and zrot as the rotation axis
    glVertex3f(x * cos(tempAngle) - z * sin(tempAngle) + xrot*(1-cos(tempAngle)) + zrot * sin(tempAngle), y,
            x * sin(tempAngle) + z * cos(tempAngle) + zrot*(1-cos(tempAngle) - xrot * sin(tempAngle)));
}

// Function to draw the room
void drawOffice(float roomLength) {
    float a[3], b[3], c[3], d[3]; // 4 vertices for each plane

    changeColor(0.4f, 0.6f, 0.7f);

    a[0] = -roomLength; a[1] = roomLength;       a[2] = roomLength;
    b[0] = roomLength;  b[1] = roomLength;       b[2] = roomLength;
    c[0] = roomLength;  c[1] = -roomLength;       c[2] = roomLength;
    d[0] = -roomLength; d[1] = -roomLength;       d[2] = roomLength;
    drawPlane(a, b, c, d);

    a[0] = roomLength; a[1] = 10;       a[2] = -roomLength; // (7, 7, -7)
    b[0] = -roomLength;  b[1] = 10;     b[2] = -roomLength; // (-7, 7, -7)
    c[0] = -roomLength;  c[1] = -10;    c[2] = -roomLength; // (-7, -7, -7)
    d[0] = roomLength; d[1] = -10;      d[2] = -roomLength; // (7, -7, -7)
    drawPlane(a, b, c, d);

    a[0] = -roomLength; a[1] = 10;       a[2] = roomLength;
    b[0] = roomLength;  b[1] = 10;       b[2] = roomLength;
    c[0] = roomLength;  c[1] = 10;       c[2] = -roomLength;
    d[0] = -roomLength; d[1] = 10;       d[2] = -roomLength;
    drawPlane(a, b, c, d);

    a[0] = -roomLength; a[1] = 10;       a[2] = roomLength;
    b[0] = -roomLength;  b[1] = -10;       b[2] = roomLength;
    c[0] = -roomLength;  c[1] = -10;       c[2] = -roomLength;
    d[0] = -roomLength; d[1] = 10;       d[2] = -roomLength;
    drawPlane(a, b, c, d);

    a[0] = roomLength; a[1] = -10;       a[2] = roomLength;
    b[0] = roomLength;  b[1] = 10;       b[2] = roomLength;
    c[0] = roomLength;  c[1] = 10;       c[2] = -roomLength;
    d[0] = roomLength; d[1] = -10;       d[2] = -roomLength;
    drawPlane(a, b, c, d);

    changeColor(0.9, 0.9, 0.9);
    a[0] = -roomLength; a[1] = -10;       a[2] = roomLength;
    b[0] = roomLength;  b[1] = -10;       b[2] = roomLength;
    c[0] = roomLength;  c[1] = -10;       c[2] = -roomLength;
    d[0] = -roomLength; d[1] = -10;       d[2] = -roomLength;
    drawPlane(a, b, c, d);
}

// Function to draw a whiteboard
void drawWhiteboard(float room) {
    glBegin(GL_QUADS);
    GLfloat vertex[][3] = { {room - 0.01, 7.0, 10.0}, {room - 0.01, 7.0, -10.0}, {room - 0.01, 0.0, -10.0}, {room - 0.01, 0.0, 10.0}};
    changeColor(1.0, 1.0, 1.0);
    drawPlane(vertex[0], vertex[1], vertex[2], vertex[3]);
    changeColor(0.0, 0.0, 0.0);
    // Marker streak on the whiteboard
    glBegin(GL_LINE_STRIP);
    changeColor(1.0, 0, 0);
    glVertex3f(19.89, 4.0, -9);
    glVertex3f(19.89, 4.0, 1);
    glVertex3f(19.89, 3.0, -1);
    glEnd();

    glBegin(GL_LINE_STRIP);
    changeColor(0, 1.0, 0);
    glVertex3f(19.89, 4.0, -9);
    glVertex3f(19.89, 2.0, 1);
    glVertex3f(19.89, 3.0, -1);
    glEnd();

    glBegin(GL_POINTS);
    changeColor(0, 0, 1.0);
    GLfloat theta, z, zCentre = 4, y, yCentre = 4, negZ, negY;
    for (theta = 0; theta <= 3.14f / 4; theta += 1 / (float)20) {
        z = zCentre + 2 * cos(theta);
        y = yCentre + 2 * sin(theta);
        negZ = zCentre - 2 * cos(theta);
        negY = yCentre - 2 * sin(theta);

        // Top right
        glVertex3f(19.89, y, z);
        glVertex3f(19.89, negY, z);

        // Bottom right
        glVertex3f(19.89, z, y);
        glVertex3f(19.89, negZ, y);

        // Top left
        glVertex3f(19.89, z, negY);
        glVertex3f(19.89, negZ, negY);

        // Bottom left
        glVertex3f(19.89, y, negZ);
        glVertex3f(19.89, negY, negZ);
    }
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(19.89, 5, 5);
    glVertex3f(19.89, 4, 5);
    glVertex3f(19.89, 5, 3);
    glVertex3f(19.89, 4, 3);
    glVertex3f(19.89, 3, 3);
    glVertex3f(19.89, 3, 5);
    glEnd();
}

// Function to draw a table
void drawTable(void) {
    float a[3], b[3], c[3], d[3]; // 4 vertices for each plane

    changeColor(0.5f, 0.3f, 0.2f);

    a[0] = -room / 2; a[1] = -1.01;       a[2] = room / 4;
    b[0] = room / 4 + 1;  b[1] = -1.01;       b[2] = room / 4;
    c[0] = room / 4 + 1;  c[1] = -1.5;       c[2] = room / 4;
    d[0] = -room / 2; d[1] = -1.5;       d[2] = room / 4;
    drawPlane(a, b, c, d);

    a[0] = room / 4 + 1; a[1] = -1.01;       a[2] = -room / 2;
    b[0] = -room / 2;  b[1] = -1.01;     b[2] = -room / 2;
    c[0] = -room / 2;  c[1] = -1.5;    c[2] = -room / 2;
    d[0] = room / 4 + 1; d[1] = -1.5;      d[2] = -room / 2;
    drawPlane(a, b, c, d);

    a[0] = -room / 2; a[1] = -1.01;       a[2] = room / 4;
    b[0] = room / 4 + 1;  b[1] = -1.01;       b[2] = room / 4;
    c[0] = room / 4 + 1;  c[1] = -1.01;       c[2] = -room / 2;
    d[0] = -room / 2; d[1] = -1.01;       d[2] = -room / 2;
    drawPlane(a, b, c, d);

    a[0] = -room / 2; a[1] = -1.01;       a[2] = room / 4;
    b[0] = -room / 2;  b[1] = -1.5;       b[2] = room / 4;
    c[0] = -room / 2;  c[1] = -1.5;       c[2] = -room / 2;
    d[0] = -room / 2; d[1] = -1.01;       d[2] = -room / 2;
    drawPlane(a, b, c, d);

    a[0] = room / 4 + 1; a[1] = -1.5;       a[2] = room / 4;
    b[0] = room / 4 + 1;  b[1] = -1.01;       b[2] = room / 4;
    c[0] = room / 4 + 1;  c[1] = -1.01;       c[2] = -room / 2;
    d[0] = room / 4 + 1; d[1] = -1.5;       d[2] = -room / 2;
    drawPlane(a, b, c, d);

    // Table leg
    a[0] = -room / 4; a[1] = -10;       a[2] = room / 8;
    b[0] = -room / 4;  b[1] = -1.5;       b[2] = room / 8;
    c[0] = -room / 4;  c[1] = -1.5;       c[2] = -room / 4;
    d[0] = -room / 4; d[1] = -10;       d[2] = -room / 4;
    drawPlane(a, b, c, d);

    a[0] = room / 8; a[1] = -1.5;       a[2] = room / 8;
    b[0] = room / 8;  b[1] = -10;       b[2] = room / 8;
    c[0] = room / 8;  c[1] = -10;       c[2] = -room / 4;
    d[0] = room / 8; d[1] = -1.5;       d[2] = -room / 4;
    drawPlane(a, b, c, d);

    a[0] = -room / 4; a[1] = -10;       a[2] = room / 8;
    b[0] = room / 8;  b[1] = -10;       b[2] = room / 8;
    c[0] = room / 8;  c[1] = -1.5;       c[2] = room / 8;
    d[0] = -room / 4; d[1] = -1.5;       d[2] = room / 8;
    drawPlane(a, b, c, d);

    a[0] = room / 8; a[1] = -10;       a[2] = -room / 4;
    b[0] = -room / 4;  b[1] = -10;     b[2] = -room / 4;
    c[0] = -room / 4;  c[1] = -1.5;    c[2] = -room / 4;
    d[0] = room / 8; d[1] = -1.5;      d[2] = -room / 4;
    drawPlane(a, b, c, d);
}

// Function to draw a cube
void drawCube(void) {
    changeColor(1.0, 0.0, 0.0);
    GLfloat cubeFace1[][4] = { {1.0, 1.0, -2.0},{3.0, 1.0, -2.0},{3.0, -1.0, -2.0},{1.0, -1.0, -2.0} };
    drawPlane(cubeFace1[0], cubeFace1[1], cubeFace1[2], cubeFace1[3]);

    changeColor(0.0, 1.0, 0.0);
    GLfloat cubeFace2[][4] = { {1.0, 1.0, -4.0},{3.0, 1.0, -4.0},{3.0, -1.0, -4.0},{1.0, -1.0, -4.0} };
    drawPlane(cubeFace2[0], cubeFace2[1], cubeFace2[2], cubeFace2[3]);

    changeColor(0.0, 0.0, 1.0);
    GLfloat cubeFace3[][4] = { {1.0, 1.0, -2.0},{3.0, 1.0, -2.0},{3.0, 1.0, -4.0},{1.0, 1.0, -4.0} };
    drawPlane(cubeFace3[0], cubeFace3[1], cubeFace3[2], cubeFace3[3]);

    changeColor(0.0, 1.0, 1.0);
    GLfloat cubeFace4[][4] = { {3.0, 1.0, -2.0},{3.0, 1.0, -4.0},{3.0, -1.0, -4.0},{3.0, -1.0, -2.0} };
    drawPlane(cubeFace4[0], cubeFace4[1], cubeFace4[2], cubeFace4[3]);

    changeColor(0.5, 0.5, 0.5);
    GLfloat cubeFace5[][4] = { {1.0, -1.0, -2.0},{3.0, -1.0, -2.0},{3.0, -1.0, -4.0},{1.0, -1.0, -4.0} };
    drawPlane(cubeFace5[0], cubeFace5[1], cubeFace5[2], cubeFace5[3]);
}

// Function to draw a light fixture on the ceiling
void drawLightFixture(void) {
    float a[3], b[3], c[3], d[3]; // 4 vertices for each plane

    changeColor(1.0f, 1.0f, 1.0f);

    a[0] = -3; a[1] = 10;       a[2] = 3;
    b[0] = 3;  b[1] = 10;       b[2] = 3;
    c[0] = 3;  c[1] = 9.5;       c[2] = 3;
    d[0] = -3; d[1] = 9.5;       d[2] = 3;
    drawPlane(a, b, c, d);

    a[0] = 3; a[1] = 10;       a[2] = -3;
    b[0] = -3;  b[1] = 10;     b[2] = -3;
    c[0] = -3;  c[1] = 9.5;    c[2] = -3;
    d[0] = 3; d[1] = 9.5;      d[2] = -3;
    drawPlane(a, b, c, d);

    a[0] = -3; a[1] = 9.5;       a[2] = 3;
    b[0] = 3;  b[1] = 9.5;       b[2] = 3;
    c[0] = 3;  c[1] = 9.5;       c[2] = -3;
    d[0] = -3; d[1] = 9.5;       d[2] = -3;
    drawPlane(a, b, c, d);

    a[0] = -3; a[1] = 10;       a[2] = 3;
    b[0] = -3;  b[1] = 9.5;       b[2] = 3;
    c[0] = -3;  c[1] = 9.5;       c[2] = -3;
    d[0] = -3; d[1] = 10;       d[2] = -3;
    drawPlane(a, b, c, d);

    a[0] = 3; a[1] = 9.5;       a[2] = 3;
    b[0] = 3;  b[1] = 10;       b[2] = 3;
    c[0] = 3;  c[1] = 10;       c[2] = -3;
    d[0] = 3; d[1] = 9.5;       d[2] = -3;
    drawPlane(a, b, c, d);
}

// Function to draw security cameras in the 4 corners
void drawSecCam(float room) {
    changeColor(0.5, 0.5, 0.5);
    GLUquadric* quad;
    quad = gluNewQuadric();

    glTranslatef(-room, 10, -room);
    gluSphere(quad, 1, 10, 10);
    glTranslatef(room, -10, room);

    glTranslatef(room, 10, -room);
    gluSphere(quad, 1, 10, 10);
    glTranslatef(-room, -10, room);

    glTranslatef(room, 10, room);
    gluSphere(quad, 1, 10, 10);
    glTranslatef(-room, -10, -room);

    glTranslatef(-room, 10, room);
    gluSphere(quad, 1, 10, 10);
    glTranslatef(room, -10, -room);
}

// Function to draw papers on a table given a location and angle in degrees
// (Assume the y is the top of the table and the overall location is the centre of the page)
void drawPaper(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
    glBegin(GL_QUADS);
    changeColor(1.0, 1.0, 1.0);
    rotationVertex(x - 1, y, z + 2, x, z, angle);
    rotationVertex(x - 1, y, z - 2, x, z, angle);
    rotationVertex(x + 1, y, z - 2, x, z, angle);
    rotationVertex(x + 1, y, z + 2, x, z, angle);

    glEnd();

    glBegin(GL_LINES);
    changeColor(0.0, 0.0, 0.0);
    rotationVertex(x - 0.5, y, z - 1, x, z, angle);
    rotationVertex(x + 0.5, y, z + 1, x, z, angle);

    rotationVertex(x + 0.5, y, z, x, z, angle);
    rotationVertex(x, y, z, x, z+0.1, angle);

    glEnd();
}

// Function to draw a laptop on a table given a location and angle
// Assume the y is the top of the table and the overall location is the centre of the laptop's keyboard section
void drawLaptop(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
    glBegin(GL_QUADS);
    changeColor(0.9, 0.9, 0.9);
    // Laptop keyboard base
    for (int i = 0; i < 10; i++) {
        rotationVertex(x - 7, y + 0.01 * i, z + 8, x, z, angle);
        rotationVertex(x - 7, y + 0.01 * i, z + 4, x, z, angle);
        rotationVertex(x - 4, y + 0.01 * i, z + 4, x, z, angle);
        rotationVertex(x - 4, y + 0.01 * i, z + 8, x, z, angle);
    }

    // Laptop screen
    changeColor(0.8, 0.8, 0.8);
    for (int i = 0; i < 5; i++) {
        rotationVertex(x - 3 + 0.01 * i, y + 3, z + 4, x, z, angle);
        rotationVertex(x - 3 + 0.01 * i, y + 3, z + 8, x, z, angle);
        rotationVertex(x - 4 + 0.01 * i, y + 0.1, z + 8, x, z, angle);
        rotationVertex(x - 4 + 0.01 * i, y + 0.1, z + 4, x, z, angle);
    }

    changeColor(0.1, 0.1, 0.1);
    
    rotationVertex(x - 3.1, y + 2.8, z + 4.3, x, z, angle);
    rotationVertex(x - 3.1, y + 2.8, z + 7.7, x, z, angle);
    rotationVertex(x - 4, y + 0.3, z + 7.7, x, z, angle);
    rotationVertex(x - 4, y + 0.3, z + 4.3, x, z, angle);

    glEnd();
}

// Function to draw chairs given a location and angle
// (Assume the y passed is the ground level and the overall location is the centre of the seat)
// The chair has armrests, doesn't roll
void drawChair(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
    glBegin(GL_QUADS);
    changeColor(0.5, 0.5, 0.6);
    // Main seat
    rotationVertex(x - 3, y + 4, z - 3, x, z, angle);
    rotationVertex(x + 3, y + 4, z - 3, x, z, angle);
    rotationVertex(x + 3, y + 4, z + 3, x, z, angle);
    rotationVertex(x - 3, y + 4, z + 3, x, z, angle);
    
    rotationVertex(x - 3, y + 3, z - 3, x, z, angle);
    rotationVertex(x + 3, y + 3, z - 3, x, z, angle);
    rotationVertex(x + 3, y + 3, z + 3, x, z, angle);
    rotationVertex(x - 3, y + 3, z + 3, x, z, angle);
   
    rotationVertex(x - 3, y + 4, z - 3, x, z, angle);
    rotationVertex(x - 3, y + 3, z - 3, x, z, angle);
    rotationVertex(x - 3, y + 3, z + 3, x, z, angle);
    rotationVertex(x - 3, y + 4, z + 3, x, z, angle);
    
    rotationVertex(x + 3, y + 4, z - 3, x, z, angle);
    rotationVertex(x + 3, y + 3, z - 3, x, z, angle);
    rotationVertex(x + 3, y + 3, z + 3, x, z, angle);
    rotationVertex(x + 3, y + 4, z + 3, x, z, angle);
    
    rotationVertex(x - 3, y + 4, z - 3, x, z, angle);
    rotationVertex(x - 3, y + 3, z - 3, x, z, angle);
    rotationVertex(x + 3, y + 3, z - 3, x, z, angle);
    rotationVertex(x + 3, y + 4, z - 3, x, z, angle);
    
    rotationVertex(x - 3, y + 4, z + 3, x, z, angle);
    rotationVertex(x - 3, y + 3, z + 3, x, z, angle);
    rotationVertex(x + 3, y + 3, z + 3, x, z, angle);
    rotationVertex(x + 3, y + 4, z + 3, x, z, angle);

    // Armrest
    // Back arm
    changeColor(0.8, 0.8, 0.8);
    rotationVertex(x+3, y+4, z-3, x, z, angle);
    rotationVertex(x+3, y+6, z-3, x, z, angle);
    rotationVertex(x+2.5, y+6, z-3, x, z, angle);
    rotationVertex(x+2.5, y+4, z-3, x, z, angle);
    
    rotationVertex(x+3, y+4, z-2.5, x, z, angle);
    rotationVertex(x+3, y+6, z-2.5, x, z, angle);
    rotationVertex(x+2.5, y+6, z-2.5, x, z, angle);
    rotationVertex(x+2.5, y+4, z-2.5, x, z, angle);
    
    rotationVertex(x+3, y+4, z-3, x, z, angle);
    rotationVertex(x+3, y+6, z-3, x, z, angle);
    rotationVertex(x+3, y+6, z-2.5, x, z, angle);
    rotationVertex(x+3, y+4, z-2.5, x, z, angle);

    
    rotationVertex(x+2.5, y+4, z-3, x, z, angle);
    rotationVertex(x+2.5, y+6, z-3, x, z, angle);
    rotationVertex(x+2.5, y+6, z-2.5, x, z, angle);
    rotationVertex(x+2.5, y+4, z-2.5, x, z, angle);

    // Front arm
    rotationVertex(x+3, y+4, z+3, x, z, angle);
    rotationVertex(x+3, y+6, z+3, x, z, angle);
    rotationVertex(x+2.5, y+6, z+3, x, z, angle);
    rotationVertex(x+2.5, y+4, z+3, x, z, angle);

    rotationVertex(x+3, y+4, z+2.5, x, z, angle);
    rotationVertex(x+3, y+6, z+2.5, x, z, angle);
    rotationVertex(x+2.5, y+6, z+2.5, x, z, angle);
    rotationVertex(x+2.5, y+4, z+2.5, x, z, angle);

    rotationVertex(x+3, y+4, z+3, x, z, angle);
    rotationVertex(x+3, y+6, z+3, x, z, angle);
    rotationVertex(x+3, y+6, z+2.5, x, z, angle);
    rotationVertex(x+3, y+4, z+2.5, x, z, angle);

    rotationVertex(x+2.5, y+4, z+3, x, z, angle);
    rotationVertex(x+2.5, y+6, z+3, x, z, angle);
    rotationVertex(x+2.5, y+6, z+2.5, x, z, angle);
    rotationVertex(x+2.5, y+4, z+2.5, x, z, angle);

    // Back armrest
    changeColor(0.5, 0.5, 0.5);
    rotationVertex(x-2.5, y+6, z-4, x, z, angle);
    rotationVertex(x-2.5, y+6, z-2.5, x, z, angle);
    rotationVertex(x+3, y+6, z-2.5, x, z, angle);
    rotationVertex(x+3, y+6, z-4, x, z, angle);

    rotationVertex(x-2.5, y+6.5, z-4, x, z, angle);
    rotationVertex(x-2.5, y+6.5, z-2.5, x, z, angle);
    rotationVertex(x+3, y+6.5, z-2.5, x, z, angle);
    rotationVertex(x+3, y+6.5, z-4, x, z, angle);

    rotationVertex(x-2.5, y+6.5, z-4, x, z, angle);
    rotationVertex(x-2.5, y+6, z-4, x, z, angle);
    rotationVertex(x+3, y+6, z-4, x, z, angle);
    rotationVertex(x+3, y+6.5, z-4, x, z, angle);

    rotationVertex(x-2.5, y+6.5, z-2.5, x, z, angle);
    rotationVertex(x-2.5, y+6, z-2.5, x, z, angle);
    rotationVertex(x+3, y+6, z-2.5, x, z, angle);
    rotationVertex(x+3, y+6.5, z-2.5, x, z, angle);

    // Front armrest
    rotationVertex(x-2.5, y+6, z+4, x, z, angle);
    rotationVertex(x-2.5, y+6, z+2.5, x, z, angle);
    rotationVertex(x+3, y+6, z+2.5, x, z, angle);
    rotationVertex(x+3, y+6, z+4, x, z, angle);

    rotationVertex(x-2.5, y+6.5, z+4, x, z, angle);
    rotationVertex(x-2.5, y+6.5, z+2.5, x, z, angle);
    rotationVertex(x+3, y+6.5, z+2.5, x, z, angle);
    rotationVertex(x+3, y+6.5, z+4, x, z, angle);

    rotationVertex(x-2.5, y+6.5, z+4, x, z, angle);
    rotationVertex(x-2.5, y+6, z+4, x, z, angle);
    rotationVertex(x+3, y+6, z+4, x, z, angle);
    rotationVertex(x+3, y+6.5, z+4, x, z, angle);

    rotationVertex(x-2.5, y+6.5, z+2.5, x, z, angle);
    rotationVertex(x-2.5, y+6, z+2.5, x, z, angle);
    rotationVertex(x+3, y+6, z+2.5, x, z, angle);
    rotationVertex(x+3, y+6.5, z+2.5, x, z, angle);

    // Back
    // Back front
    changeColor(0.8, 0.8, 0.8);
    rotationVertex(x-3, y+4, z+3, x, z, angle);
    rotationVertex(x-3, y+7, z+3, x, z, angle);
    rotationVertex(x-2.5, y+7, z+3, x, z, angle);
    rotationVertex(x-2.5, y+4, z+3, x, z, angle);
    
    rotationVertex(x-3, y+4, z+2.5, x, z, angle);
    rotationVertex(x-3, y+7, z+2.5, x, z, angle);
    rotationVertex(x-2.5, y+7, z+2.5, x, z, angle);
    rotationVertex(x-2.5, y+4, z+2.5, x, z, angle);

    rotationVertex(x-3, y+7, z+2.5, x, z, angle);
    rotationVertex(x-3, y+4, z+2.5, x, z, angle);
    rotationVertex(x-3, y+4, z+3, x, z, angle);
    rotationVertex(x-3, y+7, z+3, x, z, angle);

    
    rotationVertex(x-2.5, y+7, z+2.5, x, z, angle);
    rotationVertex(x-2.5, y+4, z+2.5, x, z, angle);
    rotationVertex(x-2.5, y+4, z+3, x, z, angle);
    rotationVertex(x-2.5, y+7, z+3, x, z, angle);

    // Back back
    
    rotationVertex(x-3, y+4, z-3, x, z, angle);
    rotationVertex(x-3, y+7, z-3, x, z, angle);
    rotationVertex(x-2.5, y+7, z-3, x, z, angle);
    rotationVertex(x-2.5, y+4, z-3, x, z, angle);

    
    rotationVertex(x-3, y+4, z-2.5, x, z, angle);
    rotationVertex(x-3, y+7, z-2.5, x, z, angle);
    rotationVertex(x-2.5, y+7, z-2.5, x, z, angle);
    rotationVertex(x-2.5, y+4, z-2.5, x, z, angle);

    
    rotationVertex(x-3, y+7, z-2.5, x, z, angle);
    rotationVertex(x-3, y+4, z-2.5, x, z, angle);
    rotationVertex(x-3, y+4, z-3, x, z, angle);
    rotationVertex(x-3, y+7, z-3, x, z, angle);

    
    rotationVertex(x-2.5, y+7, z-2.5, x, z, angle);
    rotationVertex(x-2.5, y+4, z-2.5, x, z, angle);
    rotationVertex(x-2.5, y+4, z-3, x, z, angle);
    rotationVertex(x-2.5, y+7, z-3, x, z, angle);

    // Back board
    changeColor(0.5, 0.5, 0.6);
    rotationVertex(x-3, y+7, z-3, x, z, angle);
    rotationVertex(x-3, y+10, z-3, x, z, angle);
    rotationVertex(x-3, y+10, z+3, x, z, angle);
    rotationVertex(x-3, y+7, z+3, x, z, angle);

    
    rotationVertex(x-2.5, y+7, z-3, x, z, angle);
    rotationVertex(x-2.5, y+10, z-3, x, z, angle);
    rotationVertex(x-2.5, y+10, z+3, x, z, angle);
    rotationVertex(x-2.5, y+7, z+3, x, z, angle);

    
    rotationVertex(x-3, y+7, z-3, x, z, angle);
    rotationVertex(x-2.5, y+7, z-3, x, z, angle);
    rotationVertex(x-2.5, y+7, z+3, x, z, angle);
    rotationVertex(x-3, y+7, z+3, x, z, angle);

    
    rotationVertex(x-3, y+10, z-3, x, z, angle);
    rotationVertex(x-2.5, y+10, z-3, x, z, angle);
    rotationVertex(x-2.5, y+10, z+3, x, z, angle);
    rotationVertex(x-3, y+10, z+3, x, z, angle);

    
    rotationVertex(x-3, y+7, z+3, x, z, angle);
    rotationVertex(x-2.5, y+7, z+3, x, z, angle);
    rotationVertex(x-2.5, y+10, z+3, x, z, angle);
    rotationVertex(x-3, y+10, z+3, x, z, angle);

    
    rotationVertex(x-3, y+7, z-3, x, z, angle);
    rotationVertex(x-2.5, y+7, z-3, x, z, angle);
    rotationVertex(x-2.5, y+10, z-3, x, z, angle);
    rotationVertex(x-3, y+10, z-3, x, z, angle);

    // Legs
    changeColor(0.8, 0.8, 0.8);
    // Front left
    rotationVertex(x-3, y+3, z+3, x, z, angle);
    rotationVertex(x-3, y, z+3, x, z, angle);
    rotationVertex(x-2.5, y, z+3, x, z, angle);
    rotationVertex(x-2.5, y+3, z+3, x, z, angle);

    rotationVertex(x-3, y+3, z+2.5, x, z, angle);
    rotationVertex(x-3, y, z+2.5, x, z, angle);
    rotationVertex(x-2.5, y, z+2.5, x, z, angle);
    rotationVertex(x-2.5, y+3, z+2.5, x, z, angle);

    rotationVertex(x-3, y+3, z+2.5, x, z, angle);
    rotationVertex(x-3, y, z+2.5, x, z, angle);
    rotationVertex(x-3, y, z+3, x, z, angle);
    rotationVertex(x-3, y+3, z+3, x, z, angle);

    rotationVertex(x-2.5, y+3, z+2.5, x, z, angle);
    rotationVertex(x-2.5, y, z+3, x, z, angle);
    rotationVertex(x-2.5, y, z+3, x, z, angle);
    rotationVertex(x-2.5, y+3, z+2.5, x, z, angle);

    // Front right
    rotationVertex(x+3, y+3, z+3, x, z, angle);
    rotationVertex(x+3, y, z+3, x, z, angle);
    rotationVertex(x+2.5, y, z+3, x, z, angle);
    rotationVertex(x+2.5, y+3, z+3, x, z, angle);

    rotationVertex(x+3, y+3, z+2.5, x, z, angle);
    rotationVertex(x+3, y, z+2.5, x, z, angle);
    rotationVertex(x+2.5, y, z+2.5, x, z, angle);
    rotationVertex(x+2.5, y+3, z+2.5, x, z, angle);

    rotationVertex(x+3, y+3, z+2.5, x, z, angle);
    rotationVertex(x+3, y, z+2.5, x, z, angle);
    rotationVertex(x+3, y, z+3, x, z, angle);
    rotationVertex(x+3, y+3, z+3, x, z, angle);

    rotationVertex(x+2.5, y+3, z+2.5, x, z, angle);
    rotationVertex(x+2.5, y, z+3, x, z, angle);
    rotationVertex(x+2.5, y, z+3, x, z, angle);
    rotationVertex(x+2.5, y+3, z+2.5, x, z, angle);

    // Back left
    rotationVertex(x-3, y+3, z-3, x, z, angle);
    rotationVertex(x-3, y, z-3, x, z, angle);
    rotationVertex(x-2.5, y, z-3, x, z, angle);
    rotationVertex(x-2.5, y+3, z-3, x, z, angle);

    rotationVertex(x-3, y+3, z-2.5, x, z, angle);
    rotationVertex(x-3, y, z-2.5, x, z, angle);
    rotationVertex(x-2.5, y, z-2.5, x, z, angle);
    rotationVertex(x-2.5, y+3, z-2.5, x, z, angle);

    rotationVertex(x-3, y+3, z-3, x, z, angle);
    rotationVertex(x-3, y, z-3, x, z, angle);
    rotationVertex(x-3, y, z-2.5, x, z, angle);
    rotationVertex(x-3, y+3, z-2.5, x, z, angle);

    rotationVertex(x-2.5, y+3, z-3, x, z, angle);
    rotationVertex(x-2.5, y, z-3, x, z, angle);
    rotationVertex(x-2.5, y, z-2.5, x, z, angle);
    rotationVertex(x-2.5, y+3, z-2.5, x, z, angle);

    // Back right
    rotationVertex(x+3, y+3, z-3, x, z, angle);
    rotationVertex(x+3, y, z-3, x, z, angle);
    rotationVertex(x+2.5, y, z-3, x, z, angle);
    rotationVertex(x+2.5, y+3, z-3, x, z, angle);

    rotationVertex(x+3, y+3, z-2.5, x, z, angle);
    rotationVertex(x+3, y, z-2.5, x, z, angle);
    rotationVertex(x+2.5, y, z-2.5, x, z, angle);
    rotationVertex(x+2.5, y+3, z-2.5, x, z, angle);

    rotationVertex(x+3, y+3, z-3, x, z, angle);
    rotationVertex(x+3, y, z-3, x, z, angle);
    rotationVertex(x+3, y, z-2.5, x, z, angle);
    rotationVertex(x+3, y+3, z-2.5, x, z, angle);

    rotationVertex(x+2.5, y+3, z-3, x, z, angle);
    rotationVertex(x+2.5, y, z-3, x, z, angle);
    rotationVertex(x+2.5, y, z-2.5, x, z, angle);
    rotationVertex(x+2.5, y+3, z-2.5, x, z, angle);

    glEnd();
}

// Function to draw a door, an additional flag determines which wall it goes to
void drawDoor(float room, int flag) {
    float a[3], b[3], c[3], d[3]; // 4 vertices for each plane

    changeColor(0.5f, 0.35f, 0.05f);

    if (flag == 0) {
        // Positive-z
        a[0] = -room / 2; a[1] = 9;       a[2] = room - 0.1;
        b[0] = room / 4 - 5;  b[1] = 9;       b[2] = room - 0.1;
        c[0] = room / 4 - 5;  c[1] = -10;       c[2] = room - 0.1;
        d[0] = -room / 2; d[1] = -10;       d[2] = room - 0.1;
    }
    else if (flag == 1) {
        // Negative-z
        a[0] = -room / 2; a[1] = 9;       a[2] = -room + 0.1;
        b[0] = room / 4 - 5;  b[1] = 9;       b[2] = -room + 0.1;
        c[0] = room / 4 - 5;  c[1] = -10;       c[2] = -room + 0.1;
        d[0] = -room / 2; d[1] = -10;       d[2] = -room + 0.1;
    }


    drawPlane(a, b, c, d);
}