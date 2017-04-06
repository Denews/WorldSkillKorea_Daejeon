struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
};

SamplerState state;
Texture2D image;

float4 main(PixelInputType input) : SV_TARGET
{
	return image.Sample(state, input.tex);
}