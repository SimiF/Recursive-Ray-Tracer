# Recursive Ray Tracer (RRT)

## Description
RRT is an open source recursive ray tracer implemented in C++ following the outlined unit tests in the book *The Ray Tracer Challenge* by Jamis Buck. RRT uses a Left Hand Coordinate space and points are determined as Cartesian Coordinates. The shading is based on the Phong Reflection Model where the object contains an ambient, diffuse, and specular property. These are determined via the position of the "eye" and of the point-based light dynamically. 

## Transforms
RRT uses a matrix based system to move, scale, shear, and rotate objects. Some available options include.

### No Transform Applied


![alt text](https://github.com/SimiF/Recursive-Ray-Tracer/blob/dev/500%20by%20500%20shade%20rotated%20around%20z%20squash.png)
