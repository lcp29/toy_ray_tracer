cmake_minimum_required(VERSION 3.23)
project(ray_tracing_rest_life)

set(CMAKE_CXX_STANDARD 20)

add_executable(ray_tracing_rest_life src/main.cpp src/vec3.cpp src/vec3.h src/camera.cpp src/camera.h src/ray.h src/hittable/hittable.h src/material/material.h src/hit_record.h src/hittable/sphere.cpp src/hittable/sphere.h src/hittable/hittable_list.cpp src/hittable/hittable_list.h src/material/lambertian.cpp src/material/lambertian.h src/material/dielectric.cpp src/material/dielectric.h src/material/emissive.h src/material/metal.cpp src/material/metal.h src/utils.h src/utils.cpp src/hittable/rectangle_xy.cpp src/hittable/rectangle_xy.h src/hittable/translation.cpp src/hittable/translation.h src/hittable/cuboid.cpp src/hittable/cuboid.h src/hittable/bvh_node.cpp src/hittable/bvh_node.h src/hittable/aabb.cpp src/hittable/aabb.h src/hittable/rectangle_xz.cpp src/hittable/rectangle_xz.h src/hittable/rectangle_yz.cpp src/hittable/rectangle_yz.h src/hittable/rotation_y.cpp src/hittable/rotation_y.h)
