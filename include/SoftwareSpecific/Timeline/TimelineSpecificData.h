#pragma once

#include "Common.h"
#include "XMLExport.h"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct TimelineSpecificDataV1 : public XMLExportable {
			size_t id;

			NextVersionData* v2; // TimelineSpecificDataV2

			TimelineSpecificDataV1();

			void Export(pugi::xml_node& t_node);

			void Destroy();
		};

		struct TimelineSpecificDataV2 {
			void Destroy() {}
		};

		using TimelineSpecificData = TimelineSpecificDataV1;
	};
};