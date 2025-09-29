#ifndef PICTURE_H
#define PICTURE_H

#include "ICanvas.h"
#include "IShape.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

class Picture
{
public:
	IShape* GetShape(const std::string& id) const;
	void AddShape(std::unique_ptr<IShape> shape);
	void RemoveShape(const std::string& id);
	void MoveShape(const std::string& id, double dx, double dy) const;
	void MoveAll(double dx, double dy) const;
	void Draw(ICanvas* canvas) const;
	void DrawShape(const std::string& id, ICanvas* canvas) const;
	std::vector<std::string> ListShapes() const;

private:
	std::vector<std::unique_ptr<IShape>> m_shapes;
	std::unordered_map<std::string, IShape*> m_lookup;
};

#endif // PICTURE_H