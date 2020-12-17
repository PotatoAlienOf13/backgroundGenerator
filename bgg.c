/*

The way this program usually runs is
1. Put a certain amount of points, each with their own color, on a canvas
2. For every shape/pixel that should be drawn, their x and y coordinates are passed into a function that returns an RGB value
3. That value may be modified
4. That shape is then drawn onto the canvas.

*/

#include "stdio.h"
#include "math.h"
#include <cairo/cairo.h>
#include "stdlib.h"
#include "time.h"
#include "config.h"
#include "drawing.h"
#include "limits.h"

double x = 0;
double y = 0;
double VSCsize = circleSize;

cairo_t *cr;


void doDrawing(struct point points[]) {

    color average;

    XY shapeposition;

    for(int i = 0; i < num_shapes; i++) {

        if(pixel) {
            shapeposition = (XY) {
                x, y
            };
        } else {
            shapeposition = (XY) {
                randDouble(0, surf_wid), randDouble(0, surf_hei)
            };
        }

        if(method == pointRange) {
            average = allPoint(shapeposition, points);
        } else {
            average = twoPoint( shapeposition, points);
        }

        if(colorProc == crazyColors) {  // modifies colors, if said in the config
            average.r = fmod(average.r * crazyColorsMult, 1);
            average.g = fmod(average.g * crazyColorsMult, 1);
            average.b = fmod(average.b * crazyColorsMult, 1);
        } else if(colorProc == squareMod) {
            average.r = fmod(pow(average.r * crazyColorsMult, colorExpo), 1);
            average.g = fmod(pow(average.g * crazyColorsMult, colorExpo), 1);
            average.b = fmod(pow(average.b * crazyColorsMult, colorExpo), 1);
        } else if(colorProc == limits) {
            if(average.r < lowerColLim.r) {
                average.r = lowerColLim.r;
            } else if (average.r > upperColLim.r) {
                average.r = upperColLim.r;
            }
            if(average.g < lowerColLim.g) {
                average.g = lowerColLim.g;
            } else if (average.g > upperColLim.g) {
                average.g = upperColLim.g;
            }
            if(average.b < lowerColLim.b) {
                average.b = lowerColLim.b;
            } else if (average.b > upperColLim.b) {
                average.b = upperColLim.b;
            }
        }

        cairo_set_source_rgba (cr, average.r, average.g, average.b,  circleOpacity);


        if(method == twoPointsVSC) {
            VSCsize = circleSize * fabs(distRatio[0] - distRatio[1]);
            if(VSCsize < VSCmin) {
                VSCsize = VSCmin;
            }
        }
        if(!pixel) {
            cairo_arc(cr, shapeposition.x, shapeposition.y, VSCsize, 0, 10);
            cairo_fill(cr);
            cairo_stroke(cr);
        } else {
            cairo_rectangle(cr, shapeposition.x, shapeposition.y, recDims.x,recDims.y);
            cairo_fill(cr);
            cairo_stroke (cr);
        }

        if(pixel) {  //move to the next pixel
            x += recDims.x;
            if(x >= surf_wid ) {
                y += recDims.y;
                x = 0;
                printf("now on line %f \n", y);
            }
        }
    }
}

int main (int argc, char *argv[]) {

    srand((unsigned)time(NULL));

    if(pointMethod == gridPoints) {
        num_points = ceil( (surf_wid + 1 - gridMargs.x * 2) / gridDims.x) * ceil( (surf_hei + 1 - gridMargs.y * 1) / gridDims.y);
    }
    struct point points [num_points];

    if(colorMethod == def) {
        for(int i = 0; i < num_points; i++) {
            points[i].r = randDouble(0, 1);
            points[i].g = randDouble(0, 1);
            points[i].b = randDouble(0, 1);
        }
    } else if (colorMethod == tintPoint) {
        for(int i = 0; i < num_points; i++) {
            points[i].r = randDouble(0, 1) * (1 - tintIntens) + tintColor.r * tintIntens;
            points[i].g = randDouble(0, 1) * (1 - tintIntens) + tintColor.g * tintIntens;
            points[i].b = randDouble(0, 1) * (1 - tintIntens) + tintColor.b * tintIntens;
        }
    }

    if (pointMethod == gridPoints) {
        int x = gridMargs.x, y = gridMargs.y;
        for(int i = 0; i < num_points; i++) {

            points[i].xy.x = x;
            printf("%f is it \n", points[i].xy.x);

            points[i].xy.y = y;

            x += gridDims.x;

            if(x > surf_wid - gridMargs.x) {
                y += gridDims.y;
                x = gridMargs.x;
            }
        }
    } else {
        for(int i = 0; i < num_points; i++) {
            points[i].xy.x = randDouble(0, surf_wid);
            points[i].xy.y = randDouble(0, surf_hei);
        }
    }

    cairo_surface_t *surface =
        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, surf_wid, surf_hei);

    cr = cairo_create (surface);

    if(pixel) {
        num_shapes = ceil(surf_wid / recDims.x) * ceil(surf_hei / recDims.y);
    }

    printf("%u points \n", num_points);
    printf("numshapes is %u \n",num_shapes);

    doDrawing(points);

    if(debug) {
        for(int i = 0; i < num_points; i++) { // this code creates a square at each of the points, for debugging
            cairo_set_source_rgb(cr,0,0,0);
            cairo_rectangle(cr, points[i].xy.x, points[i].xy.y, 20, 10);
            cairo_fill(cr);
            cairo_set_source_rgb(cr, points[i].r, points[i].g, points[i].b );
            cairo_rectangle(cr, points[i].xy.x, points[i].xy.y, 10, 10);
            cairo_fill(cr);
        }
        cairo_stroke(cr);
    }
    cairo_surface_write_to_png (surface, fileName);

    cairo_surface_destroy (surface);

    return 0;
}
