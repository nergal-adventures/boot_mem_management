# Structs
Simular to classes or objects.
- No inheritance
- No static variables
- No class methods

Structs are simply a way to **group multiple fields(or data pointers)** can be considered as Data Classes in Java they have **no behaviour**.
In C structs put the fields in memory one next to the other, so the order of the fields have to be considered.

You can access the struct fields by using `.` or `->`.

```C
struct Coordinate {
    int x;
    int y;
    int z;
};

struct Coordinate new_coord(int x, int y, int z) { /// Funtion to return an `struct Coordinate`
    struct Coordinate coord = { .x = x, .y = y, .z };

    return coord;
}
```
