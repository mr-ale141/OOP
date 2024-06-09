#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#define private public // для строки 88 проверка увеличения емкости в 2 раза
#include "../myArray/CMyArray.h"

/*
	+ Возможность добавления элемента в конец массива
	+ Возможность получения количества элементов, содержащихся в массиве
	+ Возможность осуществления индексированного доступа к элементам массива
		при помощи оператора «[]». В случае, если индекс элемента выходит за
		пределы массива, должно выбрасываться исключение std::out_of_range
	+ Возможность изменения длины массива при помощи метода Resize(). В случае,
		если новая длина массива больше прежней, вставляемые в конец массива
		элементы должны инициализироваться значением по умолчанию для типа T.
	+ Возможность опустошения массива (удаления всех его элементов) при помощи
		метода Clear.
	+ Конструктор копирования и оператор присваивания
	+ Массив должен динамически увеличивать свой размер при добавлении элементов.
		Вместимость буфера для хранения элементов должна удваиваться.
	+ Конструктор перемещения и перемещающий оператор присваивания
	+ Методы begin() и end(), а также rbegin() и rend(), возвращающие итераторы
		для перебора элементов вектора в прямом и обратном порядке.
*/


TEST_CASE("Push back")
{
	GIVEN("Empty array")
	{
		CMyArray<std::string> arr;
		REQUIRE(arr.Size() == 0);

		WHEN("Push")
		{
			arr.PushBack("Hello");
			REQUIRE(arr.Size() == 1);

			THEN("Push again and Compare value")
			{
				arr.PushBack("World!");
				REQUIRE(arr.Size() == 2);

				REQUIRE(arr[0] == "Hello");
				REQUIRE(arr[1] == "World!");
				REQUIRE_THROWS_AS(arr[2], std::out_of_range);
			}
		}
	}
}

TEST_CASE("Resize and Clear")
{
	GIVEN("Empty array")
	{
		CMyArray<std::string> arr;
		REQUIRE(arr.Size() == 0);

		WHEN("Push")
		{
			arr.PushBack("Hello");
			REQUIRE(arr.Size() == 1);

			arr.PushBack("World!");
			REQUIRE(arr.Size() == 2);

			THEN("Resize and Compare value")
			{
				arr.Resize(4);

				REQUIRE(arr[0] == "Hello");
				REQUIRE(arr[1] == "World!");
				REQUIRE(arr[2] == "");
				REQUIRE(arr[3] == "");
				REQUIRE_THROWS_AS(arr[4], std::out_of_range);

				arr.PushBack("word");

				REQUIRE(arr[0] == "Hello");
				REQUIRE(arr[1] == "World!");
				REQUIRE(arr[2] == "");
				REQUIRE(arr[3] == "");
				REQUIRE(arr[4] == "word");
				REQUIRE_THROWS_AS(arr[5], std::out_of_range);
				REQUIRE(arr.m_capacity == 8);

				arr.Resize(1);

				REQUIRE(arr[0] == "Hello");
				REQUIRE_THROWS_AS(arr[1], std::out_of_range);

				arr.Resize(5);

				REQUIRE(arr[0] == "Hello");
				REQUIRE(arr[1] == "");
				REQUIRE(arr[2] == "");
				REQUIRE(arr[3] == "");
				REQUIRE(arr[4] == "");
				REQUIRE_THROWS_AS(arr[5], std::out_of_range);

				arr.Clear();
				REQUIRE(arr.Size() == 0);
				REQUIRE_THROWS_AS(arr[0], std::out_of_range);
			}
		}
	}
}

TEST_CASE("Copy constructor and =")
{
	GIVEN("Empty array")
	{
		CMyArray<std::string> arr;
		REQUIRE(arr.Size() == 0);

		WHEN("Push")
		{
			arr.PushBack("Hello");
			REQUIRE(arr.Size() == 1);

			arr.PushBack("World!");
			REQUIRE(arr.Size() == 2);

			REQUIRE(arr[0] == "Hello");
			REQUIRE(arr[1] == "World!");
			REQUIRE_THROWS_AS(arr[2], std::out_of_range);

			THEN("Create with copy constructor and Compare value")
			{
				CMyArray<std::string> arr2(arr);

				REQUIRE(arr2.Size() == 2);

				REQUIRE(arr2[0] == "Hello");
				REQUIRE(arr2[1] == "World!");
				REQUIRE_THROWS_AS(arr2[2], std::out_of_range);
				
				REQUIRE(arr.Size() == 2);

				REQUIRE(arr[0] == "Hello");
				REQUIRE(arr[1] == "World!");
				REQUIRE_THROWS_AS(arr[2], std::out_of_range);

				CMyArray<std::string> arr3;
				arr3 = arr;

				REQUIRE(arr3.Size() == 2);

				REQUIRE(arr3[0] == "Hello");
				REQUIRE(arr3[1] == "World!");
				REQUIRE_THROWS_AS(arr3[2], std::out_of_range);

				REQUIRE(arr.Size() == 2);

				REQUIRE(arr[0] == "Hello");
				REQUIRE(arr[1] == "World!");
				REQUIRE_THROWS_AS(arr[2], std::out_of_range);
			}
		}
	}
}

