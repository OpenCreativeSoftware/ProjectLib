#include "GeneralProjectHeader.h"

namespace OpenCreativeSoftware {

	ProjectLib::GeneralProjectHeaderV1::GeneralProjectHeaderV1() : type(ProjectType::Unknown), name("New OCS Project"), v2(nullptr) {
		this->creationDate = time(nullptr);
		this->lastEditDate = this->creationDate;
	}

	void ProjectLib::GeneralProjectHeaderV1::Destroy() {
		if (v2) {
			auto v2Data = (GeneralProjectHeaderV2*) v2;
			v2Data->Destroy();
			delete v2Data;
		}
		v2 = nullptr;
	}
};