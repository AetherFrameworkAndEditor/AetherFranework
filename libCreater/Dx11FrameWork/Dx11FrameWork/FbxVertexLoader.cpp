#include "FbxVertexLoader.h"
#include "FbxUtility.h"
using namespace aetherFunction;
using namespace aetherClass;
FbxVertexLoader::FbxVertexLoader()
{
}


FbxVertexLoader::~FbxVertexLoader()
{
}

void FbxVertexLoader::GetVertex(FbxMeshNode* meshNode, FbxMesh* mesh){

	this->GetVertexPosition(meshNode, mesh);
	this->GetVertexUV(meshNode, mesh);
	return;
}

// ’¸“_À•WˆÊ’u‚È‚Ç‚ÌŽæ“¾
void FbxVertexLoader::GetVertexPosition(FbxMeshNode* meshNode, FbxMesh* mesh){

	// Get the all number of vertex

	// ƒ|ƒŠƒSƒ“”‚ÌŽæ“¾
	const int kPolygonCount = mesh->GetPolygonCount();
	unsigned long indexNumber = 0;

	meshNode->_vertex = new VertexType[kPolygonCount * 3]();
	meshNode->_index = new unsigned long[kPolygonCount * 3]();
	for (int i = 0; i < kPolygonCount; ++i){
		const int kPolygonSize = mesh->GetPolygonSize(i);
		for (int size = 0; size < kPolygonSize; ++size){

			const int index = mesh->GetPolygonVertex(i, size);
			meshNode->_indexBuffer.push_back(indexNumber);
			FbxVector4 vertexPosition = mesh->GetControlPointAt(index);
			FbxVector4 vertexNormal;
			mesh->GetPolygonVertexNormal(i, size, vertexNormal);

			VertexType vertex;
			vertex._position = FbxVector4ToVector3(vertexPosition);
			vertex._normal = FbxVector4ToVector3(vertexNormal);

			meshNode->_vertex[indexNumber] = vertex;
			meshNode->_index[indexNumber] = indexNumber;

			meshNode->_vertexBuffer.push_back(vertex);
			indexNumber += 1;
		}
	}

	return;
}


// UVŽæ“¾ŠÖ”
void FbxVertexLoader::GetVertexUV(FbxMeshNode* meshNode, FbxMesh* mesh){

	FbxStringList	uvsetName;
	mesh->GetUVSetNames(uvsetName);
	int numUVSet = uvsetName.GetCount();
	int lPolygonCount = mesh->GetPolygonCount();
	bool unmapped = false;
	std::vector<Vector2> buf;
	int indexNumber = 0;
	for (int uv = 0; uv<numUVSet; uv++)
	{

		for (int i = 0; i<lPolygonCount; i++)
		{
			int lPolygonsize = mesh->GetPolygonSize(i);

			for (int pol = 0; pol<lPolygonsize; pol++)
			{
				FbxString name = uvsetName.GetStringAt(uv);
				FbxVector2 texCoord;
				Vector2 pushValue;
				mesh->GetPolygonVertexUV(i, pol, name, texCoord, unmapped);
				pushValue._x = (float)((abs(texCoord[0])));
				// ã‰º‚ð”½“]‚³‚¹‚ÄŽæ“¾
				pushValue._y = (float)(abs(1.0f-texCoord[1]));

				meshNode->_vertex[indexNumber]._uv = pushValue;
				meshNode->_vertexBuffer[indexNumber]._uv = pushValue;
				indexNumber += 1;
			}
		}
	}
	return;
}