
#ifdef __APPLE__

#include <GLUT/glut.h>

#else

#include <GL/glut.h>

#endif

 

#include <cstdlib>

#include <iostream>

#include <sstream>

#include <iomanip>

//#include "Matrices.h"

#include "Vectors.h"

 

using std::stringstream;

using std::cout;

using std::endl;

using std::ends;

 

//==================================================
 

#include <cmath>

#include <algorithm>

#include "Matrices.h"

 

const float DEG2RAD = 3.141593f / 180;

///////////////////////////////////////////////////////////////////////////////

// translate this matrix by (x, y, z)

///////////////////////////////////////////////////////////////////////////////

Matrix4& Matrix4::translate(const Vector3& v)

{

    return translate(v.x, v.y, v.z);

}

 

Matrix4& Matrix4::translate(float x, float y, float z)

{

    m[0] += m[12]*x;   m[1] += m[13]*x;   m[2] += m[14]*x;   m[3] += m[15]*x;

    m[4] += m[12]*y;   m[5] += m[13]*y;   m[6] += m[14]*y;   m[7] += m[15]*y;

    m[8] += m[12]*z;   m[9] += m[13]*z;   m[10]+= m[14]*z;   m[11]+= m[15]*z;

    return *this;

}

 

///////////////////////////////////////////////////////////////////////////////

// uniform scale

///////////////////////////////////////////////////////////////////////////////

Matrix4& Matrix4::scale(float s)

{

    return scale(s, s, s);

}

 

Matrix4& Matrix4::scale(float x, float y, float z)

{

    m[0] = m[0]*x;   m[1] = m[1]*x;   m[2] = m[2]*x;   m[3] = m[3]*x;

    m[4] = m[4]*y;   m[5] = m[5]*y;   m[6] = m[6]*y;   m[7] = m[7]*y;

    m[8] = m[8]*z;   m[9] = m[9]*z;   m[10]= m[10]*z;  m[11]= m[11]*z;

    return *this;

}

 

///////////////////////////////////////////////////////////////////////////////

// build a rotation matrix with given angle(degree) and rotation axis, then

// multiply it with this object

///////////////////////////////////////////////////////////////////////////////

Matrix4& Matrix4::rotate(float angle, const Vector3& axis)

{

    return rotate(angle, axis.x, axis.y, axis.z);

}

 

Matrix4& Matrix4::rotate(float angle, float x, float y, float z)

{
	//normalize ()
 	float d = sqrt(x*x+y*y+z*z); 
 	x=fabs(x/d); 
 	y=fabs(y/d); 
 	z=fabs(z/d); 

    float c = cosf(angle * DEG2RAD);    // cosine

    float s = sinf(angle * DEG2RAD);    // sine

    float xx = x * x;

    float xy = x * y;

    float xz = x * z;

    float yy = y * y;

    float yz = y * z;

    float zz = z * z;
 	

    // build rotation matrix

    Matrix4 m;

    m[0] = xx * (1 - c) + c;

    m[1] = xy * (1 - c) - z * s;

    m[2] = xz * (1 - c) + y * s;

    m[3] = 0;

    m[4] = xy * (1 - c) + z * s;

    m[5] = yy * (1 - c) + c;

    m[6] = yz * (1 - c) - x * s;

    m[7] = 0;

    m[8] = xz * (1 - c) - y * s;

    m[9] = yz * (1 - c) + x * s;

    m[10]= zz * (1 - c) + c;

    m[11]= 0;

    m[12]= 0;

    m[13]= 0;

    m[14]= 0;

    m[15]= 1;

 

    // multiply it

    *this = m * (*this);

 

    return *this;

}

 

Matrix4& Matrix4::rotateX(float angle)

{

    float c = cosf(angle * DEG2RAD);

    float s = sinf(angle * DEG2RAD);

    float m4 = m[4], m5 = m[5], m6 = m[6],  m7 = m[7],

          m8 = m[8], m9 = m[9], m10= m[10], m11= m[11];

 

    m[4] = m4 * c + m8 *-s;

    m[5] = m5 * c + m9 *-s;

    m[6] = m6 * c + m10*-s;

    m[7] = m7 * c + m11*-s;

    m[8] = m4 * s + m8 * c;

    m[9] = m5 * s + m9 * c;

    m[10]= m6 * s + m10* c;

    m[11]= m7 * s + m11* c;

 

    return *this;

}

 

Matrix4& Matrix4::rotateY(float angle)

