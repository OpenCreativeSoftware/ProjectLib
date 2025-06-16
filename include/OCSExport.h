#pragma once

#include "Common.h"
#include "Project.h"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct ProjectArchive {
			Project project;
			std::string archivePath; // holds path to the .ocs file
			std::string unpackedPath; // holds path to the directory where project is unpacked
			time_t id; // project archive internal id

			ProjectArchive() : archivePath(""), unpackedPath(""), id(0) {}

			void Destroy();
			void DeleteTemporaryFolder();
		};

		struct OCSExport {
			static void ExportProjectArchive(const ProjectArchive& t_archive, const bool t_dumpXml = true);
			static void UnpackProjectArchive(ProjectArchive& t_archive);
			static ProjectArchive CreateEmptyProjectArchive(const Project& t_project, const std::string& t_path);
		};

		struct OCSImport {
			// const std::string& t_path - path to .ocs project
			static ProjectArchive ImportProjectArchive(const std::string& t_path);

			// const std::string& t_path - path to the content of unpacked .ocs project
			static ProjectArchive ImportUnpackedProjectArchive(const std::string& t_unpackedPath, const std::string& t_archivePath);
		};
	};
};