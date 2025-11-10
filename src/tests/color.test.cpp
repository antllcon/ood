#include "graphics/adapter.h"

#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// Проверка: линия по умолчанию рисуется черным цветом
TEST(ClassRendererToPainterAdapter, DefaultColorIsBlack)
{
	std::ostringstream output;
	{
		ClassRendererToPainterAdapter adapter(output);
		adapter.LineTo(1, 1);
	}
	std::string result = output.str();
	EXPECT_NE(result.find(R"(<color r="0.00" g="0.00" b="0.00" a="1.00"/>)"), std::string::npos);
}

// Проверка: SetColor(Red)
TEST(ClassRendererToPainterAdapter, SetColorPureRed)
{
	std::ostringstream output;
	{
		ClassRendererToPainterAdapter adapter(output);
		adapter.SetColor(0xFF0000);
		adapter.LineTo(1, 1);
	}
	std::string result = output.str();
	EXPECT_NE(result.find(R"(<color r="1.00" g="0.00" b="0.00" a="1.00"/>)"), std::string::npos);
}

// Проверка: SetColor(Green)
TEST(ClassRendererToPainterAdapter, SetColorPureGreen)
{
	std::ostringstream output;
	{
		ClassRendererToPainterAdapter adapter(output);
		adapter.SetColor(0x00FF00);
		adapter.LineTo(1, 1);
	}
	std::string result = output.str();
	EXPECT_NE(result.find(R"(<color r="0.00" g="1.00" b="0.00" a="1.00"/>)"), std::string::npos);
}

// Проверка: SetColor(Blue)
TEST(ClassRendererToPainterAdapter, SetColorPureBlue)
{
	std::ostringstream output;
	{
		ClassRendererToPainterAdapter adapter(output);
		adapter.SetColor(0x0000FF);
		adapter.LineTo(1, 1);
	}
	std::string result = output.str();
	EXPECT_NE(result.find(R"(<color r="0.00" g="0.00" b="1.00" a="1.00"/>)"), std::string::npos);
}

// Проверка: SetColor(Grey) 0x80 = 128 -> 128/255.0 = 0.50
TEST(ClassRendererToPainterAdapter, SetColorGrey)
{
	std::ostringstream output;
	{
		ClassRendererToPainterAdapter adapter(output);
		adapter.SetColor(0x808080);
		adapter.LineTo(1, 1);
	}
	std::string result = output.str();
	EXPECT_NE(result.find(R"(<color r="0.50" g="0.50" b="0.50" a="1.00"/>)"), std::string::npos);
}

// Проверка: цвет сохраняется между вызовами LineTo
TEST(ClassRendererToPainterAdapter, ColorPersistsBetweenLines)
{
	std::ostringstream output;
	{
		ClassRendererToPainterAdapter adapter(output);
		adapter.SetColor(0xFF0000); // Красный
		adapter.MoveTo(0, 0);
		adapter.LineTo(1, 1);
		adapter.LineTo(2, 2); // Эта линия тоже должна быть красной
	}

	std::string result = output.str();
	std::string redTag = R"(<color r="1.00" g="0.00" b="0.00" a="1.00"/>)";

	// Ищем первое вхождение
	size_t firstTag = result.find(redTag);
	EXPECT_NE(firstTag, std::string::npos);

	// Ищем второе вхождение, начиная ПОСЛЕ первого
	size_t secondTag = result.find(redTag, firstTag + 1);
	EXPECT_NE(secondTag, std::string::npos);
}

// Проверка: цвет корректно меняется
TEST(ClassRendererToPainterAdapter, ColorChangesCorrectly)
{
	std::ostringstream output;
	{
		ClassRendererToPainterAdapter adapter(output);

		adapter.SetColor(0xFF0000); // Красный
		adapter.LineTo(1, 1);

		adapter.SetColor(0x0000FF); // Синий
		adapter.LineTo(2, 2);
	}

	std::string result = output.str();
	std::string redTag = R"(<color r="1.00" g="0.00" b="0.00" a="1.00"/>)";
	std::string blueTag = R"(<color r="0.00" g="0.00" b="1.00" a="1.00"/>)";

	EXPECT_NE(result.find(redTag), std::string::npos);
	EXPECT_NE(result.find(blueTag), std::string::npos);
}
