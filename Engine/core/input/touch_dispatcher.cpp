#include "common.h"
#include "touch_dispatcher.h"
#include "touch_event.h"

namespace engine
{
    touch_dispatcher& touch_dispatcher::instance()
    {
        static touch_dispatcher instance;
        return instance;
    }
    
    touch_dispatcher::touch_dispatcher()
    {
        
    }
    
    touch_dispatcher::~touch_dispatcher()
    {
        
    }
}
