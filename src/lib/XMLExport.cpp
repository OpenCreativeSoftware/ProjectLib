#include "XMLExport.h"

namespace OpenCreativeSoftware {
	pugi::xml_document ProjectLib::XMLExport::ExportGeneralProjectHeader(const GeneralProjectHeader* t_header) {
		pugi::xml_document result;
		auto headerNode = result.append_child("GeneralProjectHeader");
		auto v1Node = headerNode.append_child("V1");
		if (t_header) {
			v1Node.append_child("ProjectType").append_child(pugi::node_pcdata).set_value(std::to_string(static_cast<int>(t_header->type)));
			v1Node.append_child("ProjectName").append_child(pugi::node_pcdata).set_value(t_header->name);
			v1Node.append_child("CreationDate").append_child(pugi::node_pcdata).set_value(std::to_string(t_header->creationDate));
			v1Node.append_child("LastEditData").append_child(pugi::node_pcdata).set_value(std::to_string(t_header->lastEditDate));
		}
		auto v2Node = headerNode.append_child("V2");
		if (t_header && t_header->v2) {

		}
		return result;
	}

	pugi::xml_document ProjectLib::XMLExport::ExportProjectData(const ProjectData& t_data) {
		pugi::xml_document result;
		auto dataNode = result.append_child("ProjectData");
		dataNode.append_attribute("Type") = static_cast<int>(t_data.type);
		if (t_data.ptr) {
			auto exportable = (XMLExportable*) t_data.ptr;
			exportable->Export(dataNode);
		}
		return result;
	}

};