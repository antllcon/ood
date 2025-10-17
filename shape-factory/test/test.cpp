#include "Canvas.h"
#include "IShapeFactory.h"
#include "ShapeFactory.h"
#include "Designer.h"

#include <gmock/gmock.h>

using ::testing::_;

class MockCanvas final : public ICanvas
{
public:
	MOCK_METHOD(void, SetColor, (Color color), (override));
	MOCK_METHOD(void, DrawLine, (Point from, Point to), (override));
	MOCK_METHOD(void, DrawEllipse, (Point center, int hr, int vr), (override));
};

class MockShapeFactory final : public IShapeFactory
{
public:
	MOCK_METHOD(std::unique_ptr<Shape>, CreateShape, (const std::string& descr), (override));
};

class MockShape : public Shape {
public:
	// Наследуем конструктор
	using Shape::Shape;
	MOCK_METHOD(void, Draw, (ICanvas& canvas), (const, override));
	MOCK_METHOD(std::unique_ptr<Shape>, Clone, (), (const, override));
};

// Тестирование фабрики
TEST(ShapeFactoryTests, CanCreateRectangle)
{
	ShapeFactory factory;
	auto shape = factory.CreateShape("rectangle red 10 20 100 120");

	ASSERT_NE(shape, nullptr);
	auto* rect = dynamic_cast<Rectangle*>(shape.get());
	ASSERT_NE(rect, nullptr);

	EXPECT_EQ(rect->GetColor(), Color::Red);
	EXPECT_EQ(rect->GetLeftTop().x, 10);
	EXPECT_EQ(rect->GetRightBottom().y, 120);
}

TEST(ShapeFactoryTests, CanCreateTriangle)
{
	ShapeFactory factory;
	auto shape = factory.CreateShape("triangle green 0 0 50 50 100 0");

	ASSERT_NE(shape, nullptr);
	auto* triangle = dynamic_cast<Triangle*>(shape.get());
	ASSERT_NE(triangle, nullptr);

	EXPECT_EQ(triangle->GetColor(), Color::Green);
	EXPECT_EQ(triangle->GetVertex2().x, 50);
}

TEST(ShapeFactoryTests, CanCreateEllipse)
{
	ShapeFactory factory;
	auto shape = factory.CreateShape("ellipse blue 100 100 30 40");

	ASSERT_NE(shape, nullptr);
	auto* ellipse = dynamic_cast<Ellipse*>(shape.get());
	ASSERT_NE(ellipse, nullptr);

	EXPECT_EQ(ellipse->GetColor(), Color::Blue);
	EXPECT_EQ(ellipse->GetCenter().x, 100);
	EXPECT_EQ(ellipse->GetHorizontalRadius(), 30);
}

TEST(ShapeFactoryTests, ReturnsNullptrForUnknownShape)
{
	ShapeFactory factory;
	auto shape = factory.CreateShape("circle red 10 20 100");
	EXPECT_EQ(shape, nullptr);
}

TEST(ShapeFactoryTests, ReturnsNullptrForBadColor)
{
	ShapeFactory factory;
	auto shape = factory.CreateShape("rectangle orange 10 20 100 120");
	EXPECT_EQ(shape, nullptr);
}

TEST(ShapeFactoryTests, ReturnsNullptrForWrongNumberOfArguments)
{
	ShapeFactory factory;
	auto shape = factory.CreateShape("triangle green 0 0 50 50");
	EXPECT_EQ(shape, nullptr);
}

// Тестирование Canvas
TEST(ShapeTests, RectangleDrawsCorrectly)
{
	Rectangle rect(Color::Red, {10, 20}, {100, 120});
	MockCanvas canvas;

	EXPECT_CALL(canvas, SetColor(Color::Red)).Times(1);
	EXPECT_CALL(canvas, DrawLine(_, _)).Times(4);

	rect.Draw(canvas);
}

TEST(ShapeTests, TriangleDrawsCorrectly)
{
	Triangle triangle(Color::Blue, {0, 0}, {50, 50}, {100, 0});
	MockCanvas canvas;

	EXPECT_CALL(canvas, SetColor(Color::Blue)).Times(1);
	EXPECT_CALL(canvas, DrawLine(_, _)).Times(3);

	triangle.Draw(canvas);
}

TEST(ShapeTests, EllipseDrawsCorrectly)
{
	Ellipse ellipse(Color::Yellow, {100, 100}, 30, 40);
	MockCanvas canvas;

	EXPECT_CALL(canvas, SetColor(Color::Yellow)).Times(1);
	EXPECT_CALL(canvas, DrawEllipse(_, _, _)).Times(1);

	ellipse.Draw(canvas);
}

// Тестирование Clone
TEST(ShapeTests, CanCloneShapes)
{
	Rectangle original(Color::Red, {10, 20}, {100, 120});
	auto clone = original.Clone();

	ASSERT_NE(clone, nullptr);
	auto* clonedRect = dynamic_cast<Rectangle*>(clone.get());
	ASSERT_NE(clonedRect, nullptr);

	ASSERT_NE(&original, clonedRect);
	EXPECT_EQ(original.GetColor(), clonedRect->GetColor());
	EXPECT_EQ(original.GetLeftTop().x, clonedRect->GetLeftTop().x);
}


TEST(DesignerTests, CreatesDraftFromStream)
{
	MockShapeFactory factory;
	Designer designer(factory);

	std::stringstream strm;
	strm << "line1\n";
	strm << "\n";
	strm << "line3\n";

	EXPECT_CALL(factory, CreateShape("line1"))
		.WillOnce(testing::Return(std::make_unique<Rectangle>(Color::Red, Point{}, Point{})));
	EXPECT_CALL(factory, CreateShape("line3"))
		.WillOnce(testing::Return(nullptr));

	auto draft = designer.CreateDraft(strm);

	ASSERT_NE(draft, nullptr);
	EXPECT_EQ(draft->GetShapeCount(), 1);
}

// Тестирование Painter
TEST(PainterTests, DrawsAllShapesFromDraft)
{
	PictureDraft draft;
	auto shape1 = std::make_unique<MockShape>(Color::Red);
	auto shape2 = std::make_unique<MockShape>(Color::Blue);

	MockShape* pShape1 = shape1.get();
	MockShape* pShape2 = shape2.get();

	draft.AddShape(std::move(shape1));
	draft.AddShape(std::move(shape2));

	Painter painter;
	MockCanvas canvas;

	EXPECT_CALL(*pShape1, Draw(_)).Times(1);
	EXPECT_CALL(*pShape2, Draw(_)).Times(1);

	painter.DrawPicture(draft, canvas);
}

TEST(PictureDraftTests, IsInitiallyEmpty)
{
	PictureDraft draft;
	EXPECT_TRUE(draft.IsEmpty());
	EXPECT_EQ(draft.GetShapeCount(), 0);
}

TEST(PictureDraftTests, CanAddAndGetShapes)
{
	PictureDraft draft;
	draft.AddShape(std::make_unique<Rectangle>(Color::Black, Point{}, Point{}));

	EXPECT_FALSE(draft.IsEmpty());
	EXPECT_EQ(draft.GetShapeCount(), 1);

	const Shape& shape = draft.GetShape(0);
	EXPECT_EQ(shape.GetColor(), Color::Black);
}

TEST(PictureDraftTests, GetShapeThrowsOnOutOfBounds)
{
	PictureDraft draft;
	EXPECT_THROW(draft.GetShape(0), std::out_of_range);
}
