#include <iostream>
#include "ray.hpp"


float hit_sphere(const vec3& centre, float radius, const ray& r) {
	/**
	 * Solve a quadratic equation to check if the ray hits the sphere
	 */
	vec3 vector_from_ray_origin_sphere_centre = r.origin() - centre;
	vec3 ray_direction = r.direction();
	
	float a = dot(ray_direction, ray_direction);
	float b = 2 * dot(vector_from_ray_origin_sphere_centre, ray_direction);
	float c = dot(vector_from_ray_origin_sphere_centre, vector_from_ray_origin_sphere_centre) - radius*radius;

	float discriminant = b*b - 4*a*c;

	if (discriminant < 0){
		return -1.0;
	}
	else {
		// We want the normal pointing towards the camera
		return (-b - sqrt(discriminant)) / (2.0*a);
	}
}


vec3 color(const ray& r) {
	// Check if sphere is hit
	vec3 sphere_centre (0,0,-1);
	float sphere_radius = 0.5;
	float t = hit_sphere(sphere_centre, sphere_radius, r);

	if (t>0.0) {
		vec3 normal = unit_vector(r.point_at_parameter(t) - sphere_centre);
		return (0.5*vec3(normal.x()+1, normal.y()+1, normal.z()+1));
	}

	vec3 ray_unit_direction = unit_vector(r.direction());
	// Color decided based on y-coordinate
	float blending_factor = 0.5 * (ray_unit_direction.y() + 1.0);
	// combination of blue (0.5,0.7,1.0) and white (1,1,1) to get intermediate color
	vec3 blended_color = (1.0-blending_factor) * vec3(1.0, 1.0, 1.0) + blending_factor*vec3(0.5, 0.7, 1.0);
	return blended_color;
}


int main() {
	int nx = 200;
	int ny = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	// Important Points in the scene
	vec3 lower_left_corner_img_plane (-2.0, -1.0, -1.0);
	vec3 origin (0.0, 0.0, 0.0);
	vec3 horizontal (4.0, 0.0, 0.0);
	vec3 vertical (0.0, 2.0, 0.0);

	// Rows are written from top to bottom
	for (int j=ny-1; j>=0; j--) {
		// Columns are from left to right
		for (int i=0; i<nx; i++) {
			float u = float (i) / float(nx);
			float v = float (j) / float(ny);

			ray r (origin, lower_left_corner_img_plane + u*horizontal + v*vertical);
			vec3 col = color(r);

			int int_val_red = int(255.99 * col[0]);
			int int_val_green = int(255.99 * col[1]);
			int int_val_blue = int(255.99 * col[2]);

			std::cout << int_val_red << " " << int_val_green << " " << int_val_blue << "\n";
		}
	}	

	return 0;
}