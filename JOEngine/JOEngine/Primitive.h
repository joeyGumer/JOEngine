#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

//#include "glmath.h"
#include "Color.h"
#include "Math.h"
#include <vector>
#include "DirectXGlobals.h"


enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder
};

class Primitive
{
public:

	Primitive();
	virtual ~Primitive();

	virtual void	Render() const;
	virtual void	InnerRender() const;
	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const float3 &u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;
protected:
	virtual void	Init();

public:
	
	Color color;
	float4x4 transform;
	bool axis,wire;

protected:
	PrimitiveTypes type;
	std::vector<CUSTOMVERTEX> vertices;
	CUSTOMVERTEX* vert;
};

// ============================================
class pCube : public Primitive
{
public :
	pCube();
	pCube(float sizeX, float sizeY, float sizeZ);
	void InnerRender() const;
public:
	float3 size;
};

// ============================================
class pSphere : public Primitive
{
public:
	pSphere();
	pSphere(float radius);
	void InnerRender() const;
public:
	float radius;
};

// ============================================
class pCylinder : public Primitive
{
public:
	pCylinder();
	pCylinder(float radius, float height);
	void InnerRender() const;
public:
	float radius;
	float height;
};

// ============================================
class pLine : public Primitive
{
public:
	pLine();
	pLine(float x, float y, float z);
	void InnerRender() const;
public:
	float3 origin;
	float3 destination;
};

// ============================================
class pPlane : public Primitive
{
public:
	pPlane();
	pPlane(float x, float y, float z, float d);
	void InnerRender() const;

private:
	void Init();

public:
	float3 normal;
	float constant;

private:
	LPDIRECT3DVERTEXBUFFER9 v_buffer;
};


#endif _PRIMITIVE_H_