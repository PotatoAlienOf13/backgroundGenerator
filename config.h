#include "stdbool.h"
#include "structs.h"
const int surf_wid = 1920;
const int surf_hei = 1080;
int num_shapes = 20000;
int num_points = 10;



const int circleSize = 20;
double circleOpacity = 1;


double VSCmin = 10;


int numColors;
enum colorMethods {def, tintPoint};
int colorMethod = def;
color tintColor = {0,0,1};
double tintIntens = 0.5;

enum pointMethods {randPoints, gridPoints};
int pointMethod = gridPoints;
XY gridMargs = {60, 40};
XY gridDims = {300,250};


enum methods {onePoint,imaginePoint, twoPoints, twoPointsRP, twoPointsNG, twoPointsVSC, pointRange, pointBank};
int method = twoPoints;

color imagineColor = {1,0,0};
double imagineDist =  250;

double pointBankZeroDist = 50;
double allPointPow = 40;

bool pixel = false;
XY recDims = {1,1};

bool debug = false;

enum colorProcessing {normal, crazyColors, squareMod, limits};
int colorProc = normal;

color upperColLim = {1,1,1};
color lowerColLim = {0,0,0};

double crazyColorsMult = 1.5;
double colorExpo = 2;

char fileName[] = "pic.png";
