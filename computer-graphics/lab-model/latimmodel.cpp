#include "latimmodel.h"

LaTIMModel::LaTIMModel()
{
    wall1 = Object(5.90f, 3.0f, 0.10f);
    wall2 = Object(6.80f, 3.0f, 0.10f);
    deskArm = Object(1.40f, 0.05f, 0.55f);
    deskCen = Object(1.0f, 0.05f, 0.55f);
    nDeskR = Object(4.16f, 0.05f, 0.55f);
    nDeskL = Object(1.33f, 0.05f, 0.55f);
    deskDiv1 = Object(2.95f, 1.20f, 0.05f);
    deskDiv2 = Object(4.25f, 1.20f, 0.05f);
    cabinet1 = Object(0.80f, 2.08f, 0.57f);
    cabinet2 = Object(1.0f, 2.20f, 0.57f);
    door = Object(1.0f, 2.20f, 0.05f);
    computer1 = Object();
    window1 = Object();
    blackboard = Object(3.0f, 1.40f, 0.08f);
    chair1 = Object();
}

void LaTIMModel::draw()
{
    glPushMatrix();

    //door
    drawDoor();

    //Walls
    drawWalls();

    //Cabinets
    drawCabinets();

    //Desks and Dividers
    drawDesks();

    //Shelfs (new desks)
    drawShelf();

    //Computers
    drawComputers();

    //Blackboard
    drawBlackboard();

    //Ceiling
    drawCeiling();

    glPopMatrix();
}


void LaTIMModel::drawHexahedron(GLdouble w, GLdouble h, GLdouble d)
{
    //front side
    drawRect(0.0f, 0.0f, 0.0f,
                w, 0.0f, 0.0f,
                w,    h, 0.0f,
             0.0f,    h, 0.0f);

    //back side
    drawRect(0.0f, 0.0f,    d,
                w, 0.0f,    d,
                w,    h,    d,
             0.0f,    h,    d);

    //left side
    drawRect(0.0f, 0.0f, 0.0f,
             0.0f, 0.0f,    d,
             0.0f,    h,    d,
             0.0f,    h, 0.0f);

    //right side
    drawRect(   w, 0.0f, 0.0f,
                w,    h, 0.0f,
                w,    h,    d,
                w, 0.0f,    d);

    //bottom side
    drawRect(0.0f, 0.0f, 0.0f,
             0.0f, 0.0f,    d,
                w, 0.0f,    d,
                w, 0.0f, 0.0f);

    //top side
    drawRect(0.0f,    h, 0.0f,
                w,    h, 0.0f,
                w,    h,    d,
             0.0f,    h,    d);

}

void LaTIMModel::drawRect(GLdouble p1_x, GLdouble p1_y, GLdouble p1_z,
                        GLdouble p2_x, GLdouble p2_y, GLdouble p2_z,
                        GLdouble p3_x, GLdouble p3_y, GLdouble p3_z,
                        GLdouble p4_x, GLdouble p4_y, GLdouble p4_z)
{
    glBegin(GL_POLYGON);
        glVertex3f(p1_x, p1_y, p1_z); //bottom left
        glVertex3f(p2_x, p2_y, p2_z); //bottom right
        glVertex3f(p3_x, p3_y, p3_z); //top right
        glVertex3f(p4_x, p4_y, p4_z); //top left
    glEnd();
}

void LaTIMModel::drawDesk()
{
    //right side
    drawHexahedron(deskArm.w, deskArm.h, deskArm.d);
    glTranslated(0.02f, -desk_y, 0.0f);
    drawHexahedron(deskArm.h, desk_y, deskArm.d);
    glTranslated(-0.02f, desk_y, 0.0f);
    //middle
    glTranslated(deskArm.w, 0.0f, -1.0f);
    glRotated(90.0f, 0.0f, -1.0f, 0.0f);
    drawHexahedron(deskCen.w, deskCen.h, deskCen.d);
    glRotated(-90.0f, 0.0f, -1.0f, 0.0f);
    glTranslated(-deskArm.w, 0.0f, 1.0f);
    // left side
    glTranslated(0.0f, 0.0f, -(deskCen.w + deskArm.d));
    drawHexahedron(deskArm.w, deskArm.h, deskArm.d);
    glTranslated(0.02f, -desk_y, 0.0f);
    drawHexahedron(deskArm.h, desk_y, deskArm.d);
    glTranslated(-0.02f, desk_y, 0.0f);
    glTranslated(0.0f, 0.0f, (deskCen.w + deskArm.d));
}

