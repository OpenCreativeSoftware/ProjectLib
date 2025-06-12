#include "SoftwareSpecific/Timeline/TimelineSpecificData.h"
#include "XMLExport.h"

namespace OpenCreativeSoftware {

	ProjectLib::TimelineSpecificDataV1::TimelineSpecificDataV1() : v2(nullptr) {
		this->id = time(nullptr);
	}

	void ProjectLib::TimelineSpecificDataV1::Export(pugi::xml_node& t_node) {
		auto v1Node = t_node.append_child("V1");
		v1Node.append_child("ID").append_child(pugi::node_pcdata).set_value(std::to_string(id));

		auto v2Node = t_node.append_child("V2");
		if (v2) {
			// not implemented
		}
	}

	void ProjectLib::TimelineSpecificDataV1::Destroy() {
		if (v2) {
			auto v2Data = (TimelineSpecificDataV2*) v2;
			v2Data->Destroy();
			delete v2Data;
		}
		v2 = nullptr;
	}
};