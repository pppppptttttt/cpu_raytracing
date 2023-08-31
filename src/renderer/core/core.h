#pragma once
#include "../../def.h"

class core
{
public:
    virtual void Init( uint32_t Width, uint32_t Height ) {}
    virtual void Close() {}
    virtual void PutPixel( uint32_t x, uint32_t y, const mth::vec3<u_char>& color ) {}
    virtual void Render() {}
    virtual void MainLoop() {}
    virtual ~core() = default;
};