void LaTIMModel::drawCabinet(GLdouble w, GLdouble h, GLdouble d)
{
    //right side
    drawRect(0.0f, 0.0f, 0.0f,
             0.0f,    h, 0.0f,
             0.0f,    h,    d,
             0.0f, 0.0f,    d);

    //left side
    drawRect(   w, 0.0f, 0.0f,
                w, 0.0f,    d,
                w,    h,    d,
                w,    h, 0.0f);

    //bottom side
    drawRect(0.0f, 0.0f, 0.0f,
             0.0f, 0.0f,    d,
                w, 0.0f,    d,
                w, 0.0f, 0.0f);

    //top side
    drawRect(0.0f,    h, 0.0f,
                w,    h, 0.0f,
                w,    h,    d,
             0.0f,    h,    d);

    glColor3f(0.85f, 0.85f, 0.85f); //cabinet color
    //back side
    drawRect(0.0f, 0.0f,    d,
                w, 0.0f,    d,
                w,    h,    d,
             0.0f,    h,    d);

    glColor3f(0.6f, 0.6f, 0.6f); //cabinet color
    //right door
    drawRect(           0.0f, 0.0f, 0.0f,
                w/2 - 0.005f, 0.0f, 0.0f,
                w/2 - 0.005f,    h, 0.0f,
                        0.0f,    h, 0.0f);

    //left door
    drawRect(w/2 + 0.005f, 0.0f, 0.0f,
                        w, 0.0f, 0.0f,
                        w,    h, 0.0f,
             w/2 + 0.005f,    h, 0.0f);
}

void LaTIMModel::drawDoor()
{
    glColor3f(0.25f, 0.25f, 0.25f); //door colors
    glPushMatrix();

    glTranslated(0.0f, 0.0f, wall1.d);
    glRotated((doorAngle), 0.0f, 1.0f, 0.0f);
    drawHexahedron(door.w, door.h, -door.d);
    glRotated(-(doorAngle), 0.0f, 1.0f, 0.0f);
    glTranslated(0.0f, 0.0f, -wall1.d);

    glPopMatrix();
}

void LaTIMModel::moveDoor()
{
    doorPos *= -1;
    if(doorPos > 0) {
        doorAngle = 0.0f;
    } else {
        doorAngle = -80.0f;
    }
}

void LaTIMModel::drawWalls()
{
    glPushMatrix();

    glColor3f(0.9f, 0.9f, 0.9f); //wall colors
    //Wall1 (door)
    //wall on the right of the door
    glTranslated(-(0.1f), 0.0f, 0.0f);
    drawHexahedron(0.1f, wall1.h, wall1.d);
    glTranslated((0.1f), 0.0f, 0.0f);
    //wall above the door
    glColor3f(0.9f, 0.9f, 0.9f); //wall colors
    glTranslated(0.0f, door.h, 0.0f);
    drawHexahedron(door.w, wall1.h - door.h, wall1.d);
    glTranslated(0.0f, -door.h, 0.0f);
    //wall on the left of the door
    glTranslated(-(0.1f), 0.0f, 0.0f);
    glTranslated((0.1f + door.w), 0.0f, 0.0f);
    drawHexahedron(wall1.w - 0.1f - door.w, wall1.h, wall1.d);
    glTranslated(-(0.1f + door.w), 0.0f, 0.0f);

    //Wall1 (windows)
    //front wall
    glTranslated(0.0f, 0.0f, (wall2.w - wall2.d));
    drawHexahedron(wall1.w, wall1.h, wall1.d);
    glTranslated(0.0f, 0.0f, -(wall2.w - wall2.d));

    //Wall2 (in front of the AC wall)
    glTranslated(wall1.w, 0.0f, wall2.w);
    glRotated(-90.0f, 0.0f, -1.0f, 0.0f);
    drawHexahedron(wall2.w, wall2.h, wall2.d);
    glRotated(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslated(-wall1.w, 0.0f, -wall2.w);

    //Wall2 (AC)
    glRotated(90.0f, 0.0f, -1.0f, 0.0f);
    drawHexahedron(wall2.w, wall2.h, wall2.d);
    glRotated(-90.0f, 0.0f, -1.0f, 0.0f);

    glPopMatrix();
}

void LaTIMModel::drawCabinets()
{
    glPushMatrix();

    //cabinets
    //cabinet 1 (in front of the AC wall)
    glColor3f(0.85f, 0.85f, 0.85f); //cabinet color
    glTranslated( (wall1.w - cabinet1.d - wall1.d), 0.0f,  (cabinet1.w + wall1.d + 0.2f));
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    drawCabinet(cabinet1.w, cabinet1.h, cabinet1.d);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(wall1.w - cabinet1.d - wall1.d), 0.0f, -(cabinet1.w + wall1.d + 0.2f));

    //cabinet 2 (AC)
    glColor3f(0.85f, 0.85f, 0.85f); //cabinet color
    glTranslated( (cabinet2.d - 0.05f), 0.0f,  (wall2.w - nDeskR.w - cabinet2.w - 0.01f - wall2.d));
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    drawCabinet(cabinet2.w, cabinet2.h, cabinet2.d);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(cabinet2.d - 0.05f), 0.0f, -(wall2.w - nDeskR.w - cabinet2.w - 0.01f - wall2.d));

    glPopMatrix();
}

