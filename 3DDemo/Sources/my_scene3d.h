#pragma once

#include "engine.h"

class my_scene3d : public engine::scene
{
public:
    void on_enter() override;
    void draw(engine::renderer* r) override;
private:
};
