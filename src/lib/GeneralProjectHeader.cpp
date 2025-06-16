#include "GeneralProjectHeader.h"

namespace OpenCreativeSoftware {
	ProjectLib::GeneralProjectHeaderV1::GeneralProjectHeaderV1() : type(ProjectType::Unknown), name("New OCS Project"), v2(nullptr) {
		this->creationDate = time(nullptr);
		this->lastEditDate = this->creationDate;
	}

	void ProjectLib::GeneralProjectHeaderV1::Import(pugi::xml_node& t_node) {
		auto v1Node = t_node.child("GeneralProjectHeader").child("V1");
		type = static_cast<ProjectType>(v1Node.child("ProjectType").text().as_int());
		name = v1Node.child("ProjectName").text().as_string();
		creationDate = v1Node.child("CreationDate").text().as_ullong();
		lastEditDate = v1Node.child("LastEditDate").text().as_ullong();
	}

	void ProjectLib::GeneralProjectHeaderV1::Export(pugi::xml_node& t_node) {
		auto v1Node = t_node.append_child("V1");
		v1Node.append_child("ProjectType").append_child(pugi::node_pcdata).set_value(std::to_string(static_cast<int>(type)));
		v1Node.append_child("ProjectName").append_child(pugi::node_pcdata).set_value(name);
		v1Node.append_child("CreationDate").append_child(pugi::node_pcdata).set_value(std::to_string(creationDate));
		v1Node.append_child("LastEditDate").append_child(pugi::node_pcdata).set_value(std::to_string(lastEditDate));
		auto v2Node = t_node.append_child("V2");
		if (v2) {
			// not implemented now
		}
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