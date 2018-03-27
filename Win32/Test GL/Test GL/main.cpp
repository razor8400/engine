#include "app_delegate.h"

engine::application app;

int main()
{
	auto delegate = new my_app_delegate();

	app.set_delegate(delegate);
	app.on_launched();

	return 0;
}