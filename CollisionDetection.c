//
// Created by nathan on 9/23/2020.
//

#include "CollisionDetection.h"
#include "GameCore.h"
#include <math.h>


bool onSegment(SDL_Point p, SDL_Point q, SDL_Point r)
{
    if (q.x <= fmax(p.x, r.x) && q.x >= fmin(p.x, r.x) &&
        q.y <= fmax(p.y, r.y) && q.y >= fmin(p.y, r.y))
        return true;

    return false;
}
int orientation(SDL_Point p, SDL_Point q, SDL_Point r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}
bool doIntersect(SDL_Point p1, SDL_Point q1, SDL_Point p2, SDL_Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}



int distance(SDL_Point p1, SDL_Point p2){
    return sqrt(pow((p2.x-p1.x),2)+pow((p2.y-p1.y),2));
}
/**
 * a distance optimized  collision detection
 * @param box1 the bounding box that is is colliding with the second entity(box2)
 * @param box2 the entity that is being collided with.
 * @param dist the distance that the  boxes have to have between the to do check for collision
 * @return the collition side on box2
 */

int optCheckCollisions(BoundingBox *box1, BoundingBox *box2,int dist){
    int check=-1;
    if(distance(box1->center,box2->center)<dist) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (doIntersect(box1->coords[i], box1->coords[(i+1)%4], box2->coords[j], box2->coords[(j+1)%4])) {
                    check = j;
                    return check;
                }
            }
        }
    }
    return check;
}
/**
 * checks collisions between 2 SDl_Rects
 * @param a the first rect
 * @param b the second rect
 * @return if thare is a collision for not
 */
bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}