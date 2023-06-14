// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Vector.cpp
#include "Vector.h"
#include <algorithm>
#include <cmath>
#include <sstream>

template<typename T, unsigned int Size>
Vector<T, Size>::Vector() : data() {
	for(unsigned int i = 0; i < Size; ++i) {
		data[i] = 0;
	}
}

template<typename T, unsigned int Size>
Vector<T, Size>::Vector(const Vector<T, Size>& copy) : data{copy.data} {}

template<typename T, unsigned int Size>
Vector<T, Size>::Vector(const std::array<T, Size>& copy) : data{copy} {}

template<typename T, unsigned int Size>
Vector<T, Size>::~Vector() {}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::zero() {
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = 0;
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::one() {
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = 1;
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::up() {
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = 0;
	}

	if(Size > 1) {
		values[1] = 1;
	}

	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::right() {
	std::array<T, Size> values;
	for(int i = 1; i < Size; ++i) {
		values[i] = 0;
	}
	if(Size > 0) {
		values[0] = 1;
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::forward() {
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = 0;
	}
	if(Size > 2) {
		values[2] = 1;
	}
	return {values};
}

template<typename T, unsigned int Size>
T& Vector<T, Size>::operator[](const unsigned int& index){
	if(index >= Size) throw std::runtime_error("Invalid Index");

	return data[index];
}

template<typename T, unsigned int Size>
const T& Vector<T, Size>::operator[](const unsigned int& index) const{
	if(index >= Size) throw std::runtime_error("Invalid Index");

	return data[index];
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::operator+(const Vector<T, Size> &right) const
{
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = data[i] + right.data[i];
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::operator-(const Vector<T, Size> &right) const
{
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = data[i] - right.data[i];
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::operator*(const float &right) const
{
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = data[i] * right;
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> operator*(const float &left, const Vector<T, Size> &right)
{
	return right * left;
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::operator/(const float &right) const
{
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = data[i] / right;
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> operator/(const float &left, const Vector<T, Size> &right)
{
	return right / left;
}

template<typename T, unsigned int Size>
Vector<T, Size> &Vector<T, Size>::operator+=(const Vector<T, Size> &right)
{
	for(int i = 0; i < Size; ++i) {
		data[i] += right.data[i];
	}
	return *this;
}

template<typename T, unsigned int Size>
Vector<T, Size> &Vector<T, Size>::operator-=(const Vector<T, Size> &right)
{
	for(int i = 0; i < Size; ++i) {
		data[i] -= right.data[i];
	}
	return *this;
}

template<typename T, unsigned int Size>
Vector<T, Size>& Vector<T, Size>::operator *=(const float& value) {
	for(int i = 0; i < Size; ++i) {
		data[i] *= value;
	}
	return *this;
}

template<typename T, unsigned int Size>
Vector<T, Size>& Vector<T, Size>::operator /=(const float& value) {
	for(int i = 0; i < Size; ++i) {
		data[i] /= value;
	}
	return *this;
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::cross(const Vector<T, Size> &left, const Vector<T, Size> &right)
{
	if(Size == 2) {
		T value = left.data[0] * right.data[1] - left.data[1] * right.data[0];
		return {{value, -value}};
	}

	// Determine the Cross Product using a method described according to the website https://cs.wellesley.edu/~cs307/readings/08-geometry.html.
	return {{
		left.data[1] * right.data[2] - left.data[2] * right.data[1],
		left.data[2] * right.data[0] - left.data[0] * right.data[2],
		left.data[0] * right.data[1] - left.data[1] * right.data[0]
	}};
}

template<typename T, unsigned int Size>
float Vector<T, Size>::dot(const Vector<T, Size> &left, const Vector<T, Size> &right)
{
	T Sum = 0;
	for(int i = 0; i < Size; ++i) {
		Sum += left.data[i] * right.data[i];
	}
	return Sum;
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::min(const Vector<T, Size>& left, const Vector<T, Size>& right) {
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = std::min(left.data[i], right.data[i]);
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::max(const Vector<T, Size>& left, const Vector<T, Size>& right) {
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = std::max(left.data[i], right.data[i]);
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::clamp(const Vector<T, Size>& left, const Vector<T, Size>& min, const Vector<T, Size>& max) {
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = std::clamp(left.data[i], min.data[i], max.data[i]);
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::lerp(const Vector<T, Size>& left, const Vector<T, Size>& right, const float& amount) {
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = left.data[i] + (right.data[i] - left.data[i]) * amount;
	}
	return {values};
}

template<typename T, unsigned int Size>
std::istream &operator>>(std::istream &in, Vector<T, Size> &value)
{
	for(int i = 0; i < Size; ++i) {
		in >> value.data[i];
	}
	return in;
}

template<typename T, unsigned int Size>
std::ostream &operator<<(std::ostream &out, const Vector<T, Size> &value)
{
	for(int i = 0; i < Size; ++i) {
		out << value.data[i];
		if(i < Size-1) {
			out << ", ";
		}
	}
	return out;
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::normalize(const Vector<T, Size> &value)
{
	// Create a Unit Vector of Length 1 by dividing each element by the length of the Vector.
	float magnitude = value.magnitude();
	return value / magnitude;
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::invert(const Vector<T, Size> &value)
{
	std::array<T, Size> values;
	for(int i = 0; i < Size; ++i) {
		values[i] = -value.data[i];
	}
	return {values};
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::reflect(const Vector<T, Size> &normal) const
{
	// The First Parameter in the Dot Product Function "dot()" that is "*this" represents the Angle of Incidence. The Second Parameter in the
	// Dot Product Function "dot()" that is "normal" represents the Perpendicular Surface Vector to reflect around according to the following
	// website https://www.brown.edu/research/labs/mittleman/sites/brown.edu.research.labs.mittleman/files/uploads/lecture13_0.pdf.
	return *this - 2.f * Vector<T, Size>::dot(*this, normal) * normal;
}

template<typename T, unsigned int Size>
Vector<T, Size> Vector<T, Size>::refract(const Vector<T, Size> &normal, const float &indexOfRefraction) const
{
	// The First Parameter in the Dot Product Function "dot()" that is "*this" represents the Angle of Incidence. The Second Parameter in the
	// Dot Product Function "dot()" that is "normal" represents the Perpendicular Surface Vector to reflect around according to the following
	// website https://www.brown.edu/research/labs/mittleman/sites/brown.edu.research.labs.mittleman/files/uploads/lectur13_0.pdf.
	float clampI = std::clamp(Vector<T, Size>::dot(*this, normal), -1.f, 1.f);
	float closeRefractiveValue = 1, farRefractiveValue = indexOfRefraction;
	Vector<T, Size> norm = normal;
	if (clampI < 0)
	{
		clampI = -clampI;
	}
	else
	{
		std::swap(closeRefractiveValue, farRefractiveValue);
		norm = Vector<T, Size>::invert(norm);
	}

	float iorRatio = closeRefractiveValue / farRefractiveValue;
	float angleOfIncidence = 1 - iorRatio * iorRatio * (1 - clampI * clampI);
	// Total Reflection.
	if (angleOfIncidence < 0)
	{
		return reflect(normal);
	}
	return iorRatio * (*this) + (iorRatio * clampI - sqrt(angleOfIncidence)) * norm;
}

template<typename T, unsigned int Size>
// Get the angle between two vectors in radians.
float Vector<T, Size>::getAngle(const Vector<T, Size> &b) const
{
	float determinantOfMatrix = Vector<T, Size>::dot(*this, b);
	return acos(determinantOfMatrix);
}

template<typename T, unsigned int Size>
float Vector<T, Size>::squareMagnitude() const
{
	return dot(*this, *this);
}

template<typename T, unsigned int Size>
float Vector<T, Size>::magnitude() const
{
	return sqrt(squareMagnitude());
}

template<typename T, unsigned int Size>
// Use the Equality Operator that is the Equal To Operator "==" to check if x, y, and z are the same between this vector and the 'right' vector.
bool Vector<T, Size>::operator==(const Vector<T, Size> &right) const
{
	for(unsigned int i = 0; i < Size; ++i) {
		if(data[i] != right.data[i]) return false;
	}
	return true;
}

template<typename T, unsigned int Size>
// Use the Inequality Operator that is the Not Equal To Operator "!=" to check if the Equality Operator returned False.
bool Vector<T, Size>::operator!=(const Vector<T, Size> &right) const
{
	return !(*this == right);
}

template<typename T, unsigned int Size>
std::string Vector<T, Size>::toString() const {
	std::stringstream stream;
	stream << *this;
	return stream.str();
}
