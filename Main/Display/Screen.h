#ifndef _SCREEN_H
#define _SCREEN_H

#include <Display/font8x8.h>
#include <Display/VideoSettings.h>
#include "m4vgalib/rasterizer.h"

using namespace vga;

namespace Display
{

class Screen: public Rasterizer
{
private:
    void PrintChar(char c, uint16_t color);
    void PrintCharAt(uint8_t x, uint8_t y, unsigned char c, uint16_t color);
    void DrawChar(const uint8_t *f, uint16_t x, uint16_t y, uint8_t c);
    void Bitmap(uint16_t x, uint16_t y, const unsigned char *bmp,
                uint16_t i, uint8_t width, uint8_t lines);
    void CursorNext();
    void InvertColor();

	uint16_t _startLine;
    uint16_t _horizontalBorder;
    uint8_t _verticalBorder;
    bool _isCursorVisible;

protected:
	virtual uint8_t* GetPixelPointer(uint16_t line);
	virtual uint8_t* GetPixelPointer(uint16_t line, uint8_t character);

    uint16_t _hResolution;
    uint16_t _hResolutionNoBorder;
    uint16_t _vResolution;

    uint8_t* _font = (uint8_t*)font8x8;
    uint16_t _attribute = 0x3F10; // white on blue

public:
    uint8_t _cursor_x = 0;
    uint8_t _cursor_y = 0;
    uint16_t _pixelCount;
    uint16_t _attributeCount;
    volatile uint32_t _frames = 0;

    VideoSettings Settings;
    Screen(VideoSettings settings);
	Screen(VideoSettings settings, uint16_t startLine, uint16_t height);

	void Clear();
	void SetFont(const uint8_t* font);
	void SetAttribute(uint16_t attribute);
	void SetCursorPosition(uint8_t x, uint8_t y);
	void ShowCursor();
	void HideCursor();

	void Print(const char* str);
	void PrintAt(uint8_t x, uint8_t y, const char* str);
	void PrintAlignRight(uint8_t y, const char *str);
	void PrintAlignCenter(uint8_t y, const char *str);

	RasterInfo rasterize(unsigned cycles_per_pixel, unsigned line_number,
			Pixel *target) override;

	virtual ~Screen() = default;
};

}

#endif
