#pragma once

namespace engine
{
    class action
    {
    public:
        virtual void update(float dt);
        virtual void start(game_object* target);
        
        virtual void finish() = 0;
    protected:
        virtual void step(float dt) = 0;
        virtual bool action_done() const = 0;
    private:
        game_object* m_target = nullptr;
        bool m_done = false;
    };
}
