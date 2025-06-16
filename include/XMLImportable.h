#pragma once
#include "XML/XML.hpp"

namespace OpenCreativeSoftware {
	namespace ProjectLib {
		struct XMLImportable {
			virtual void Import(pugi::xml_node& t_node) = 0;
		};
	};
};