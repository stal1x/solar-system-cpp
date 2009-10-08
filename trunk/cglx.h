//////////////////////////////////////////////////////////////////
// A basic framework designed for a monitor wall using CGLX.
//
// This file simply correctly includes CGLX or GLUT, each of which
// correctly include GLU and GL.
//
// Authors: Robert C. Duvall
//          Todd Berreth
//          Duke University
// Date   : 2009
//////////////////////////////////////////////////////////////////
// Includes
//
#ifdef DEF_USE_CGLX
  #ifdef __APPLE__
    #include <cglX/cglX.h>
  #else
    #include "cglX.h"
  #endif
    using namespace cglx;
#else
  #ifdef __APPLE__
    #include <GLUT/glut.h>
  #else
    #include <GL/glut.h>
  #endif
#endif