{

    float c = cosf(angle * DEG2RAD);

    float s = sinf(angle * DEG2RAD);

    float m0 = m[0], m1 = m[1], m2 = m[2],  m3 = m[3],

          m8 = m[8], m9 = m[9], m10= m[10], m11= m[11];

 

    m[0] = m0 * c + m8 * s;

    m[1] = m1 * c + m9 * s;

    m[2] = m2 * c + m10* s;

    m[3] = m3 * c + m11* s;

    m[8] = m0 *-s + m8 * c;

    m[9] = m1 *-s + m9 * c;

    m[10]= m2 *-s + m10* c;

    m[11]= m3 *-s + m11* c;

 

    return *this;

}

 

Matrix4& Matrix4::rotateZ(float angle)

{

    float c = cosf(angle * DEG2RAD);

    float s = sinf(angle * DEG2RAD);

    float m0 = m[0], m1 = m[1], m2 = m[2],  m3 = m[3],

          m4 = m[4], m5 = m[5], m6 = m[6],  m7 = m[7];

 

    m[0] = m0 * c + m4 *-s;

    m[1] = m1 * c + m5 *-s;

    m[2] = m2 * c + m6 *-s;

    m[3] = m3 * c + m7 *-s;

    m[4] = m0 * s + m4 * c;

    m[5] = m1 * s + m5 * c;

    m[6] = m2 * s + m6 * c;

    m[7] = m3 * s + m7 * c;

 

    return *this;

}

 

 

//===================================================

 

// GLUT CALLBACK functions

void displayCB();

void reshapeCB(int w, int h);

void timerCB(int millisec);

void idleCB();

void keyboardCB(int key, int x, int y);

void mouseCB(int button, int stat, int x, int y);

void mouseMotionCB(int x, int y);

 

void initGL();

int  initGLUT(int argc, char **argv);

bool initSharedMem();

void clearSharedMem();

void initLights();

void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);

void drawString(const char *str, int x, int y, float color[4], void *font);

void showInfo();

void toOrtho();

void toPerspective();

void drawAxis(float size=4.0f);

void drawModel();


Matrix4 setFrustum(float l, float r, float b, float t, float n, float f);

Matrix4 setFrustum(float fovY, float aspectRatio, float front, float back);

 

// constants

const int   SCREEN_WIDTH    = 600;

const int   SCREEN_HEIGHT   = 600;

const float CAMERA_DISTANCE = 6.0f;

const int   TEXT_WIDTH      = 8;

const int   TEXT_HEIGHT     = 13;

//const float DEG2RAD         = 3.141593f / 180;

 

// global variables

void *font = GLUT_BITMAP_8_BY_13;

int screenWidth;

int screenHeight;

bool mouseLeftDown;

bool mouseRightDown;

float mouseX, mouseY;

float Px = 2.0f;
float Py = 1.0f;
float Pz = 2.0f;

float Qx = 4.0f;
float Qy = 3.0f;
float Qz = 2.0f;
float cameraAngleX;

float cameraAngleY;

float cameraAngleZ;

float cameraAngleBK;

float camereTulaX;

float camereTulaY;

float camereTulaZ;

float bdX=1.0f;

float bdY=1.0f;

float bdZ=1.0f;

float cameraDistance;

int drawMode = 0;

Matrix4 matrixView;

Matrix4 matrixModel;

Matrix4 matrixModelView;    // = matrixView * matrixModel

Matrix4 matrixProjection;

 

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)

{  	initSharedMem();

    initGLUT(argc, argv);

    initGL();

    glutMainLoop(); /* Start GLUT event-processing loop */

    return 0;
}

 

 

///////////////////////////////////////////////////////////////////////////////

// draw the local axis of an object

///////////////////////////////////////////////////////////////////////////////

void drawAxis(float size)

