Talha Hussain, MyRasterizationRenderingPipelineProjectAssignmentThree, Computer Science
Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline

Websites:
To complete my Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline, I received helpful inspiration from the following website:
Geometry - https://cs.wellesley.edu/~cs307/readings/08-geometry.html

Usage: A make file that is the "Makefile" for my Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline has been included with the following commands.
make rasterize - Runs the compilation using the g++ compiler.
make clean - cleans the intermediate files and compiled target.

After running the command "make rasterize", choose one of the following make commands below to run and then run the "make clean" command. Each .ppm File can
be generated one at a time. 
make teapot - Runs the compiled target using the teapot-3.nff file.
make teapot-fragment - Runs the compiled target using the teapot-3.nff file and fragment shading.

Summary: In terms of my Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline, due to the fact that the main object of this project was to
build a basic Rasterizer, I reused some components from the Raytracing project that is primarily the math, nff parsing, ppm writing, and geometry structures. I
added a few more structures and completed my C++ code for the matrix math to allow for the operations to work according to Steve Marschner's and Peter Shirley's
textbook "Fundamentals of Computer Graphics, Fourth Edition". For rasterizing I have a 5 stage process. TransformVertices performs basic diffuse shading and
transformation into the canonical volume. Clipping removes points that fall outside the frustum by saving, rejecting, or clipping triangles that
intersect. Rasterizing converts the canonical volume into image space and determines the fragments that must be processed and the fragments then go through
a per-pixel phong shading and get returned for blending. Blending then finishes the process by determining if the fragment should be stored in the image and
saving it. Then I pass all of the processed pixels to the ppm writer for my final output image.


