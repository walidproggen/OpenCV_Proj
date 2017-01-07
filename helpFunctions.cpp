#include "helpFunctions.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <iterator>



bool elementFound(int element, int arrays[], int arraysize) {
	for (int i = 0; i < arraysize; i++) {
		if (arrays[i] == element) {
			return true;
		}
	}
	return false;
}