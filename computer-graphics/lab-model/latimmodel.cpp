#include "latimmodel.h"
#include <math.h>
#include <iostream>

LaTIMModel::LaTIMModel()
{
    wall1 = Object(6.90f, 3.0f, 0.10f);
    wall2 = Object(7.80f, 3.0f, 0.10f);
    deskArm = Object(1.40f, 0.05f, 0.55f);
    deskCen = Object(1.40f, 0.05f, 0.55f);
    nDeskR = Object(4.16f, 0.05f, 0.55f);
    nDeskL = Object(1.63f, 0.05f, 0.55f);
    deskDiv1 = Object(deskArm.w*2 + 0.15f, 1.20f, 0.05f);
    deskDiv2 = Object(deskArm.d*4 + deskCen.w*2 + 0.05f, 1.20f, 0.05f);
    cabinet1 = Object(0.80f, 2.08f, 0.57f);
    cabinet2 = Object(1.0f, 2.20f, 0.57f);
    door = Object(1.0f, 2.20f, 0.05f);
    computer1 = Object();
    window1 = Object(0.575f, 1.15f, 0.10f);
    window2 = Object(0.575f, 0.575f, 0.10f);
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
    drawWhiteboard();

    //Ceiling
    drawCeiling();

    //Lamps
    drawLamps();

    /*
     * Chairs
     * Windows
     * Keyboard
     * Mouse
     */
    glPopMatrix();
}

void LaTIMModel::halfCylinder3d(GLdouble radius, GLdouble width, bool bottom, bool top)
{
    GLdouble x              = 0.0f;
    GLdouble y              = 0.0f;
    GLdouble angle          = 0.0f;
    GLdouble angle_stepsize = 0.05f;
    GLdouble PI = 3.1415f;

    if(bottom) {
        // Draw the circle on bottom of cylinder
        glBegin(GL_POLYGON);
        angle = 0.0;
        while( angle < PI ) {
            x = radius * sin(angle);
            y = radius * cos(angle);
            glVertex3f(x, y, 0.0f);
            angle = angle + angle_stepsize;
        }
        //glVertex3f(radius, 0.0, 0.0f);
        glEnd();
    }

    // Draw the tube
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, width);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    //glVertex3f(radius, 0.0, width);
    //glVertex3f(radius, 0.0, 0.0);
    glEnd();

    if(top) {
        // Draw the circle on top of cylinder
        glBegin(GL_POLYGON);
        angle = 0.0;
        while( angle < PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , width);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, width);
        glEnd();
    }
}

void LaTIMModel::cylinder3d(GLdouble radius, GLdouble width, bool bottom, bool top)
{
    GLdouble x              = 0.0f;
    GLdouble y              = 0.0f;
    GLdouble angle          = 0.0f;
    GLdouble angle_stepsize = 0.05f;
    GLdouble PI = 3.1415f;

    if(bottom) {
        // Draw the circle on bottom of cylinder
        glBegin(GL_POLYGON);
        angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * sin(angle);
            y = radius * cos(angle);
            glVertex3f(x, y, 0.0f);
            angle = angle + angle_stepsize;
        }
        //glVertex3f(radius, 0.0, 0.0f);
        glEnd();
    }

    // Draw the tube
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, width);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, width);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    if(top) {
        // Draw the circle on top of cylinder
        glBegin(GL_POLYGON);
        angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , width);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, width);
        glEnd();
    }
}

void LaTIMModel::hexahedron3d(GLdouble w, GLdouble h, GLdouble d)
{
    //front side
    rect3d(   w, 0.0f, 0.0f,
             0.0f, 0.0f, 0.0f,
             0.0f,    h, 0.0f,
                w,    h, 0.0f);

    //back side
    rect3d(0.0f, 0.0f,    d,
                w, 0.0f,    d,
                w,    h,    d,
             0.0f,    h,    d);

    //left side
    rect3d(0.0f, 0.0f, 0.0f,
             0.0f, 0.0f,    d,
             0.0f,    h,    d,
             0.0f,    h, 0.0f);

    //right side
    rect3d(   w, 0.0f, 0.0f,
                w,    h, 0.0f,
                w,    h,    d,
                w, 0.0f,    d);

    //bottom side
    rect3d(0.0f, 0.0f, 0.0f,
                w, 0.0f, 0.0f,
                w, 0.0f,    d,
             0.0f, 0.0f,    d);

    //top side
    rect3d(   w,    h, 0.0f,
             0.0f,    h, 0.0f,
             0.0f,    h,    d,
                w,    h,    d);
}

