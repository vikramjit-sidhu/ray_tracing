#ifndef SPHERE
#define SPHERE

# include "hitable.hpp"

class sphere : public hitable {
	public:
		vec3 centre;
		float radius;

		sphere() {}
		sphere(vec3 centre_, float radius_) : centre(centre_), radius(radius_) {}

		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const;
};


bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& record) const {
	vec3 vector_from_ray_origin_sphere_centre = r.origin() - centre;
	vec3 ray_direction = r.direction();
	
	float a = dot(ray_direction, ray_direction);
	float b = dot(vector_from_ray_origin_sphere_centre, ray_direction);
	float c = dot(vector_from_ray_origin_sphere_centre, vector_from_ray_origin_sphere_centre) - radius*radius;

	float discriminant = b*b - a*c;

	if (discriminant <= 0) {
		return false;
	}

	float solution1 = (-b - sqrt(discriminant)) / a;
	if (solution1 < t_max && solution1 > t_min) {
		record.t = solution1;
		record.p = r.point_at_parameter(record.t);
		record.normal = (record.p - centre) / radius;
		return true;
	}

	float solution2 = (-b + sqrt(discriminant)) / a;
	if (solution2 < t_max && solution2 > t_min) {
		record.t = solution2;
		record.p = r.point_at_parameter(record.t);
		record.normal = (record.p - centre) / radius;
		return true;
	}

	return false;
}

#endif