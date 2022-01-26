// #include <iostream>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <AL/alut.h>

#define nx (1600) // Window size
#define ny (800) // window size

#define MAGICNUMBER1 (6)
#define MAGICNUMBER2 (9)

// Audio
ALuint sndBuffer, sndSource;

float width, height;

// Size/dimensions of the numbers on screen
float x1 = 200.f;
float y1 = 100.f;
float numthickness = 400.0;
float numhight = 600.0;
float numwidth = 60.0;
float bigwidth = (numhight-3.0*numwidth)/2;
float separationX = nx/2;

int listSize, *numVec;

int num1, num2; // Pair of random generated numbers
bool flag = false; // Flag for when we hit a 69

int count, picounter = 0; // Seed for the rrandom generator
int celebration = 0; // Number of frames the celebration will last

float FPS = 1.0;
int initial_time = time(NULL); // Timer for controlling the fps
int final_time, frame_count; // More fram/fps stuff

int initGL(int *argc, char **argv);
void resize(int w, int h);
void keyboard(unsigned char key, int x, int y);
void idle(int);

void numSelector(int num, float x1, float y1, 
  float numthickness, float numhight, float numwidth, bool flag);
void drawZero(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag);
void drawOne(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag);
void drawTwo(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag);
void drawThree(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag);
void drawFour(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag);
void drawFive(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag);
void drawSix(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag);
void drawSeven(float x1, float y1, float numthickness,
  float numhight, float numwidth, bool flag);
void drawEight(float x1, float y1, float numthickness,
  float numhight, float numwidth, bool flag);
void drawNine(float x1, float y1, float numthickness,
  float numhight, float numwidth, bool flag);

void sound(void);
void tuneSelection(int track);



void display(void) {

  if (count > listSize) {
    printf("No more numbers in the list");
    exit(0);
  }

  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // My 69 detector
  if ((num1 == MAGICNUMBER1) && (num2 == MAGICNUMBER2)) {

    sound();

    flag = true;
    numSelector(MAGICNUMBER1,x1,y1,numthickness,numhight,numwidth,flag);
    numSelector(MAGICNUMBER2,x1+separationX,y1,numthickness,numhight,numwidth,flag);


    celebration++;
    if (celebration > 2) {
      num1 = numVec[count];
      num2 = numVec[count+1];
      count++;
      celebration = 0;
      picounter++;
      printf("Beautiful event %d\n",picounter);
    }

    FPS = 1.0;

  } else {

    flag = false;
    numSelector(num1,x1,y1,numthickness,numhight,numwidth,flag);
    numSelector(num2,x1+separationX,y1,numthickness,numhight,numwidth,flag);
    count++;
    num1 = numVec[count];
    num2 = numVec[count+1];
    FPS = 1.0;

  }

  glutSwapBuffers();

  // Count frames per second
  frame_count++;
  final_time = time(NULL);
  if ( (final_time - initial_time) > 0) {
    // frames drawn / time taken (seconds)
    // printf("FPS : %d\n", frame_count / (final_time-initial_time));
    frame_count = 0;
    initial_time = final_time;
  }

}

void sound(void) {

  srand(time(NULL));
  tuneSelection(rand()%3);
  alGenSources (1, &sndSource); 
  alSourcei (sndSource, AL_BUFFER, sndBuffer);
  alSourcePlay (sndSource);
  alutSleep(2);
}

void drawZero(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numthickness,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numthickness,y1+numhight); // northeast
    glColor3f(1.0,0.0,1.0); glVertex2d(x1,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numthickness,y1); // southeast
    glVertex2d(x1+numthickness,y1+numhight); // northeast
    glVertex2d(x1,y1+numhight); // northwest
    glVertex2d(x1,y1); // southwest
    glEnd();
  }

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+numwidth);
  glVertex2d(x1+numthickness-numwidth,y1+numhight-numwidth);
  glVertex2d(x1+numwidth, y1+numhight-numwidth);
  glVertex2d(x1+numwidth,y1+numwidth);
  glEnd();

}

