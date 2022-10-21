
#include <iostream>
#include <fstream>
#include "vec3.h"
#include "camera.h"
#include "hittable/hittable_list.h"
#include "hittable/sphere.h"
#include "material/lambertian.h"
#include "material/dielectric.h"
#include "material/emissive.h"
#include "material/metal.h"
#include "hittable/rectangle_xy.h"
#include "hittable/translation.h"
#include "hittable/cuboid.h"
#include "hittable/bvh_node.h"

using std::make_shared, std::cout, std::endl;

constexpr int resx = 640;
constexpr int resy = 480;
constexpr int N = 1;
constexpr int MSAA = 1;

color ray_color(const ray &r, float tmin, float tmax, const hittable &world, int depth)
{
    if (depth < 0)
        return {0, 0, 0};
    hit_record rec;
    if (!world.hit(r, tmin, tmax, rec))
    {
        // return {0, 0, 0};
        float rx = r.d().x(), ry = r.d().y(), rz = r.d().z();
        float t = atan(ry / sqrt(rx * rx + rz * rz)) * 1.27323954 + 1;
        return color(135, 206, 235) * (1 - t) + color(200, 200, 200) * t;
    }
    color att;
    ray scattered;
    if(rec.mat->scatter(r, scattered, rec, att))
        return att * ray_color(scattered, tmin, tmax, world, depth - 1);
    else
        return rec.mat->emission(r, rec);
}

color buffer[resy][resx];

int main()
{
    camera cam({0, 1, 0}, {0, 1, -1}, {0, 1, 0}, 0.1, 10000, 1.5708, 0.75);
    hittable_list hittables;
    hittables.add(make_shared<sphere>(vec3(0, -1000, 0), 999,
                                           make_shared<lambertian>(color(0.8, 0.8, 0.3))));
    hittables.add(make_shared<translation>(vec3(1, 0, 0), make_shared<sphere>(vec3(0, 1, -4), 1,
                                           make_shared<dielectric>(0.7, color(1, 1, 1), 0.1))));
    hittables.add(make_shared<sphere>(vec3(-2, 1, -3.5), 0.4,
                                      make_shared<metal>(color(0.8, 0.2, 0.2), 0.2)));
    hittables.add(make_shared<sphere>(vec3(0, 3, -4), 0.4,
                                      make_shared<emissive>(color(2560, 1000, 1000))));
    hittables.add(make_shared<cuboid>(vec3(-2, 0, -2), vec3(-1.8, 1, -3),
                                      make_shared<dielectric>(0.7, color(0.8, 1, 0.8), 1)));
    /*
    for (int ix = 0; ix < 10; ++ix)
    {
        for (int iy = 0; iy < 10; iy++)
        {
            hittables.add(make_shared<sphere>(vec3(-5 + ix * 0.5, iy * 0.5, -6), 0.4,
                    make_shared<metal>(color(random_float_0_1(), random_float_0_1(), random_float_0_1()), 0.3)));
        }
    }*/
    /*
    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<emissive>(color(3000, 3000, 3000));
    hittables.add(make_shared<rectangle_yz>(-2, -4, 2, -1, -2, green));
    hittables.add(make_shared<rectangle_yz>(-2, -4, 2, -1, 2, red));
    //hittables.add(make_shared<rectangle_xz>(213, 343, 227, 332, 554, light));
    hittables.add(make_shared<rectangle_xz>(-2, -4, 2, -1, -2, white));
    //hittables.add(make_shared<rectangle_xz>(0, 555, 0, 555, 555, white));
    //hittables.add(make_shared<rectangle_xy>(0, 555, 0, 555, 555, white));
     */
    bvh_node world(hittables.get_objects(), 0, hittables.get_objects().size());
    cout << "BVH tree generated." << endl;
    for (auto &j: buffer)
        for (auto &i: j)
            i = {0, 0, 0};
    float sub_pixel_a = 1.0 / MSAA;
    for (int n = 0; n < N; ++n)
    {
        for (int j = 0; j < resy; ++j)
        {
            for (int i = 0; i < resx; ++i)
            {
                for (int u = 0; u < MSAA; ++u)
                {
                    for (int v = 0; v < MSAA; ++v)
                    {
                        buffer[j][i] = buffer[j][i] + ray_color(cam.gen_ray(static_cast<float>(i + u * sub_pixel_a) / static_cast<float>(resx),
                                                                            static_cast<float>(j + v * sub_pixel_a) / static_cast<float>(resy)),
                                                                cam.tmin(), cam.tmax(), world, 5);
                    }
                }
            }
        }
    }
    for (auto &j: buffer)
        for (auto &i: j)
            i = i / (N * MSAA * MSAA);
    std::ofstream fout("output.ppm");
    fout << "P3\n" << resx << " " << resy << "\n255\n";
    for (int iy = resy - 1; iy >= 0; iy--)
    {
        for (int ix = 0; ix < resx; ix++)
        {
            fout << (buffer[iy][ix].x() > 255 ? 255 : (int) buffer[iy][ix].x()) << " "
                 << (buffer[iy][ix].y() > 255 ? 255 : (int) buffer[iy][ix].y()) << " "
                 << (buffer[iy][ix].z() > 255 ? 255 : (int) buffer[iy][ix].z()) << "\n";
        }
    }
    return 0;
}
