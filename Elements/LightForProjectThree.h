// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// LightForProjectThree.h
#ifndef LIGHTFORPROJECTTHREE_H
#define LIGHTFORPROJECTTHREE_H

#include "../Math/Vector.h"
#include "../Math/Matrix4.h"
#include "../Elements/ColorForProjectThree.h"
#include <vector>

class LightForProjectThree {
public:
    LightForProjectThree();
    LightForProjectThree(const Vector3f&);

    Vector3f getPosition() const;
    Matrix4 getMatrix() const;
    float getDepth(const Vector3f&) const;
    std::vector<ColorForProjectThree> getPixels() const;
    bool isInShadow(const Vector3f&) const;


    Vector3f transformPoint(const Vector3f&) const;
    void setResolution(const Vector2i&);
    void setMatrix(const Matrix4&, const Matrix4&, const Matrix4&);
    void setDepth(const Vector3f&);

    friend std::istream& operator >> (std::istream&, LightForProjectThree&);
    friend std::ostream& operator << (std::ostream&, const LightForProjectThree&);
private:
    Vector2i resolution;
    Vector3f position;
    Matrix4 lightView;
    Matrix4 lightProj;
    Matrix4 lightVP;
    std::vector<float> buffer;
};

#endif

