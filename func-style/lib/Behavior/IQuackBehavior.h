#ifndef IQUAKBEHAVIOR_H
#define IQUAKBEHAVIOR_H

#include <functional>
#include <iostream>

using IQuackBehavior = std::function<void()>;

inline IQuackBehavior CreateQuack()
{
	return []() { std::cout << "Quack Quack!" << std::endl; };
}

inline IQuackBehavior CreateSqueak()
{
	return []() { std::cout << "Squeak!" << std::endl; };
}

inline IQuackBehavior CreateMuteQuack()
{
	return []() { /* Молчание (квест-рум) */ };
}

#endif // IQUAKBEHAVIOR_H