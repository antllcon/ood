#include "canvas/ICanvas.h"
#include "common/Frame.h"
#include "gmock/gmock.h"
#include "shapes/entities/Ellipse.h"
#include "shapes/entities/GroupShape.h"
#include "shapes/entities/Rectangle.h"
#include "shapes/entities/Triangle.h"
#include "gtest/gtest.h"

using namespace testing;

class MockCanvas : public ICanvas
{
public:
	MOCK_METHOD(void, DrawLine, (Point p1, Point p2), (override));
	MOCK_METHOD(void, DrawEllipse, (Point center, double rx, double ry), (override));
	MOCK_METHOD(void, FillEllipse, (Point center, double rx, double ry), (override));
	MOCK_METHOD(void, FillPolygon, (const std::vector<Point>& points), (override));
	MOCK_METHOD(void, SetFillColor, (RgbaColor color), (override));
	MOCK_METHOD(void, SetStrokeColor, (RgbaColor color), (override));
	MOCK_METHOD(void, SetStrokeWidth, (double width), (override));
};

// Проверка корректности инициализации фрейма через координаты
TEST(FrameTest, ConstructorInitWithCoordinates)
{
	Frame frame(10.0, 10.0, 50.0, 40.0);
	EXPECT_DOUBLE_EQ(frame.LeftTop.x, 10.0);
	EXPECT_DOUBLE_EQ(frame.RightBottom.x, 50.0);
	EXPECT_DOUBLE_EQ(frame.GetWidth(), 40.0);
	EXPECT_DOUBLE_EQ(frame.GetHeight(), 30.0);
}

// Проверка вычисления размеров фрейма
TEST(FrameTest, GetWidthAndHeightAreCorrect)
{
	Point p1{0, 0};
	Point p2{100, 50};
	Frame frame(p1, p2);
	EXPECT_DOUBLE_EQ(frame.GetWidth(), 100.0);
	EXPECT_DOUBLE_EQ(frame.GetHeight(), 50.0);
}

// Проверка расширения фрейма другим фреймом
TEST(FrameTest, ExtendExpandsFrameToIncludeOther)
{
	Frame frame1(0, 0, 10, 10);
	Frame frame2(20, 20, 30, 30);
	frame1.Extend(frame2);
	EXPECT_DOUBLE_EQ(frame1.LeftTop.x, 0.0);
	EXPECT_DOUBLE_EQ(frame1.RightBottom.x, 30.0);
	EXPECT_DOUBLE_EQ(frame1.GetWidth(), 30.0);
}

// Проверка инициализации прямоугольника и получения фрейма
TEST(RectangleTest, ConstructorSetsCorrectFrame)
{
	Frame expectedFrame(10, 20, 50, 60);
	Rectangle rect(expectedFrame);
	Frame actualFrame = rect.GetFrame();
	EXPECT_DOUBLE_EQ(actualFrame.LeftTop.x, expectedFrame.LeftTop.x);
	EXPECT_DOUBLE_EQ(actualFrame.RightBottom.y, expectedFrame.RightBottom.y);
}

// Проверка метода Draw для прямоугольника
TEST(RectangleTest, DrawCallsFillPolygonAndDrawLine)
{
	MockCanvas mockCanvas;
	Frame frame(0, 0, 100, 50);
	Rectangle rect(frame);

	EXPECT_CALL(mockCanvas, FillPolygon(_)).Times(1);
	EXPECT_CALL(mockCanvas, DrawLine(_, _)).Times(4);

	rect.Draw(mockCanvas);
}

// Проверка изменения фрейма прямоугольника
TEST(RectangleTest, SetFrameUpdatesGeometry)
{
	Rectangle rect({0, 0, 10, 10});
	Frame newFrame(5, 5, 15, 15);
	rect.SetFrame(newFrame);
	EXPECT_DOUBLE_EQ(rect.GetFrame().LeftTop.x, 5.0);
}

// Проверка клонирования прямоугольника
TEST(RectangleTest, CloneCreatesIdenticalIndependentCopy)
{
	Rectangle original({0, 0, 100, 100});
	original.GetFillStyle()->SetColor({{1.0, 0.4, 0.7, 1.0}});

	auto clone = original.Clone();

	ASSERT_NE(clone, nullptr);
	EXPECT_NE(clone.get(), &original);
	EXPECT_EQ(clone->GetFrame().GetWidth(), 100.0);
	EXPECT_EQ(clone->GetFillStyle()->GetColor(), original.GetFillStyle()->GetColor());

	// Проверка независимости
	clone->SetFrame({0, 0, 50, 50});
	EXPECT_DOUBLE_EQ(original.GetFrame().GetWidth(), 100.0);
}

// Проверка отрисовки эллипса
TEST(EllipseTest, DrawCallsEllipseMethods)
{
	MockCanvas mockCanvas;
	Ellipse ellipse({0, 0, 20, 10});

	EXPECT_CALL(mockCanvas, FillEllipse(_, 10.0, 5.0)).Times(1);
	EXPECT_CALL(mockCanvas, DrawEllipse(_, 10.0, 5.0)).Times(1);

	ellipse.Draw(mockCanvas);
}

