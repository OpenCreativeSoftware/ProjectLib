#pragma once

#include "Common.h"
#include "XMLExportable.h"
#include "XMLImportable.h"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct GeneralProjectHeaderV1 : public XMLExportable, public XMLImportable {
			ProjectType type;
			std::string name;
			time_t creationDate;
			time_t lastEditDate;

			NextVersionData* v2; // GeneralProjectHeaderV2

			GeneralProjectHeaderV1();

			void Import(pugi::xml_node& t_node);
			void Export(pugi::xml_node& t_node);

			void Destroy();
		};

		struct GeneralProjectHeaderV2 {
			void Destroy() {}
		};

		using GeneralProjectHeader = GeneralProjectHeaderV1;
	};
};