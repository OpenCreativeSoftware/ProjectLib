#pragma once

#include "Common.h"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct GeneralProjectHeaderV1 {
			ProjectType type;
			std::string name;
			time_t creationDate;
			time_t lastEditDate;

			NextVersionData* v2; // GeneralProjectHeaderV2

			GeneralProjectHeaderV1();

			void Destroy();
		};

		struct GeneralProjectHeaderV2 {
			void Destroy() {}
		};

		using GeneralProjectHeader = GeneralProjectHeaderV1;
	};
};