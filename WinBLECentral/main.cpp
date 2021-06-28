#include "pch.h"

#include <Windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

using winrt::Windows::Foundation::Collections::IVector;

int main()
{
    IVector<int> foo;
    foo.Append(1);
    uint32_t bar;
    foo.IndexOf(1, bar);
    return EXIT_SUCCESS;
}
