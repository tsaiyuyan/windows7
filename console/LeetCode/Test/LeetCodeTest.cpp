#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SolutionList.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LeetCodeTest
{		
	TEST_CLASS(LeetCodeTest)
	{
	private:
		Solution *solution;
	public:
		TEST_METHOD_INITIALIZE(initial) 
		{
			// method initialization code
			Logger::WriteMessage("solution initial()\n");
			
		}
		TEST_METHOD_CLEANUP(destroy) 
		{
			// test method cleanup  code
			Logger::WriteMessage("solution destroy()\n");
			
		}
		TEST_METHOD(test125)
		{
			solution = new Solution_125_Valid_Palindrome();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test125() finish testing!\n");
		}
		TEST_METHOD(test412)
		{
			solution = new Solution_412_Fizz_Buzz();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test412() finish testing!\n");
		}
		TEST_METHOD(test561)
		{
			solution = new Solution_561_Array_Partition_I();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test561() finish testing!\n");
		}
		TEST_METHOD(test575)
		{
			solution = new Solution_575_Distribute_Candies();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test575() finish testing!\n");
		}
		TEST_METHOD(test680)
		{
			solution = new Solution_680_Valid_Palindrome_II();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test680() finish testing!\n");
		}
		TEST_METHOD(test728)
		{
			solution = new Solution_728_Self_Dividing_Numbersr();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test728() finish testing!\n");
		}
		TEST_METHOD(test771)
		{
			solution = new Solution_771_Jewels_and_Stones();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test771() finish testing!\n");
		}
		TEST_METHOD(test848)
		{
			solution = new Solution_848_Shifting_Letters();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test848() finish testing!\n");
		}

		TEST_METHOD(test937)
		{
			solution = new Solution_937_Reorder_Log_Files();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test937() finish testing!\n");
		}
		
		TEST_METHOD(test980)
		{
			solution = new Solution_980_Unique_Paths_III();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test980() finish testing!\n");
		}
		TEST_METHOD(test1008)
		{
			solution = new Solution_1008_Construct_Binary_Search_Tree_from_Preorder_Traversal();
			Assert::AreEqual(0, solution->test());
			delete solution;
			Logger::WriteMessage("test1008() finish testing!\n");
		}
	};
}