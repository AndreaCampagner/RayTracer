# Ray Tracer
## Description
This project consists of a StochasticRay Tracer implemented in C++, it was implemented as a project for an
 exam in Computer Graphics.
The project has been implemented with more focus towards readibility and simplicity than towards performance,
still performance have not completely been overlooked and the implementation should be reasonable for simple
tasks.
It supports various feature:
* Spheres and general Trimesh objects
* Anti-aliasing via uniform multisampling
* Depth-of-Field
* Reflection and Transmission (using Schlick's approximation to Fresnel)
* Soft Shadows
* Glossiness
* Phong lighting model
* Diffuse texture maps

Note however that most features (such as Anti-aliasing, depth of field or soft shadows) impact on performances.
The repository also contains some example images that were produced using the Ray Tracer.

## Requirements
In order to compile and execute the project you need the glm [link](https://glm.g-truc.net/0.9.8/index.html)
math library.