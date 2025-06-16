#include "OCSExport.h"
#include "XMLExport.h"
#include "XMLExportable.h"
#include "XMLImportable.h"
#include "Zip/zip.h"
#include "SoftwareSpecific/Timeline/TimelineSpecificData.h"

#ifdef _WIN32
#include "win_dirent.h"
#else
#include <dirent.h>
#endif

namespace OpenCreativeSoftware {
    void ZipWalk(struct zip_t* zip, const char* path) {
        auto reservedCwd = fs::current_path();
        std::filesystem::current_path(path);
        for (auto file : fs::recursive_directory_iterator(".")) {
            auto stringPath = file.path().lexically_normal().string();
            if (fs::is_directory(stringPath)) continue;
            zip_entry_open(zip, stringPath.c_str());
            zip_entry_fwrite(zip, stringPath.c_str());
            zip_entry_close(zip);
        }
        std::filesystem::current_path(reservedCwd);
    }

    void ZipPack(const std::string& t_zipFile, const std::string& t_inputDirectory) {
        auto zip = zip_open(t_zipFile.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
        ZipWalk(zip, t_inputDirectory.c_str());
        zip_close(zip);
    }

    void ZipExtract(const std::string& t_zipFile, const std::string& t_outputDirectory) {
        zip_extract(t_zipFile.c_str(), t_outputDirectory.c_str(), nullptr, nullptr);
    }

    void ProjectLib::ProjectArchive::Destroy() {
        project.Destroy();
        DeleteTemporaryFolder();
        unpackedPath = "";
        id = 0;
    }

    void ProjectLib::ProjectArchive::DeleteTemporaryFolder() {
        if (!unpackedPath.empty()) {
            std::filesystem::remove_all(unpackedPath);
        }
    }

	void ProjectLib::OCSExport::ExportProjectArchive(const ProjectArchive& t_archive, const bool t_dumpXml) {
        if (t_archive.unpackedPath.empty()) {
            throw std::runtime_error("invalid ProjectArchive! unpackedPath is empty");
        }
        if (t_dumpXml) {
            std::stringstream headerStream;
            std::stringstream projectStream;
            XMLExport::ExportGeneralProjectHeader(t_archive.project.header).print(headerStream);
            XMLExport::ExportProjectData(t_archive.project.data).print(projectStream);
            WriteFile(t_archive.unpackedPath + "/header.xml", headerStream.str());
            WriteFile(t_archive.unpackedPath + "/project.xml", projectStream.str());
            if (!fs::exists(t_archive.unpackedPath + "/files/")) {
                fs::create_directory(t_archive.unpackedPath + "/files/");
            }
        }
        ZipPack(t_archive.archivePath, t_archive.unpackedPath);
	}
    
    void ProjectLib::OCSExport::UnpackProjectArchive(ProjectArchive& t_archive) {
        auto temporaryFolder = fs::temp_directory_path().string();
        auto id = time(nullptr);
        auto unpackedPath = temporaryFolder + "/" + std::to_string(id);
        ZipExtract(t_archive.archivePath.c_str(), unpackedPath.c_str());
        t_archive.unpackedPath = unpackedPath;
        t_archive.id = id;
    }

    ProjectLib::ProjectArchive ProjectLib::OCSExport::CreateEmptyProjectArchive(const Project& t_project, const std::string& t_path) {
        std::stringstream headerStream;
        std::stringstream projectStream;
        XMLExport::ExportGeneralProjectHeader(t_project.header).print(headerStream);
        XMLExport::ExportProjectData(t_project.data).print(projectStream);

        auto zip = zip_open(t_path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
        zip_entry_open(zip, "header.xml");
        zip_entry_write(zip, headerStream.str().c_str(), headerStream.str().size());
        zip_entry_close(zip);

        zip_entry_open(zip, "project.xml");
        zip_entry_write(zip, projectStream.str().c_str(), projectStream.str().size());
        zip_entry_close(zip);

        char placeholder[64];
        zip_entry_open(zip, "files/placeholder");
        zip_entry_write(zip, placeholder, 64);
        zip_entry_close(zip);

        zip_close(zip);

        ProjectArchive result;
        result.project = t_project;
        result.archivePath = t_path;
        result.unpackedPath = "";
        result.id = time(nullptr);
        return result;
    }

    ProjectLib::ProjectArchive ProjectLib::OCSImport::ImportProjectArchive(const std::string& t_path) {
        auto id = time(nullptr);
        std::string temporaryPath = fs::temp_directory_path().string() + "/" + std::to_string(id);
        ZipExtract(t_path, temporaryPath);
        auto result = ImportUnpackedProjectArchive(temporaryPath, t_path);
        result.id = id;
        return result;
    }

    ProjectLib::ProjectArchive ProjectLib::OCSImport::ImportUnpackedProjectArchive(const std::string& t_path, const std::string& t_archivePath) {
        Project project;

        pugi::xml_document headerDocument;
        headerDocument.load_file((t_path + "/header.xml").c_str());

        project.header = new GeneralProjectHeader();
        (dynamic_cast<XMLImportable*>(project.header))->Import(headerDocument);

        project.data.type = project.header->type;
        if (project.header->type == ProjectType::Timeline) {
            project.data.ptr = (SoftwareSpecificData*) new TimelineSpecificData();
        } else {
            throw std::runtime_error("unknown project type");
        }

        pugi::xml_document projectDocument;
        projectDocument.load_file((t_path + "/project.xml").c_str());
        ((XMLImportable*)(project.data.ptr))->Import(projectDocument);

        ProjectArchive archive;
        archive.project = project;
        archive.archivePath = t_archivePath;
        archive.unpackedPath = t_path;
        archive.id = time(nullptr);
        return archive;
    }
};