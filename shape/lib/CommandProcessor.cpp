#include "CommandProcessor.h"
#include "ShapeCreator.h"

#include <iostream>
#include <sstream>

namespace
{
void AssertIsShapeIdExist(const IShape* shape, const std::string& id)
{
	if (!shape)
	{
		throw std::invalid_argument("Shape with id " + id + " not found");
	}
}
} // namespace

CommandProcessor::CommandProcessor(Picture& picture, ICanvas* canvas)
	: m_picture(picture)
	, m_canvas(canvas)
{
}

void CommandProcessor::SetCanvas(ICanvas* canvas)
{
	m_canvas = canvas;
}

void CommandProcessor::ProcessCommand(const std::string& command) const
{
	const auto tokens = Tokenize(command);

	if (tokens.empty())
	{
		return;
	}

	const std::string& cmd = tokens[0];

	if (cmd == "AddShape")
	{
		ProcessAddShape(tokens);
	}
	else if (cmd == "MoveShape")
	{
		ProcessMoveShape(tokens);
	}
	else if (cmd == "MovePicture")
	{
		ProcessMovePicture(tokens);
	}
	else if (cmd == "DeleteShape")
	{
		ProcessDeleteShape(tokens);
	}
	else if (cmd == "List")
	{
		ProcessList();
	}
	else if (cmd == "ChangeColor")
	{
		ProcessChangeColor(tokens);
	}
	else if (cmd == "ChangeShape")
	{
		ProcessChangeShape(tokens);
	}
	else if (cmd == "DrawShape")
	{
		ProcessDrawShape(tokens);
	}
	else if (cmd == "DrawPicture")
	{
		ProcessDrawPicture();
	}
	else
	{
		std::cout << "Unknown command" << std::endl;
	}
}

std::vector<std::string> CommandProcessor::Tokenize(const std::string& command)
{
	std::vector<std::string> tokens;
	std::istringstream inputstream(command);
	std::string token;

	while (inputstream >> token)
	{
		tokens.emplace_back(token);
	}

	return tokens;
}

void CommandProcessor::ProcessAddShape(const std::vector<std::string>& tokens) const
{
	// TODO: добавить проверку
	const std::string id = tokens[1];
	const std::string color = tokens[2];
	const std::string type = tokens[3];
	const std::vector<std::string> params(tokens.begin() + 4, tokens.end());

	auto shape = ShapeCreator::CreateShape(id, color, type, params);
	m_picture.AddShape(std::move(shape));
}

void CommandProcessor::ProcessMoveShape(const std::vector<std::string>& tokens) const
{
	if (tokens.size() != 4)
	{
		throw std::invalid_argument("MoveShape requires 3 parameters: <id> <dx> <dy>");
	}

	const std::string id = tokens[1];
	const double dx = std::stod(tokens[2]);
	const double dy = std::stod(tokens[3]);
	m_picture.MoveShape(id, dx, dy);
}

void CommandProcessor::ProcessMovePicture(const std::vector<std::string>& tokens) const
{
	if (tokens.size() != 3)
	{
		throw std::invalid_argument("MovePicture requires 2 parameters: <dx> <dy>");
	}

	const double dx = std::stod(tokens[1]);
	const double dy = std::stod(tokens[2]);
	m_picture.MoveAll(dx, dy);
}

void CommandProcessor::ProcessDeleteShape(const std::vector<std::string>& tokens) const
{
	if (tokens.size() != 2)
	{
		throw std::invalid_argument("DeleteShape requires 1 parameters: <id>");
	}

	const std::string id = tokens[1];
	m_picture.RemoveShape(id);
}

void CommandProcessor::ProcessList() const
{
	for (const std::string& shape : m_picture.ListShapes())
	{
		std::cout << shape << std::endl;
	}
}

void CommandProcessor::ProcessChangeColor(const std::vector<std::string>& tokens) const
{
	if (tokens.size() != 3)
	{
		throw std::invalid_argument("ChangeColor requires 2 parameters: <id> <color>");
	}

	const std::string& id = tokens[1];
	const std::string& colorStr = tokens[2];

	IShape* shape = m_picture.GetShape(id);
	AssertIsShapeIdExist(shape, id);

	const Color newColor = Color::FromString(colorStr);
	shape->SetColor(newColor);
}

// TODO: улучшить методом Clone()
void CommandProcessor::ProcessChangeShape(const std::vector<std::string>& tokens) const
{
	if (tokens.size() < 3)
	{
		throw std::invalid_argument("ChangeShape requires at least 3 parameters: <id> <type> <params...>");
	}

	const std::string& id = tokens[1];
	const std::string& newType = tokens[2];

	IShape* shape = m_picture.GetShape(id);
	AssertIsShapeIdExist(shape, id);

	const std::vector<std::string> params(tokens.begin() + 3, tokens.end());

	const std::string currentId = shape->GetId();
	const Color currentColor = shape->GetColor();

	const auto tempShape = ShapeCreator::CreateShape(currentId, currentColor.ToString(), newType, params);
	shape->ChangeParameters(tempShape.get());
}

void CommandProcessor::ProcessDrawShape(const std::vector<std::string>& tokens) const
{
	if (tokens.size() != 2)
	{
		throw std::invalid_argument("DrawShape requires 1 parameter: <id>");
	}

	if (!m_canvas)
	{
		throw std::runtime_error("Canvas is not set");
	}

	const std::string& id = tokens[1];
	m_picture.DrawShape(id, m_canvas);
}

void CommandProcessor::ProcessDrawPicture() const
{
	if (!m_canvas)
	{
		throw std::runtime_error("Canvas is not set");
	}

	m_picture.Draw(m_canvas);
}
