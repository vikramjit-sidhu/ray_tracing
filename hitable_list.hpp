#ifndef HITABLELIST
#define HITABLELIST

# include "hitable.hpp"

class hitable_list {
	public:
		hitable **list_objects;
		int list_size;

		hitable_list() {}
		hitable_list(hitable** list_objects_, int list_size_){
			list_objects = list_objects_;
			list_size = list_size_;
		}

		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& record) const {
	bool hit_anything = false;
	float closest_object_so_far = t_max;
	hit_record temp_hit_record;

	/* Iterate over all the objects and check if the ray, 'r' hits it */
	for (int i=0; i<list_size; i++) {
		if (list_objects[i]->hit(r, t_min, closest_object_so_far, temp_hit_record)) {
			hit_anything = true;
			closest_object_so_far = temp_hit_record.t;
			record = temp_hit_record;
		}
	}
	return hit_anything;
}


#endif