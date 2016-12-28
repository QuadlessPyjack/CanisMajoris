// ComparativeTesting.cpp : Defines the entry point for the console application.
//

#include<iostream>

#include<Renderer/CoreUtils/Primitives/Vertex.h>

struct VertexStruct
{
	float x;
	float y;
	float z;

	float v[3];
};

void VertexMemoryFootprint();

int main(int argc, char** argv)
{
	VertexMemoryFootprint();

	getchar();

	return 0;
}

void VertexMemoryFootprint()
{
	VertexStruct mockStruct;
	mockStruct.x = 123.456f;
	mockStruct.y = 123.456f;
	mockStruct.z = 123.456f;
	float vect[3] = { 123.456f, 123.456f, 123.456f };
	mockStruct.v[0] = vect[0];
	mockStruct.v[1] = vect[1];
	mockStruct.v[2] = vect[2];

	Core::Renderer::CoreUtils::Vertex mockEngineVertex = Core::Renderer::CoreUtils::Vertex(123.456f, 123.456f, 123.456f);
	VertexStruct VertexStructArray[5000];

	VertexStruct vertexStructArray[5000];
	Core::Renderer::CoreUtils::Vertex VertexArray[5000];

	for (auto i = 0; i < 5000; ++i)
	{
		vertexStructArray[i] = mockStruct;
		VertexArray[i] = mockEngineVertex;
	}

	std::cout << "Sizeof Vertex Struct: " << sizeof(mockStruct) << std::endl;
	std::cout << "Sizeof Vertex Class: " << sizeof(mockEngineVertex) << std::endl;

	std::cout << "Sizeof Vector3: " << sizeof(mockEngineVertex.Location()) << std::endl;
	std::cout << "Sizeof x,y,z: " << 16 << std::endl;

	std::cout << "Sizeof Struct Array: " << sizeof(vertexStructArray) << std::endl;
	std::cout << "Sizeof Class Array: " << sizeof(VertexArray) << std::endl;
}