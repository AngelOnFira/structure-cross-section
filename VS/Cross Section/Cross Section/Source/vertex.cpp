#include "vertex.h"

Vertex::Vertex() {
	position[Xelt] = 0.0f;
	position[Yelt] = 0.0f;
	position[Zelt] = 0.0f;
}

Vertex::Vertex(float x, float y, float z) {
	position[Xelt] = x;
	position[Yelt] = y;
	position[Zelt] = z;
}

Vertex::Vertex(float x, float y, float z, Vertex *parent) {
	position[Xelt] = x;
	position[Yelt] = y;
	position[Zelt] = z;
	this->children.push_back(parent);
}

void Vertex::add_child(Vertex *vert) {
	if (vert != NULL) {
		this->children.push_back(vert);
	}
}