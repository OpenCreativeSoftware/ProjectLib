#include "Project.h"

#include "SoftwareSpecific/Timeline/TimelineSpecificData.h"

namespace OpenCreativeSoftware {
	
	void ProjectLib::Project::Destroy() {
		DestroyHeader();
		DestroyData();
	}

	void ProjectLib::Project::DestroyHeader() {
		if (!header) return;
		header->Destroy();
		delete header;
		header = nullptr;
	}

	void ProjectLib::Project::DestroyData() {
		if (!data.ptr) return;
		if (!header) return;
		if (header->type == ProjectType::Timeline && data.ptr) {
			auto timelineData = (TimelineSpecificData*) data.ptr;
			timelineData->Destroy();
			delete timelineData;
		}
		else if (header->type == ProjectType::Raster && data.ptr) {
			// not implemented
		}
		data = ProjectData();
	}

	ProjectLib::Project ProjectLib::Project::CreateTimelineProject() {
		Project result;
		result.header = new GeneralProjectHeader();
		result.header->name = "New Timeline Project";
		result.data.type = result.header->type = ProjectType::Timeline;
		result.data.ptr = (SoftwareSpecificData*) new TimelineSpecificData();
		return result;
	}

	ProjectLib::Project ProjectLib::Project::CreateRasterProject() {
		// not implemented
		return Project();
	}

};