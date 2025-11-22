#include "composite/Common.h"
#include "composite/Ellipse.h"
#include "composite/Rectangle.h"
#include "composite/Slide.h"
#include "composite/SvgCanvas.h"
#include "composite/Triangle.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#pragma once

class Triangle;
class Slide;
class Ellipse;
int main()
{
	try
	{
std::string filename;
	std::cout << "Enter output filename (e.g., drawing.svg): ";
	if (!(std::cin >> filename) || filename.empty())
	{
		return 1;
	}

	std::ofstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file for writing." << std::endl;
		return 1;
	}

	// Цвета
	constexpr RgbaColor orange{ 255, 165, 0, 1 };
	constexpr RgbaColor pink{ 255, 182, 193, 1 };
	constexpr RgbaColor green{ 0, 128, 0, 1 };
	constexpr RgbaColor black{ 0, 0, 0, 1 };
	constexpr RgbaColor white{ 255, 255, 255, 1 };

	auto slide = std::make_unique<Slide>(800, 600);
	slide->SetBackgroundColor(white);

	// Head
	auto head = std::make_shared<Ellipse>(Point{ 400, 250 }, 100, 80);
	head->SetFillStyle(true, orange);
	head->SetLineStyle(true, black, 2);
	slide->InsertShape(head);

	// Ears
	auto leftEar = std::make_shared<Triangle>(Point{ 320, 200 }, Point{ 360, 120 }, Point{ 400, 180 });
	leftEar->SetFillStyle(true, pink);
	leftEar->SetLineStyle(true, black, 2);
	slide->InsertShape(leftEar);

	auto rightEar = std::make_shared<Triangle>(Point{ 480, 200 }, Point{ 440, 120 }, Point{ 400, 180 });
	rightEar->SetFillStyle(true, pink);
	rightEar->SetLineStyle(true, black, 2);
	slide->InsertShape(rightEar);

	// Eyes
	auto leftEye = std::make_shared<Ellipse>(Point{ 360, 230 }, 15, 20);
	leftEye->SetFillStyle(true, green);
	leftEye->SetLineStyle(true, black, 1);
	slide->InsertShape(leftEye);

	auto rightEye = std::make_shared<Ellipse>(Point{ 440, 230 }, 15, 20);
	rightEye->SetFillStyle(true, green);
	rightEye->SetLineStyle(true, black, 1);
	slide->InsertShape(rightEye);

	// Nose
	auto nose = std::make_shared<Triangle>(Point{ 390, 270 }, Point{ 410, 270 }, Point{ 400, 290 });
	nose->SetFillStyle(true, pink);
	nose->SetLineStyle(true, black, 1);
	slide->InsertShape(nose);

	// Body
	auto body = std::make_shared<Rectangle>(350, 330, 450, 500);
	body->SetFillStyle(true, orange);
	body->SetLineStyle(true, black, 2);
	slide->InsertShape(body);

	// Whiskers helper lambda
	auto createWhisker = [&](double x1, double y1, double x2, double y2) {
		auto w = std::make_shared<Rectangle>(x1, y1, x2, y2);
		w->SetFillStyle(false, black);
		w->SetLineStyle(true, black, 1);
		slide->InsertShape(w);
	};

	createWhisker(340, 270, 380, 272);
	createWhisker(340, 280, 380, 282);
	createWhisker(420, 270, 460, 272);
	createWhisker(420, 280, 460, 282);

	{
		SvgCanvas canvas(file);
		slide->Draw(canvas);
	}

	std::cout << "Drawing saved to " << filename << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}
