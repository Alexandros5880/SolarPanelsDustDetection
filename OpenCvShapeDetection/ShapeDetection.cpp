#include "pch.h"
#include "ShapeDetection.h"
#if __has_include("ShapeDetection.g.cpp")
#include "ShapeDetection.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::OpenCvShapeDetection::implementation
{
    int32_t ShapeDetection::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ShapeDetection::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ShapeDetection::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
