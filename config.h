#pragma once			// Only VS, checks that the headerfile is include only once, fastest
#if !defined (INCLUDED_CONFIG_H)			// see endif, alternative to #pragma, safest
#define INCLUDED_CONFIG_H					// always use both

#include <iostream>
#define PRINT(X) std::cout << (X) << std::endl;

#endif
