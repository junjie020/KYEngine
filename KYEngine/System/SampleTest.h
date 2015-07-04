#ifndef _SAMPLETEST_H_
#define _SAMPLETEST_H_

namespace KY
{
    class SampleTest
    {
    public:
		virtual ~SampleTest(){}

		virtual bool Init() = 0;
		virtual void Update() = 0;
    	

    private:

    };
}
#endif // _SAMPLETEST_H_