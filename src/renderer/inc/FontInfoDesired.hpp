/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- FontInfo.hpp

Abstract:
- This serves as the structure defining font information.

- FontInfoDesired - derived from FontInfoBase.  It also contains
  a desired size { X, Y }, to be supplied to the GDI's LOGFONT
  structure.  Unlike FontInfo, both desired X and Y can be zero.

Author(s):
- Michael Niksa (MiNiksa) 17-Nov-2015
--*/

#pragma once

#include "FontInfoBase.hpp"
#include "IFontDefaultList.hpp"
#include "CSSLengthPercentage.h"

struct FontInfoDesired : FontInfoBase
{
    FontInfoDesired(
        std::wstring faceName,
        const unsigned char family,
        const unsigned int weight,
        const unsigned int codePage,
        CellSizeInDIP cellSizeInDIP,
        float fontSizeInPt);

    FontInfoDesired(
        const wchar_t* faceName,
        const unsigned char family,
        const unsigned int weight,
        const unsigned int codePage,
        til::size cellSizeInDIP);

    void SetEnableBuiltinGlyphs(bool builtinGlyphs) noexcept;
    void SetEnableColorGlyphs(bool colorGlyphs) noexcept;

    const CellSizeInDIP& GetEngineSize() const noexcept;
    float GetFontSize() const noexcept;
    const CSSLengthPercentage& GetCellWidth() const noexcept;
    const CSSLengthPercentage& GetCellHeight() const noexcept;
    bool GetEnableBuiltinGlyphs() const noexcept;
    bool GetEnableColorGlyphs() const noexcept;

    bool IsTrueTypeFont() const noexcept;
    void FillLegacyNameBuffer(wchar_t (&buffer)[LF_FACESIZE]) const noexcept;
    bool IsDefaultRasterFont() const noexcept;

    static void s_SetFontDefaultList(_In_ Microsoft::Console::Render::IFontDefaultList* const pFontDefaultList) noexcept;

private:
    void _validate();

    CellSizeInDIP _cellSizeInDIP;
    CSSLengthPercentage _cellWidth;
    CSSLengthPercentage _cellHeight;
    float _fontSizeInPt = 0;
    bool _builtinGlyphs = false;
    bool _colorGlyphs = true;
};
