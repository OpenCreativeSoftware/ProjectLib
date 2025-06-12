#pragma once

#include "Common.h"
#include "GeneralProjectHeader.h"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct SoftwareSpecificData;

		struct ProjectData {
			ProjectType type;
			SoftwareSpecificData* ptr;

			ProjectData() : type(ProjectType::Unknown), ptr(nullptr) {}
		};

		struct Project {
			GeneralProjectHeader* header;
			ProjectData data; // TimelineSpecificData, RasterSpecificData and etc.

			Project() : header(nullptr) {}

			// Project data must be manually deleted using Destroy() or DestroyHeader() + DestroyData() functions
			void Destroy();
			void DestroyHeader();
			void DestroyData();

			static Project CreateTimelineProject();
			static Project CreateRasterProject();
		};
	};
};