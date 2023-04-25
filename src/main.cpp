#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath>
using namespace std;

class Screen
{
private:
    static int w, h;

public:
    static int get_width()
    {
        return w;
    }

    static int get_height()
    {
        return h;
    }

    static void set_width(int new_w)
    {
        w = new_w;
    }

    static void set_height(int new_h)
    {
        h = new_h;
    }
};

int Screen::w, Screen::h;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);
    Screen::set_width(780);
    Screen::set_height(600);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, w, 0.0, h, -1.0, 1.0);

    Screen::set_width(w);
    Screen::set_height(h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

class Object
{
public:
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void mouse(int button, int state, int x, int y) = 0;
};

class Scene
{
private:
    static map<string, shared_ptr<Object>> objects;

public:
    static void add_object(const string name, shared_ptr<Object> obj)
    {
        objects[name] = obj;
    }

    static void update(void)
    {
        for (auto& object : objects)
        {
            object.second->update();
        }
        glutPostRedisplay();
        glutPostRedisplay();
    }

    static void mouse(int button, int state, int x, int y)
    {
        for (auto& object : objects)
        {
            object.second->mouse(button, state, x, y);
        }
    }

    static void draw(void)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        for (auto& object : objects)
        {
            object.second->draw();
        }
        glutSwapBuffers();
        glFlush();
    }

    static shared_ptr<Object> get_object(const string name)
    {
        if (objects.find(name) == objects.end())
        {
            return nullptr;
        }

        return objects[name];
    }

    static int get_objects_len(void)
    {
        return objects.size();
    }
};

map<string, shared_ptr<Object>> Scene::objects;

class Point : public Object
{
private:
    double x, y;

public:
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    double getX() { return x; }
    double getY() { return y; }

    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }

    void draw()
    {
        glColor3f(0.0, 0.0, 0.0);
        glPointSize(10.0);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);

        glVertex2f(x, y);

        glEnd();
    }

    void update() { ; }
    void mouse(int button, int state, int x, int y) { ; }
};

class EcuatieDreapta
{
private:
    double xCoef, yCoef, b;

public:
    EcuatieDreapta(double xCoef, double yCoef, double b)
    {
        this->xCoef = xCoef;
        this->yCoef = yCoef;
        this->b = b;
    }

    EcuatieDreapta(Point p1, Point p2)
    {
        double xA = p1.getX(), yA = p1.getY();
        double xB = p2.getX(), yB = p2.getY();
        xCoef = yB - yA;
        yCoef = xA - xB;
        b = yB * (xB - xA) - xB * (yB - yA);
    }

    double eval(Point p)
    {
        return yCoef * p.getY() + xCoef * p.getX() + b;
    }

    double get_y(double x)
    {
        return -(xCoef * x + b) / yCoef;
    }

    double getXCoef()
    {
        return xCoef;
    }
    double getYCoef()
    {
        return yCoef;
    }
    double getB()
    {
        return b;
    }
};

class Square : public Object
{
private:
    Point centru;

    double latura;

    double viteza_x;
    double viteza_y;

    double unghi_rotatie;
    double viteza_rotatie;

public:
    Square(double centru_x, double centru_y, double latura,
        double viteza_x, double viteza_y, double unghi_rotatie,
        double viteza_rotatie)
    {

        this->centru.setX(centru_x);
        this->centru.setY(centru_y);
        this->latura = latura;
        this->viteza_x = viteza_x;
        this->viteza_y = viteza_y;
        this->unghi_rotatie = unghi_rotatie;
        this->viteza_rotatie = viteza_rotatie;
    }

    void update(void)
    {
        centru.setX(centru.getX() + viteza_x);
        if (centru.getX() < 0.0 || centru.getX() > 750.0)
        {
            viteza_x = -viteza_x;
            viteza_rotatie = -viteza_rotatie;
        }
        unghi_rotatie += viteza_rotatie;
    }

    void draw() override
    {
        glPushMatrix();
        glTranslated(centru.getX(), centru.getY(), 0.0);
        glRotated(unghi_rotatie, 0.0, 0.0, 1.0);
        glColor3f(1.0, 0.0, 0.0);
        glRecti(-latura / 2.0, -latura / 2.0,
            latura / 2.0, latura / 2.0);
        glPopMatrix();
    }

