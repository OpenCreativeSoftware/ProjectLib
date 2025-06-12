#pragma once

/* Reusable code pieces are located here */

#include <iostream>
#include <string>
#include <ctime>
#include <cstdint>

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		enum class ProjectType : int {
			Unknown = 0, Timeline = 1, Raster = 2
		};

		struct NextVersionData;
	};
};