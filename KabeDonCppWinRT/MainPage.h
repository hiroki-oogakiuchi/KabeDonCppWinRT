#pragma once

#include "MainPage.g.h"

namespace winrt::KabeDonCppWinRT::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        Windows::Foundation::IAsyncAction Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction Image_Tapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::TappedRoutedEventArgs const& e);
    private:
        int score = 0;
        Windows::Foundation::IAsyncAction TapAreaCheck(winrt::Windows::Foundation::Point& pos);
        Windows::Foundation::IAsyncAction PlaySound(winrt::Windows::Foundation::Uri mediaUri);
        Windows::Foundation::IAsyncActionWithProgress<int> ShowImage(winrt::Windows::Foundation::Uri imageUri);
    };
}

namespace winrt::KabeDonCppWinRT::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
