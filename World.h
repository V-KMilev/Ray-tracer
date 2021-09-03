#pragma once

#include "Utility_functions.h"

#include "Thread_manager.h"

#include "Hittable_list.h"
#include "Hittable.h"
#include "Bucket.h"

#include "Material.h"
#include "Sphere.h"

#include "Camera.h"

#include "Color.h"
#include "Vec.h"
#include "Ray.h"

// Image: 1.5 in full image width
// Image: 1 is full image heigth
const float aspect_ratio = {16.0 / 9.0};                                    // Image: Aspect ratio: resolution
const int image_width = {500};                                              // Image: Width
const int image_height = {static_cast<int>(image_width / aspect_ratio)};    // Image: Height

const int samples_per_pixel = {100};                                        // Rays per pixel
const int max_depth = {10};                                                 // Ray bounce limit per pixel

std::vector<Color> pixels(image_height *image_width);

Hittable_list random_scene() {
	// World set: +x goes right from the camera
	// World set: +y goes down from the camera
	// World set: +z goes behind from the camera
	// WOLRD left hand:
	Hittable_list world;

	shared_ptr<Material> material_sphere_g = make_shared<Lambertian>(Color(0.1, 0.1, 0.1));
	shared_ptr<Material> material_sphere_c = make_shared<Glass>(Color(0.8, 0.8, 0.8));
	shared_ptr<Material> material_sphere_m = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
	shared_ptr<Material> material_sphere_d = make_shared<dielectric>(1.5);

	for (int i = -5; i < 5; i++) {
		for (int j = -5; j < 5; j++) {

			shared_ptr<Material> material_sphere_l = make_shared<Lambertian>(Color(random_float(0, 1), random_float(0, 1), random_float(0, 1)));

			Point position(j * 10 * random_float(), 0.0, i * 10 * random_float());

			if (i % 3 == 0 || i % 7 == 0) {
				world.add(make_shared<Sphere>(
					position,
					random_float(0.5, 1.0),
					material_sphere_l));
			}
			else if (i % 4 == 0) {
				world.add(make_shared<Sphere>(
					position,
					random_float(0.5, 1.0),
					material_sphere_m));
			}
			else if (i % 5 == 0) {
				world.add(make_shared<Sphere>(
					position,
					random_float(0.5, 1.0),
					material_sphere_d));
			}
			else {
				world.add(make_shared<Sphere>(
					position,
					random_float(0.5, 1.0),
					material_sphere_c));
			}
		}
	}

	world.add(make_shared<Sphere>(Point(-10.0, -3.5, -17.0), 3.5, material_sphere_c));
	world.add(make_shared<Sphere>(Point(-0.0,  -3.5, -20.0), 3.5, material_sphere_m));
	world.add(make_shared<Sphere>(Point(+10.0, -3.5, -17.0), 3.5, material_sphere_d));

	world.add(make_shared<Sphere>(Point(0.0, 1000.5, -1.0), 1000.0, material_sphere_g));

	return world;
}

Camera get_camera(const float aspect_ratio) {

	// CAMERA: World rules applied
	Point lookfrom(+20.0, -5.0, +10.0);
	Point lookat(-0.0, -4.5, -17.0);
	Vec view_up(+0.0, +1.0, +0.0);                                                      // Its +1 because of the camera's coordinate not the world's

	float dist_to_focus = lookat.getZ() < 0 ? lookat.getZ() * (-1) : lookat.getZ();
	float aperture = 0.1;

	return Camera(lookfrom, lookat, view_up, 37.0, aspect_ratio, aperture, dist_to_focus);
}

// WORLD:
const Hittable_list world = random_scene();

// CAMERA:
const Camera camera = get_camera(aspect_ratio);

// 7680
// 1337