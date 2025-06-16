#include <iostream>
#include "VersionCapabilities.h"
#include "Project.h"
#include "XMLExport.h"
#include "OCSExport.h"

#include "argparse.hpp"

using namespace OpenCreativeSoftware::ProjectLib;

int main(int argc, char** argv) {
	argparse::ArgumentParser cli("ProjectLibCLI");
	
	cli.add_argument("--path", "-p")
		.help("path to .ocs project file")
		.default_value(std::string(""))
		.metavar("PATH");
	cli.add_argument("--new", "-n")
		.help("create new project")
		.implicit_value(true)
		.default_value(true);
	cli.add_argument("--name")
		.help("new project name")
		.default_value(std::string(""))
		.metavar("NAME");
	cli.add_argument("--type", "-t")
		.help("explicitly specify project type")
		.default_value(std::string("unknown"))
		.metavar("TYPE");
	cli.add_argument("--modify", "-m")
		.help("specify modified project part (header/project)")
		.default_value(std::string(""))
		.metavar("PART");
	cli.add_argument("--modify-path")
		.help("specify modification path (xpath)")
		.default_value(std::string(""))
		.metavar("PATH");
	cli.add_argument("--modify-value")
		.help("specify modification value (string)")
		.default_value(std::string(""))
		.metavar("VALUE");
	cli.add_argument("--dump", "-d")
		.help("dump project .xml files")
		.implicit_value(true)
		.default_value(false);
	cli.add_argument("-h", "--help")
		.action([&](const std::string& s) {
			std::cout << cli.help().str();
		})
		.default_value(false)
		.help("shows help message")
		.implicit_value(true)
		.nargs(0);

	cli.add_description("create and edit .ocs project file from your terminal");

	try {
		cli.parse_args(argc, argv);
		// cli.parse_known_args({ "--path", "project.ocs", "--dump" });
	} catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << cli;
		std::exit(1);
	}

	std::string projectPath = cli.get<std::string>("--path");
	std::string projectName = cli.get<std::string>("--name");
	bool createNew = cli.get<bool>("--new");
	bool dump = cli.get<bool>("--dump");
	ProjectType projectType = ProjectType::Unknown;
	std::string projectTypeString = cli.get<std::string>("--type");
	if (projectTypeString == "timeline") {
		projectType = ProjectType::Timeline;
	}
	if (projectTypeString == "raster") {
		projectType = ProjectType::Raster;
	}

	std::string modifyType = cli.get<std::string>("--modify");
	std::string modifyPath = cli.get<std::string>("--modify-path");
	std::string modifyValue = cli.get<std::string>("--modify-value");

	bool done = false;
	bool modified = false;

	if (createNew && projectType != ProjectType::Unknown) {
		auto project = Project();
		if (projectType == ProjectType::Timeline) project = Project::CreateTimelineProject();
		if (projectType == ProjectType::Raster) project = Project::CreateRasterProject();
		if (!projectName.empty()) project.header->name = projectName;
		std::cout << "creating project '" << project.header->name << "' (" << projectTypeString << " " << static_cast<int>(projectType) << ")" << std::endl;

		OCSExport::CreateEmptyProjectArchive(project, projectPath);
		done = true;
		project.Destroy();
	}

	if (!modifyType.empty() && projectPath.empty()) {
		std::cout << "no project to modify" << std::endl;
		done = true;
	}

	if (!modifyType.empty() && !projectPath.empty() && modifyPath.empty()) {
		std::cout << "--modify-path is empty! cannot modify " << projectPath << std::endl;
		done = true;
	}

	if (!modifyType.empty() && !projectPath.empty() && !modifyPath.empty()) {
		if (!std::filesystem::exists(projectPath)) {
			std::cout << projectPath << " is not found" << std::endl;
			return 1;
		}
		auto archive = OCSImport::ImportProjectArchive(projectPath);
		if (modifyType == "header") {
			std::cout << "modifying header.xml" << std::endl;
			pugi::xml_document headerDocument;
			headerDocument.load_file((archive.unpackedPath + "/header.xml").c_str());
			auto xpathNode = headerDocument.select_node(("GeneralProjectHeader/" + modifyPath).c_str());
			if (xpathNode.node()) {
				auto node = xpathNode.node();
				node.text().set(modifyValue.c_str());
				std::stringstream headerStream;
				headerDocument.print(headerStream);
				WriteFile(archive.unpackedPath + "/header.xml", headerStream.str());
			}
			else {
				std::cerr << "failed to get node by path " << modifyPath << std::endl;
			}
			done = true;
			modified = true;
			headerDocument.print(std::cout);
		}
		if (modifyType == "project") {
			std::cout << "modifying project.xml" << std::endl;
			pugi::xml_document projectDocument;
			projectDocument.load_file((archive.unpackedPath + "/project.xml").c_str());
			auto xpathNode = projectDocument.select_node(("ProjectData/" + modifyPath).c_str());
			if (xpathNode.node()) {
				auto node = xpathNode.node();
				node.text().set(modifyValue.c_str());
				std::stringstream projectStream;
				projectDocument.print(projectStream);
				WriteFile(archive.unpackedPath + "/project.xml", projectStream.str());
			}
			else {
				std::cerr << "failed to get node by path " << modifyPath << std::endl;
			}
			done = true;
			modified = true;
			projectDocument.print(std::cout);
		}
		OCSExport::ExportProjectArchive(archive, false);
		archive.Destroy();
	}

	if (dump) {
		if (!std::filesystem::exists(projectPath)) {
			std::cout << projectPath << " is not found" << std::endl;
			return 1;
		}
		auto archive = OCSImport::ImportProjectArchive(projectPath);

		std::cout << archive.project.header->name << " (";
		if (archive.project.header->type == ProjectType::Timeline) {
			std::cout << "timeline 1)" << std::endl;
		}
		if (archive.project.header->type == ProjectType::Raster) {
			std::cout << "raster 2)" << std::endl;
		}
		if (archive.project.header->type == ProjectType::Unknown) {
			std::cout << "unknown 0)" << std::endl;
		}
		std::cout << "archive path: " << archive.archivePath << std::endl;
		std::cout << "unpacked path: " << archive.unpackedPath << std::endl;

		XMLExport::ExportGeneralProjectHeader(archive.project.header).print(std::cout);
		XMLExport::ExportProjectData(archive.project.data).print(std::cout);

		archive.Destroy();
		done = true;
	}

	if (!done) {
		std::cout << cli.help().str();
	}
	else {
		if (!projectPath.empty() && std::filesystem::exists(projectPath)) {
			if (modified) {
				std::cout << "modifying last edit date (" << time(nullptr) << ")" << std::endl;
				auto archive = OCSImport::ImportProjectArchive(projectPath);
				pugi::xml_document headerDocument;
				headerDocument.load_file((archive.unpackedPath + "/header.xml").c_str());
				auto xpathNode = headerDocument.select_node("GeneralProjectHeader/V1/LastEditDate");
				if (xpathNode.node()) {
					auto node = xpathNode.node();
					node.text().set(std::to_string(time(nullptr)));
					std::stringstream headerStream;
					headerDocument.print(headerStream);
					WriteFile(archive.unpackedPath + "/header.xml", headerStream.str());
				}
				else {
					std::cerr << "failed to change last edit date (GeneralProjectHeader/V1/LastEditDate)";
				}
				OCSExport::ExportProjectArchive(archive, false);
				archive.Destroy();
			}
			else {
				std::cout << "no need to modify last edit date" << std::endl;
			}
		}
		std::cout << "done" << std::endl;
	}

	return 0;
}