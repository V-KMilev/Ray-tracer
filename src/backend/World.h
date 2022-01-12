#pragma once

#include "Utility_functions.h"

#include "Thread_manager.h"

#include "Hittable_list.h"
#include "Hittable.h"
#include "Bucket.h"

#include "Sphere_moving.h"
#include "Sphere.h"

#include "Material.h"
#include "Texture.h"
#include "AArect.h"

#include "Camera.h"

#include "Color.h"
#include "Vec.h"
#include "Ray.h"
#include "Color.h"

shared_ptr<Material> image_material(const char *image_name) {
	shared_ptr<Texture> image = make_shared<Image_Texture>(image_name);

	return make_shared<Lambertian>(image);
}

Hittable_list get_scene() {
	// World set: +x goes right from the camera
	// World set: +y goes up from the camera
	// World set: +z goes front from the camera
	// WOLRD right hand:
	Hittable_list world;

	/* Textues */
	shared_ptr<Texture> checker_w = make_shared<Checker_Texture>(Color(0.0, 0.0, 0.0), Color(1.0, 1.0, 1.0));
	shared_ptr<Texture> checker_m = make_shared<Checker_Texture>(Color(0.0, 0.0, 0.0), Color(1.0, 0.0, 1.0));
	shared_ptr<Texture> noise = make_shared<Noise_Texture>();

	/* Materials */
	shared_ptr<Material> material_sphere_i_0 = image_material("");

	shared_ptr<Material> material_n = make_shared<Lambertian>(noise);
	
	shared_ptr<Material> material_white_c = make_shared<Lambertian>(checker_w);
	shared_ptr<Material> material_magenta_c = make_shared<Lambertian>(checker_m);

	shared_ptr<Material> material_white = make_shared<Lambertian>(Color(1,1,1));
	shared_ptr<Material> material_black = make_shared<Lambertian>(Color(0,0,0));
	shared_ptr<Material> material_gray = make_shared<Lambertian>(Color(0.5,0.5,0.5));
	shared_ptr<Material> material_red = make_shared<Lambertian>(Color(1,0,0));
	shared_ptr<Material> material_green = make_shared<Lambertian>(Color(0,1,0));
	shared_ptr<Material> material_blue = make_shared<Lambertian>(Color(0,0,1));

	shared_ptr<Material> material_magenta = make_shared<Lambertian>(Color(0.7,0,0.7));

	shared_ptr<Material> difflight_red = make_shared<Diffuse_light>(Color(3,0,0));
	shared_ptr<Material> difflight_blue = make_shared<Diffuse_light>(Color(0,0,3));
	shared_ptr<Material> difflight_green = make_shared<Diffuse_light>(Color(0,3,0));
	shared_ptr<Material> difflight_white = make_shared<Diffuse_light>(Color(3,3,3));
	shared_ptr<Material> difflight_magenta = make_shared<Diffuse_light>(Color(6,0,6));

	shared_ptr<Material> difflight_w = make_shared<Diffuse_light>(Color(37,37,37));
	shared_ptr<Material> difflight_w_low = make_shared<Diffuse_light>(Color(1,1,1));
	shared_ptr<Material> difflight_d = make_shared<Diffuse_light>(Color(0,0,0));
	shared_ptr<Material> difflight_magenta_m = make_shared<Diffuse_light>(Color(7,0,6));

	/* Objects */
	world.add(make_shared<xz_rect>(-1000, 1000, -1000, 1000, 0, material_n));
	world.add(make_shared<Sphere>(Point(0, 2000, 200), 100, difflight_w));

	// bases
	world.add(make_shared<xz_rect>(-5, 5, -5, 5, 0.2, material_black));           // base in
	world.add(make_shared<xz_rect>(-10, 10, -10, 10, 0.19, material_magenta));    // base out

	// center sphere
	world.add(make_shared<Sphere>(Point(0, 2, 0), 1, difflight_white));    // sphere

	// walls in
	world.add(make_shared<xy_rect>(-2.5, 2.5, 0, 3.2, 5, material_white_c));     // wall in
	world.add(make_shared<xy_rect>(-2.5, 2.5, 0, 3.2, -5, material_white_c));    // wall in
	world.add(make_shared<yz_rect>(0, 3.2, -2.5, 2.5, 5, material_white_c));     // wall in
	world.add(make_shared<yz_rect>(0, 3.2, -2.5, 2.5, -5, material_white_c));    // wall in

	// walls out
	world.add(make_shared<xy_rect>(-10, 10, 0, 4.2, 10, material_white_c));      // wall out
	world.add(make_shared<xy_rect>(-10, 10, 0, 4.2, -10, material_white_c));     // wall out
	world.add(make_shared<yz_rect>(0, 4.2, -10, 10, 10, material_white_c));      // wall out
	world.add(make_shared<yz_rect>(0, 4.2, -10, 10, -10, material_white_c));     // wall out



	// t1
	world.add(make_shared<xy_rect>(6, 10, 0, 6, 10, material_gray));                 // turret wall
	world.add(make_shared<xy_rect>(6, 10, 0, 6, 6, material_gray));                  // turret wall
	world.add(make_shared<yz_rect>(0, 6, 6, 10, 6, material_gray));                  // turret wall
	world.add(make_shared<yz_rect>(0, 6, 6, 10, 10, material_gray));                 // turret wall
	world.add(make_shared<xz_rect>(4, 10, 4, 10, 6, material_gray));                 // turret roof

	// t1 lamps
	world.add(make_shared<xz_rect>(4.5, 5.5, 4.5, 5.5, 5.99, difflight_magenta_m));    // turret roof
	world.add(make_shared<xz_rect>(4.5, 5.5, 8.5, 9.5, 5.99, difflight_magenta_m));    // turret roof
	world.add(make_shared<xz_rect>(8.5, 9.5, 4.5, 5.5, 5.99, difflight_magenta_m));    // turret roof



	// t2
	world.add(make_shared<xy_rect>(6, 10, 0, 6, -10, material_gray));                  // turret wall
	world.add(make_shared<xy_rect>(6, 10, 0, 6, -6, material_gray));                   // turret wall
	world.add(make_shared<yz_rect>(0, 6, -10, -6, 6, material_gray));                  // turret wall
	world.add(make_shared<yz_rect>(0, 6, -10, -6, 10, material_gray));                 // turret wall
	world.add(make_shared<xz_rect>(4, 10, -10, -4, 6, material_gray));                 // turret roof

	// t2 lamps
	world.add(make_shared<xz_rect>(4.5, 5.5, -5.5, -4.5, 5.99, difflight_magenta_m));    // turret roof
	world.add(make_shared<xz_rect>(4.5, 5.5, -9.5, -8.5, 5.99, difflight_magenta_m));    // turret roof
	world.add(make_shared<xz_rect>(8.5, 9.5, -5.5, -4.5, 5.99, difflight_magenta_m));    // turret roof



	// t3
	world.add(make_shared<xy_rect>(-10, -6, 0, 6, 10, material_gray));                 // turret wall
	world.add(make_shared<xy_rect>(-10, -6, 0, 6, 6, material_gray));                  // turret wall
	world.add(make_shared<yz_rect>(0, 6, 6, 10, -6, material_gray));                   // turret wall
	world.add(make_shared<yz_rect>(0, 6, 6, 10, -10, material_gray));                  // turret wall
	world.add(make_shared<xz_rect>(-10, -4, 4, 10, 6, material_gray));                 // turret roof

	// t3 lamps
	world.add(make_shared<xz_rect>(-5.5, -4.5, 4.5, 5.5, 5.99, difflight_magenta_m));    // turret roof
	world.add(make_shared<xz_rect>(-5.5, -4.5, 8.5, 9.5, 5.99, difflight_magenta_m));    // turret roof
	world.add(make_shared<xz_rect>(-9.5, -8.5, 4.5, 5.5, 5.99, difflight_magenta_m));    // turret roof



	// t4
	world.add(make_shared<xy_rect>(-10, -6, 0, 6, -10, material_gray));                  // turret wall
	world.add(make_shared<xy_rect>(-10, -6, 0, 6, -6, material_gray));                   // turret wall
	world.add(make_shared<yz_rect>(0, 6, -10, -6, -6, material_gray));                   // turret wall
	world.add(make_shared<yz_rect>(0, 6, -10, -6, -10, material_gray));                  // turret wall
	world.add(make_shared<xz_rect>(-10, -4, -10, -4, 6, material_gray));                 // turret roof

	// t4 lamps
	world.add(make_shared<xz_rect>(-5.5, -4.5, -5.5, -4.5, 5.99, difflight_magenta));    // turret roof
	world.add(make_shared<xz_rect>(-5.5, -4.5, -9.5, -8.5, 5.99, difflight_magenta));    // turret roof
	world.add(make_shared<xz_rect>(-9.5, -8.5, -5.5, -4.5, 5.99, difflight_magenta));    // turret roof

	return world;
}

// 7680
// 1337