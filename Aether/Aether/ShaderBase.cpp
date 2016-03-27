#include "ShaderBase.h"
#include<fstream>
#include<assert.h>
#include"ModelUtility.h"

using namespace aetherClass;
using namespace aetherFunction;

	ShaderBase::ShaderBase()
	{
		m_vertexShader = nullptr;
		m_pixelShader = nullptr;
		m_geometryShader = nullptr;
		m_computeShader = nullptr;
		m_hullShader = nullptr;
		m_domainShader = nullptr;
		m_matrixBuffer = nullptr;

		m_layout = nullptr;
	}

	bool ShaderBase::Initialize(const ShaderDesc& shaderDesc, shaderType type){

		bool result;

		result = InitializeConstantBuffer();
		if (!result){
			return false;
		}
		result = InitializeShaderBuffer(shaderDesc, type);
		if (!result){
			return false;
		}
		result = InitializeShader();
		if (!result){
			return false;
		}


		return true;
	}

	bool ShaderBase::InitializeShaderBuffer(const ShaderDesc& shaderDesc, shaderType type){
	
		HRESULT hresult;
		ID3D10Blob* errorMessage;
		ID3D10Blob *vertexShaderBuffer, *pixelShaderBuffer, *hullShaderBuffer, *domainShaderBuffer, *geometryShaderBuffer, *computeShaderBuffer;
		unsigned int numElements;

		errorMessage = 0;
		vertexShaderBuffer = 0;
		pixelShaderBuffer = 0;
		hullShaderBuffer = 0;
		domainShaderBuffer = 0;
		geometryShaderBuffer = 0;
		computeShaderBuffer = 0;


		if (type & ShaderType::eVertex){
			hresult = D3DX11CompileFromFile(shaderDesc._vertex._srcFile.c_str(),
				shaderDesc._vertex._pDefines, shaderDesc._vertex._pInclude,
				shaderDesc._vertex._entryName.c_str(), shaderDesc._vertex._shaderModel.c_str(),
				shaderDesc._vertex._shaderCompileFlags, shaderDesc._vertex._effectCompileFlags,
				shaderDesc._vertex._pPump, &vertexShaderBuffer, &errorMessage, NULL);
			if (FAILED(hresult)){
				if (errorMessage){
					OutputShaderErrorMessage(errorMessage, shaderDesc._vertex._srcFile.c_str());
				}
				else{
					MessageBox(NULL, shaderDesc._vertex._srcFile.c_str(), L"Missing Shader File", MB_OK);
				}
				return false;
			}

			hresult = GetDirect3DManager()->GetDevice()->CreateVertexShader(
				vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
			if (FAILED(hresult)){
				assert(!"Could not Create Vertex Shader Buffer");
				return false;
			}
		}
		if (type & ShaderType::ePixel){
			hresult = D3DX11CompileFromFile(shaderDesc._pixel._srcFile.c_str(),
				shaderDesc._pixel._pDefines, shaderDesc._pixel._pInclude,
				shaderDesc._pixel._entryName.c_str(), shaderDesc._pixel._shaderModel.c_str(),
				shaderDesc._pixel._shaderCompileFlags, shaderDesc._pixel._effectCompileFlags,
				shaderDesc._pixel._pPump, &pixelShaderBuffer, &errorMessage, NULL);
			if (FAILED(hresult)){
				if (errorMessage){
					OutputShaderErrorMessage(errorMessage, shaderDesc._pixel._srcFile.c_str());
				}
				else{
					MessageBox(NULL, shaderDesc._pixel._srcFile.c_str(), L"Missing Shader File", MB_OK);
				}
				return false;
			}

			hresult = GetDirect3DManager()->GetDevice()->CreatePixelShader(
				pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
			if (FAILED(hresult)){
				assert(!"Could not Create Pixel Shader Buffer");
				return false;
			}
		}
		if (type & ShaderType::eGeometry){
			hresult = D3DX11CompileFromFile(shaderDesc._geometry._srcFile.c_str(),
				shaderDesc._geometry._pDefines, shaderDesc._geometry._pInclude,
				shaderDesc._geometry._entryName.c_str(), shaderDesc._geometry._shaderModel.c_str(),
				shaderDesc._geometry._shaderCompileFlags, shaderDesc._geometry._effectCompileFlags,
				shaderDesc._geometry._pPump, &geometryShaderBuffer, &errorMessage, NULL);
			if (FAILED(hresult)){
				if (errorMessage){
					OutputShaderErrorMessage(errorMessage, shaderDesc._geometry._srcFile.c_str());
				}
				else{
					MessageBox(NULL, shaderDesc._geometry._srcFile.c_str(), L"Missing Shader File", MB_OK);
				}
				return false;
			}

			hresult = GetDirect3DManager()->GetDevice()->CreateGeometryShader(
				geometryShaderBuffer->GetBufferPointer(), geometryShaderBuffer->GetBufferSize(), NULL, &m_geometryShader);
			if (FAILED(hresult)){
				assert(!"Could not Create Geometry Shader Buffer");
				return false;
			}
		}
		if (type & ShaderType::eHull){
			hresult = D3DX11CompileFromFile(shaderDesc._hull._srcFile.c_str(),
				shaderDesc._hull._pDefines, shaderDesc._hull._pInclude,
				shaderDesc._hull._entryName.c_str(), shaderDesc._hull._shaderModel.c_str(),
				shaderDesc._hull._shaderCompileFlags, shaderDesc._hull._effectCompileFlags,
				shaderDesc._hull._pPump, &hullShaderBuffer, &errorMessage, NULL);
			if (FAILED(hresult)){
				if (errorMessage){
					OutputShaderErrorMessage(errorMessage, shaderDesc._hull._srcFile.c_str());
				}
				else{
					MessageBox(NULL, shaderDesc._hull._srcFile.c_str(), L"Missing Shader File", MB_OK);
				}
				return false;
			}

			hresult = GetDirect3DManager()->GetDevice()->CreateHullShader(
				hullShaderBuffer->GetBufferPointer(), hullShaderBuffer->GetBufferSize(), NULL, &m_hullShader);
			if (FAILED(hresult)){
				assert(!"Could not Create Hull Shader Buffer");
				return false;
			}
		}
		if (type & ShaderType::eDomain){
			hresult = D3DX11CompileFromFile(shaderDesc._domain._srcFile.c_str(),
				shaderDesc._domain._pDefines, shaderDesc._domain._pInclude,
				shaderDesc._domain._entryName.c_str(), shaderDesc._domain._shaderModel.c_str(),
				shaderDesc._domain._shaderCompileFlags, shaderDesc._domain._effectCompileFlags,
				shaderDesc._domain._pPump, &domainShaderBuffer, &errorMessage, NULL);
			if (FAILED(hresult)){
				if (errorMessage){
					OutputShaderErrorMessage(errorMessage, shaderDesc._domain._srcFile.c_str());
				}
				else{
					MessageBox(NULL, shaderDesc._domain._srcFile.c_str(), L"Missing Shader File", MB_OK);
				}
				return false;
			}

			hresult = GetDirect3DManager()->GetDevice()->CreateDomainShader(
				domainShaderBuffer->GetBufferPointer(), domainShaderBuffer->GetBufferSize(), NULL, &m_domainShader);
			if (FAILED(hresult)){
				assert(!"Could not Create Domain Shader Buffer");
				return false;
			}
		}
		if (type & ShaderType::eCompute){
			hresult = D3DX11CompileFromFile(shaderDesc._compute._srcFile.c_str(),
				shaderDesc._compute._pDefines, shaderDesc._compute._pInclude,
				shaderDesc._compute._entryName.c_str(), shaderDesc._compute._shaderModel.c_str(),
				shaderDesc._compute._shaderCompileFlags, shaderDesc._compute._effectCompileFlags,
				shaderDesc._compute._pPump, &computeShaderBuffer, &errorMessage, NULL);
			if (FAILED(hresult)){
				if (errorMessage){
					OutputShaderErrorMessage(errorMessage, shaderDesc._compute._srcFile.c_str());
				}
				else{
					MessageBox(NULL, shaderDesc._compute._srcFile.c_str(), L"Missing Shader File", MB_OK);
				}
				return false;
			}

			hresult = GetDirect3DManager()->GetDevice()->CreateComputeShader(
				computeShaderBuffer->GetBufferPointer(), computeShaderBuffer->GetBufferSize(), NULL, &m_computeShader);
			if (FAILED(hresult)){
				assert(!"Could not Create Compute Shader Buffer");
				return false;
			}
		}

		D3D11_INPUT_ELEMENT_DESC polygonLayout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		// Get a count of the elements in the layout.
		numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

		// Create the vertex input layout.
		hresult = GetDirect3DManager()->GetDevice()->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(), &m_layout);
		if (FAILED(hresult))
		{
			return false;
		}
		
		if (vertexShaderBuffer){
			vertexShaderBuffer->Release();
			vertexShaderBuffer = nullptr;
		}
		if (pixelShaderBuffer){
			pixelShaderBuffer->Release();
			pixelShaderBuffer = nullptr;
		}
		if (geometryShaderBuffer){
			geometryShaderBuffer->Release();
			geometryShaderBuffer = nullptr;
		}
		if (hullShaderBuffer){
			hullShaderBuffer->Release();
			hullShaderBuffer = nullptr;
		}
		if (domainShaderBuffer){
			domainShaderBuffer->Release();
			domainShaderBuffer = nullptr;
		}
		if (computeShaderBuffer){
			computeShaderBuffer->Release();
			computeShaderBuffer = nullptr;
		}

		return true;
	}
	
	bool ShaderBase::InitializeConstantBuffer(){
		HRESULT result;

		result = GetDirect3DManager()->GetDevice()->CreateBuffer(&GetConstantBufferDesc(sizeof(MatrixBuffer)), NULL, &m_matrixBuffer);
		if (FAILED(result)){
			assert(!"Could not Create Buffer");
			return false;
		}




		return true;
	}

	void ShaderBase::OutputShaderErrorMessage(ID3D10Blob* errorMessage, std::wstring shaderFileName){
		char* compileErrors;
		unsigned long bufferSize;
		std::ofstream fout;

		compileErrors = (char*)(errorMessage->GetBufferPointer());

		bufferSize = errorMessage->GetBufferSize();

		fout.open("shader-error.txt");

		for (int i = 0; i < bufferSize; i++)
		{
			fout << compileErrors[i];
		}

		fout.close();

		errorMessage->Release();
		errorMessage = nullptr;
		MessageBox(NULL, L"Error compiling shader. Check shader-error.txt for message", shaderFileName.c_str(), MB_OK);

		return;
	}

	void ShaderBase::Finalize(){
		FinalizeShader();

		if (m_matrixBuffer){
			m_matrixBuffer->Release();
			m_matrixBuffer = nullptr;
		}

		if (m_layout){
			m_layout->Release();
			m_layout = nullptr;
		}

		if (m_pixelShader){
			m_pixelShader->Release();
			m_pixelShader = nullptr;
		}
		if (m_vertexShader){
			m_vertexShader->Release();
			m_vertexShader = nullptr;
		}
		if (m_geometryShader){
			m_geometryShader->Release();
			m_geometryShader = nullptr;
		}
		if (m_hullShader){
			m_hullShader->Release();
			m_hullShader = nullptr;
		}
		if (m_domainShader){
			m_domainShader->Release();
			m_domainShader = nullptr;
		}
		if (m_computeShader){
			m_computeShader->Release();
			m_computeShader = nullptr;
		}


	}


	bool ShaderBase::Render(int indexCount, Matrix4x4 worldMatrix, Matrix4x4 viewMatrix,
		Matrix4x4 projectionMatrix)
	{
		bool result;

		// Set the shader parameters that it will use for rendering.
		result = SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix);
		if (!result){
			return false;
		}
		result = SetConstantBuffer();
		if (!result){
			return false;
		}

		// Now render the prepared buffers with the shader.
		RenderShader(GetDirect3DManager()->GetDeviceContext(), indexCount);


		return true;
	}

	void ShaderBase::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount){
		// Set the vertex input layout.
		deviceContext->IASetInputLayout(m_layout);

		if (m_vertexShader){
			deviceContext->VSSetShader(m_vertexShader, NULL, 0);
		}
		if (m_pixelShader){
			deviceContext->PSSetShader(m_pixelShader, NULL, 0);
		}
		if (m_geometryShader){
			deviceContext->GSSetShader(m_geometryShader, NULL, 0);
		}
		if (m_hullShader){
			deviceContext->HSSetShader(m_hullShader, NULL, 0);
		}
		if (m_domainShader){
			deviceContext->DSSetShader(m_domainShader, NULL, 0);
		}
		if (m_computeShader){
			deviceContext->CSSetShader(m_computeShader, NULL, 0);
		}

		// Render.
		deviceContext->DrawIndexed(indexCount, 0, 0);
	}
	
	bool ShaderBase::SetShaderParameters(Matrix4x4 world, Matrix4x4 view, Matrix4x4 projection){
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ID3D11DeviceContext* deviceContext = GetDirect3DManager()->GetDeviceContext();

		MatrixBuffer* dataPtr;
		unsigned int bufferNumber;


		// Transpose the matrices to prepare them for the shader.
		world.Transpose();
		view.Transpose();
		projection.Transpose();


		result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result)){
			return false;
		}

		dataPtr = (MatrixBuffer*)mappedResource.pData;

		// Copy the matrices into the constant buffer.
		dataPtr->_world = world;
		dataPtr->_view = view;
		dataPtr->_projection = projection;

		deviceContext->Unmap(m_matrixBuffer, 0);

		bufferNumber = 0;

		deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);


		return true;
	}
