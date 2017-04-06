cbuffer MatrixBuffer
{
	float4x4 worldOrtho;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	output.position = mul(input.position, worldOrtho);
	output.tex = input.tex;
	return output;
}