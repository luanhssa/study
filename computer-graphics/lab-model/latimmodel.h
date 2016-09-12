#ifndef CEPETECBUILD_H
#define CEPETECBUILD_H

#include <QtOpenGL>

typedef struct Object {
    GLdouble w, h, d;

    Object() {}	// constructor
    Object(GLdouble width, GLdouble height, GLdouble depth) {
        w = width;
        h = height;
        d = depth;
    }
}Object;

class LaTIMModel
{
public:
    LaTIMModel();
    void draw();
    void moveDoor();
    int doorPos = 1;
    GLdouble doorAngle = 0.0f;

private:
    /**
     * wall1: wall that contains the window or the door
     * wall2: wall that contains cabinets
     * deskArm: desk arm side
     * deskCen: desk centre side
     * nDeskL: new desk left side
     * nDeskR: new desk right side
     */
    Object wall1,
            wall2,
            deskArm,
            deskCen,
            nDeskR,
            nDeskL,
            deskDiv1,
            deskDiv2,
            cabinet1,
            cabinet2,
            door,
            computer1,
            window1,
            blackboard,
            chair1;

    /**
     * desk_y: height of the desk from the floor
     */
    GLdouble desk_y = 0.7f;


    void cylinder3d(GLdouble radius, GLdouble width, bool bottom, bool top);
    void halfCylinder3d(GLdouble radius, GLdouble width, bool bottom, bool top);
    void hexahedron3d(GLdouble width, GLdouble height, GLdouble depth);
    void rect3d(GLdouble p1_x, GLdouble p1_y, GLdouble p1_z,
                  GLdouble p2_x, GLdouble p2_y, GLdouble p2_z,
                  GLdouble p3_x, GLdouble p3_y, GLdouble p3_z,
                  GLdouble p4_x, GLdouble p4_y, GLdouble p4_z);
    void drawDesk();
    void drawCabinet(GLdouble w, GLdouble h, GLdouble d);
    void drawDoor();
    void drawWalls();
    void drawCabinets();
    void drawDesks();
    void drawShelf();
    void drawWindows();
    void drawComputers();
    void drawCPU(GLdouble x, GLdouble y, GLdouble z);
    void drawMonitor(GLdouble x, GLdouble y, GLdouble z);
    void drawBlackboard();
    void drawCeiling();
    void drawLamp(GLdouble radius, GLdouble width);
    void drawLamps();
};

#endif // CEPETECBUILD_H