void drawOne(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numwidth+(numthickness-numwidth)/2,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numwidth+(numthickness-numwidth)/2,y1+numhight); // noetheast
    glColor3f(1.0,0.0,1.0); glVertex2d(x1+(numthickness-numwidth)/2,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+(numthickness-numwidth)/2,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numwidth+(numthickness-numwidth)/2,y1); // southeast
    glVertex2d(x1+numwidth+(numthickness-numwidth)/2,y1+numhight); // noetheast
    glVertex2d(x1+(numthickness-numwidth)/2,y1+numhight); // northwest
    glVertex2d(x1+(numthickness-numwidth)/2,y1); // southwest
    glEnd();
  }

}

void drawTwo(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numthickness,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numthickness,y1+numhight); // northeast
    glColor3f(0.0,0.0,1.0); glVertex2d(x1,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numthickness,y1); // southeast
    glVertex2d(x1+numthickness,y1+numhight); // northeast
    glVertex2d(x1,y1+numhight); // northwest
    glVertex2d(x1,y1); // southwest
    glEnd();
  }

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness,y1+numwidth); // southeast
  glVertex2d(x1+numthickness,y1+numwidth+bigwidth); // northeast
  glVertex2d(x1+numwidth,y1+numwidth+bigwidth); // northwest
  glVertex2d(x1+numwidth,y1+numwidth); // southwest
  glEnd();

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+2*numwidth+bigwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+2*numwidth+2*bigwidth); // northeast
  glVertex2d(x1,y1+2*numwidth+2*bigwidth); // northwest
  glVertex2d(x1,y1+2*numwidth+bigwidth); // southwest
  glEnd();

}

void drawThree(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numthickness,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numthickness,y1+numhight); // northeast
    glColor3f(0.0,0.0,1.0); glVertex2d(x1,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numthickness,y1); // southeast
    glVertex2d(x1+numthickness,y1+numhight); // northeast
    glVertex2d(x1,y1+numhight); // northwest
    glVertex2d(x1,y1); // southwest
    glEnd();
  }

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+numwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+numwidth+bigwidth); // northeast
  glVertex2d(x1,y1+numwidth+bigwidth); // northwest
  glVertex2d(x1,y1+numwidth); // southwest
  glEnd();

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+2*numwidth+bigwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+2*numwidth+2*bigwidth); // northeast
  glVertex2d(x1,y1+2*numwidth+2*bigwidth); // northwest
  glVertex2d(x1,y1+2*numwidth+bigwidth); // southwest
  glEnd();

}

void drawFour(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numthickness,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numthickness,y1+numhight); // northeast
    glColor3f(0.0,0.0,1.0); glVertex2d(x1,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numthickness,y1); // southeast
    glVertex2d(x1+numthickness,y1+numhight); // northeast
    glVertex2d(x1,y1+numhight); // northwest
    glVertex2d(x1,y1); // southwest
    glEnd();
  }

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+numwidth+bigwidth); // northeast
  glVertex2d(x1,y1+numwidth+bigwidth); // northwest
  glVertex2d(x1,y1); // southwest
  glEnd();

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+2*numwidth+bigwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+3*numwidth+2*bigwidth); // northeast
  glVertex2d(x1+numwidth,y1+3*numwidth+2*bigwidth); // northwest
  glVertex2d(x1+numwidth,y1+2*numwidth+bigwidth); // southwest
  glEnd();

}

void drawFive(float x1, float y1, float numthickness, 
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numthickness,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numthickness,y1+numhight); // northeast
    glColor3f(0.0,0.0,1.0); glVertex2d(x1,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numthickness,y1); // southeast
    glVertex2d(x1+numthickness,y1+numhight); // northeast
    glVertex2d(x1,y1+numhight); // northwest
    glVertex2d(x1,y1); // southwest
    glEnd();
  }

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+numwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+numwidth+bigwidth); // northeast
  glVertex2d(x1,y1+numwidth+bigwidth); // northwest
  glVertex2d(x1,y1+numwidth); // southwest
  glEnd();

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness,y1+2*numwidth+bigwidth); // southeast
  glVertex2d(x1+numthickness,y1+2*numwidth+2*bigwidth); // northeast
  glVertex2d(x1+numwidth,y1+2*numwidth+2*bigwidth); // northwest
  glVertex2d(x1+numwidth,y1+2*numwidth+bigwidth); // southwest
  glEnd();

}

