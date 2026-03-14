#include <GL/glut.h>
#include <math.h>

float ballX = 0.0f;
float ballY = 2.0f;
float ySpeed = 0.05f;
float xSpeed = 0.03f;

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for(int i = 0; i <= 30; i++) {
        float angle = 2.0f * 3.14159 * i / 30;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

void drawRectangle(float x, float y, float w, float h) {
    glBegin(GL_POLYGON);
    glVertex2f(x - w/2, y - h/2);
    glVertex2f(x + w/2, y - h/2);
    glVertex2f(x + w/2, y + h/2);
    glVertex2f(x - w/2, y + h/2);
    glEnd();
}

void drawBall() {
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(ballX, ballY, 0.5f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(ballX - 0.1f, ballY + 0.1f, 0.1f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(ballX - 0.3f, ballY);
    glVertex2f(ballX + 0.3f, ballY);
    glVertex2f(ballX, ballY - 0.3f);
    glVertex2f(ballX, ballY + 0.3f);
    glEnd();
}

void drawGround() {
    glColor3f(0.0f, 0.8f, 0.0f);
    drawRectangle(0, -2.5f, 15, 1);

    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(ballX, -2.3f, 0.4f);
}

void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-7, 7, -3, 5);
}

void update(int value) {
    ballY += ySpeed;
    if(ballY > 3.5f) ySpeed = -0.05f;
    if(ballY < -1.8f) ySpeed = 0.05f;

    ballX += xSpeed;
    if(ballX > 5.0f || ballX < -5.0f) xSpeed = -xSpeed;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawGround();
    drawBall();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Bola Memantul");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}