TEST_CASE("Move constructor and =")
{
	GIVEN("Empty array")
	{
		CMyArray<std::string> arr;
		REQUIRE(arr.Size() == 0);

		WHEN("Push")
		{
			arr.PushBack("Hello");
			REQUIRE(arr.Size() == 1);

			arr.PushBack("World!");
			REQUIRE(arr.Size() == 2);

			REQUIRE(arr[0] == "Hello");
			REQUIRE(arr[1] == "World!");
			REQUIRE_THROWS_AS(arr[2], std::out_of_range);

			THEN("Move and Compare value")
			{
				CMyArray<std::string> arr2(std::move(arr));

				REQUIRE(arr2.Size() == 2);

				REQUIRE(arr2[0] == "Hello");
				REQUIRE(arr2[1] == "World!");
				REQUIRE_THROWS_AS(arr2[2], std::out_of_range);

				REQUIRE(arr.Size() == 0);
				REQUIRE(arr.m_data == nullptr);
				REQUIRE_THROWS_AS(arr[0], std::out_of_range);
			}

			THEN("Move and Compare value")
			{
				CMyArray<std::string> arr3;
				arr3 = std::move(arr);

				REQUIRE(arr3.Size() == 2);

				REQUIRE(arr3[0] == "Hello");
				REQUIRE(arr3[1] == "World!");
				REQUIRE_THROWS_AS(arr3[2], std::out_of_range);

				REQUIRE(arr.Size() == 0);
				REQUIRE(arr.m_data == nullptr);
				REQUIRE_THROWS_AS(arr[0], std::out_of_range);
			}
		}
	}
}

TEST_CASE("Push back with move")
{
	GIVEN("Empty array")
	{
		CMyArray<std::string> arr;
		REQUIRE(arr.Size() == 0);

		WHEN("Push with move")
		{
			std::string str("Hello");
			arr.PushBack(std::move(str));
			REQUIRE(arr.Size() == 1);

			THEN("Push again and Compare value")
			{
				std::string str2("World!");

				arr.PushBack(std::move(str2));
				REQUIRE(arr.Size() == 2);

				REQUIRE(arr[0] == "Hello");
				REQUIRE(arr[1] == "World!");
				REQUIRE_THROWS_AS(arr[2], std::out_of_range);

				REQUIRE(str == "");
				REQUIRE(str2 == "");
			}
		}
	}
}

TEST_CASE("Iterators")
{
	GIVEN("Empty array")
	{
		CMyArray<std::string> arr;
		REQUIRE(arr.Size() == 0);

		WHEN("Push")
		{
			arr.PushBack("Hello");
			REQUIRE(arr.Size() == 1);

			arr.PushBack("World!");
			REQUIRE(arr.Size() == 2);

			REQUIRE(arr[0] == "Hello");
			REQUIRE(arr[1] == "World!");
			REQUIRE_THROWS_AS(arr[2], std::out_of_range);

			THEN("Get iterators and Compare value")
			{
				auto itStart = arr.begin();
				REQUIRE(*itStart == "Hello");

				REQUIRE(*(itStart++) == "Hello");
				REQUIRE(*itStart == "World!");

				auto itEnd = arr.end();
				--itEnd;
				REQUIRE(*itEnd == "World!");
			}

			THEN("Get reverse iterators and Compare value")
			{
				auto itStart = arr.rbegin();
				REQUIRE(*itStart == "World!");

				REQUIRE(*(itStart++) == "World!");
				REQUIRE(*itStart == "Hello");

				auto itEnd = arr.rend();
				--itEnd;
				REQUIRE(*itEnd == "Hello");
			}

			THEN("Print with range base for")
			{
				std::stringstream ss;
				for (auto& item : arr)
				{
					ss << item;
				}
				std::string outString(ss.str());
				REQUIRE(outString == "HelloWorld!");
			}
		}
	}
}
