#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

#include <sstream>
#include "Area.h"
using namespace std;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::UI::Popups;
using namespace winrt::Windows::UI::Xaml::Media::Imaging;

namespace winrt::KabeDonCppWinRT::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
        image().IsTapEnabled(false);
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    Windows::Foundation::IAsyncAction MainPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        button().Visibility(Visibility::Collapsed);
        score = 0;
        PlaySound(Uri{ L"ms-appx:///Assets/Sound/start.mp3" });

        image().IsTapEnabled(true);

        apartment_context ui_thread;
        co_await 5s;
        co_await ui_thread;

        image().IsTapEnabled(false);

        PlaySound(Uri{ L"ms-appx:///Assets/Sound/finish.mp3" });

        MessageDialog md{ L"あなたの壁ドン力は" + to_hstring(score) + L"です！", L"そこまで！" };
        md.Commands().Append(UICommand{ L"Close" });
        co_await md.ShowAsync();

        button().Visibility(Visibility::Visible);
    }

    static const Area areas[] =
    {
        {396, 238, 320, 108, L"Claudia4", L"ah", -20},
        {365, 215, 380, 529, L"Claudia2", L"ah", -10},
        {276, 340, 65, 415, L"Claudia3", L"chui", 10},
        {739, 340, 65, 415, L"Claudia3", L"chui", 20},
        {271, 772, 590, 1148, L"Claudia4", L"oujougiwa", -50}
    };

    Windows::Foundation::IAsyncAction MainPage::Image_Tapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::TappedRoutedEventArgs const& e)
    {
        image().IsTapEnabled(false);
        auto pos = e.GetPosition(image());
        TapAreaCheck(pos);

        apartment_context ui_thread;
        co_await 1s;
        co_await ui_thread;

        image().IsTapEnabled(true);
        ShowImage(Uri{ L"ms-appx:///Assets/Image/Claudia1.png" });
    }

    Windows::Foundation::IAsyncAction MainPage::TapAreaCheck(winrt::Windows::Foundation::Point& pos)
    {
        auto x = pos.X / image().ActualWidth() * 1080;
        auto y = pos.Y / image().ActualHeight() * 1920;

        for (Area area : areas)
        {
            if (area.X < x && x < (double)area.X + (double)area.Width && area.Y < y && y < (double)area.Y + (double)area.Height)
            {
                Uri mediaUri{ L"ms-appx:///Assets/Sound/" + area.Sound + L".mp3" };
                PlaySound(mediaUri);

                Uri imageUri{ L"ms-appx:///Assets/Image/" + area.Image + L".png" };
                auto async_op_with_progress{ ShowImage(imageUri) };
                co_await async_op_with_progress;

                score += area.Score;
                break;
            }
        }
    }

    Windows::Foundation::IAsyncAction MainPage::PlaySound(winrt::Windows::Foundation::Uri mediaUri)
    {
        auto file = co_await StorageFile::GetFileFromApplicationUriAsync(mediaUri);
        auto stream = co_await file.OpenReadAsync();
        mediaElement().SetSource(stream, file.ContentType());
        mediaElement().Play();
    }

    Windows::Foundation::IAsyncActionWithProgress<int> MainPage::ShowImage(winrt::Windows::Foundation::Uri imageUri)
    {
        co_await get_progress_token();

        BitmapImage bitmap = BitmapImage();
        auto file = co_await StorageFile::GetFileFromApplicationUriAsync(imageUri);
        auto stream = co_await file.OpenReadAsync();
        co_await bitmap.SetSourceAsync(stream);
        image().Source(bitmap);
    }
}
