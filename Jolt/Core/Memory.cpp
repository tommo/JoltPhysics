// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#include <Jolt.h>

#include <Core/Memory.h>
#include <cstdlib>
#include <stdlib.h>

// #ifdef __APPLE__
// #include <boost/align/aligned_alloc.hpp>
// using boost::alignment::aligned_alloc;
// #endif

namespace JPH {

void *AlignedAlloc(size_t inSize, size_t inAlignment)
{
#if defined(JPH_PLATFORM_WINDOWS)
	// Microsoft doesn't implement C++17 std::aligned_alloc
	return _aligned_malloc(inSize, inAlignment);
#elif defined(JPH_PLATFORM_ANDROID)
	return memalign(inAlignment, AlignUp(inSize, inAlignment));
#elif defined(JPH_PLATFORM_APPLE)
	return aligned_alloc(inAlignment, AlignUp(inSize, inAlignment));
#else
	return std::aligned_alloc(inAlignment, AlignUp(inSize, inAlignment));
#endif
}

void AlignedFree(void *inBlock)
{
#if defined(JPH_PLATFORM_WINDOWS)
	_aligned_free(inBlock);
#elif defined(JPH_PLATFORM_ANDROID)
	free(inBlock);
#elif defined(JPH_PLATFORM_APPLE)
	free(inBlock);
#else
	std::free(inBlock);
#endif
}

} // JPH