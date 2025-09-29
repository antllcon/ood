#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "Picture.h"
#include <string>
#include <vector>

class CommandProcessor
{
public:
	explicit CommandProcessor(Picture& picture, ICanvas* canvas = nullptr);
	void SetCanvas(ICanvas* canvas);
	void ProcessCommand(const std::string& command) const;

private:
	void ProcessAddShape(const std::vector<std::string>& tokens) const;
	void ProcessMoveShape(const std::vector<std::string>& tokens) const;
	void ProcessMovePicture(const std::vector<std::string>& tokens) const;
	void ProcessDeleteShape(const std::vector<std::string>& tokens) const;
	void ProcessList() const;
	void ProcessChangeColor(const std::vector<std::string>& tokens) const;
	void ProcessChangeShape(const std::vector<std::string>& tokens) const;
	void ProcessDrawShape(const std::vector<std::string>& tokens) const;
	void ProcessDrawPicture() const;

	static std::vector<std::string> Tokenize(const std::string& command);

	Picture& m_picture;
	ICanvas* m_canvas;
};

#endif // COMMANDPROCESSOR_H