/***************************************************************************
                          timer.h  -  description
                             -------------------
    begin                : lun sep 22 2003
    copyright            : (C) 2003 by Lynn Hazan
    email                : lynn.hazan@myrealbox.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// Elapsed-time helpers used for debug timing output. std::chrono replaces
// gettimeofday(), which does not exist on Windows.
#include <chrono>

static std::chrono::steady_clock::time_point tv0;

inline void RestartTimer()
{
    tv0 = std::chrono::steady_clock::now();
}

// Seconds elapsed since the last RestartTimer() call.
inline float Timer()
{
    return std::chrono::duration<float>(std::chrono::steady_clock::now() - tv0).count();
}

