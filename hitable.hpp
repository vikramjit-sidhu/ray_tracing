#ifndef HITABLE
#define HITABLE

#include "ray.hpp"

struct hit_record{
	float t;
	vec3 p;	/* Hit point */
	vec3 normal; /* Normal towards hit point */
};

class hitable {
	public:
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const = 0;
};

#endif