void drawSix(float x1, float y1, float numthickness,
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numthickness,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numthickness,y1+numhight); // northeast
    glColor3f(0.0,0.0,1.0); glVertex2d(x1,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numthickness,y1); // southeast
    glVertex2d(x1+numthickness,y1+numhight); // northeast
    glVertex2d(x1,y1+numhight); // northwest
    glVertex2d(x1,y1); // southwest
    glEnd();
  }

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+numwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+numwidth+bigwidth); // northeast
  glVertex2d(x1+numwidth,y1+numwidth+bigwidth); // northwest
  glVertex2d(x1+numwidth,y1+numwidth); // southwest
  glEnd();

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness,y1+2*numwidth+bigwidth); // southeast
  glVertex2d(x1+numthickness,y1+2*numwidth+2*bigwidth); // northeast
  glVertex2d(x1+numwidth,y1+2*numwidth+2*bigwidth); // northwest
  glVertex2d(x1+numwidth,y1+2*numwidth+bigwidth); // southwest
  glEnd();

}

void drawSeven(float x1, float y1, float numthickness,
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numthickness,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numthickness,y1+numhight); // northeast
    glColor3f(0.0,0.0,1.0); glVertex2d(x1,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numthickness,y1); // southeast
    glVertex2d(x1+numthickness,y1+numhight); // northeast
    glVertex2d(x1,y1+numhight); // northwest
    glVertex2d(x1,y1); // southwest
    glEnd();
  }

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+numwidth-numwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+numhight-numwidth); // northeast
  glVertex2d(x1,y1+numhight-numwidth); // northwest
  glVertex2d(x1,y1); // southwest
  glEnd();

}

void drawEight(float x1, float y1, float numthickness,
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numthickness,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numthickness,y1+numhight); // northeast
    glColor3f(0.0,0.0,1.0); glVertex2d(x1,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numthickness,y1); // southeast
    glVertex2d(x1+numthickness,y1+numhight); // northeast
    glVertex2d(x1,y1+numhight); // northwest
    glVertex2d(x1,y1); // southwest
    glEnd();
  }

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+numwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+numwidth+bigwidth); // northeast
  glVertex2d(x1+numwidth,y1+numwidth+bigwidth); // northwest
  glVertex2d(x1+numwidth,y1+numwidth); // southwest
  glEnd();

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+2*numwidth+bigwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+2*numwidth+2*bigwidth); // northeast
  glVertex2d(x1+numwidth,y1+2*numwidth+2*bigwidth); // northwest
  glVertex2d(x1+numwidth,y1+2*numwidth+bigwidth); // southwest
  glEnd();

}

void drawNine(float x1, float y1, float numthickness,
  float numhight, float numwidth, bool flag) {

  if (flag) {
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0); glVertex2d(x1+numthickness,y1); // southeast
    glColor3f(0.0,1.0,0.0); glVertex2d(x1+numthickness,y1+numhight); // northeast
    glColor3f(0.0,0.0,1.0); glVertex2d(x1,y1+numhight); // northwest
    glColor3f(1.0,0.0,0.0); glVertex2d(x1,y1); // southwest
    glEnd();
  } else {
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(x1+numthickness,y1); // southeast
    glVertex2d(x1+numthickness,y1+numhight); // northeast
    glVertex2d(x1,y1+numhight); // northwest
    glVertex2d(x1,y1); // southwest
    glEnd();
  }

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+numwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+numwidth+bigwidth); // northeast
  glVertex2d(x1,y1+numwidth+bigwidth); // northwest
  glVertex2d(x1,y1+numwidth); // southwest
  glEnd();

  glColor3d(0.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2d(x1+numthickness-numwidth,y1+2*numwidth+bigwidth); // southeast
  glVertex2d(x1+numthickness-numwidth,y1+2*numwidth+2*bigwidth); // northeast
  glVertex2d(x1+numwidth,y1+2*numwidth+2*bigwidth); // northwest
  glVertex2d(x1+numwidth,y1+2*numwidth+bigwidth); // southwest
  glEnd();

}


