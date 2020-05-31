#pragma once

#include "MainPage.g.h"

namespace winrt::KabeDonCppWinRT::implementation
{
    struct Area
    {
        int X;
        int Y;
        int Width;
        int Height;
        hstring Image;
        hstring Sound;
        int Score;
    };
};
