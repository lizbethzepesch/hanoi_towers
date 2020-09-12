#include <gl/glut.h>
#include <iostream>
#include "Game.h"
using namespace Hanoi;
Game* game;

void draw()
{
    game->draw();
}
void ssize(int width, int height)
{

    game->on_size(width, height);
}
void mouse(int button, int state, int x, int y)
{
    game->on_mouse(button, state, x, y);
}
void motion(int x, int y)
{
    game->on_motion(x, y);
}
void specialKeyboard(int key, int x, int y)
{
    game->on_special(key, x, y);
}
void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}
void on_timer(int value)
{
    game->on_timer(value);
    glutTimerFunc(25, on_timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);//initialization GLUT
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//display mode (режим отображения)

    glutInitWindowSize(800, 600);//size of the window
    glutInitWindowPosition(100, 50);//position of the window
    glutCreateWindow("hanoi towers");//make a new window
    int M = 5;
    game = new Game(M);
    glutDisplayFunc(draw);//func of dispaly

    glutReshapeFunc(ssize);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

    glutTimerFunc(25, on_timer, 0);
    glutMainLoop();
    delete game;
    system("pause");
    return(0);
}