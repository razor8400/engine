#import <Foundation/Foundation.h>
#include "engine.h"

int main(int argc, char **argv)
{
    engine::director& director = engine::director::instance();
    director.set_frame_rate(60);
    director.set_display_name("Test Application");
    director.set_win_size(1024, 768);
    director.run();
    
    return 0;
}
