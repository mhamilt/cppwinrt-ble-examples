# C++/WinRT BLE Examples

A straight forward example for interacting with the Windows Bluetooth API is a little difficult to find. So here are some barebones Console applications to get you started.

## Setup

If you have never worked with development on windows, you may be in for a long ride. There are few things to do first before you can get started.

The [C++/WinRT](https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/) has you covered for the most part, but the key points are:

### Install UWP development tools

>For Visual Studio support, you'll need Visual Studio 2019 or Visual Studio 2017 (at least version 15.6; we recommend at least 15.7). From within the Visual Studio Installer, install the Universal Windows Platform development workload. In Installation Details > Universal Windows Platform development, check the C++ (v14x) Universal Windows Platform tools option(s), if you haven't already done so. And, in Windows Settings > Update & Security > For developers, choose the Developer mode option rather than the Sideload apps option.


### Install C++/WinRT Visual Studio Extension (VSIX)

>[download and install the latest version of the C++/WinRT Visual Studio Extension (VSIX)](https://marketplace.visualstudio.com/items?itemName=CppWinRTTeam.cppwinrt101804264) from the Visual Studio Marketplace.

OR

> convert an existing project by manually installing the Microsoft.Windows.CppWinRT NuGet package. After installing (or updating to) the latest version of the VSIX extension, open the existing project in Visual Studio, click Project > Manage NuGet Packages... > Browse, type or paste Microsoft.Windows.CppWinRT in the search box, select the item in search results, and then click Install to install the package for that project. Once you've added the package, you'll get C++/WinRT MSBuild support for the project, including invoking the cppwinrt.exe tool.
