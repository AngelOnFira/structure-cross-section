#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>
#include "vertex.h"
#include "includes.h"
#include <cstddef>

using namespace gmtl;

struct Structure {
public:
	Vertex* head;

	Structure();
	//Structure();

	Vertex* build_tree(Vertex* parent, int depth);
	void draw();
	void add_child(Vertex *vert);
	void draw_child(Vertex* this_vert);
	void update_plane_vectors();
	float new_location(float old);
	float vector_angle(Vec3f vec_1, Vec3f vec_2);
	float get_dot(Vec3f vec_1, Vec3f vec_2);
	Vec3f normalize(Vec3f vec_before);
	Vec3f cross(Vec3f vec_1, Vec3f vec_2);
	float distance(Vec3f vec1, Vec3f vec2);

	/*User set parameters*/
	float test = 20.0f;


	int total_nodes = 0;

	Vec3f plane_normal = Vec3f(0.0, 0.0, 1.0);
	Vec3f plane_origin = Vec3f(0.0, 0.0, 10.0);
	float plane_angle = 0.0f;
	Vec3f plane_x_axis = Vec3f(1.0, 0.0, 0.0);
	Vec3f plane_y_axis = Vec3f(0.0, 1.0, 0.0);

	#define PI 3.1415926535897932384626433832795
	#define WIDTH 640
	#define HEIGHT 480
	float radius = 0.051f;
};

#endif