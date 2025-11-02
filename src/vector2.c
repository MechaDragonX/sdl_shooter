#include <math.h>
#include "vector2.h"

// Params: Vector2 distance
// Normalize vectors so diagonal is at same speed as cardinal
// Returns: void
void normalizeDistance(Vector2* distance)
{
    float normalizedDiagonal = sqrtf((distance->x * distance->x) + (distance->y * distance->y));
    if(normalizedDiagonal != 0)
    {
        distance->x /= normalizedDiagonal;
        distance->y /= normalizedDiagonal;
    }
}
