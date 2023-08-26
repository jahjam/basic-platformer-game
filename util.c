#include "util.h"

double collision(double x1, double y1, double h1, double w1, double x2, double y2, double w2, double h2){
    return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}