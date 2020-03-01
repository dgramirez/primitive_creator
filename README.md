# primitive_creator (Version 0.1a)
Welcome to my Primitive Creator!  
This project was made only because I wanted a quick way to generate Vertices and Normals of Primitives.  

## How to Build
  - Download/Install CMake 3.5+ [Windows and Linux is my target platform, MacOS whenever I get a hold of a mac]
  - Build using CMake, or use the scripts provided (Will not guarantee it will work on your machine, as of yet).
  - (Windows): Open up the solution and build.
  - (Linux): Open up the workspace and build (Scripts use CodeLite)
  - (MacOS): Open up XCode Project and build (And hope it build, for now)

## What this Entails (TL;DR)
Since this was a quick project, on Version 0.1a, This contains very little (and inconvenient) ways of creating basic primitives.  
Here is the following Primitives I have:
  - Cube
  - Sphere (UV, Math)
  - Cone
  - Cylinder
  - Capsule
  - Torus
  
## How to generate Primitives
Inside "main()" function, the first function should be the "CreateXXXXXX". Replace that with the shape you need. Build and Run.
  - Did i mention this was awful? Will fix this in an official 1.0 release.
  - \_degreeFactor determines how much LESS divisions you want. the formula is: \_PI/180 * \_degreeFactor. To be safe, use whatever is divisible by 360 and no higher than 90 for most cases.
  - Lastly, \_degreeFactor does the subdivisions for both theta and phi. This will be fixed also when i do a 1.0 release.
  
## Questions?
E-mail me at dgramirez@protonmail.com, or just tell me how awful for uploading this on github lol.  
For those who want to know when a Version 1.0 will come, it will not be a quick thing. This will more than likely be a project that I come to whenever I need a break from my real project.

## Future Updates
  - Command Line This Creator!
    - primitive_creator sphere uv 1.0f 30.0f [Create a sphere with a 1.0 unit diameter and divide by 30 degrees]
  - Fix Degree Division to Subdivisions.
    - primitive_creator sphere uv 1.0f 13 13 [Create a sphere with 1.0 unit diameter and subdivisions of 13 meridian and 13 equator(???)]
  - More to come
