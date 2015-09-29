#ifndef _HASHIMPL_H_
#define _HASHIMPL_H_

namespace std
{
	template<>
	struct hash<fs::path>{
		size_t operator()(const fs::path& val) const{
			return hash<std::string>()(val.string());
		}
	};
}
#endif //_HASHIMPL_H_