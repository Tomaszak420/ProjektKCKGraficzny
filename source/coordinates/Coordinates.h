#ifndef COORDINATES_H
#define COORDINATES_H
struct coordinates {
    int x;
    int y;

    bool operator==(struct coordinates other) {
        return x == other.x && y == other.y;
    }
};
#endif