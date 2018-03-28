#import <Foundation/Foundation.h>
#include "app_delegate.h"

int main(int argc, const char * argv[])
{
    @autoreleasepool
    {
        auto delegate = new my_app_delegate();
        auto& application = engine::application::instance();
        
        application.set_delegate(delegate);
        application.on_launched();
        
        // insert code here...
        NSLog(@"Hello, World!");
    }
    return 0;
}
