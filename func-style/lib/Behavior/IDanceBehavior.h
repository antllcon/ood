#ifndef IDANCEBEHAVIOR_H
#define IDANCEBEHAVIOR_H

#include <functional>
#include <iostream>

using IDanceBehavior = std::function<void()>;

inline IDanceBehavior CreateDanceWaltz()
{
	return []() { std::cout << "I'm dancing waltz!" << std::endl; };
}

inline IDanceBehavior CreateDanceMinuet()
{
	return []() { std::cout << "I'm dancing minuet!" << std::endl; };
}

inline IDanceBehavior CreateDanceNoWay()
{
	return []() { /* Женщина, не танцую... */ };
}
#endif // IDANCEBEHAVIOR_H