#define _CRT_SECURE_NO_WARNINGS
#include <GLFW/glfw3.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 
#include <math.h>
float x = 0;
float y = 0;
float xAlpha = 0.1;
float yAlpha = 0.1;

int Height = 1000;
int Width = 1000;

const double Pi = 3.14159265358979323846264338327950288419716939937510;



void Documentation()
{

    printf("\tA program for plotting functions\n"
        "\t\tGuide:\n"
        "1.Supported functions:\n"
        "\t '+' - addition, '-' - subtraction, '*' - multiplication, '/' - division\n"
        "\t '()' - parentheses (Each opening parenthesis must have a closing one)\n"
        "\t '^' - exponentiation\n"
        "\t 'sin()','cos()','tan()','ctg()' - trigonometric functions\n"
        "\t 'exp()' - exponent (exp(1) - exponent of the 1st degree)\n"
        "2.Functional:\n"
        "\tPlotting functions\n"
        "\t\tEnter the function: ");
}

typedef struct Node {
    float value;
    char operation;
    struct Node* pNext;
}Node;

struct Point3D
{
    double x;
    double y;
    double z;
};
int push(Node** top, float value, char operation) {
    Node* pNew = (Node*)malloc(sizeof(Node));
    pNew->operation = operation;
    pNew->value = value;
    if (*top == NULL) {
        pNew->pNext = NULL;
        *top = pNew;
    }
    else {
        pNew->pNext = *top;
        *top = pNew;
    }
    return 0;
}
int pop(Node** top) {
    if (top == NULL) {
        return 0;
    }

    Node* tmp = *top;
    char operation = tmp->operation;

    *top = tmp->pNext;

    free(tmp);

    return 0;
}
void CreateAxis()
{
    glLineWidth(5);

    glBegin(GL_LINES);
    //x
    glColor3f(1, 0, 0);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    //y
    glColor3f(0, 1, 0);
    glVertex3f(0, -1, 0);
    glVertex3f(0, 1, 0);
    //z
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -1);
    glVertex3f(0, 0, 1);
    glEnd();


    glBegin(GL_TRIANGLE_FAN);
    //x
    glColor3f(1, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0.95, 0.02, 0);
    glVertex3f(0.95, 0, 0.02);
    glVertex3f(0.95, -0.02, 0);
    glVertex3f(0.95, 0, -0.02);
    glVertex3f(0.95, 0.02, 0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    //y
    glColor3f(0, 1, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(0.02, 0.95, 0);
    glVertex3f(0, 0.95, 0.02);
    glVertex3f(-0.02, 0.95, 0);
    glVertex3f(0, 0.95, -0.02);
    glVertex3f(0.02, 0.95, 0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    //z
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0.02, 0, 0.95);
    glVertex3f(0, 0.02, 0.95);
    glVertex3f(-0.02, 0, 0.95);
    glVertex3f(0, -0.02, 0.95);
    glVertex3f(0.02, 0, 0.95);
    glEnd();
}
void ControlAxis()
{
    if (GetKeyState(VK_UP) < 0)
        x += xAlpha;
    if (GetKeyState(VK_DOWN) < 0)
        x -= xAlpha;
    glRotatef(-x, 1, 0, 0);
    if (GetKeyState(VK_RIGHT) < 0)
        y += yAlpha;
    if (GetKeyState(VK_LEFT) < 0)
        y -= yAlpha;
    glRotatef(y, 0, 0, 1);
}

int getRang(char Ch)
{
    if (Ch == '+' || Ch == '-') return 1;
    if (Ch == '*' || Ch == '/') return 2;
    if (Ch == '^') return 3;
    if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e') return 4;
    return 0;
}
int SortingStation(char* infixNotation, char* PostfixNotation)
{
    char Ch = 0;
    int i = 0, j = 0;//Счетчик строки input и output соответсвенно

    Node* top = NULL;//указатель на вершину стека для операций

    for (int i = 0; i < strlen(infixNotation);)
    {
        Ch = infixNotation[i];
        if (Ch == ' ')
        {
            continue;
        }
        if (Ch == 'x')
        {
            PostfixNotation[j++] = Ch;
            PostfixNotation[j++] = ' ';
            i++;
            continue;

        }
        if (Ch == 'y')
        {
            PostfixNotation[j++] = Ch;
            PostfixNotation[j++] = ' ';
            i++;
            continue;

        }
        if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'e')
        {
            char chars[3];
            for (int n = 0; n < 3; n++)
            {
                Ch = infixNotation[i++];
                chars[n] = Ch;
            }
            if (chars[0] == 's' && chars[1] == 'i' && chars[2] == 'n')
            {
                push(&top, NULL, 's');
            }
            else if (chars[0] == 'c' && chars[1] == 'o' && chars[2] == 's')
            {
                push(&top, NULL, 'c');
            }
            else if (chars[0] == 't' && chars[1] == 'a' && chars[2] == 'n')
            {
                push(&top, NULL, 't');
            }
            else if (chars[0] == 'c' && chars[1] == 't' && chars[2] == 'g')
            {
                push(&top, NULL, 'g');
            }
            continue;
        }
        if (Ch >= '0' && Ch <= '9')
        {
            while (isdigit(infixNotation[i]) || infixNotation[i] == '.')
            {
                Ch = infixNotation[i++];
                PostfixNotation[j++] = Ch;
            }
            PostfixNotation[j++] = ' ';
        }
        if (Ch == '+' || Ch == '-' || Ch == '*' || Ch == '/' || Ch == '^')
        {
            float value = 0;
            char operation = 0;
            if (top != NULL && getRang(Ch) > getRang(top->operation))
            {
                push(&top, NULL, Ch);
                i++;
                continue;
            }
            if (top != NULL && getRang(Ch) <= getRang(top->operation))
            {
                PostfixNotation[j++] = top->operation;
                PostfixNotation[j++] = ' ';
                pop(&top);
            }
            if (top == NULL) {
                push(&top, NULL, Ch);
                i++;
                continue;
            }
        }
        if (Ch == '(') {

            push(&top, NULL, Ch);
            i++;
            continue;
        }
        if (Ch == ')') {
            while (top->operation != '(') {
                PostfixNotation[j++] = top->operation;
                PostfixNotation[j++] = ' ';
                pop(&top);
                if (top == NULL)
                {
                    printf("Скобки не согласованы");
                    return -1;
                }
            }
            pop(&top);//Выталкиваем открывыющую скобку
            i++;
            continue;
        }

    }
    while (top != NULL)
    {
        PostfixNotation[j++] = top->operation;
        PostfixNotation[j++] = ' ';
        pop(&top);
    }

    return 0;
}
float Math(char* PostfixNotation, float xParam, float yParam)
{
    double a, b, c;

    

    Node* top = NULL;

    char Ch = 0;
    for (int i = 0; i < strlen(PostfixNotation); i++)
    {
        Ch = PostfixNotation[i];
        if (Ch == ' ')
        {
            continue;
        }
        if (Ch == 'x')
        {
            push(&top, xParam, NULL);
            continue;
        }
        if (Ch == 'y')
        {
            push(&top, yParam, NULL);
            continue;
        }
        if (Ch >= '0' && Ch <= '9')
        {
            double value;
            char num[100] = { 0 };
            int j = 0;
            while (isdigit(PostfixNotation[i]) || PostfixNotation[i] == '.')
            {
                num[j] = PostfixNotation[i];
                i++;
                j++;
            }
            value = atof(num);
            push(&top, value, NULL);
            continue;
        }
        if (Ch == '+' || Ch == '-' || Ch == '*' || Ch == '/' || Ch == '^')
        {
            switch (Ch)
            {
            case'+':
                a = top->value;
                pop(&top);
                b = top->value;
                pop(&top);
                c = a + b;
                push(&top, c, NULL);
                break;
            case'-':
                a = top->value;
                pop(&top);
                b = top->value;
                pop(&top);
                c = b - a;
                push(&top, c, NULL);
                break;
            case'*':
                a = top->value;
                pop(&top);
                b = top->value;
                pop(&top);
                c = a * b;
                push(&top, c, NULL);
                break;
            case'/':
                a = top->value;
                pop(&top);
                b = top->value;
                pop(&top);
                if (a == 0)
                {
                    printf("На 0 делить нельзя!");
                    return false;
                }
                c = b / a;
                push(&top, c, NULL);
                break;
            case'^':
                a = top->value;
                pop(&top);
                b = top->value;
                pop(&top);
                c = pow(b, a);
                push(&top, c, NULL);
                break;
            }
        }
        if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g')
        {
            switch (Ch)
            {
            case 's':
                a = top->value;
                pop(&top);
                c = sin(a);
                push(&top, c, NULL);
                break;
            case 'c':
                a = top->value;
                pop(&top);
                c = cos(a);
                push(&top, c, NULL);
                break;
            case 't':
                a = top->value;
                if (cos(a) == 0) {
                    printf("tan(%d) Не существует", a);
                    return false;
                }
                pop(&top);
                c = tan(a);
                push(&top, c, NULL);
                break;
            case 'g':
                a = top->value;
                if (sin(a) == 0) {
                    printf("ctg(%d) Не существует", a);
                    return false;
                }
                pop(&top);
                c = 1 / tan(a);
                push(&top, c, NULL);
                break;
            }
        }
    }
    float result = top->value;
    return result;
}
int main()
{
    system("chcp 1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Documentation();


    char infixNotation[100] = { 0 }, PostfixNotation[100] = { 0 };
    scanf("%s", infixNotation);

    SortingStation(infixNotation, PostfixNotation);//Перевел инфиксную нотацию в постфиксную


    struct Point3D Points[15000];

    int pointCount = 0;
    for (float xParam = -8; xParam < 8; xParam += 0.15)
    {
        for (float yParam = -8; yParam < 8; yParam += 0.15)
        {
            Point3D newPoint;
            newPoint.x = xParam;
            newPoint.y = yParam;
            newPoint.z = Math(PostfixNotation, xParam, yParam);
            Points[pointCount++] = newPoint;
        }
    }


    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(Width, Height, "FunctionGraph", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(-90, 1, 0, 0);

        glPushMatrix();

        ControlAxis();
        CreateAxis();

        glPointSize(5);



        glBegin(GL_POINTS);
        glColor3f(0, 0, 1);
        for (int p = 0; p <= pointCount; p++)
            glVertex3f(Points[p].x * 0.1, Points[p].y * 0.1, Points[p].z * 0.1);
        glEnd();

        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}