cbuffer CBuf
{
    matrix transform;
};

float4 main( float2 pos : POSITION ) : SV_POSITION
{
    return mul(float4(pos, 1.0f, 1.0f), transform);
}