#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <cstddef>

#include "includes.h"

using namespace gmtl;

struct Vertex {
	int id;
	Vec3f position;
	std::vector<Vertex*> children;
	Vertex* parent;

	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, Vertex *parent);

	void add_child(Vertex *vert);
};

#endif