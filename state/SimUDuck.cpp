#include "lib/Duck/DecoyDuck.h"
#include "lib/Duck/MallardDuck.h"
#include "lib/Duck/ModelDuck.h"
#include "lib/DuckFunctions.h"

#include <cstdlib>

int main()
{
	MallardDuck mallardDuck;
	// DropDuckFromFloor(mallardDuck, 5);
	//
	// mallardDuck.SetFlyBehavior(std::make_unique<FlyNoWay>());
	// DropDuckFromFloor(mallardDuck, 3);
	// PlayWithDuck(mallardDuck);

	mallardDuck.Fly();
	mallardDuck.Fly();
	mallardDuck.Fly();
	mallardDuck.Fly();

	return EXIT_SUCCESS;
}