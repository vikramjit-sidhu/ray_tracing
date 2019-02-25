
# include <iostream>
# include "sphere.hpp"
# include "hitable_list.hpp"
# include "float.h"


vec3 color(const ray& r, hitable_list *world) {
	hit_record record;

	if (world->hit(r, 0.0, MAXFLOAT, record)) {
		return 0.5 * vec3(record.normal.x()+1, record.normal.y()+1, record.normal.z()+1);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0-t) * vec3(1.0,1.0,1.0) + t * vec3(0.5, 0.7, 1.0);
	}
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

	// Objects in the world
	hitable *list[2];
	list[0] = new sphere(vec3(0,0,-1), 0.5);
	list[1] = new sphere(vec3(0,-100.5,-1), 100);
	hitable_list *world = new hitable_list(list, 2);


	// Rows are written from top to bottom
	for (int j=ny-1; j>=0; j--) {
		// Columns are from left to right
		for (int i=0; i<nx; i++) {
			float u = float (i) / float(nx);
			float v = float (j) / float(ny);

			ray r (origin, lower_left_corner_img_plane + u*horizontal + v*vertical);
			vec3 point = r.point_at_parameter(2.0);
			
			vec3 col = color(r, world);

			int int_val_red = int(255.99 * col[0]);
			int int_val_green = int(255.99 * col[1]);
			int int_val_blue = int(255.99 * col[2]);

			std::cout << int_val_red << " " << int_val_green << " " << int_val_blue << "\n";
		}
	}	

	return 0;
}