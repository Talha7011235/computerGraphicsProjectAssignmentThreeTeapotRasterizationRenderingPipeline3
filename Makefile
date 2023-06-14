rasterize: main3.cpp NffParserForProjectThree.cpp PpmFileForProjectThree.cpp Rasterizer.cpp Elements/ColorForProjectThree.cpp Elements/LightForProjectThree.cpp Elements/ShadingForProjectThree.cpp Elements/ViewPortForProjectThree.cpp Geometry/Plane.cpp Geometry/PolygonForProjectThree.cpp Geometry/Triangle.cpp Math/Matrix3.cpp Math/Matrix4.cpp
	g++ -ggdb -std=c++17 -o rasterize main3.cpp NffParserForProjectThree.cpp PpmFileForProjectThree.cpp Rasterizer.cpp Elements/ColorForProjectThree.cpp Elements/LightForProjectThree.cpp Elements/ShadingForProjectThree.cpp Elements/ViewPortForProjectThree.cpp Geometry/Plane.cpp Geometry/PolygonForProjectThree.cpp Geometry/Triangle.cpp Math/Matrix3.cpp Math/Matrix4.cpp

teapot: rasterize
	./rasterize teapot-3.nff teapot-3.ppm
	convert teapot-3.ppm teapot.png

teapot-fragment: rasterize
	./rasterize -f teapot-3.nff teapot-3.ppm
	convert teapot-3.ppm teapot.png

clean:
	rm rasterize

