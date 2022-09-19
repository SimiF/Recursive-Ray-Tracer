# Recursive Ray Tracer (RRT)

## Description
RRT is an open source recursive ray tracer implemented in C++ following the outlined unit tests in the book *The Ray Tracer Challenge* by Jamis Buck. RRT uses a Left Hand Coordinate space and points are determined as Cartesian Coordinates. The shading is based on the Phong Reflection Model where the object contains an ambient, diffuse, and specular property. These are determined via the position of the "eye" and of the point-based light dynamically. 

## Transforms
RRT uses a matrix based system to move, scale, shear, and rotate objects. The transforms can be applied by multiplying multiple transforms with each other. This will occur before the shading and ray - tracing algorithm.

### No Transform Applied

![alt text](https://github.com/SimiF/Recursive-Ray-Tracer/blob/dev/Example%20Renders/6_0_sphere.png)

This is a 200 px by 200 px render of a sphere with no transforms applied.

### Scaling Transform on Y Axis Applied

![alt text](https://github.com/SimiF/Recursive-Ray-Tracer/blob/dev/Example%20Renders/6_1_sphere_scaled_y.png)

This is a 200 px by 200 px render of the previous sphere with a Scaling transform applied by a factor of 0.5 on the y-axis.

### Scaling Tranform on Y Axis and Rotation on Z Axis Applied

![alt text](https://github.com/SimiF/Recursive-Ray-Tracer/blob/dev/Example%20Renders/6_2_sphere_scaled_y_rotated_z.png)

This is a 200 px by 200 px render of the previous sphere with an additional Rotation matrix on Z axis applied by 45 degrees.
