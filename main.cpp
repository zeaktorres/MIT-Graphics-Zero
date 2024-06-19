
#include <GL/glut.h>
#include <vecmath/vecmath.h>
#include <vecmath/Vector3f.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "include/ColorPicker.h"
#include "include/KeboardEvents.h"
#include "include/LightPicker.h"

// Globals
KeyboardEvents *keyboardEventManager = new KeyboardEvents();
typedef void (ColorPicker::*Update)(int *colorChoice);
auto srcPath = "/home/zeak/Projects/MIT-Computer-Graphics-Linux/zero";
auto includePath =
    "/home/zeak/Projects/MIT-Computer-Graphics-Linux/zero/include";
ColorPicker dataColorPickers;
LightPicker *lightPicker;
// This is the list of points (3D vectors)
std::vector<Vector3f> vecv;

// This is the list of normals (also 3D vectors)
std::vector<Vector3f> vecn;

// This is the list of faces (indices into vecv and vecn)
std::vector<std::vector<std::vector<unsigned>>> vecf;

// Color picker
int colorChoice = 0;
int MAX_COLORS = 4;

// You will need more global variables to implement color and position changes

// These are convenience functions which allow us to call OpenGL
// methods on Vec3d objects
inline void glVertex(const GLfloat *a) { glVertex3fv(a); }

inline void glNormal(const GLfloat *a) { glNormal3fv(a); }

// This function is called whenever a "Normal" key press iutPostRedisplay after
// the update, whis received.
void keyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
    case 27:  // Escape key
      exit(0);
      break;
    case 'c':
      // add code to change color here
      keyboardEventManager->emit("cPress", 1);
      break;
    default:
      std::cout << "Unhandled key press " << key << "." << std::endl;
  }

  // this will refresh the screen so that the user sees the color change
  glutPostRedisplay();
}

// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      // add code to change light position
      lightPicker->UpdateSecond(0.5);
      break;
    case GLUT_KEY_DOWN:
      // add code to change light position
      lightPicker->UpdateSecond(-0.5);
      break;
    case GLUT_KEY_LEFT:
      // add code to change light position
      lightPicker->UpdateFirst(-0.5);
      break;
    case GLUT_KEY_RIGHT:
      // add code to change light position
      lightPicker->UpdateFirst(0.5);
      break;
  }

  // this will refresh the screen so that the user sees the light position
  glutPostRedisplay();
}

// This function is responsible for displaying the object.
void drawScene(void) {
  int i;

  // Clear the rendering window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Rotate the image
  glMatrixMode(GL_MODELVIEW);  // Current matrix affects objects positions
  glLoadIdentity();            // Initialize to the identity

  // Position the camera at [0,0,5], looking at [0,0,0],
  // with [0,1,0] as the up direction.
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  // Set material properties of object

  // Here are some colors you might use - feel free to add more
  GLfloat diffColors[4][4] = {{0.5, 0.5, 0.9, 1.0},
                              {0.9, 0.5, 0.5, 1.0},
                              {0.5, 0.9, 0.3, 1.0},
                              {0.3, 0.8, 0.9, 1.0}};

  // Here we use the first color entry as the diffuse color
  glMaterialfv(
      GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,
      diffColors[dataColorPickers.getColorChoice()]);

  // Define specular color and shininess
  GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat shininess[] = {100.0};

  // Note that the specular color and shininess can stay constant
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  // Set light properties

  // Light color (RGBA)
  GLfloat Lt0diff[] = {1.0, 1.0, 1.0, 1.0};
  // Light position

  glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPicker->getLightPosition());

  // This GLUT method draws a teapot.  You should replace
  // it with code which draws the object you loaded.
  glutSolidTeapot(1.0);

  // Dump the image to the screen.
  glutSwapBuffers();
}

// Initialize OpenGL's rendering modes
void initRendering() {
  glEnable(GL_DEPTH_TEST);  // Depth testing must be turned on
  glEnable(GL_LIGHTING);    // Enable lighting calculations
  glEnable(GL_LIGHT0);      // Turn on light #0.
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h) {
  // Always use the largest square viewport possible
  if (w > h) {
    glViewport((w - h) / 2, 0, h, h);
  } else {
    glViewport(0, (h - w) / 2, w, w);
  }

  // Set up a perspective view, with square aspect ratio
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // 50 degree fov, uniform aspect ratio, near = 1, far = 100
  gluPerspective(50.0, 1.0, 1.0, 100.0);
}

void loadInput() {
  // load the OBJ file here
    std::string fileName = "torus.obj";

    std::ifstream inFile(fileName);

    if (inFile.is_open()) {
        std::string line;

        while (std::getline(inFile, line)) {
            if (line.length() == 0)
                continue;

            std::string token;
            std::vector<std::string> tokens;
            std::stringstream readLine(line);
            while (std::getline(readLine, token, ' ')) {
                tokens.push_back(token);
            }

            if (tokens[0][0] == 'v') {
                vecv.push_back(Vector3f(std::stof(&token[1]),
                            std::stof(&token[2]), std::stof(&token[3])));
            }

            if (tokens[0][0] == 'f') {
                std::vector<std::vector<unsigned>> face;
                for (int i = 1; i < tokens.size(); i++) {
                    std::stringstream readFaceLine(tokens[i]);
                    std::string faceVN;
                    std::vector<unsigned> faceVNs;
                    while (std::getline(readFaceLine, faceVN, '/')) {
                        faceVNs.push_back(std::stoi(faceVN));
                    }
                    face.push_back(faceVNs);
                }
                vecf.push_back(face);
            }

            if (tokens[0][0] == 'v' && tokens[0][1] == 'n') {
                vecn.push_back(Vector3f(std::stof(&token[1]),
                            std::stof(&token[2]), std::stof(&token[3])));
            }
        }
    }
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main(int argc, char **argv) {
  // Setup keyboard events
  keyboardEventManager->on("cPress", [&]() { dataColorPickers.Update(1); });

  GLfloat Lt0pos[] = {1.0f, 1.0f, 5.0f, 1.0f};
  lightPicker = new LightPicker();
  lightPicker->Init(Lt0pos, 0);
  loadInput();

  glutInit(&argc, argv);

  // We're going to animate it, so double buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Initial parameters for window position and size
  glutInitWindowPosition(60, 60);
  glutInitWindowSize(360, 360);
  glutCreateWindow("Assignment 0");

  // Initialize OpenGL parameters.
  initRendering();

  // Set up callback functions for key presses
  glutKeyboardFunc(keyboardFunc);  // Handles "normal" ascii symbols
  glutSpecialFunc(specialFunc);    // Handles "special" keyboard keys

  // Set up the callback function for resizing windows
  glutReshapeFunc(reshapeFunc);

  // Call this whenever window needs redrawing
  glutDisplayFunc(drawScene);

  // Start the main loop.  glutMainLoop never returns.
  glutMainLoop();
  return 0;
}
