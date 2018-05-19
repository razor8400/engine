#import <Foundation/Foundation.h>
#include <QApplication>

#include "engine.h"
#include "editor_app_delegate.h"

int main(int argc, char* argv[])
{
    @autoreleasepool
    {
        QApplication app(argc, argv);
        
        auto delegate = editor_app_delegate();
        auto& application = engine::application::instance();
        
        application.set_delegate(&delegate);
        
        if (!application.on_launched())
            return 0;

        return app.exec();
    }
    return 0;
}
