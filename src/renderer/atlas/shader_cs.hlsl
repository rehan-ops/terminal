// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "dwrite.hlsl"
#include "shader_common.hlsl"

cbuffer ConstBuffer : register(b0)
{
    float4 backgroundColor;
    float2 backgroundCellSize;
    float2 backgroundCellCount;
    float4 gammaRatios;
    float enhancedContrast;
    float underlineWidth;
    float doubleUnderlineWidth;
    float curlyLineHalfHeight;
    float shadedGlyphDotSize;
}

struct Cell
{
    uint background;
    uint foreground;
    uint2 glyph;
};

Texture2D<float4> glyphs : register(t0);
StructuredBuffer<Cell> cells : register(t1);
RWTexture2D<float4> output : register(u0);

[numthreads(8, 8, 1)]
void main(uint2 dispatchThreadId : SV_DispatchThreadID)
{
    uint2 cellIndex = dispatchThreadId / uint2(backgroundCellSize);
    uint2 cellOffset = dispatchThreadId % uint2(backgroundCellSize);
    Cell cell = cells.Load(cellIndex.y * uint(backgroundCellCount.x) + cellIndex.x);

    float4 fg = decodeRGBA(cell.foreground);
    float4 bg = decodeRGBA(cell.background);

    if (cell.glyph.x != -1)
    {
        float4 glyph = glyphs[cell.glyph + cellOffset];
        bg = alphaBlendPremultiplied(bg, fg * glyph);
    }

    output[dispatchThreadId] = bg;
}
