
typedef struct
{
    double x;
    double y;
} XY;

typedef struct colors
{
    double r;
    double g;
    double b;
} color;

double randDouble(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}
struct point
{
    XY xy;
    double r;
    double g;
    double b;
};
