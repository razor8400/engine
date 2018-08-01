#include "my_scene3d.h"

using namespace engine;

void my_scene3d::on_enter()
{
    auto obj = game_object::create<game_object>();
    
    obj->set_size(math::vector3d(1, 1, 1));
    obj->set_position(math::vector3d(-0.5f, -0.5f, 0.0f));
    
    add_child(obj);
}

void my_scene3d::draw(engine::renderer* r)
{
    engine::scene::draw(r);
}