void numSelector(int num, float x1, float y1, 
  float numthickness, float numhight, float numwidth, bool flag) {

  switch (num) {

    case 0:
      // printf("%f\n",x1);// excecutes double?
      drawZero(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    case 1:
      drawOne(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    case 2:
      drawTwo(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    case 3:
      drawThree(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    case 4:
      drawFour(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    case 5:
      drawFive(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    case 6:
      drawSix(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    case 7:
      drawSeven(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    case 8:
      drawEight(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    case 9:
      drawNine(x1,y1,numthickness,numhight,numwidth,flag);
    break;

    default:
      puts("No number");
    break;

    }

}

void tuneSelection(int track) {

  switch (track) {

    case 0:
      sndBuffer = alutCreateBufferFromFile("./common/LetsDrink!.wav");
    break;

    case 1:
      sndBuffer = alutCreateBufferFromFile("./common/Air-Horn2.wav");
    break;

    case 2:
      sndBuffer = alutCreateBufferFromFile("./common/iamtheprotectorofthissystem.wav");
    break;

    default:
      puts("No track available");
    break;

  }
}

int initGL(int *argc, char **argv) {

  /*------------------------------------------------------------------------
  * Graphics stuff. Do not later
  *------------------------------------------------------------------------
  */

  //
  // Iinitialise OpenGL display - use glut
  //
  glutInit(argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(nx, ny);                   // Window of nx x ny pixels
  glutInitWindowPosition(200, 50);               // Window position

  glutCreateWindow("pi69app         version 0.1.69");         // Window title

  printf("Loading extensions: %s\n", glewGetErrorString(glewInit()));
  if(!glewIsSupported(
                      "GL_VERSION_2_0 "
                      "GL_ARB_pixel_buffer_object "
                      "GL_EXT_framebuffer_object "
                      )){
      fprintf(stderr, "ERROR: Support for necessary OpenGL extensions missing.");
      fflush(stderr);
      return 1;
  }

  // Set up view
  glClearColor(0.0,0.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,nx,0.,ny, -200.0, 200.0);

  printf("Starting GLUT main loop...\n");

  glutKeyboardFunc(keyboard);
  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutTimerFunc(1000/FPS,idle,0); // Timer function will be called after 1000/FPS
  // glutIdleFunc(idle);

  glutMainLoop();

  return true;

}

void resize(int w, int h) {

  // GLUT resize callback to allow us to change the window size

  width = w;
  height = h;
  glViewport (0, 0, w, h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho (0., nx, 0., ny, -200. ,200.);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

}

void idle(int) {
  glutPostRedisplay();
  glutTimerFunc(1000/FPS,idle,0); // Timer function will be called after 1000/FPS
}

void keyboard(unsigned char key, int x, int y) {

  switch (key) {

    case 27:
      exit(0);
	  break;

    default:
      puts("No function assigned to this key");
    break;

    }
}

int main(int argc, char **argv)  {

  // Load number to array

  FILE *fp;
  int i, num;

  fp = fopen("./common/elongList.txt", "r");

  if (fp==NULL) {
    printf("Error: can't open file \n");
    exit(0);
  }

  fscanf(fp, "%d", &listSize);
  printf("List size %d\n",listSize);
  numVec = (int*)malloc(listSize*sizeof(int));

  for (i=0;i<listSize;i++) {
    fscanf(fp, "%d", &num);
    // printf("Number :  %d\n", num );
    numVec[i] = (int)num;
  }

  fclose(fp);

  num1 = numVec[0];
  num2 = numVec[1];
  count = -1;

  // Create audio objects

  alutInit (&argc, argv);
  // sndBuffer = alutCreateBufferFromFile("./common/LetsDrink!.wav");

  // Rendering OpenGl

  if (false == initGL(&argc, argv)) exit(0);

  return 0;
}
