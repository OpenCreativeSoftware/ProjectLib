#include "XMLExport.h"
#include "XMLExportable.h"

namespace OpenCreativeSoftware {
	pugi::xml_document ProjectLib::XMLExport::ExportGeneralProjectHeader(const GeneralProjectHeader* t_header) {
		pugi::xml_document result;
		auto headerNode = result.append_child("GeneralProjectHeader");
		((XMLExportable*) t_header)->Export(headerNode);
		return result;
	}

	pugi::xml_document ProjectLib::XMLExport::ExportProjectData(const ProjectData& t_data) {
		pugi::xml_document result;
		auto dataNode = result.append_child("ProjectData");
		dataNode.append_attribute("Type") = static_cast<int>(t_data.type);
		((XMLExportable*) t_data.ptr)->Export(dataNode);
		return result;
	}

};