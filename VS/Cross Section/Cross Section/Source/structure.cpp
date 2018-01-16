#include "structure.h"

Structure::Structure() {
	head = new Vertex(12.0f, 0.0f, 2.0f);
	head = build_tree(head, 0);
}

Vertex* Structure::build_tree(Vertex* parent, int depth) {
	//Random number for this instance
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	//Base Case, choose if we should make more children
	if (r > 1.0f / depth) {
		return NULL;
	}

	Vertex* this_vert = new Vertex(new_location(parent->position[Xelt]), new_location(parent->position[Yelt]), parent->position[Zelt] + 10.0f);
	int num_of_children = ceil(r * (10.0f - (float)depth));
	total_nodes++;
	std::cout << this_vert->position[Xelt] << "," << this_vert->position[Yelt] << "," << this_vert->position[Zelt] << std::endl;

	for (int i = 0; i < num_of_children; i++) {
		this_vert->add_child(build_tree(this_vert, depth + 1));
	}
	return this_vert;
}

float Structure::new_location(float old) {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	return ((r - 0.5f) * 20.0f);
}

void Structure::draw() {
	draw_child(head);

	plane_origin[Zelt] -= 0.10f;
	std::cout << plane_origin[Zelt] << std::endl;
	update_plane_vectors();
}

void Structure::draw_child(Vertex* this_vert) {
	for (int i = 0; i < this_vert->children.size(); i++) {
		Vertex* child = this_vert->children.at(i);
		draw_child(child);

		//Direction of the line based on the parent and child
		Vec3f line_direction = Vec3f(child->position[Xelt] - this_vert->position[Xelt], child->position[Yelt] - this_vert->position[Yelt], child->position[Zelt] - this_vert->position[Zelt]);

		//The start of the line
		Vec3f line_point = Vec3f(this_vert->position[Xelt], this_vert->position[Yelt], this_vert->position[Zelt]);

		float angle_plane_line = vector_angle(plane_normal, plane_x_axis);
		//If the plane is not parallel to the line
		if (angle_plane_line != 0.0f) {
			
			//// Compute the X value for the directed line ray intersecting the plane
			Vec3f line_point_plane = Vec3f(plane_origin[Xelt] - this_vert->position[Xelt], plane_origin[Yelt] - this_vert->position[Yelt], plane_origin[Zelt] - this_vert->position[Zelt]);
			float u = dot(plane_normal, line_point_plane) / dot(plane_normal, line_direction);

			////Intersection point
			//Vec3f intersection = plane_origin + normalize(line_direction) * t;

			////Intersection point relative to plane's origin
			//Vec3f intersection_on_plane = intersection - plane_origin;

			//float dot_x = vector_angle(plane_x_axis, intersection_on_plane);
			//float dot_y = vector_angle(plane_y_axis, intersection_on_plane);

			float x_intersection = u * line_point[Xelt] + (1 - u) * child->position[Xelt];
			float y_intersection = u * line_point[Yelt] + (1 - u) * child->position[Yelt];
			float z_intersection = u * line_point[Zelt] + (1 - u) * child->position[Zelt];
			std::cout << z_intersection << std::endl;

			glBegin(GL_POLYGON);
			for (double i = 0; i < 2 * PI; i += PI / 20) {//<-- Change this Value
				glVertex3f(cos(i) * radius + (x_intersection / 20.0f), sin(i) * radius + (y_intersection / 20.0f), 0.0);
			}
			glEnd();
		}
	}
}

void setup_verts() {

}

float Structure::vector_angle(Vec3f vec_1, Vec3f vec_2) {
	float dot_product = (vec_1[Xelt] * vec_2[Xelt]) + (vec_1[Yelt] * vec_2[Yelt]) + (vec_1[Zelt] * vec_2[Zelt]);
	float mag_1 = sqrt(pow(vec_1[Xelt], 2.0f) + pow(vec_1[Yelt], 2.0f) + pow(vec_1[Zelt], 2.0f));
	float mag_2 = sqrt(pow(vec_2[Xelt], 2.0f) + pow(vec_2[Yelt], 2.0f) + pow(vec_2[Zelt], 2.0f));

	float angle = dot_product / (mag_1 * mag_2);

	return (float)acos(angle);
}

float Structure::get_dot(Vec3f vec_1, Vec3f vec_2) {
	return (vec_1[Xelt] * vec_2[Xelt] + vec_1[Yelt] * vec_2[Yelt] + vec_1[Zelt] * vec_2[Zelt]);
}

Vec3f Structure::cross(Vec3f vec_1, Vec3f vec_2) {
	Vec3f return_vec = Vec3f(
		(vec_1[Yelt] * vec_2[Zelt] - vec_1[Zelt] * vec_2[Yelt]),
		(vec_1[Zelt] * vec_2[Xelt] - vec_1[Xelt] * vec_2[Zelt]),
		(vec_1[Xelt] * vec_2[Yelt] - vec_1[Yelt] * vec_2[Xelt]));

	return return_vec;
}

Vec3f Structure::normalize(Vec3f vec_before) {
	float mag = sqrt(pow(vec_before[Xelt], 2) + pow(vec_before[Yelt], 2) + pow(vec_before[Zelt], 2));
	Vec3f vec_after = Vec3f(vec_before[Xelt] * mag, vec_before[Yelt] * mag, vec_before[Zelt] * mag);
	return vec_after;
}

void Structure::update_plane_vectors() {
	plane_x_axis = normalize(plane_x_axis);
	plane_y_axis = normalize(plane_y_axis);
	plane_normal = normalize(plane_normal);
}