#include <cmath>
#include <random> 
#include <iostream>

using namespace std;

struct point {
  long double x;
  long double y;

  point(long double x, long double y): x(x), y(y) { }
};


long double dist(long double x1, long double x2, long double y1, long double y2) {
  return (x2 - x1) * (x2 - x1)  + (y2 - y1) * (y2 - y1); 
}

bool doesEqExist(point blue, point red) {
  // case 1:
  // blue_x <= 1 - blue_x and blue_y and 1 - blue_y 
  if (blue.x <= 0.5 && blue.x <= blue.y && blue.x <= 1 - blue.y) { 
    // 1a. red_y <= blue_y 
    if(red.y <= blue.y) {
      return dist(0, red.x, 0, red.y) <= dist(0, blue.x, 0, blue.y) && dist(0, red.x, 1, red.y) > dist(0, blue.x, 1, blue.y);
    }
    // 1b. red_y > blue_y 
    return dist(0, red.x, 1, red.y) <= dist(0, blue.x, 1, blue.y) && dist(0, red.x, 0, red.y) > dist(0, blue.x, 0, blue.y);
  } 

  // case 2:
  // 1 - blue_x < blue_x and blue_y and 1 - blue_y 
  else if (blue.x > 0.5 && 1 - blue.x < blue.y && 1 - blue.x < blue.y) {
    // 2a. red_y <= blue_y
    if(red.y <= blue.y) {
      return dist(1, red.x, 0, red.y) <= dist(1, blue.x, 0, blue.y) && dist(1, red.x, 1, red.y) > dist(1, blue.x, 1, blue.y);
    }
    // 2b. red_y > blue_y 
    return dist(1, red.x, 1, red.y) <= dist(1, blue.x, 1, blue.y) && dist(1, red.x, 0, red.y) > dist(1, blue.x, 0, blue.y);
  }

  // case 3: 
  // blue_y < blue_x and 1 - blue_x and 1 - blue_y 

  else if (blue.y <= 0.5 && blue.y < blue.x && blue.y < 1 - blue.x) {
    // 3a. red_x <= blue_x 
    if(red.x <= blue.x) {
      return dist(0, red.x, 0, red.y) <= dist(0, blue.x, 0, blue.y) && dist(1, red.x, 0, red.y) > dist(1, blue.x, 0, blue.y);
    }
    // 3b. red_x > blue_x
    return dist(1, red.x, 0, red.y) <= dist(1, blue.x, 0, blue.y) && dist(0, red.x, 0, red.y) > dist(0, blue.x, 0, blue.y);
  }
  // case 4:
  // 1 - blue_y < blue_x and 1 - blue_x and blue_y 
  else {
    // 4a. red_x <= blue_x 
    if(red.x <= blue.x) {
      return dist(0, red.x, 1, red.y) <= dist(0, blue.x, 1, blue.y) && dist(1, red.x, 1, red.y) > dist(1, blue.x, 1, blue.y);
    }
    // 4b. red_x > blue_x
    return dist(1, red.x, 1, red.y) <= dist(1, blue.x, 1, blue.y) && dist(0, red.x, 1, red.y) > dist(0, blue.x, 1, blue.y);
  }
}

long countTruth(long N) {
  long countTrue = 0;

  random_device rd;
  uniform_real_distribution<long double> dis(0.0, 1.0);
  mt19937_64 gen(rd());

  for(; N >= 0; N--) {
    point blue(dis(gen), dis(gen));
    point red(dis(gen), dis(gen));

    // cout << "Blue: (" <<  blue.x << ", " << blue.y << ")" << endl;
    // cout << "Red: (" <<  red.x << ", " << red.y << ")" << endl;

    countTrue += doesEqExist(blue, red);
  }

  return countTrue;
}

int main() { 
  long N = 1000000000000; 


  cout << "N: " << N << endl;

  long truthCount = countTruth(N);
  cout << "True: " << truthCount << endl;

  return 0;
}
