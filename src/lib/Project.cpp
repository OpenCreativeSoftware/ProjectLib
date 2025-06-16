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
			auto timelineData = (TimelineSpecificData*)data.ptr;
			timelineData->Destroy();
			delete timelineData;
		}
		else if (header->type == ProjectType::Raster && data.ptr) {
			// not implemented
		}
		data = ProjectData();
	}

	ProjectLib::Project BaseCreateProject(std::string t_name, ProjectLib::ProjectType t_type, ProjectLib::SoftwareSpecificData* t_data) {
		ProjectLib::Project result;
		result.header = new ProjectLib::GeneralProjectHeader();
		result.header->name = t_name;
		result.data.type = result.header->type = t_type;
		result.data.ptr = t_data;
		return result;
	}

	ProjectLib::Project ProjectLib::Project::CreateTimelineProject() {
		return BaseCreateProject("New Timeline Project", ProjectType::Timeline, reinterpret_cast<SoftwareSpecificData*>(new TimelineSpecificData()));
	}

	ProjectLib::Project ProjectLib::Project::CreateRasterProject() {
		// not implemented
		return Project();
	}

};