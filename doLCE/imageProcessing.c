//
// doLCE - do Lenticular film Color rEconstruction -
// Copyright (C) 2012 Joakim Reuteler

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 3 as 
// published by the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// _______________________________________________________________________ 



// imageProcessing.c
// - implementation of simple operations on images


#include "imageProcessing.h"

#include <stdio.h>
#include <stdlib.h>
#include "imageHandling.h"




// *** unary operations ***
// ************************

int addGl_glImage( glImage_t *glImage, int gl ) {
    int status = 0;
    
    int i, j;
    int minGl, maxGl;
    
    if ( glImage->img == NULL ) {
        status = -1;
        printf( "ERROR: addGl_glImage(): Cannot add gray level to empty image.\n" );
    }
    
    if ( status == 0 ) {
        for ( j=0; j<glImage->height; j++ ) {
            for ( i=0; i<glImage->width; i++ ) {
                glImage->img[j][i] += gl;
            }
        }
    }
    
    return status;
}


int multiplyGl_glImage( glImage_t *glImage, float factor ) {
  int status = 0;

  int width;
  int i, j;

  if ( glImage->img==NULL || glImage->memState!=1 ) {
    status = -1;
    printf ( "ERROR: multiplyGl_glImage(): Invalid argument ''\n" );
  }
  else if ( factor<0.0 ) {
    status = -1;
    printf ( "ERROR: multiplyGl_glImage(): Invalid argument ''\n" );
  }

  if ( status == 0 ) {
    width = glImage->width;
    for ( j=0; j<glImage->height; j++ ) {
      for ( i=0; i<width; i++ ) {
	glImage->img[j][i] = (int)( factor * glImage->img[j][i] );
      }
    }
  }

  return status;
}





int setValue_rgbImage( rgbImage_t *rgbImage, int value ) {
int status = 0;

  int i, j;
  int width, height, c;

  if ( rgbImage->img==NULL || rgbImage->memState!=1 ) {
    status = -1;
    printf ( "ERROR: setZero_rgbImage(): Invalid argument 'rgbImage->img==NULL || rgbImage->memState!=1'\n" );
  }
  
  if ( status == 0 ) {
    width = rgbImage->width;
    height = rgbImage->height;
    for ( c=0; c<3; c++ ) {
      for ( j=0; j<height; j++ ) {
        for ( i=0; i<width; i++ ) {
          rgbImage->img[c][j][i] = value;
        }
      }
    }
  }

  return status;
}



int multiplyVal_rgbImage( rgbImage_t *rgbImage, float factors[3] ) {
    int status = 0;
    
    int i, j;
    int width, height, c;
    
    if ( rgbImage->img==NULL || rgbImage->memState!=1 ) {
        status = -1;
        printf ( "ERROR: multiplyVal_rgbImage(): Invalid argument 'rgbImage->img==NULL || rgbImage->memState!=1'\n" );
    }
    
    if ( status == 0 ) {
        width = rgbImage->width;
        height = rgbImage->height;
        for ( c=0; c<3; c++ ) {
            for ( j=0; j<height; j++ ) {
                for ( i=0; i<width; i++ ) {
                    rgbImage->img[c][j][i] = (int)(factors[c]*rgbImage->img[c][j][i]);
                }
            }
        }
    }
    
    return status;    
}


int subtractVal_rgbImage( rgbImage_t *rgbImage, int values[3] ){
    int status = 0;
    
    int i, j;
    int width, height, c;
    
    if ( rgbImage->img==NULL || rgbImage->memState!=1 ) {
        status = -1;
        printf ( "ERROR: subtractVal_rgbImage(): Invalid argument 'rgbImage->img==NULL || rgbImage->memState!=1'\n" );
    }
    
    if ( status == 0 ) {
        width = rgbImage->width;
        height = rgbImage->height;
        for ( c=0; c<3; c++ ) {
            for ( j=0; j<height; j++ ) {
                for ( i=0; i<width; i++ ) {
                    rgbImage->img[c][j][i] -= values[c];
                }
            }
        }
    }
    
    return status;    
}

// *** binary operations ***
// *************************
int add_glImage_to_rgbImage( glImage_t *glImage, rgbImage_t *rgbImage, int channel ) {
  int status = 0;

  int i, j;
  int width;

  if ( glImage->img==NULL || glImage->memState!=1 ) {
    status = -1;
    printf ( "ERROR: add_glImage_to_rgbImage(): Invalid argument 'glImage->img==NULL || glImage->memState!=1'\n" );
  }
  else if ( rgbImage->img==NULL || rgbImage->memState!=1 ) {
    status = -1;
    printf ( "ERROR: add_glImage_to_rgbImage(): Invalid argument 'rgbImage->img==NULL || rgbImage->memState!=1'\n" );
  }
  else if ( channel<0 || channel>2 ) {
    status = -1;
    printf ( "ERROR: add_glImage_to_rgbImage(): Invalid argument 'channel<0 || channel>2'\n" );
  }
  else if ( glImage->width!=rgbImage->width || glImage->height!=rgbImage->height ) {
    status = -1;
    printf ( "ERROR: add_glImage_to_rgbImage(): Unequal image dimensions.\n" );
  }

  if ( status == 0 ) {
    width = glImage->width;
    for ( j=0; j<glImage->height; j++ ) {
      for ( i=0; i<width; i++ ) {
	rgbImage->img[channel][j][i] += glImage->img[j][i];
      }
    }
  }


  return status;
}













