#include "block.h"

// Return "distance" between rightmost column of this (leftBlock)
// and leftmost column of rightBlock
double Block::distanceTo(Block const & rightBlock) const {
  int h = height();
  int w = width();
  double d = 0.0;
  for( int y=0; y<h; ++y ) {
    if( data[w-1][y] != rightBlock.data[0][y] ) d = d+1;
  }
  d = d/h;
  return d;
}
