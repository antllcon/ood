#include "graphics/adapter.h"
#include "graphics/graphics_lib.h"
#include "graphics/modern_graphics_lib.h"
#include "graphics/shape_drawing_lib.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace modern_graphics_lib;

// Проверка: при создании адаптера вызывается BeginDraw()
TEST(RendererToPainterAdapter, BeginDrawCalledOnConstruction)
{
    std::ostringstream output;
    {
        ModernGraphicsRenderer renderer(output);
        RendererToPainterAdapter adapter(renderer);
    }

    std::string result = output.str();
    EXPECT_NE(result.find("<draw>"), std::string::npos);
}

// Проверка: при уничтожении адаптера вызывается EndDraw()
TEST(RendererToPainterAdapter, EndDrawCalledOnDestruction)
{
    std::ostringstream output;
    {
        ModernGraphicsRenderer renderer(output);
        RendererToPainterAdapter adapter(renderer);
    }

    std::string result = output.str();
    EXPECT_NE(result.find("</draw>"), std::string::npos);
}

// Проверка: MoveTo() НЕ выводит линию
TEST(RendererToPainterAdapter, MoveToDoesNotProduceOutput)
{
    std::ostringstream output;
    ModernGraphicsRenderer renderer(output);
    {
        RendererToPainterAdapter adapter(renderer);
        adapter.MoveTo(10, 20);
    }
    std::string result = output.str();

    EXPECT_EQ(result.find("line"), std::string::npos);
}

// Проверка: LineTo() выводит корректную линию с последней MoveTo позиции
TEST(RendererToPainterAdapter, LineToDrawsLineCorrectly)
{
    std::ostringstream output;
    ModernGraphicsRenderer renderer(output);
    {
        RendererToPainterAdapter adapter(renderer);
        adapter.MoveTo(10, 20);
        adapter.LineTo(30, 40);
    }

    std::string result = output.str();
    EXPECT_NE(result.find(R"(fromX="10")"), std::string::npos);
    EXPECT_NE(result.find(R"(fromY="20")"), std::string::npos);
    EXPECT_NE(result.find(R"(toX="30")"), std::string::npos);
    EXPECT_NE(result.find(R"(toY="40")"), std::string::npos);
}

// Проверка: последовательные LineTo используют предыдущую конечную точку как старт
TEST(RendererToPainterAdapter, MultipleLineSegmentsUseLastPosition)
{
    std::ostringstream output;
    ModernGraphicsRenderer renderer(output);
    {
        RendererToPainterAdapter adapter(renderer);
        adapter.MoveTo(0, 0);
        adapter.LineTo(5, 5);
        adapter.LineTo(10, 10);
    }

    std::string result = output.str();
    EXPECT_NE(result.find(R"(fromX="5")"), std::string::npos);
    EXPECT_NE(result.find(R"(fromY="5")"), std::string::npos);
    EXPECT_NE(result.find(R"(toX="10")"), std::string::npos);
    EXPECT_NE(result.find(R"(toY="10")"), std::string::npos);
}

// Проверка: адаптер корректно используется через CanvasPainter
TEST(RendererToPainterAdapter, WorksWithCanvasPainterAndShapes)
{
	std::ostringstream output;
	ModernGraphicsRenderer renderer(output);
	RendererToPainterAdapter adapter(renderer);
	shape_drawing_lib::CanvasPainter painter(adapter);

	shape_drawing_lib::Triangle t({0, 0}, {10, 0}, {10, 10});
	painter.Draw(t);

	std::string result = output.str();
	EXPECT_NE(result.find("<line"), std::string::npos);
	EXPECT_NE(result.find(R"(fromX="0")"), std::string::npos);
	EXPECT_NE(result.find(R"(toX="10")"), std::string::npos);
}