void LaTIMModel::rect3d(GLdouble p1_x, GLdouble p1_y, GLdouble p1_z,
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
    hexahedron3d(deskArm.w, deskArm.h, deskArm.d);
    glTranslated(0.02f, -desk_y, 0.0f);
    hexahedron3d(deskArm.h, desk_y, deskArm.d);
    glTranslated(-0.02f, desk_y, 0.0f);
    //middle
    glTranslated(deskArm.w, 0.0f, -(deskCen.w));
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    hexahedron3d(deskCen.w, deskCen.h, deskCen.d);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-deskArm.w, 0.0f, (deskCen.w));
    // left side
    glTranslated(0.0f, 0.0f, -(deskCen.w + deskArm.d));
    hexahedron3d(deskArm.w, deskArm.h, deskArm.d);
    glTranslated(0.02f, -desk_y, 0.0f);
    hexahedron3d(deskArm.h, desk_y, deskArm.d);
    glTranslated(-0.02f, desk_y, 0.0f);
    glTranslated(0.0f, 0.0f, (deskCen.w + deskArm.d));
}

void LaTIMModel::drawCabinet(GLdouble w, GLdouble h, GLdouble d)
{
    //right side
    rect3d(0.0f, 0.0f, 0.0f,
             0.0f,    h, 0.0f,
             0.0f,    h,    d,
             0.0f, 0.0f,    d);

    //left side
    rect3d(   w, 0.0f, 0.0f,
                w, 0.0f,    d,
                w,    h,    d,
                w,    h, 0.0f);

    //bottom side
    rect3d(0.0f, 0.0f, 0.0f,
             0.0f, 0.0f,    d,
                w, 0.0f,    d,
                w, 0.0f, 0.0f);

    //top side
    rect3d(0.0f,    h, 0.0f,
                w,    h, 0.0f,
                w,    h,    d,
             0.0f,    h,    d);

    glColor3f(0.85f, 0.85f, 0.85f); //cabinet color
    //back side
    rect3d(0.0f, 0.0f,    d,
                w, 0.0f,    d,
                w,    h,    d,
             0.0f,    h,    d);

    glColor3f(0.6f, 0.6f, 0.6f); //cabinet color
    //right door
    rect3d(           0.0f, 0.0f, 0.0f,
                w/2 - 0.005f, 0.0f, 0.0f,
                w/2 - 0.005f,    h, 0.0f,
                        0.0f,    h, 0.0f);

    //left door
    rect3d(w/2 + 0.005f, 0.0f, 0.0f,
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
    hexahedron3d(door.w, door.h, -door.d);
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
    hexahedron3d(0.1f, wall1.h, wall1.d);
    glTranslated((0.1f), 0.0f, 0.0f);
    //wall above the door
    glColor3f(0.9f, 0.9f, 0.9f); //wall colors
    glTranslated(0.0f, door.h, 0.0f);
    hexahedron3d(door.w, wall1.h - door.h, wall1.d);
    glTranslated(0.0f, -door.h, 0.0f);
    //wall on the left of the door
    glTranslated(-(0.1f), 0.0f, 0.0f);
    glTranslated((0.1f + door.w), 0.0f, 0.0f);
    hexahedron3d(wall1.w - 0.1f - door.w, wall1.h, wall1.d);
    glTranslated(-(0.1f + door.w), 0.0f, 0.0f);

    //Wall1 (windows)
    //front wall
    //space between windows
    GLdouble space = (wall1.w - (window1.w*4)*2) / 3;
    glTranslated(0.0f, 0.0f, (wall2.w - wall2.d));
    hexahedron3d(space, wall1.h, wall1.d);
    glTranslated(space, 0.0f, 0.0f);
    hexahedron3d((window1.w*4), 1.0f, wall1.d);
    //draw right window
    drawWindow();
    glTranslated((window1.w*4), 0.0f, 0.0f);
    hexahedron3d(space, wall1.h, wall1.d);
    glTranslated(space, 0.0f, 0.0f);
    hexahedron3d((window1.w*4), 1.0f, wall1.d);
    //draw left window
    drawWindow();
    glTranslated((window1.w*4), 0.0f, 0.0f);
    hexahedron3d(space, wall1.h, wall1.d);

    glTranslated(-((window1.w*8) + space*2), 0.0f, -(wall2.w - wall2.d));

    //Wall2 (in front of the AC wall)
    glTranslated(wall1.w, 0.0f, wall2.w);
    glRotated(-90.0f, 0.0f, -1.0f, 0.0f);
    hexahedron3d(wall2.w, wall2.h, wall2.d);
    glRotated(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslated(-wall1.w, 0.0f, -wall2.w);

    //Wall2 (AC)
    glRotated(90.0f, 0.0f, -1.0f, 0.0f);
    hexahedron3d(wall2.w, wall2.h, wall2.d);
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
    glTranslated(-(deskArm.w*2 + 0.05f), 0.0f, (deskCen.w));
    //desk 3
    glTranslated((deskCen.w*2 + 0.05f), 0.0f, (deskArm.d*2 + 0.05f));
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
    glTranslated((nDeskL.w + nDeskR.d - wall2.d - deskDiv1.d), 0.0f, (wall2.w - (deskArm.d*2 + deskCen.w) - 0.05f - wall2.d));
    hexahedron3d(deskDiv1.w, deskDiv1.h, deskDiv1.d);
    //divider 2
    glTranslated(0.0f, 0.0f, -(deskCen.w + deskArm.d*2 + deskDiv1.d));
    hexahedron3d(deskDiv1.w, deskDiv1.h, deskDiv1.d);
    glTranslated(0.07f, 0.0f, (deskCen.w + deskArm.d*2 + deskDiv1.d));
    //divider 3
    glTranslated((deskArm.w - 0.02f), 0.0f, (deskCen.w + deskArm.d*2 + deskDiv2.d));
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    hexahedron3d(deskDiv2.w, deskDiv2.h, deskDiv2.d);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(deskArm.w - 0.02f), 0.0f, -(deskCen.w + deskArm.d*2 + deskDiv2.d));
    glTranslated(-(nDeskL.w + nDeskR.d - wall2.d - deskDiv1.d), 0.0f, -(wall2.w - (deskArm.d*2 + deskCen.w) - 0.05f - wall2.d));

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
    hexahedron3d(nDeskR.w, nDeskR.h, nDeskR.d);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(wall2.d, -desk_y, -(wall2.w - wall2.d));
    //Shelf Left (windows)
    glTranslated((nDeskL.d - wall2.d), desk_y, (wall2.w - nDeskL.d - wall2.d));
    hexahedron3d(nDeskL.w, nDeskL.h, nDeskL.d);
    glTranslated(-(nDeskL.d - wall2.d), -desk_y, -(wall2.w - nDeskL.d - wall2.d));

    glPopMatrix();
}

void LaTIMModel::drawComputers()
{
    GLdouble pc_x[4], pc_z[4];
    pc_x[0] = nDeskR.d + nDeskL.w + deskArm.w - 0.62f;
    pc_z[0] = wall2.w - 0.20f;
    pc_x[1] = nDeskR.d + nDeskL.w + deskArm.w - 0.62f;
    pc_z[1] = wall2.w - 0.25f - deskCen.w;
    pc_x[2] = nDeskR.d + nDeskL.w + deskArm.w - 0.62f;
    pc_z[2] = wall2.w - 0.20f - (deskArm.d*2 + deskCen.w);
    pc_x[3] = nDeskR.d + nDeskL.w + deskArm.w - 0.62f;
    pc_z[3] = wall2.w - 0.25f- (deskArm.d + deskCen.w)*2;

    glPushMatrix();

    drawMonitor(pc_x[0] + 0.40f, desk_y + deskArm.h, pc_z[0] - 0.50f);
    drawCPU(pc_x[0], desk_y + deskArm.h, pc_z[0]);
    drawMonitor(pc_x[1] + 0.40f, desk_y + deskArm.h, pc_z[1]);
    drawCPU(pc_x[1], desk_y + deskArm.h, pc_z[1] - 0.70f);
    drawMonitor(pc_x[2] + 0.40f, desk_y + deskArm.h, pc_z[2] - 0.50f);
    drawCPU(pc_x[2], desk_y + deskArm.h, pc_z[2]);
    drawMonitor(pc_x[3] + 0.40f, desk_y + deskArm.h, pc_z[3]);
    drawCPU(pc_x[3], desk_y + deskArm.h, pc_z[3] - 0.70f);

    glPopMatrix();
    glPushMatrix();

    glRotated(180.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(wall1.w + 0.12f), 0.0f, -(wall2.w + wall2.w/3 - 0.05f));

    drawMonitor(pc_x[0] + 0.40f, desk_y + deskArm.h, pc_z[0] - 0.50f);
    drawCPU(pc_x[0], desk_y + deskArm.h, pc_z[0]);
    drawMonitor(pc_x[1] + 0.40f, desk_y + deskArm.h, pc_z[1]);
    drawCPU(pc_x[1], desk_y + deskArm.h, pc_z[1] - 0.70f);
    drawMonitor(pc_x[2] + 0.40f, desk_y + deskArm.h, pc_z[2] - 0.50f);
    drawCPU(pc_x[2], desk_y + deskArm.h, pc_z[2]);
    drawMonitor(pc_x[3] + 0.40f, desk_y + deskArm.h, pc_z[3]);
    drawCPU(pc_x[3], desk_y + deskArm.h, pc_z[3] - 0.70f);

    glTranslated((wall1.w + 0.12f), 0.0f, (wall2.w + wall2.w/3 - 0.05f));
    glRotated(-180.0f, 0.0f, 1.0f, 0.0f);
    glPopMatrix();

}

void LaTIMModel::drawCPU(GLdouble x, GLdouble y, GLdouble z)
{
    glColor3f(0.1f, 0.1f, 0.1f); //cpu color
    glPushMatrix();

    glTranslated(x, y, z);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    hexahedron3d(0.20f, 0.35f, 0.50f);
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
    hexahedron3d(0.40f, 0.30f, 0.02f);
    glTranslated(0.0f, -0.10f, 0.0f);
    glTranslated((0.40f/2 - 0.05f/2), 0.0f, 0.0f);
    hexahedron3d(0.05f, 0.10f, 0.02f);
    glTranslated(-(0.40f/2 - 0.05f/2), 0.0f, 0.0f);
    //Base
    glTranslated(0.125f, 0.0f, -0.10f);
    hexahedron3d(0.15f, 0.01f, 0.15f);
    glTranslated(-0.125f, 0.0f, 0.10f);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-x, -y, -z);

    glPopMatrix();

}

