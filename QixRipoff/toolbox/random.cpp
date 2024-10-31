#include "random.hpp"

int random32() {
	int r = 0;
	r |= rand();
	r |= rand() << 15;
	r |= (rand() & 3) << 30;
	return r;
}