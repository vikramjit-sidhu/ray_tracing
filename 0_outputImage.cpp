
#include <iostream>
#include "vec3.hpp"

int main() {
	int nx = 200;
	int ny = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	// Rows are written from top to bottom
	for (int row=ny-1; row>=0; row--) {
		// Columns are from left to right
		for (int col=0; col<nx; col++) {
			float r = float (col) / float(nx);
			float g = float (row) / float(ny);
			float b = 0.2;
			vec3 color (r, g, b);

			int int_val_red = int(255.99 * color[0]);
			int int_val_green = int(255.99 * color[1]);
			int int_val_blue = int(255.99 * color[2]);

			std::cout << int_val_red << " " << int_val_green << " " << int_val_blue << "\n";
		}
	}	

	return 0;
}