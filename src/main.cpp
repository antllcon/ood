#include "canvas/SvgCanvas.h"
#include "document/Slide.h"
#include "shapes/entities/GroupShape.h"
#include "shapes/entities/Rectangle.h"

#include <memory>

std::shared_ptr<Rectangle> MakeBlock(double x, double y, double w, double h, RgbaColor color)
{
	auto rect = std::make_shared<Rectangle>(Frame(x, y, x + w, y + h));

	rect->GetFillStyle()->SetColor(color);
	rect->GetLineStyle()->Enable(false);

	return rect;
}

std::shared_ptr<GroupShape> CreateLetterL(double x, double y, const RgbaColor& color)
{
	auto group = std::make_shared<GroupShape>();
	group->AddShape(MakeBlock(x, y, 20, 100, color));
	group->AddShape(MakeBlock(x, y + 80, 60, 20, color));
	return group;
}

std::shared_ptr<GroupShape> CreateLetterO(double x, double y, const RgbaColor& color)
{
	auto group = std::make_shared<GroupShape>();
	group->AddShape(MakeBlock(x, y, 20, 100, color));
	group->AddShape(MakeBlock(x + 40, y, 20, 100, color));
	group->AddShape(MakeBlock(x, y, 60, 20, color));
	group->AddShape(MakeBlock(x, y + 80, 60, 20, color));
	return group;
}

std::shared_ptr<GroupShape> CreateLetterV(double x, double y, const RgbaColor& color)
{
	auto group = std::make_shared<GroupShape>();
	group->AddShape(MakeBlock(x, y, 20, 70, color));
	group->AddShape(MakeBlock(x + 50, y, 20, 70, color));
	group->AddShape(MakeBlock(x + 10, y + 50, 20, 30, color));
	group->AddShape(MakeBlock(x + 40, y + 50, 20, 30, color));
	group->AddShape(MakeBlock(x + 25, y + 80, 20, 20, color));
	return group;
}

std::shared_ptr<GroupShape> CreateLetterE(double x, double y, const RgbaColor& color)
{
	auto group = std::make_shared<GroupShape>();
	group->AddShape(MakeBlock(x, y, 20, 100, color));
	group->AddShape(MakeBlock(x, y, 60, 20, color));
	group->AddShape(MakeBlock(x, y + 40, 50, 20, color));
	group->AddShape(MakeBlock(x, y + 80, 60, 20, color));
	return group;
}

std::shared_ptr<GroupShape> CreateLetterC(double x, double y, const RgbaColor& color)
{
	auto group = std::make_shared<GroupShape>();
	group->AddShape(MakeBlock(x, y, 20, 100, color));
	group->AddShape(MakeBlock(x, y, 60, 20, color));
	group->AddShape(MakeBlock(x, y + 80, 60, 20, color));
	return group;
}

std::shared_ptr<GroupShape> CreateLetterP(double x, double y, const RgbaColor& color)
{
	auto group = std::make_shared<GroupShape>();
	group->AddShape(MakeBlock(x, y, 20, 100, color));
	group->AddShape(MakeBlock(x + 40, y, 20, 60, color));
	group->AddShape(MakeBlock(x, y, 60, 20, color));
	group->AddShape(MakeBlock(x, y + 40, 60, 20, color));
	return group;
}

void RunSvgDemo()
{
	RgbaColor red = {0.9, 0.1, 0.1, 1.0};
	RgbaColor blue = {0.1, 0.3, 0.8, 1.0};
	RgbaColor heart = {1.0, 0.4, 0.7, 1.0};

	auto slide = std::make_shared<Slide>();

	auto wordLove = std::make_shared<GroupShape>();

	wordLove->AddShape(CreateLetterL(50, 50, red));
	wordLove->AddShape(CreateLetterO(130, 50, heart));
	wordLove->AddShape(CreateLetterV(210, 50, red));
	wordLove->AddShape(CreateLetterE(290, 50, red));

	auto wordCpp = std::make_shared<GroupShape>();

	wordCpp->AddShape(CreateLetterC(420, 50, blue));
	wordCpp->AddShape(CreateLetterP(500, 50, blue));
	wordCpp->AddShape(CreateLetterP(580, 50, blue));

	slide->AddShape(wordLove);
	slide->AddShape(wordCpp);

	SvgCanvas svgCanvas(700, 200);

	slide->Draw(svgCanvas);
	svgCanvas.Save("print.svg");
}

int main()
{
	try
	{
		RunSvgDemo();
	}
	catch (...)
	{
		return 1;
	}
	return 0;
}