{

    glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines

    glDisable(GL_LIGHTING);

 

    // draw axis

    glLineWidth(3);

    glBegin(GL_LINES);

        glColor3f(1, 0, 0);			//red

        glVertex3f(0, 0, 0);

        glVertex3f(size, 0, 0);

        glColor3f(0, 1, 0);			//green

        glVertex3f(0, 0, 0);

        glVertex3f(0, size, 0);

        glColor3f(0, 0, 1);			//blue

        glVertex3f(0, 0, 0);

        glVertex3f(0, 0, size);

    glEnd();

    glLineWidth(1);

 

    // draw arrows(actually big square dots)

    glPointSize(5);

    glBegin(GL_POINTS);

        glColor3f(1, 0, 0);

        glVertex3f(size, 0, 0);

        glColor3f(0, 1, 0);

        glVertex3f(0, size, 0);

        glColor3f(0, 0, 1);

        glVertex3f(0, 0, size);

    glEnd();

    glPointSize(1);

 	// ve vector PQ
	glBegin(GL_LINES);
	  glColor3f(0.0, 1.0, 0.0);
	  glVertex3f(Px, Py, Pz);
	  glVertex3f(Qx, Qy, Qz);
	  glEnd();

    // restore default settings
    glPointSize(1);

 	// ve vector chi phuong PQ
	glBegin(GL_LINES);
	  glColor3f(0.0, 1.0, 0.0);
	  glVertex3f(0, 0, 0);
	  glVertex3f(Qx-Px, Qy-Py, Qz-Pz);
	  glEnd();
    

    glEnable(GL_LIGHTING);

    glDepthFunc(GL_LEQUAL);

}

 

///////////////////////////////////////////////////////////////////////////////

// draw a model (tetrahedron)

///////////////////////////////////////////////////////////////////////////////

void drawModel()

{
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
	
	
}

 

///////////////////////////////////////////////////////////////////////////////

// initialize GLUT for windowing

///////////////////////////////////////////////////////////////////////////////

int initGLUT(int argc, char **argv)

{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

    glutInitWindowSize(screenWidth, screenHeight);  // window size

    glutInitWindowPosition(100, 100);           // window location

    int handle = glutCreateWindow("doan xem");     // param is the title of window

    glutDisplayFunc(displayCB);

    glutReshapeFunc(reshapeCB);

    glutSpecialFunc(keyboardCB);

    return handle;

}

 

///////////////////////////////////////////////////////////////////////////////

// initialize OpenGL

// disable unused features

///////////////////////////////////////////////////////////////////////////////

void initGL()

{

    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

 

    // enable /disable features

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);

 

    // enable /disable features

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);

 

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_COLOR_MATERIAL);

 

    glClearColor(0, 0, 0, 0);                   // background color

    glClearStencil(0);                          // clear stencil buffer

    glClearDepth(1.0f);                         // 0 is near, 1 is far

    glDepthFunc(GL_LEQUAL);

 

    initLights();

}

 
void initLights()

{

    // set up light colors (ambient, diffuse, specular)

    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light

    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light

    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);

    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

 

    // position the light

    float lightPos[4] = {0, 0, 20, 1}; // positional light

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

 

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration

}

 
 

 

///////////////////////////////////////////////////////////////////////////////

// write 2d text using GLUT

// The projection matrix must be set to orthogonal before call this function.

///////////////////////////////////////////////////////////////////////////////

void drawString(const char *str, int x, int y, float color[4], void *font)

{

    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask

    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

    glDisable(GL_TEXTURE_2D);

 

    glColor4fv(color);          // set text color

    glRasterPos2i(x, y);        // place text position

 

    // loop all characters in the string

    while(*str)

    {

        glutBitmapCharacter(font, *str);

        ++str;

    }

 

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);

    glPopAttrib();

}

///////////////////////////////////////////////////////////////////////////////

// initialize global variables

///////////////////////////////////////////////////////////////////////////////

bool initSharedMem()

{

    screenWidth = SCREEN_WIDTH;

    screenHeight = SCREEN_HEIGHT;

 

    mouseLeftDown = mouseRightDown = false;

    mouseX = mouseY = 0;

 

    cameraAngleX = cameraAngleY = 0;

    cameraDistance = CAMERA_DISTANCE;

 

    drawMode = 0; // 0:fill, 1: wireframe, 2:points

 

    return true;

}
 

///////////////////////////////////////////////////////////////////////////////

// display info messages

///////////////////////////////////////////////////////////////////////////////

void showInfo()

