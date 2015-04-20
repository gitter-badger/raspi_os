#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

typedef struct {
  uint8_t red,
    green,
    blue;
} color_t;

typedef struct {
  volatile uint32_t m_uWidth,
    m_uHeight,
    m_uVirtualWidth,
    m_uVirtualHeight,
    m_uPitch,
    m_uDepth,
    m_uXOffset,
    m_uYOffset,
    m_pBuffer,
    m_uSize;
} frame_buffer_t;

extern color_t MakeColor(uint8_t red, uint8_t green, uint8_t blue);
extern void ClearFrameBuffer(color_t color);
extern void SetBackgroundColor(color_t color);
extern void SetForegroundColor(color_t color);

extern frame_buffer_t* GetFrameBuffer(void);
extern void FrameBufferInit(void);

#endif