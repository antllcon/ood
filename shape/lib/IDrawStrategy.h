#ifndef IDRAWSTRATEGY_H
#define IDRAWSTRATEGY_H

class IDrawStrategy
{
public:
    virtual ~IDrawStrategy() = default;
    virtual void Draw(ICanvas* canvas, const IShape* shape) const = 0;
};

#endif // IDRAWSTRATEGY_H