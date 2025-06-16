#pragma once

/* Reusable code pieces are located here */

#include <iostream>
#include <string>
#include <ctime>
#include <cstdint>
#include <sstream>
#include <filesystem>
#include <fstream>

namespace OpenCreativeSoftware {
	namespace fs = std::filesystem;

	namespace ProjectLib {
		enum class ProjectType : int {
			Unknown = 0, Timeline = 1, Raster = 2
		};

		struct NextVersionData;

        static void WriteFile(const std::string& path, const std::string& content) {
            std::ofstream file(path, std::ios_base::binary);
            file.exceptions(std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit);
            file << content;
        }
	};
};