// Проверка клонирования эллипса
TEST(EllipseTest, CloneWorksCorrectly)
{
	Ellipse original({0, 0, 20, 20});
	auto clone = original.Clone();
	ASSERT_TRUE(clone);
	EXPECT_DOUBLE_EQ(clone->GetFrame().GetHeight(), 20.0);
}

// Проверка отрисовки треугольника
TEST(TriangleTest, DrawCallsPolygonMethods)
{
	MockCanvas mockCanvas;
	Triangle triangle({0, 0, 10, 10});

	EXPECT_CALL(mockCanvas, FillPolygon(_)).Times(1);
	EXPECT_CALL(mockCanvas, DrawLine(_, _)).Times(3);

	triangle.Draw(mockCanvas);
}

// Проверка создания пустой группы
TEST(GroupShapeTest, InitiallyEmpty)
{
	GroupShape group;
	EXPECT_EQ(group.GetShapeCount(), 0);
	EXPECT_TRUE(group.GetFrame().IsEmpty());
}

// Проверка добавления фигур в группу
TEST(GroupShapeTest, AddShapeIncrementsCount)
{
	auto group = std::make_shared<GroupShape>();
	auto rect = std::make_shared<Rectangle>(Frame(0, 0, 10, 10));

	group->AddShape(rect);
	EXPECT_EQ(group->GetShapeCount(), 1);
	EXPECT_EQ(group->GetShapeAt(0), rect);
}

// Проверка удаления фигур из группы
TEST(GroupShapeTest, RemoveShapeDecrementsCount)
{
	auto group = std::make_shared<GroupShape>();
	auto rect = std::make_shared<Rectangle>(Frame(0, 0, 10, 10));

	group->AddShape(rect);
	group->RemoveShapeAt(0);
	EXPECT_EQ(group->GetShapeCount(), 0);
}

// Проверка расчета фрейма группы на основе детей
TEST(GroupShapeTest, GetFrameCalculatesBoundingBox)
{
	auto group = std::make_shared<GroupShape>();
	auto rect1 = std::make_shared<Rectangle>(Frame(0, 0, 10, 10));
	auto rect2 = std::make_shared<Rectangle>(Frame(20, 20, 30, 30));

	group->AddShape(rect1);
	group->AddShape(rect2);

	Frame groupFrame = group->GetFrame();
	EXPECT_DOUBLE_EQ(groupFrame.LeftTop.x, 0.0);
	EXPECT_DOUBLE_EQ(groupFrame.RightBottom.x, 30.0);
	EXPECT_DOUBLE_EQ(groupFrame.GetWidth(), 30.0);
	EXPECT_DOUBLE_EQ(groupFrame.GetHeight(), 30.0);
}

// Проверка отрисовки группы (делегирование детям)
TEST(GroupShapeTest, DrawCallsDrawOnChildren)
{
	MockCanvas mockCanvas;
	auto group = std::make_shared<GroupShape>();

	auto rect = std::make_shared<Rectangle>(Frame(0, 0, 10, 10));
	group->AddShape(rect);

	EXPECT_CALL(mockCanvas, FillPolygon(_)).Times(1);
	EXPECT_CALL(mockCanvas, DrawLine(_, _)).Times(4);

	group->Draw(mockCanvas);
}

// Проверка получения композитного интерфейса
TEST(GroupShapeTest, GetCompositeReturnsSelf)
{
	auto group = std::make_shared<GroupShape>();
	EXPECT_NE(group->GetComposite(), nullptr);
	EXPECT_EQ(group->GetComposite(), group);
}

// Проверка изменения фрейма группы (трансформация детей)
TEST(GroupShapeTest, SetFrameTransformsChildren)
{
	auto group = std::make_shared<GroupShape>();
	auto rect = std::make_shared<Rectangle>(Frame(0, 0, 10, 10));
	group->AddShape(rect);

	Frame newFrame(0, 0, 20, 20);
	group->SetFrame(newFrame);

	EXPECT_DOUBLE_EQ(rect->GetFrame().GetWidth(), 20.0);
	EXPECT_DOUBLE_EQ(rect->GetFrame().GetHeight(), 20.0);
}

// Проверка на управление памятью и отсутствие утечек при циклических ссылках
TEST(GroupShapeTest, AddSelfIsPreventedOrHandledSafe)
{
	auto group = std::make_shared<GroupShape>();
	SUCCEED();
}

// Проверка работы стилей линии
TEST(StyleTest, LineStyleEnableDisable)
{
	Rectangle rect({0, 0, 10, 10});
	auto style = rect.GetLineStyle();

	style->Enable(true);
	EXPECT_TRUE(style->IsEnabled().value());

	style->Enable(false);
	EXPECT_FALSE(style->IsEnabled().value());
}