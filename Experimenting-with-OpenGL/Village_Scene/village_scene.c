#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265

float angle = 0.0;
bool isDay = true;
bool shadingMode = true;
bool spotlightOn = false;
bool autoDayCycle = true;

float cameraAngle = 90.0f;
float cameraHeight = 40.0f;


void setCamera() {
    float camX = 110 * cos(cameraAngle * PI / 180.0);
    float camZ = 110 * sin(cameraAngle * PI / 180.0);
    gluLookAt(camX, cameraHeight, camZ, 0, 10, 0, 0, 1, 0);
}

void drawSunOrMoon() {
    GLfloat lightColor[] = { isDay ? 1.0 : 0.8, isDay ? 1.0 : 0.8, isDay ? 0.0 : 1.0, 1.0 };
    GLfloat lightPos[] = { 50.0f * (float)cos(angle), 50.0f * (float)sin(angle), 0.0f, 1.0f };

    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    glEnable(GL_LIGHT1);

    glPushMatrix();
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lightColor);
    glutSolidSphere(2.0, 20, 20);
    glPopMatrix();
}

void drawHouse(float r, float g, float b, int h) {
    float a = 0.0f;
    float n = 0.0f;
    float c = 0.0f;
    if (h == 1) {
        a = 8.0f; n = 10.0f; c = 15.0f;
    }
    else if (h == 2) {
        a = 9.0f; n = 10.0f; c = 16.0f;
    }
    else if (h == 3) {
        a = 7.0f; n = 10.0f; c = 14.0f;
    }
    glPushMatrix();
    glTranslatef(0, -5, 0);
    glScalef(a, n, c);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (GLfloat[]) { r, g, b, 1.0 });
    glutSolidCube(1.0);
    glPopMatrix();

    float roofHeight = 0.0f;
    float houseHeight = 0.0f;
    float width = 0.0f;
    float length = 0.0f;
    if (h == 1) {
        roofHeight = 5.0f; houseHeight = 10.0f; width = 15.0f; length = 8.0f;
    }
    else if (h == 2) {
        roofHeight = 6.0f; houseHeight = 10.0f; width = 16.0f; length = 9.0f;
    }
    else if (h == 3) {
        roofHeight = 4.0f; houseHeight = 10.0f; width = 14.0f; length = 7.0f;
    }

    glPushMatrix();
    glTranslatef(0, -10, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (GLfloat[]) { 0.5, 0.0, 0.0, 1.0 });

    glBegin(GL_QUADS);
    glNormal3f(0, 1, 1);
    glVertex3f(0, houseHeight + roofHeight, -width / 2);
    glVertex3f(length / 2, houseHeight, -width / 2);
    glVertex3f(length / 2, houseHeight, width / 2);
    glVertex3f(0, houseHeight + roofHeight, width / 2);

    glVertex3f(0, houseHeight + roofHeight, -width / 2);
    glVertex3f(-length / 2, houseHeight, -width / 2);
    glVertex3f(-length / 2, houseHeight, width / 2);
    glVertex3f(0, houseHeight + roofHeight, width / 2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-length / 2, houseHeight, width / 2);
    glVertex3f(length / 2, houseHeight, width / 2);
    glVertex3f(0, houseHeight + roofHeight, width / 2);

    glVertex3f(-length / 2, houseHeight, -width / 2);
    glVertex3f(length / 2, houseHeight, -width / 2);
    glVertex3f(0, houseHeight + roofHeight, -width / 2);
    glEnd();
    glPopMatrix();
}

void drawGround() {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (GLfloat[]) { 0.6, 0.6, 0.6, 1.0 });
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-200, 0, -200);
    glVertex3f(-200, 0, 200);
    glVertex3f(200, 0, 200);
    glVertex3f(200, 0, -200);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    setCamera();

    glShadeModel(shadingMode ? GL_SMOOTH : GL_FLAT);

    if (spotlightOn) {
        GLfloat spotPos[] = { 0.0, 30.0, 0.0, 1.0 };
        GLfloat spotDir[] = { 0.0, -1.0, 0.0 };
        glLightfv(GL_LIGHT2, GL_POSITION, spotPos);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);
        glEnable(GL_LIGHT2);
    }
    else {
        glDisable(GL_LIGHT2);
    }

    drawSunOrMoon();
    drawGround();

    glPushMatrix();
    glTranslatef(-30, 10, -10);
    drawHouse(0.5, 0.25, 0.1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 10, 10);
    drawHouse(0.5, 0.25, 0.1, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30, 10, -10);
    drawHouse(0.5, 0.25, 0.1, 3);
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {
    if (autoDayCycle) {
        angle += 0.01;
        if (angle > PI) {
            angle = 0.0;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void handleSpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) cameraAngle += 2.0f;
    if (key == GLUT_KEY_RIGHT) cameraAngle -= 2.0f;
    if (key == GLUT_KEY_UP) cameraHeight += 2.0f;
    if (key == GLUT_KEY_DOWN) cameraHeight -= 2.0f;
    glutPostRedisplay();
}

void handleMenu(int option) {
    switch (option) {
    case 1: isDay = !isDay; break;
    case 2: spotlightOn = !spotlightOn; break;
    case 3: shadingMode = !shadingMode; break;
    case 4: exit(0); break;
    }
}

void createMenu() {
    glutCreateMenu(handleMenu);
    glutAddMenuEntry("Day/Night Cycle", 1);
    glutAddMenuEntry("Spotlight On/Off", 2);
    glutAddMenuEntry("Shading Smooth/Flat", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glClearColor(0.3, 0.3, 0.3, 1.0);
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("I was made for loving u Nikolaidi <3");

    initRendering();
    createMenu();

    glutDisplayFunc(display);
    glutSpecialFunc(handleSpecialKeys);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}
