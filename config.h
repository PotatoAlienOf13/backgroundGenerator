#include "stdbool.h"
#include "structs.h"
const int surf_wid = 5720;
const int surf_hei = 1080;
int num_shapes = 100000;
int num_points = 100;



const int circleSize = 50;
double circleOpacity = 1;


double VSCmin = 10;


int numColors;
enum colorMethods {def, tintPoint};
int colorMethod = tintPoint;
color tintColor = {0,0,1};
double tintIntens = 0.2;

enum pointMethods {randPoints, gridPoints};
int pointMethod = gridPoints;
XY gridMargs = {0, 0};
XY gridDims = {240,250};


enum methods {onePoint,imaginePoint, twoPoints, twoPointsRP, twoPointsNG, twoPointsVSC, pointRange, pointBank};
int method = twoPoints;
double pointBankZeroDist = 1000;
double allPointPow = 40;

color imagineColor = {0.7,0.1,0.1};
double imagineDist =  10;

bool pixel = true;
XY recDims = {1,1};


bool debug = false;



enum colorProcessing {normal, crazyColors, squareMod, limits};
int colorProc = normal;

color upperColLim = {1,1,0.7};
color lowerColLim = {0,0.3,0};

double crazyColorsMult = 1.5;
double colorExpo = 2;
