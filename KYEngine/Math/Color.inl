namespace KY
{
	template<>
	Color<float> Color<float>::Red(1.0f, 0.0f, 0.0f, 1.0f);
	template<>
	Color<float> Color<float>::Green(0.0f, 1.0f, 0.0f, 1.0f);
	template<>
	Color<float> Color<float>::Blue(0.0f, 0.0f, 1.0f, 1.0f);
	template<>
	Color<float> Color<float>::Black(0.0f, 0.0f, 0.0f, 1.0f);
	template<>
	Color<float> Color<float>::None(0.0f, 0.0f, 0.0f, 0.0f);


	template<>
	Color<uint8> Color<uint8>::Red(255, 0, 0, 255);
	template<>
	Color<uint8> Color<uint8>::Green(0, 255, 0, 255);
	template<>
	Color<uint8> Color<uint8>::Blue(0, 0, 255, 255);
	template<>
	Color<uint8> Color<uint8>::Black(0, 0, 0, 255);
	template<>
	Color<uint8> Color<uint8>::None(0, 0, 0, 0);
}