void LaTIMModel::drawWhiteboard()
{
    glPushMatrix();

    glTranslated(wall1.w - door.w - blackboard.w, wall1.h/2 - blackboard.h/2 - 0.10f, wall1.d);

    glColor3f(1.0f, 1.0f, 1.0f); //blackboard color
    glTranslated(blackboard.d, (blackboard.d), 0.0f);
    hexahedron3d(blackboard.w - blackboard.d*2, blackboard.h - blackboard.d*2, blackboard.d/2);
    glTranslated(-(blackboard.d), -(blackboard.d), 0.0f);

    glColor3f(0.5f, 0.5f, 0.5f); //blackboard color
    glTranslated(0.0f, blackboard.d, 0.0f);
    hexahedron3d(blackboard.d, blackboard.h - blackboard.d*2, blackboard.d);
    glTranslated(0.0f, -blackboard.d, 0.0f);

    hexahedron3d(blackboard.w, blackboard.d, blackboard.d);

    glTranslated((blackboard.w - blackboard.d), blackboard.d, 0.0f);
    hexahedron3d(blackboard.d, blackboard.h - blackboard.d*2, blackboard.d);
    glTranslated(-(blackboard.w - blackboard.d), -blackboard.d, 0.0f);

    glTranslated(0.0f, (blackboard.h - blackboard.d), 0.0f);
    hexahedron3d(blackboard.w, blackboard.d, blackboard.d);
    glTranslated(0.0f, -(blackboard.h - blackboard.d), 0.0f);

    glPopMatrix();
}

