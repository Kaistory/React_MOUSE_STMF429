/******************************************************************************
* Copyright (c) 2018(-2025) STMicroelectronics.
* All rights reserved.
*
* This file is part of the TouchGFX 4.25.0 distribution.
*
* This software is licensed under terms that can be found in the LICENSE file in
* the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
*******************************************************************************/

/**
 * @file touchgfx/lcd/LCD8ABGR2222DebugPrinter.hpp
 *
 * Declares the touchgfx::LCD8ABGR2222DebugPrinter class.
 */
#ifndef TOUCHGFX_LCD8ABGR2222DEBUGPRINTER_HPP
#define TOUCHGFX_LCD8ABGR2222DEBUGPRINTER_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/lcd/LCD8DebugPrinterBase.hpp>

namespace touchgfx
{
/**
 * The class LCD8ABGR2222DebugPrinter implements the DebugPrinter interface for printing debug messages
 * on top of 8bit framebuffer.
 *
 * @see DebugPrinter
 */
class LCD8ABGR2222DebugPrinter : public LCD8DebugPrinterBase
{
public:
    virtual void draw(const Rect& rect) const;
};

} // namespace touchgfx

#endif // TOUCHGFX_LCD8ABGR2222DEBUGPRINTER_HPP
