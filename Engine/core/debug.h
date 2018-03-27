#pragma once

#include <cstdio>

#define LOG(MESSAGE, ...)\
printf(MESSAGE, __VA_ARGS__);\
printf("\n");
