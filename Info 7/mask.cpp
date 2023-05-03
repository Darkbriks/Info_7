#include "mask.h"
#include <iostream>

using namespace std;

type_mask empty_mask() {const type_mask mask; return mask;}

int get_mask(const type_mask mask) {return *mask.mask;}

void clear_mask(const type_mask mask) {for (int i = 0; i < 64; i++) mask.set_mask(i/8, i%8, 0);}
