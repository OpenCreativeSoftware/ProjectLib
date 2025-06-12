#pragma once

#include "Common.h"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct BuildInfo {
			static std::string GetBuildTimestamp();
		};

		struct VersionCapabilities {
			static int GetMaxTimelineProjectVersion();
			static int GetMaxRasterProjectVersion();
		};
	};
};