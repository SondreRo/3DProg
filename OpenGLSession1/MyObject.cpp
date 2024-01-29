#include "MyObject.h"

MyObject::MyObject()
{
	vertices.emplace_back(0, 0, 0, 1, 0, 0);
	vertices.emplace_back(1, 0, 0, 1, 0, 0);
	vertices.emplace_back(0, 0, 0, 0, 1, 0);
	vertices.emplace_back(0, 1, 0, 0, 1, 0);
	vertices.emplace_back(0, 0, 0, 0, 0, 1);
	vertices.emplace_back(0, 0, 1, 0, 0, 1);

}
