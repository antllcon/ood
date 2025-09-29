#ifndef SHAPECREATOR_H
#define SHAPECREATOR_H

#include "IShape.h"
#include <memory>
#include <string>
#include <vector>

class ShapeCreator
{
public:
	static std::unique_ptr<IShape> CreateShape(
		const std::string& id,
		const std::string& colorStr,
		const std::string& type,
		const std::vector<std::string>& params);

	static void ChangeShapeType(
		IShape* shape,
		const std::string& newType,
		const std::vector<std::string>& params);
};

#endif // SHAPECREATOR_H