    void mouse(int button, int state, int x, int y)
    {
        switch (button)
        {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                viteza_x = -abs(viteza_x);
                viteza_rotatie = abs(viteza_rotatie);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                viteza_x = abs(viteza_x);
                viteza_rotatie = -abs(viteza_rotatie);
            }
            break;
        default:
            break;
        }
    }
};

class Line : public Object
{
private:
    Point A;
    Point B;

public:
    Line(double xA, double yA, double xB, double yB) : A(xA, yA), B(xB, yB) { ; }

    void draw()
    {
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2i(A.getX(), A.getY());
        glVertex2i(B.getX(), B.getY());
        glEnd();
    }

    void update() { ; }
    void mouse(int button, int state, int x, int y) { ; }

    Point getA() { return A; }
    Point getB() { return B; }
};

class Hamburger : public Object
{
public:
    Point centru;
    double angle;

    Hamburger(double x, double y) : centru(x, y), angle(0) { ; }

    void draw()
    {
        glPushMatrix();

        glTranslated(centru.getX(), centru.getY(), 0);
        glRotated(angle, 0, 0, 1);
        glTranslated(0, 15, 0);


        // top bun
        glColor3f(1.0, 0.8, 0.0); 
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
        for (float theta = 0; theta <= M_PI; theta += 0.01)
        {
            float x = cos(theta) * 50;
            float y = sin(theta) * 30;
            glVertex2f(x, y);
        }
        glEnd();

       
        //bottom bun
        glColor3f(1.0, 0.8, 0.0);
        int offset = -35;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, offset);
        for (float theta = 0; theta <= M_PI; theta += 0.01)
        {
            float x = -cos(theta) * 50;
            float y = -sin(theta) * 30;
            glVertex2f(x, y + offset);
        }
        glEnd();

        // lettuce
        glColor3f(0.64, 0.78, 0.35);
        glBegin(GL_POLYGON);
        glVertex2f(-55, -28);
        glVertex2f(55, -28);
        glVertex2f(50, -40);
        glVertex2f(40, -28);
        glVertex2f(30, -40);
        glVertex2f(20, -28);
        glVertex2f(10, -48);
        glVertex2f(0, -28);
        glVertex2f(-10, -40);
        glVertex2f(-20, -28);
        glVertex2f(-30, -40);
        glVertex2f(-40, -28);

        glEnd();

        //tomato
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        int numSegments = 100;
        float radiusX = 55;
        float radiusY = 7;
        for (int i = 0; i < numSegments; i++)
        {
            float theta = 2.0 * M_PI * float(i) / float(numSegments);
            float x = radiusX * cos(theta);
            float y = radiusY * sin(theta);
            glVertex2f(x, y - 23);
        }
        glEnd();

        // meat
        glColor3f(0.46, 0.36, 0.30);
        glRecti(-50, -20, 50, 0);

        // cheese
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0.95, 0.18);
        glVertex2f(-50, 0);
        glVertex2f(50, 0);
        glVertex2f(30, -12.5);
        glEnd();

        glPopMatrix();
    }

    void update()
    {
        angle += 0.05;
        if (angle > 360)
        {
            angle = 0;
        }
        if (angle < 0)
        {
            angle = 360;
        }
        glutPostRedisplay();
    }
    void mouse(int button, int state, int x, int y) { ; }
};

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Patrat care se rostogoleste");
    init();

    shared_ptr<Square> square1 = make_shared<Square>(Square(0, 100, 20, 0.05, 0, 0, -0.06));
    shared_ptr<Line> line1 = make_shared<Line>(Line(-30, 100, 780, 100));
    shared_ptr<Hamburger> hamburger = make_shared<Hamburger>(Hamburger(300, 300));

    Scene::add_object("Hamburger", hamburger);
    Scene::add_object("square1", square1);
    Scene::add_object("line1", line1);

    glutIdleFunc(Scene::update);
    glutDisplayFunc(Scene::draw);
    glutReshapeFunc(reshape);
    glutMouseFunc(Scene::mouse);
    glutMainLoop();
}