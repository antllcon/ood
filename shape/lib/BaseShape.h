#ifndef BASESHAPE_H
#define BASESHAPE_H

#include "IShape.h"
#include <vector>

class BaseShape : public IShape
{
public:
	std::string GetId() const override;
	Color GetColor() const override;
	void SetColor(Color color) override;

protected:
	BaseShape(const std::string& id, Color color);
	static void AssertIsValidParams(const std::vector<std::string>& params, size_t count);
	void ChangeParameters(IShape* source) override;

	std::string m_id;
	Color m_color;
};

#endif // BASESHAPE_H