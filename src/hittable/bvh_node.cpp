//
// Created by helmholtz on 2022/8/31.
//

#include "bvh_node.h"

using std::vector, std::shared_ptr, std::make_shared, std::sort, std::numeric_limits;

bool comparator_x(const shared_ptr<hittable> &a, const shared_ptr<hittable> &b)
{
    auto ba = a->get_aabb();
    auto bb = b->get_aabb();
    return ba.c0[0] < bb.c0[0];
}

bool comparator_y(const shared_ptr<hittable> &a, const shared_ptr<hittable> &b)
{
    auto ba = a->get_aabb();
    auto bb = b->get_aabb();
    return ba.c0[1] < bb.c0[1];
}

bool comparator_z(const shared_ptr<hittable> &a, const shared_ptr<hittable> &b)
{
    auto ba = a->get_aabb();
    auto bb = b->get_aabb();
    return ba.c0[2] < bb.c0[2];
}

float get_surface_area(const aabb &box)
{
    vec3 geo_para = box.c1 - box.c0;
    return 2 * (geo_para.x() * geo_para.y() + geo_para.x() * geo_para.z() + geo_para.y() * geo_para.z());
}

bool bvh_node::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    if (!box.hit(r, tmin, tmax))
        return false;
    bool hit_left = left->hit(r, tmin, tmax, rec);
    bool hit_right = right->hit(r, tmin, hit_left ? rec.t : tmax, rec);
    return hit_left || hit_right;
}

aabb bvh_node::get_aabb()
{
    if (!aabb_valid)
    {
        aabb bl = left->get_aabb();
        aabb br = right->get_aabb();
        box = aabb::merge(bl, br);
    }
    return box;
}

bvh_node::bvh_node(vector<shared_ptr<hittable>> &objects, int il, int ir)
{
    auto width = ir - il;
    if (width == 1)
    {
        left = right = objects[il];
    } else if (width == 2)
    {
        left = objects[il];
        right = objects[il + 1];
    } else
    {
        static bool (*comparator[3])(const shared_ptr<hittable> &, const shared_ptr<hittable> &) = {comparator_x,
                                                                                                    comparator_y,
                                                                                                    comparator_z};
        // SAH
        int max_a = 0;
        int max_i = 0;
        float min_cost = numeric_limits<float>::max();
        auto *cost_left = new float[width];
        auto *cost_right = new float[width];
        auto iter_il = objects.begin() + il;
        auto iter_ir = objects.begin() + ir;
        for (int a = 0; a < 3; ++a)
        {
            sort(iter_il, iter_ir, *(comparator[a]));
            aabb left = objects[il]->get_aabb(), right = objects[ir - 1]->get_aabb();
            for (int i = 0; i < width - 1 ; ++i)
            {
                cost_left[i + 1] = get_surface_area(left);
                cost_right[width - i - 1] = get_surface_area(right);
                left = aabb::merge(left, objects[il + i + 1]->get_aabb());
                right = aabb::merge(right, objects[ir - i - 2]->get_aabb());
            }
            for (int i = 1; i < width; ++i)
            {
                auto c = cost_left[i] * static_cast<float>(i) + cost_right[i] * static_cast<float>(width - i);
                if (c < min_cost)
                {
                    min_cost = c;
                    max_a = a;
                    max_i = i;
                }
            }
        }
        delete[] cost_left;
        delete[] cost_right;
        sort(iter_il, iter_ir, *(comparator[max_a]));
        left = (max_i == 1) ? objects[il] : make_shared<bvh_node>(objects, il, il + max_i);
        right = (max_i == width - 1) ? objects[ir - 1] : make_shared<bvh_node>(objects, il + max_i, ir);
    }
    box = aabb::merge(left->get_aabb(), right->get_aabb());
    aabb_valid = true;
}
