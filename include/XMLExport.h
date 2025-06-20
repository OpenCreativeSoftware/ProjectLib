#pragma once

#include "Common.h"
#include "GeneralProjectHeader.h"
#include "Project.h"
#include "XML/XML.hpp"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct XMLExport {
			static pugi::xml_document ExportGeneralProjectHeader(const GeneralProjectHeader* t_header);
			static pugi::xml_document ExportProjectData(const ProjectData& t_data);
		};
	};
};