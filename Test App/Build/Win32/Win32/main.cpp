#include "my_app_delegate.h"

int main()
{
	auto& application = engine::application::instance();
	auto app_delegate = my_app_delegate();

	application.set_delegate(&app_delegate);
	application.on_launched();

	return 1;
}