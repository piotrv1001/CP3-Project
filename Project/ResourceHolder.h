
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void						load(Identifier id, const std::string& filename);
		Resource&					get(Identifier id);
private:
		void						insertResource(Identifier id, std::unique_ptr<Resource> resource);
		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "ResourceHolder.inl"

