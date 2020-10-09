
#include <gl/glut.h>
#include "Base.h"
#include "Board.h"
#include "Build.h"
using namespace Hanoi;
using namespace Build;

namespace Hanoi
{

    void Board::draw()
    {

        glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
        glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());
        glMaterialf(GL_FRONT, GL_SHININESS, Build::shininess);

        glPushMatrix();
        glTranslatef(getXCenter(), getYCenter(), getZCenter());
        Build::parallelepiped(getXSize(), getYSize(), getZSize());

        glPopMatrix();
    }

}
