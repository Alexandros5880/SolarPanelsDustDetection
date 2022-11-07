#pragma once

#include "ShapeDetection.g.h"

namespace winrt::OpenCvShapeDetection::implementation
{
    struct ShapeDetection : ShapeDetectionT<ShapeDetection>
    {
        ShapeDetection() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::OpenCvShapeDetection::factory_implementation
{
    struct ShapeDetection : ShapeDetectionT<ShapeDetection, implementation::ShapeDetection>
    {
    };
}