{

    // backup current model-view matrix

    glPushMatrix();                     // save current modelview matrix

    glLoadIdentity();                   // reset modelview matrix

 

    // set to 2D orthogonal projection

    glMatrixMode(GL_PROJECTION);        // switch to projection matrix

    glPushMatrix();                     // save current projection matrix

    glLoadIdentity();                   // reset projection matrix

    gluOrtho2D(0, screenWidth, 0, screenHeight); // set to orthogonal projection

 

    float color[4] = {1, 1, 1, 1};

 

    stringstream ss;

    ss << std::fixed << std::setprecision(3);

 

    drawString("=== View Matrix ===", 0, screenHeight-TEXT_HEIGHT, color, font);

    ss << "[" << std::setw(8) << matrixView[0] << std::setw(8) << matrixView[1] << std::setw(8) << matrixView[2] << std::setw(8) << matrixView[3] << "]" << ends;

    drawString(ss.str().c_str(), 0, screenHeight-(2*TEXT_HEIGHT), color, font);

    ss.str("");

    ss << "[" << std::setw(8) << matrixView[4] << std::setw(8) << matrixView[5] << std::setw(8) << matrixView[6] << std::setw(8) << matrixView[7] << "]" << ends;

    drawString(ss.str().c_str(), 0, screenHeight-(3*TEXT_HEIGHT), color, font);

    ss.str("");

    ss << "[" << std::setw(8) << matrixView[8] << std::setw(8) << matrixView[9] << std::setw(8) << matrixView[10]<< std::setw(8) << matrixView[11]<< "]" << ends;

    drawString(ss.str().c_str(), 0, screenHeight-(4*TEXT_HEIGHT), color, font);

    ss.str("");

    ss << "[" << std::setw(8) << matrixView[12]<< std::setw(8) << matrixView[13]<< std::setw(8) << matrixView[14]<< std::setw(8) << matrixView[15]<< "]" << ends;

    drawString(ss.str().c_str(), 0, screenHeight-(5*TEXT_HEIGHT), color, font);

    ss.str("");

 

    drawString("=== Model Matrix ===", 0, 4*TEXT_HEIGHT, color, font);

    ss << "[" << std::setw(8) << matrixModel[0] << std::setw(8) << matrixModel[1] << std::setw(8) << matrixModel[2] << std::setw(8) << matrixModel[3] << "]" << ends;

    drawString(ss.str().c_str(), 0, 3*TEXT_HEIGHT, color, font);

    ss.str("");

    ss << "[" << std::setw(8) << matrixModel[4] << std::setw(8) << matrixModel[5] << std::setw(8) << matrixModel[6] << std::setw(8) << matrixModel[7] << "]" << ends;

    drawString(ss.str().c_str(), 0, 2*TEXT_HEIGHT, color, font);

    ss.str("");

    ss << "[" << std::setw(8) << matrixModel[8] << std::setw(8) << matrixModel[9] << std::setw(8) << matrixModel[10]<< std::setw(8) << matrixModel[11]<< "]" << ends;

    drawString(ss.str().c_str(), 0, TEXT_HEIGHT, color, font);

    ss.str("");

    ss << "[" << std::setw(8) << matrixModel[12]<< std::setw(8) << matrixModel[13]<< std::setw(8) << matrixModel[14]<< std::setw(8) << matrixModel[15]<< "]" << ends;

    drawString(ss.str().c_str(), 0, 0, color, font);

    ss.str("");

 

    // unset floating format

    ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

 

    // restore projection matrix

    glPopMatrix();                   // restore to previous projection matrix

 

    // restore modelview matrix

    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix

    glPopMatrix();                   // restore to previous modelview matrix

}

///////////////////////////////////////////////////////////////////////////////

// set the projection matrix as perspective

///////////////////////////////////////////////////////////////////////////////

void toPerspective()

