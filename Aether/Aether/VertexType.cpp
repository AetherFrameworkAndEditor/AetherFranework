#include "VertexType.h"
#include<stddef.h>
using namespace aetherClass;

VertexType::VertexType()
{
	_position = NULL;
	_uv = NULL;
	_normal = NULL;
}


VertexType::~VertexType()
{
	_position = NULL;
	_uv = NULL;
	_normal = NULL;
}