void LaTIMModel::drawDesks()
{
    glPushMatrix();

    //desks
    glColor3f(0.65f, 0.65f, 0.65f); //desk color
    glTranslated((nDeskL.d + nDeskL.w - wall2.d), desk_y, (wall2.w - nDeskL.d - wall2.d));
    //desk 1
    drawDesk();
    //desk 2
    glTranslated(0.0f, 0.0f, -(deskArm.d*2 + deskCen.w + 0.05f));
    drawDesk();
    //desk 4
    glTranslated((deskArm.w*2 + 0.05f), 0.0f, -(deskCen.w));
    glRotated(180.0f, 0.0f, 1.0f, 0.0f);
    drawDesk();
    glRotated(-180.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(deskArm.w*2 + 0.05f), 0.0f, 1.0f);
    //desk 3
    glTranslated((deskArm.w*2 + 0.05f), 0.0f, (deskArm.d*2 + 0.05f));
    glRotated(180.0f, 0.0f, 1.0f, 0.0f);
    drawDesk();
    glRotated(-180.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(deskArm.w*2 + 0.05f), 0.0f, -(deskArm.d*2 + 0.05f));
    glTranslated(0.0f, 0.0f, (deskArm.d*2 + 0.05f));
    glTranslated(-(nDeskL.d + nDeskL.w - wall2.d), -desk_y, -(wall2.w - nDeskL.d - wall2.d));

    glPopMatrix();
    glPushMatrix();

    //desks divider
    glColor3f(0.85f, 0.85f, 0.85f); //divider color
    //divider 1
    glTranslated((deskArm.w + deskCen.d - deskDiv1.d - 0.02f - wall2.d - 0.05f), 0.0f, (wall2.w - (deskArm.d*2 + deskCen.w) - 0.05f - wall2.d));
    drawHexahedron(deskDiv1.w, deskDiv1.h, deskDiv1.d);
    //divider 2
    glTranslated(0.0f, 0.0f, -(deskCen.w + deskArm.d*2 + deskDiv1.d));
    drawHexahedron(deskDiv1.w, deskDiv1.h, deskDiv1.d);
    glTranslated(0.07f, 0.0f, (deskCen.w + deskArm.d*2 + deskDiv1.d));
    //divider 3
    glTranslated((deskArm.w - 0.02f), 0.0f, (deskCen.w + deskArm.d*2 + deskDiv2.d));
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    drawHexahedron(deskDiv2.w, deskDiv2.h, deskDiv2.d);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(deskArm.w - 0.02f), 0.0f, -(deskCen.w + deskArm.d*2 + deskDiv2.d));
    glTranslated(-(deskArm.w + deskCen.d - deskDiv1.d - 0.02f - wall2.d), 0.0f, -(wall2.w - (deskArm.d*2 + deskCen.w) - 0.05f - wall2.d));

    glPopMatrix();
}