{

    // set viewport to be the entire window

    glViewport(0, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);

 

    // set perspective viewing frustum

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(60.0f, (float)(screenWidth)/screenHeight, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

 

    // switch to modelview matrix in order to set scene

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}

///////////////////////////////////////////////////////////////////////////////

// set a perspective frustum with 6 params similar to glFrustum()

// (left, right, bottom, top, near, far)

// Note: this is for row-major notation. OpenGL needs transpose it

///////////////////////////////////////////////////////////////////////////////

Matrix4 setFrustum(float l, float r, float b, float t, float n, float f)

{

    Matrix4 mat;

    mat[0]  =  2 * n / (r - l);

    mat[2]  =  (r + l) / (r - l);

    mat[5]  =  2 * n / (t - b);

    mat[6]  =  (t + b) / (t - b);

    mat[10] = -(f + n) / (f - n);

    mat[11] = -(2 * f * n) / (f - n);

    mat[14] = -1;

    mat[15] =  0;

    return mat;

}

 

///////////////////////////////////////////////////////////////////////////////

// set a symmetric perspective frustum with 4 params similar to gluPerspective

// (vertical field of view, aspect ratio, near, far)

///////////////////////////////////////////////////////////////////////////////

Matrix4 setFrustum(float fovY, float aspectRatio, float front, float back)

{

    float tangent = tanf(fovY/2 * DEG2RAD);   // tangent of half fovY

    float height = front * tangent;           // half height of near plane

    float width = height * aspectRatio;       // half width of near plane

 

    // params: left, right, bottom, top, near, far

    return setFrustum(-width, width, -height, height, front, back);

}

 


//=============================================================================

// CALLBACKS

//=============================================================================

 

void displayCB()

{

    // clear buffer

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

 

    // save the initial ModelView matrix before modifying ModelView matrix

    glPushMatrix();

 

    // tramsform camera

    matrixView.identity();

    matrixView.rotate(0, 0, 1, 0);

    matrixView.rotate(0, 1, 0, 0);

    matrixView.translate(-1, -1, -cameraDistance);//-1,-1.-cameraDistance

    
 

    // Copy view matrix to OpenGL

    glLoadMatrixf(matrixView.getTranspose());

    // Compute model matrix

    matrixModel.identity();

    matrixModel.rotateZ(0);        

    matrixModel.rotateY(0);        

	matrixModel.rotateX(0); // 15'C

    matrixModel.translate(0, 0, 0); // move 2 unit up

 	

    // Compute modelview matrix

    matrixModelView = matrixView * matrixModel;

 

    // Copy modelview matrix to OpenGL

    glLoadMatrixf(matrixModelView.getTranspose());

 

    drawAxis();
    
    // tramsform camera

    matrixView.identity();
	// quay quanh ox,oy,oz
    matrixView.rotateZ(cameraAngleZ);

    matrixView.rotateY(cameraAngleY);

    matrixView.rotateX(cameraAngleX);
    //quay quanh truc bat ky PQ
    matrixView.rotate(cameraAngleBK, Px-Qx, Py-Qy, Pz-Qz);
    
	//  tinh tien
    matrixView.translate(camereTulaX-1, camereTulaY-1, camereTulaZ-cameraDistance);
	//bien dang
	matrixView.scale(bdX,bdY,bdZ);

 	matrixModelView = matrixView * matrixModel;

    // Copy view matrix to OpenGL

    glLoadMatrixf(matrixModelView.getTranspose());

    drawModel();

 

    // Draw info messages

    showInfo();

    glPopMatrix();

    glutSwapBuffers();

}

 

 

void reshapeCB(int w, int h)

{

    screenWidth = w;

    screenHeight = h;

 

    // set viewport to be the entire window

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

 

    // set perspective viewing frustum

    glMatrixMode(GL_PROJECTION);

    matrixProjection = setFrustum(80, (float)w/h, 1.0f, 100.0f);

    glLoadMatrixf(matrixProjection.getTranspose());

    // The equivalent OpenGL call

    // gluPerspective(45.0f, (float)(w)/h, 1.0f, 100.0f); // FOV, AspectRatio, NearClip, FarClip

 

    // DEBUG

    std::cout << "===== Projection Matrix =====\n";

    std::cout << matrixProjection << std::endl;

 

    // switch to modelview matrix in order to set scene

    glMatrixMode(GL_MODELVIEW);
}

 

 

void keyboardCB(int key, int x, int y)

{

    if (key == GLUT_KEY_END) 	exit(0); 
//quay	
	if (key == GLUT_KEY_UP) 	    cameraAngleY +=10.0f; 	
	if (key == GLUT_KEY_RIGHT)	    cameraAngleX +=10.0f; 
	if (key == GLUT_KEY_LEFT)	    cameraAngleZ +=10.0f; 
//quay quanh truc bat ky
	if (key == GLUT_KEY_DOWN)     	cameraAngleBK+=10.0f;
//tinh tien	
	if (key == GLUT_KEY_F1)         camereTulaX-=0.1f;
	if (key == GLUT_KEY_F2)     	camereTulaX+=0.1f;
	if (key == GLUT_KEY_F3)     	camereTulaY-=0.1f;
	if (key == GLUT_KEY_F4)     	camereTulaY+=0.1f;
	if (key == GLUT_KEY_F5)     	camereTulaZ-=0.1f;
	if (key == GLUT_KEY_F6)     	camereTulaZ+=0.1f;	
//bien dang
	if (key == GLUT_KEY_F7)         bdX-=0.1f;
	if (key == GLUT_KEY_F8)     	bdX+=0.1f;
	if (key == GLUT_KEY_F9)     	bdY-=0.1f;
	if (key == GLUT_KEY_F10)     	bdY+=0.1f;
	if (key == GLUT_KEY_F11)     	bdZ-=0.1f;
	if (key == GLUT_KEY_F12)     	bdZ+=0.1f;
	
	glutPostRedisplay();

} 

