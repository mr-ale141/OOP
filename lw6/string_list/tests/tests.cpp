#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../string_list/CStringList.h"
#include <iostream>
#include <algorithm>

TEST_CASE("Create list")
{
	GIVEN("Empty")
	{
		CStringList list;

		REQUIRE(list.Empty());

		WHEN("Get size")
		{
			size_t size = list.Size();
			THEN("Compare value")
			{
				REQUIRE(size == 0);
			}
		}

		WHEN("Push front some string")
		{
			std::string str1("hello");
			list.PushFront(str1);
			
			THEN("Compare front")
			{
				REQUIRE(list.Front() == str1);
			}

			THEN("Compare back")
			{
				REQUIRE(list.Back() == str1);
			}

			THEN("Push again front and compare")
			{
				std::string str2("world");
				list.PushFront(str2);
				REQUIRE(list.Front() == str2);
				REQUIRE(list.Back() == str1);
			}

			THEN("Push back and compare")
			{
				std::string str2("world");
				list.PushBack(str2);
				REQUIRE(list.Front() == str1);
				REQUIRE(list.Back() == str2);
			}
		}

		WHEN("Push back some string")
		{
			std::string str1("hello");
			list.PushBack(str1);
			
			THEN("Compare front")
			{
				REQUIRE(list.Front() == str1);
			}

			THEN("Compare back")
			{
				REQUIRE(list.Back() == str1);
			}

			THEN("Push again front and compare")
			{
				std::string str2("world");
				list.PushFront(str2);
				REQUIRE(list.Front() == str2);
				REQUIRE(list.Back() == str1);
			}

			THEN("Push back and compare")
			{
				std::string str2("world");
				list.PushBack(str2);
				REQUIRE(list.Front() == str1);
				REQUIRE(list.Back() == str2);
			}
		}
	}

	GIVEN("List with 2 items")
	{
		CStringList list;
		std::string str1("hello");
		std::string str2("world");
		list.PushBack(str1);
		list.PushBack(str2);

		WHEN("Create new list with copy constructor")
		{
			CStringList newList(list);

			THEN("Compare value")
			{
				REQUIRE(newList.Size() == 2);
				REQUIRE(newList.Front() == str1);
				REQUIRE(newList.Back() == str2);
			}
		}

		WHEN("Create new list with move constructor")
		{
			CStringList newList(std::move(list));

			THEN("Compare value")
			{
				REQUIRE(newList.Size() == 2);
				REQUIRE(newList.Front() == str1);
				REQUIRE(newList.Back() == str2);

				REQUIRE(list.Size() == 0);
				REQUIRE_THROWS(list.Front());
				REQUIRE_THROWS(list.Back());
			}
		}
	}
}

TEST_CASE("Clear list")
{
	GIVEN("Empty")
	{
		CStringList list;

		WHEN("Set items")
		{
			std::string str1("hello");
			std::string str2("world");
			std::string str3("!");
			list.PushBack(str1);
			list.PushBack(str2);
			list.PushBack(str3);

			REQUIRE(list.Size() == 3);

			THEN("Compare value")
			{
				list.Clear();
				REQUIRE(list.Size() == 0);
				REQUIRE_THROWS(list.Front());
				REQUIRE_THROWS(list.Back());
			}
		}

	}
}

TEST_CASE("Insert in list with iterator")
{
	GIVEN("Empty")
	{
		CStringList list;

		WHEN("Set items")
		{
			std::string str1("hello");
			std::string str2("world");
			std::string str3("!");
			list.PushBack(str1);
			list.PushBack(str2);
			list.PushBack(str3);

			REQUIRE(list.Size() == 3);

			THEN("Insert and compare value")
			{
				auto it = list.begin();
				++it;
				list.Insert(it, "guys");

				REQUIRE(list.Size() == 3);

				it = list.begin();

				REQUIRE(*it == "hello");
				REQUIRE(*(++it) == "guys");
				REQUIRE(*(++it) == "!");
			}
		}

	}
}

TEST_CASE("Erase in list with iterator")
{
	GIVEN("Empty")
	{
		CStringList list;

		WHEN("Set items")
		{
			std::string str1("hello");
			std::string str2("world");
			std::string str3("!");
			list.PushBack(str1);
			list.PushBack(str2);
			list.PushBack(str3);

			REQUIRE(list.Size() == 3);

			THEN("Insert and compare value")
			{
				auto it = list.begin();
				++it;
				list.Erase(it);

				REQUIRE(list.Size() == 2);

				it = list.begin();

				REQUIRE(*it == "hello");
				REQUIRE(*(++it) == "!");
			}
		}

	}
}

TEST_CASE("Range base for")
{
	GIVEN("Empty")
	{
		CStringList list;

		WHEN("Set items")
		{
			std::string str1("hello");
			std::string str2("hello");
			std::string str3("hello");
			list.PushBack(str1);
			list.PushBack(str2);
			list.PushBack(str3);

			REQUIRE(list.Size() == 3);

			THEN("Insert and compare value")
			{
				for (auto& str : list)
				{
					REQUIRE(str == "hello");
				}
			}
		}

	}
}

TEST_CASE("Binary '-' with iter")
{
	GIVEN("Empty")
	{
		CStringList list;

		WHEN("Set items")
		{
			std::string str1("a");
			std::string str2("b");
			std::string str3("c");
			list.PushBack(str1);
			list.PushBack(str2);
			list.PushBack(str3);

			REQUIRE(list.Size() == 3);

			THEN("Insert and compare value")
			{
				auto it1 = list.begin();
				auto it2 = list.begin() + 2;
				REQUIRE((it2 - it1) == 2);
			}
		}

	}
}

/*
TEST_CASE("Sort")
{
	GIVEN("Empty")
	{
		CStringList list;

		WHEN("Set items")
		{
			std::string str1("b");
			std::string str2("a");
			std::string str3("c");
			list.PushBack(str1);
			list.PushBack(str2);
			list.PushBack(str3);

			REQUIRE(list.Size() == 3);

			std::sort(list.begin(), list.end());

			auto it = list.begin();

			REQUIRE(*it == "a");
			REQUIRE(*(++it) == "b");
			REQUIRE(*(++it) == "c");
		}

	}
}
*/