#include <stdio.h>
#include <stdbool.h>


struct Point {
    float x;
    float y;
};

struct Rectangle {
    struct Point bl;
    struct Point tr;
};

float area(struct Rectangle r) {
    float length = r.tr.x - r.bl.x;
    float breadth = r.tr.y - r.bl.y;
    return length*breadth;
}

bool isInside(struct Point p, struct Rectangle r) {    
    return ((p.x>r.bl.x && p.x<r.tr.x) && (p.y>r.bl.y && p.y<r.tr.y))?true:false;
}

int main(int argc, char *argv[]) {
    struct Point p1 = {2.0, 1.0};
    struct Point p2 = {5.0, 6.0};
    struct Rectangle r1 = {p1, p2};
    struct Point p3 = {3.0, 2.0};
    struct Point p0 = {1.0, 1.0};
    
    printf("Area of rectangle = %.2f.\n", area(r1));

    printf("Point p3 is inside Rectangle r1: %s\n", isInside(p3, r1)?"true":"false");
    printf("Point p1 is inside Rectangle r1: %s\n", isInside(p1, r1)?"true":"false");
    printf("Point p0 is inside Rectangle r1: %s\n", isInside(p0, r1)?"true":"false");
    
    
    return 0;
}

