#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  if (data.empty()) return 0;
  return data[0].size();
}

int Block::width() const {
  return data.size();
}

void Block::render(PNG &im, int x) const {

  for (int y = 0; y < im.height(); y++) {
    for (int i = x; i < x + width() && i < im.width(); i++) {
      *im.getPixel(i, y) = data[i - x][y];
    }
  }
}

void Block::build(PNG &im, int x, int width) {

  vector<HSLAPixel> yStrip(im.height());
   data.assign(width, yStrip);

   for (int y = 0; y < im.height(); y++) {
      for (int i = x; i < x + width; i++) {
         data[i-x][y] = *im.getPixel(i, y);
        }
    }
}
