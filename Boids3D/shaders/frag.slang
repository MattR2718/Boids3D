struct VertexOutput {
    float3 colour;
    float4 sv_position : SV_Position;
};

[shader("fragment")]
float4 fragMain(VertexOutput inVert) : SV_Target{
    return float4(inVert.colour, 1.0);
}