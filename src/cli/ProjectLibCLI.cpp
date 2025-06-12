#include <iostream>
#include "VersionCapabilities.h"
#include "Project.h"
#include "XMLExport.h"

using namespace OpenCreativeSoftware::ProjectLib;

int main(int argc, char** argv) {
	Project timelineProject = Project::CreateTimelineProject();
	std::cout << timelineProject.header->name << std::endl;
	auto header = XMLExport::ExportGeneralProjectHeader(timelineProject.header);
	header.print(std::cout);
	auto project = XMLExport::ExportProjectData(timelineProject.data);
	project.print(std::cout);
	timelineProject.Destroy();
	return 0;
}