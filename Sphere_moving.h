#pragma once

#include "Utility_functions.h"

#include "Hittable.h"

class Sphere_moving : public Hittable {
	public:
		Sphere_moving() {}
		Sphere_moving(Point center_0, Point center_1, float s_time, float e_time, float radius, shared_ptr<Material> material)
		: center_0(center_0), center_1(center_1), s_time(s_time), e_time(e_time), radius(radius), material_ptr(material) {};

		virtual bool hit(
		const Ray &ray, float t_min, float t_max, hit_record &record) const override;

		virtual bool bounding_box(float s_time, float e_time, AABB &output_box) const override;

		Point center(float time) const;

	public:
		Point center_0;                       // Sphere moving: center one
		Point center_1;                       // Sphere moving: center two

		float s_time;                         // Sphere moving: start time
		float e_time;                         // Sphere moving: end time

		float radius;                         // Sphere moving: radius

		shared_ptr<Material> material_ptr;    // Sphere moving: material pointer
};

Point Sphere_moving::center(float time) const {
	return center_0 + ((time - s_time) / (e_time - s_time)) * (center_1 - center_0);
}

bool Sphere_moving::hit(const Ray &ray, float distance_min, float distance_max, hit_record &record) const {

	Vec oc = ray.get_origin() - center(ray.get_time());                                                         // Vec OC: camera to center

	float a = ray.get_direction().length_squared();                                                             // Discriminant: a: ray.dir * sqrt(length)
	float half_b = dot(oc, ray.get_direction());                                                                // Discriminant: half b:
	float c = oc.length_squared() - radius * radius;                                                            // Discriminant: c: OC.sqrt(length) - sqrt(radius)

	float discriminant = half_b * half_b - a * c;                                                               // Discriminant: with half b
	
	if (discriminant < 0) { return false; }                                                                     // Hit: fail: The sphere was not hit

	float sqrt_discriminant = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	float root = (-half_b - sqrt_discriminant) / a;                                                             // Quadratic equation: - version: first hit point
	
	if (root < distance_min || distance_max < root) {                                                           // Hit: if fist point out of range
		root = (-half_b + sqrt_discriminant) / a;                                                               // Quadratic equation: + version: second hit point

		if (root < distance_min || distance_max < root) { return false; }                                       // Hit: fail: second hit point out of range
	}

	record.material_ptr = material_ptr;
	
	record.distance = root;
	record.point = ray.at(record.distance);
	Vec outward_normal = (record.point - center(ray.get_time())) / radius;

	record.set_face_normal(ray, outward_normal);

	return true;
}

bool Sphere_moving::bounding_box(float s_time, float e_time, AABB& output_box) const {
	
	AABB box_0(
		center(s_time) - Vec(radius, radius, radius),
		center(s_time) + Vec(radius, radius, radius));
	
	AABB box_1(
		center(e_time) - Vec(radius, radius, radius),
		center(e_time) + Vec(radius, radius, radius));

	output_box = surrounding_box(box_0, box_1);
	
	return true;
}
