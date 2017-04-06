#include "Shader.h"
#include <D3DX11.h>

Shader::Shader(ID3D11Device* device) :
	m_InputLayout(nullptr),
	m_VertexShader(nullptr),
	m_PixelShader(nullptr)
{
	HRESULT hr;
	ID3D10Blob* vertexShaderBuffer = nullptr;
	ID3D10Blob* pixelShaderBuffer = nullptr;
	ID3D10Blob* errorMessage = nullptr;

	UINT shaderCompileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderCompileFlags |= D3D10_SHADER_DEBUG;
#endif

	hr = D3DX11CompileFromFileA("./VertexShader.hlsl", nullptr, NULL, "main", "vs_5_0", 
		shaderCompileFlags, NULL, nullptr, &vertexShaderBuffer, &errorMessage, nullptr);
	if (FAILED(hr))
	{
		if (errorMessage)
		{
			throw static_cast<char *>(errorMessage->GetBufferPointer());
		}
		else
		{
			throw "No VertexShader File";
		}
	}

	hr = D3DX11CompileFromFileA("./PixelShader.hlsl", nullptr, NULL, "main", "ps_5_0",
		shaderCompileFlags, NULL, nullptr, &pixelShaderBuffer, &errorMessage, nullptr);
	if (FAILED(hr))
	{
		if (errorMessage)
		{
			throw static_cast<char *>(errorMessage->GetBufferPointer());
		}
		else
		{
			throw "No PixelShader File";
		}
	}

	D3D11_INPUT_ELEMENT_DESC ied[2];
	ied[0].AlignedByteOffset = 0;
	ied[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	ied[0].InputSlot = 0;
	ied[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	ied[0].InstanceDataStepRate = 0;
	ied[0].SemanticIndex = 0;
	ied[0].SemanticName = "POSITION";

	ied[1].AlignedByteOffset = 16;
	ied[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	ied[1].InputSlot = 0;
	ied[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	ied[1].InstanceDataStepRate = 0;
	ied[1].SemanticIndex = 0;
	ied[1].SemanticName = "TEXCOORD";

	hr = device->CreateInputLayout(ied, 2, vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), &m_InputLayout);
	if (FAILED(hr))
	{
		throw "Create InputLayout Failed";
	}

	hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), NULL, &m_VertexShader);
	if (FAILED(hr))
	{
		throw "Create VertexShader Failed";
	}

	hr = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &m_PixelShader);
	if (FAILED(hr))
	{
		throw "Create PixelShader Failed";
	}

	if (vertexShaderBuffer)
	{
		vertexShaderBuffer->Release();
		vertexShaderBuffer = nullptr;
	}
	if (pixelShaderBuffer)
	{
		pixelShaderBuffer->Release();
		pixelShaderBuffer = nullptr;
	}
	if (errorMessage)
	{
		errorMessage->Release();
		errorMessage = nullptr;
	}
}

Shader::~Shader()
{
	if (m_InputLayout)
	{
		m_InputLayout->Release();
		m_InputLayout = nullptr;
	}
	if (m_VertexShader)
	{
		m_VertexShader->Release();
		m_VertexShader = nullptr;
	}
	if (m_PixelShader)
	{
		m_PixelShader->Release();
		m_PixelShader = nullptr;
	}
}

void Shader::bind(ID3D11DeviceContext* deviceContext)
{
	deviceContext->IASetInputLayout(m_InputLayout);

	deviceContext->VSSetShader(m_VertexShader, nullptr, 0);

	deviceContext->PSSetShader(m_PixelShader, nullptr, 0);
}