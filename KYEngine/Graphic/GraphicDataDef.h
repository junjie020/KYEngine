#ifndef _GRAPHICDATADEF_H_
#define _GRAPHICDATADEF_H_

namespace KY
{
	class ShaderResourceView;
	using ShaderResourceViewVec = std::vector<ShaderResourceView*>;
	using ShaderResourceViewConstVec = std::vector<const ShaderResourceView*>;

	class SamplerStateObj;
	using SamplerStateObjVec = std::vector<SamplerStateObj*>;
	using SamplerStateObjConstVec = std::vector<const SamplerStateObj*>;
}
#endif // _GRAPHICDATADEF_H_