void LaTIMModel::drawCeiling()
{
    glPushMatrix();

    glColor3f(0.95f, 0.95f, 0.95f); //wall colors
    glTranslated(-(wall1.d*2), (wall1.h), 0.0f);
    hexahedron3d(wall1.w + (wall1.d*2), wall1.d, wall2.w);
    glTranslated((wall1.d*2), -(wall1.h), 0.0f);

    glPopMatrix();
}

void LaTIMModel::drawWindow()
{
    glPushMatrix();

    glTranslated(0.0f, 1.0f, 0.0f);
    //drawWindow1
    glTranslated(0.0f, window1.h, 0.0f);
    hexahedron3d((window1.w*4), 0.10f, wall1.d);
    glTranslated(0.0f, 0.10f, 0.0f);
    //drawWindow2
    glTranslated(0.0f, window2.h, 0.0f);
    hexahedron3d((window1.w*4), (wall1.h - 1.10f - window1.h - window2.h), wall1.d);

    glTranslated(0.0f, -window2.h, 0.0f);
    glTranslated(0.0f, -0.10f, 0.0f);
    glTranslated(0.0f, -window1.h, 0.0f);
    glTranslated(0.0f, -1.0f, 0.0f);

    glPopMatrix();
}

void LaTIMModel::drawLamp(GLdouble radius, GLdouble width)
{
    GLdouble caseWidth = width/7;
    GLdouble tubeRadius = radius - radius/3;
    GLdouble tubeWidth = width - (caseWidth)*2;

    glPushMatrix();

    //left case
    glColor3f(0.9f, 0.9f, 0.9f);
    cylinder3d(radius, caseWidth, true, false);

    glTranslated(0.0f, 0.0f, caseWidth/2);

    //Tube
    glColor3f(1.0f, 1.0f, 1.0f);
    cylinder3d(tubeRadius, tubeWidth, true, true);

    glTranslated(0.0f, 0.0f, caseWidth/2);

    //Top case
    glColor3f(0.9f, 0.9f, 0.9f);
    halfCylinder3d(radius, tubeWidth - caseWidth, false, false);

    glTranslated(0.0f, 0.0f, tubeWidth - caseWidth);

    //Right case
    glColor3f(0.9f, 0.9f, 0.9f);
    cylinder3d(radius, caseWidth, false, true);

    glTranslated(0.0f, 0.0f, -(tubeWidth));

    glPopMatrix();
}

void LaTIMModel::drawLamps()
{
    GLdouble piece1 = wall1.w/3;
    GLdouble piece2 = wall2.w/4;
    GLdouble lampRadius = 0.05f;
    GLdouble lampWidth = 2.0f;

    glPushMatrix();

    glTranslated(0.0f, (wall1.h - wall1.d/2), 0.0f);
    glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(0.0f, 0.0f, wall2.d);

    for(int i = 0; i < 3; ++i) {
        glTranslated((piece2 + i*piece2), 0.0f, -(piece1 + lampWidth/3));
        drawLamp(lampRadius, lampWidth);

        glTranslated(0.0f, 0.0f, -(piece1 + lampWidth/3));
        drawLamp(lampRadius, lampWidth);
        glTranslated(0.0f, 0.0f, (piece1 + lampWidth/3));

        glTranslated(-(piece2 + i*piece2), 0.0f, (piece1 + lampWidth/3));
    }

    glTranslated(0.0f, 0.0f, -wall2.d);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(0.0f, -(wall1.h - wall1.d/2), 0.0f);

    glPopMatrix();
}
