#pragma once

class Rect {
public:
  int x, y, w, h;

  Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

  int area() const { return w * h; }
};
