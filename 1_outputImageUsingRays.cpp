#include <iostream>
#include "ray.hpp"

vec3 color(const ray& r) {
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