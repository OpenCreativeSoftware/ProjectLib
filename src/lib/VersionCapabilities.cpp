#include "VersionCapabilities.h"

namespace OpenCreativeSoftware {
	std::string ProjectLib::BuildInfo::GetBuildTimestamp() {
		return OCS_PROJECTLIB_TIMESTAMP;
	}

	int ProjectLib::VersionCapabilities::GetMaxTimelineProjectVersion() {
		return 1;
	}

	int ProjectLib::VersionCapabilities::GetMaxRasterProjectVersion() {
		return 1;
	}
};