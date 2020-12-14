
double pointDistance( XY point1,  XY point2)
{
    return sqrt(pow(point1.x - point2.x,2) + pow(point1.y - point2.y,2));
}

double distRatio [2];

color twoPoint( XY shapepos, struct point points[])   // both this function and allPoint() take in a position and returna  color
{
    color average = (color)
    {
        0,0,0
    };

    //printf("using two points method \n");
    int closestPoint = 0;
    double closeDist = 999999;
    double newDist;

    for(int j = 0; j < num_points; j++)
    {
        newDist = pointDistance(shapepos, points[j].xy);
        if(newDist <  closeDist)
        {
            closeDist = newDist;
            closestPoint = j;
        }
    }
    double secCloseDist = 999999;
    int secClosestPoint = 0;


    if(method != onePoint && method != imaginePoint)
    {
        for(int j = 0; j < num_points; j++)
        {
            if(j == closestPoint)
            {
                continue;
            }
            newDist = pointDistance(shapepos, points[j].xy);
            if(newDist <  secCloseDist)
            {
                secCloseDist = newDist;
                secClosestPoint = j;
            }
        }
    }

    if(method == twoPointsNG)
    {
        average = (color)
        {
            (points[closestPoint].r + points[secClosestPoint].r)/2,
            (points[closestPoint].g + points[secClosestPoint].g)/2,
            (points[closestPoint].b + points[secClosestPoint].b)/2
        };
    }
    else if(method == onePoint)
    {
        average = (color)
        {
            points[closestPoint].r,
                   points[closestPoint].g,
                   points[closestPoint].b
        };
    }
    else if(method == twoPoints)
    {
        double distAdd = secCloseDist + closeDist;
        distRatio[0] = closeDist/distAdd;

        distRatio[1] = secCloseDist/distAdd;


        average = (color)
        {
            points[closestPoint].r * distRatio[1] + points[secClosestPoint].r * distRatio[0],
                   points[closestPoint].g * distRatio[1] + points[secClosestPoint].g * distRatio[0],
                   points[closestPoint].b * distRatio[1] + points[secClosestPoint].b * distRatio[0],
        };
    }
    else if(method == imaginePoint)
    {
        double distAdd = imagineDist + closeDist;
        distRatio[0] = closeDist/distAdd;

        distRatio[1] = imagineDist/distAdd;

        average = (color)
        {
            points[closestPoint].r * distRatio[1] + imagineColor.r * distRatio[0],
                   points[closestPoint].g * distRatio[1] + imagineColor.g * distRatio[0],
                   points[closestPoint].b * distRatio[1] + imagineColor.b * distRatio[0],
        };
    }
    else
    {
        double distAdd = secCloseDist + closeDist;
        distRatio[0] = closeDist/distAdd;
        distRatio[1] = imagineDist/distAdd;
        //printf("%f \n", distRatio[0]);
        if(randDouble(0,1) < distRatio[0])
        {
            average = (color)
            {
                points[closestPoint].r,
                       points[closestPoint].g,
                       points[closestPoint].b
            };
            //printf("dsadsads \n");
        }
        else
        {
            average = (color)
            {
                points[secClosestPoint].r,
                       points[secClosestPoint].g,
                       points[secClosestPoint].b
            };
        }
    }
    return average;
}

color allPoint(XY shapepos, struct point points[]) //works, looks bad
{
    color average;
    double distToFarthestPoint = 0;
    double fullDists [num_points];
    double dist = 0;
    double antiAdd = 0;
    double antiFullDists [num_points];
    double antiDistRatios [num_points];

    for(int j = 0; j < num_points; j++)   // takes distaance to all points
    {
        dist =  pointDistance(points[j].xy, shapepos);
        if(dist > distToFarthestPoint)
        {
            distToFarthestPoint = dist;
        }
        fullDists[j] = dist;
    }

    for(int j = 0; j < num_points; j++)
    {
        antiFullDists[j] = pow(distToFarthestPoint - fullDists[j], allPointPow);
        antiAdd += antiFullDists[j];
    }

    for(int j = 0; j < num_points; j++)
    {
        antiDistRatios[j] = antiFullDists[j]/antiAdd;
    }
/*
    double DEBUGADD = 0;

    for(int j = 0; j < num_points; j++)
    {
        //printf("ratio %f \n", antiDistRatios[j]);
        DEBUGADD += antiDistRatios[j];
    }

*/
    for(int j = 0; j < num_points; j++)
    {
        average.r += antiDistRatios[j] * points[j].r;
        average.g += antiDistRatios[j] * points[j].g;
        average.b += antiDistRatios[j] * points[j].b;
    }

    return average;
}


/*  This is planned to be a way to get smooth transitions between all points, it is not done
color bankMulPoint(XY shapepos, struct point points[]){

    color average;
    double distToFarthestPoint = 0;
    double fullDists [num_points];
    double dist = 0;
    double antiAdd = 0;
    double antiFullDists [num_points];

    for(int j = 0; j < num_points; j++)   // takes distaance to all points
    {
        dist =  pointDistance(points[j].xy, shapepos);
        if(dist > distToFarthestPoint)
        {
            distToFarthestPoint = dist;
        }
        fullDists[j] = dist;
    }

    for(int j = 0; j < num_points; j++) // takes inverse of point distances
    {
        antiFullDists[j] = (distToFarthestPoint - fullDists[j]);
        antiAdd += antiFullDists[j];  // needed ?
    }
    for(int j = 0; j < num_points; j++){


    }
}
*/
