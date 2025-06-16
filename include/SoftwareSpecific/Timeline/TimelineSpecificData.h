#pragma once

#include "Common.h"
#include "XMLExport.h"
#include "XMLExportable.h"
#include "XMLImportable.h"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct TimelineSpecificDataV1 : public XMLExportable, public XMLImportable {
			size_t id;

			NextVersionData* v2; // TimelineSpecificDataV2

			TimelineSpecificDataV1();

			void Import(pugi::xml_node& t_node);
			void Export(pugi::xml_node& t_node);

			void Destroy();
		};

		struct TimelineSpecificDataV2 {
			void Destroy() {}
		};

		using TimelineSpecificData = TimelineSpecificDataV1;
	};
};