void LaTIMModel::drawShelf()
{
    glPushMatrix();

    //Shelfs
    //Shelf Right (AC)
    glColor3f(0.75f, 0.75f, 0.75f); //desk color
    glTranslated(-wall2.d, desk_y, (wall2.w - wall2.d));
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    drawHexahedron(nDeskR.w, nDeskR.h, nDeskR.d);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(wall2.d, -desk_y, -(wall2.w - wall2.d));
    //Shelf Left (windows)
    glTranslated((nDeskL.d - wall2.d), desk_y, (wall2.w - nDeskL.d - wall2.d));
    drawHexahedron(nDeskL.w, nDeskL.h, nDeskL.d);
    glTranslated(-(nDeskL.d - wall2.d), -desk_y, -(wall2.w - nDeskL.d - wall2.d));

    glPopMatrix();
}

void LaTIMModel::drawComputers()
{
    drawMonitor(3.0f, desk_y + deskArm.h, 4.0f);
    drawCPU(2.65f, desk_y + deskArm.h, 4.50f);
}

void LaTIMModel::drawCPU(GLdouble x, GLdouble y, GLdouble z)
{
    glColor3f(0.1f, 0.1f, 0.1f); //cpu color
    glPushMatrix();

    glTranslated(x, y, z);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    drawHexahedron(0.20f, 0.35f, 0.50f);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-x, -y, -z);

    glPopMatrix();
}

void LaTIMModel::drawMonitor(GLdouble x, GLdouble y, GLdouble z)
{
    glColor3f(0.1f, 0.1f, 0.1f); //cpu color
    glPushMatrix();

    glTranslated(x, y + 0.10f, z);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    //Screen
    drawHexahedron(0.40f, 0.30f, 0.02f);
    glTranslated(0.0f, -0.10f, 0.0f);
    glTranslated((0.40f/2 - 0.05f/2), 0.0f, 0.0f);
    drawHexahedron(0.05f, 0.10f, 0.02f);
    glTranslated(-(0.40f/2 - 0.05f/2), 0.0f, 0.0f);
    //Base
    glTranslated(0.125f, 0.0f, -0.10f);
    drawHexahedron(0.15f, 0.01f, 0.15f);
    glTranslated(-0.125f, 0.0f, 0.10f);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-x, -y, -z);

    glPopMatrix();

}

void LaTIMModel::drawBlackboard()
{
    glPushMatrix();

    glTranslated(wall1.w - door.w - blackboard.w, wall1.h/2 - blackboard.h/2 - 0.10f, wall1.d);

    glColor3f(1.0f, 1.0f, 1.0f); //blackboard color
    glTranslated(blackboard.d, (blackboard.d), 0.0f);
    drawHexahedron(blackboard.w - blackboard.d*2, blackboard.h - blackboard.d*2, blackboard.d/2);
    glTranslated(-(blackboard.d), -(blackboard.d), 0.0f);

    glColor3f(0.5f, 0.5f, 0.5f); //blackboard color
    glTranslated(0.0f, blackboard.d, 0.0f);
    drawHexahedron(blackboard.d, blackboard.h - blackboard.d*2, blackboard.d);
    glTranslated(0.0f, -blackboard.d, 0.0f);

    drawHexahedron(blackboard.w, blackboard.d, blackboard.d);

    glTranslated((blackboard.w - blackboard.d), blackboard.d, 0.0f);
    drawHexahedron(blackboard.d, blackboard.h - blackboard.d*2, blackboard.d);
    glTranslated(-(blackboard.w - blackboard.d), -blackboard.d, 0.0f);

    glTranslated(0.0f, (blackboard.h - blackboard.d), 0.0f);
    drawHexahedron(blackboard.w, blackboard.d, blackboard.d);
    glTranslated(0.0f, -(blackboard.h - blackboard.d), 0.0f);

    glPopMatrix();
}

void LaTIMModel::drawCeiling()
{
    glPushMatrix();

    glColor3f(0.95f, 0.95f, 0.95f); //wall colors
    glTranslated(-(wall1.d*2), (wall1.h), 0.0f);
    drawHexahedron(wall1.w + (wall1.d*2), wall1.d, wall2.w);
    glTranslated((wall1.d*2), -(wall1.h), 0.0f);

    glPopMatrix();
}

void LaTIMModel::drawWindows()
{

}
