// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "pch.h"
#include "Profiles_Advanced.h"
#include "Profiles_Advanced.g.cpp"
#include "ProfileViewModel.h"

#include "EnumEntry.h"
#include <LibraryResources.h>
#include "..\WinRTUtils\inc\Utils.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Navigation;

namespace winrt::Microsoft::Terminal::Settings::Editor::implementation
{
    Profiles_Advanced::Profiles_Advanced()
    {
        InitializeComponent();
    }

    void Profiles_Advanced::OnNavigatedTo(const NavigationEventArgs& e)
    {
        const auto args = e.Parameter().as<Editor::NavigateToProfileArgs>();
        _Profile = args.Profile();
        _windowRoot = args.WindowRoot();

        //if (const auto& bellSounds = _Profile.CurrentBellSounds())
        //{
        //    auto uiStack = BellSoundStack().Children();
        //    const auto dataTemplate = Resources().Lookup(box_value(L"BellSoundEntryViewModelTemplate")).as<DataTemplate>();
        //    for (const auto&& entry : bellSounds)
        //    {
        //        ContentControl ctrl;
        //        ctrl.Content(entry);
        //        ctrl.ContentTemplate(dataTemplate);
        //
        //        uiStack.Append(ctrl);
        //    }
        //}
    }

    void Profiles_Advanced::OnNavigatedFrom(const NavigationEventArgs& /*e*/)
    {
        _ViewModelChangedRevoker.revoke();
    }

    safe_void_coroutine Profiles_Advanced::BellSoundBrowse_Click(const IInspectable& sender, const RoutedEventArgs& /*e*/)
    {
        static constexpr COMDLG_FILTERSPEC supportedFileTypes[] = {
            { L"All Files (*.*)", L"*.*" }
        };

        const auto parentHwnd{ reinterpret_cast<HWND>(WindowRoot().GetHostingWindow()) };
        auto file = co_await OpenFilePicker(parentHwnd, [](auto&& dialog) {
            try
            {
                auto folderShellItem{ winrt::capture<IShellItem>(&SHGetKnownFolderItem, FOLDERID_ComputerFolder, KF_FLAG_DEFAULT, nullptr) };
                dialog->SetDefaultFolder(folderShellItem.get());
            }
            CATCH_LOG(); // non-fatal
            THROW_IF_FAILED(dialog->SetFileTypes(ARRAYSIZE(supportedFileTypes), supportedFileTypes));
            THROW_IF_FAILED(dialog->SetFileTypeIndex(1)); // the array is 1-indexed
            //THROW_IF_FAILED(dialog->SetDefaultExtension(L"exe;cmd;bat"));
        });
        if (!file.empty())
        {
            // TODO CARLOS: apply text
        }
    }

    void Profiles_Advanced::BellSoundDelete_Click(const IInspectable& /*sender*/, const RoutedEventArgs& /*e*/)
    {
        //auto bellSoundEntry = sender.as<Button>().Tag().as<Editor::BellSoundEntryViewModel>();
        //auto bellSoundEntry = sender.as<Button>().DataContext().as<hstring>();
        //_Profile.RequestDeleteBellSound(bellSoundEntry);

        // Update UI
        //auto uiStack = BellSoundStack().Children();
        //for (uint32_t i = 0; i < uiStack.Size(); i++)
        //{
        //    auto ctrl = uiStack.GetAt(i).as<ContentControl>();
        //    if (ctrl.Content().as<Editor::BellSoundEntryViewModel>() == bellSoundEntry)
        //    {
        //        uiStack.RemoveAt(i);
        //        break;
        //    }
        //}
    }

    void Profiles_Advanced::AddBellSound_Click(const IInspectable& /*sender*/, const RoutedEventArgs& /*e*/)
    {
        _Profile.RequestAddBellSound();
        //auto bellSound = _Profile.RequestAddBellSound();

        //const auto dataTemplate = Resources().Lookup(box_value(L"BellSoundEntryViewModelTemplate")).as<DataTemplate>();
        //ContentControl ctrl;
        //ctrl.Content(bellSound);
        //ctrl.ContentTemplate(dataTemplate);
        // 
        //BellSoundStack().Children().Append(ctrl);
    }
}
