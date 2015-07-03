#ifndef _COLOR_H_
#define _COLOR_H_

namespace KY
{
	template<typename Type>
    class Color
    {
    public:
		Color(){}
		Color(const Type &_r, const Type &_g, const Type &_b, const Type &_a)
			: r(_r), g(_g), b(_b), a(_a)
		{}

		~Color(){}
		
		union {
			struct {
				Type r, g, b, a;
			};
			Type m[4];
		};

		static Color Red;
		static Color Green;
		static Color Blue;
		static Color Black;
		static Color None;
    };

	typedef Color<float>	ColorF;
	typedef Color<uint8>	Color32B;


}
#endif // _COLOR_H_