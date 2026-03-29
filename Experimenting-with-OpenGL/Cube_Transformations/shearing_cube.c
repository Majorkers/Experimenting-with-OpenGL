#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535897932

// Animation parameters
float angle = 0.0f;               // Rotation angle
float shear_angle = 45.0f;        // Starts at 45°
int shear_direction = 1;          // 1 = increasing, -1 = decreasing
float beta = 90.0f;                // Distance from camera
float rotation_vector[3] = { 1.0f, 0.0f, 1.0f }; // Rotation axis

// Display list for the cube
GLuint cubeDL;

// Face colors (RGB)
float face_colors[6][3] = {
    {1,0,0}, {0,1,0}, {0,0,1},  
    {1,1,0}, {0,1,1}, {1,0,1}   
};

void normalize(float* v) {
    float len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= len; v[1] /= len; v[2] /= len;
}

void drawSquare() {
    float s = 1.0f / sqrt(2.0f);
    glBegin(GL_QUADS);
    glVertex3f(s, s, 1);
    glVertex3f(s, s, -1);
    glVertex3f(-s, -s, -1);
    glVertex3f(-s, -s, 1);
    glEnd();
}

void createCubeDisplayList() {
    cubeDL = glGenLists(1);
    glNewList(cubeDL, GL_COMPILE);

    glPushMatrix();
    glTranslatef(0, sqrt(2.0f), 0);
    glColor3fv(face_colors[0]);
    drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sqrt(2.0f), 0, 0);
    glColor3fv(face_colors[1]);
    drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, 0, 0, 1);
    glColor3fv(face_colors[2]);
    drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sqrt(2.0f), sqrt(2.0f), 0);
    glRotatef(90, 0, 0, 1);
    glColor3fv(face_colors[3]);
    drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sqrt(2.0f) / 2, sqrt(2.0f) / 2, 1);
    glRotatef(90, 1, 1, 0);
    glColor3fv(face_colors[4]);
    drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sqrt(2.0f) / 2, sqrt(2.0f) / 2, -1);
    glRotatef(90, 1, 1, 0);
    glColor3fv(face_colors[5]);
    drawSquare();
    glPopMatrix();

    glEndList();
}

void applyShear() {
    // Convert shear angle to radians and calculate shear factor
    float theta_rad = shear_angle * (PI / 180.0);
    float shear_factor = tan(theta_rad - PI / 2);  

    GLfloat shear_matrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        shear_factor, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glMultMatrixf(shear_matrix);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glOrtho(-10, 10, -10, 10, 0.1, 100);

    glTranslatef(0, 0, -beta);

    // Apply transformations in order: Rotation -> Shearing
    glRotatef(angle, rotation_vector[0], rotation_vector[1], rotation_vector[2]);
    applyShear();

    glCallList(cubeDL);

    glutSwapBuffers();
}

void update(int value) {
    angle = fmod(angle + 1.0f, 360.0f);

    // Update shear angle (oscillate between 45° and 135°)
    shear_angle += 0.5f * shear_direction;
    if (shear_angle > 135.0f || shear_angle < 45.0f) {
        shear_direction *= -1;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating & Shearing Cube");

    glEnable(GL_DEPTH_TEST);
    normalize(rotation_vector);

    createCubeDisplayList();

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    glDeleteLists(cubeDL, 1);
    return 0;
}