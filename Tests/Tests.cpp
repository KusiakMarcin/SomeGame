#include "pch.h"
#include "ResourceManager.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ResourceManager::getInstance().LoadShader("vertex.vrtx", "frag.frag", nullptr, "triangle");
		}
	};
}
