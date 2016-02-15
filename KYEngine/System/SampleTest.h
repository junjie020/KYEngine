#ifndef _SAMPLETEST_H_
#define _SAMPLETEST_H_

namespace KY
{
	class RenderTarget;

    class SampleTest
    {
    public:
		virtual ~SampleTest(){}

		virtual bool Init(RenderTarget *) = 0;
    	

    private:

    };
}
#endif // _SAMPLETEST_H_