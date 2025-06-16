#pragma once
#include "XML/XML.hpp"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct XMLExportable {
			virtual void Export(pugi::xml_node& t_node) = 0;
		};
	};
};