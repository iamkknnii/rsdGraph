#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>

using namespace std;

//UTF-8תUnicode 
std::wstring Utf82Unicode(const std::string& utf8string) {
    int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (widesize == 0)
    {
        throw std::exception("Error in conversion.");
    }
    std::vector<wchar_t> resultstring(widesize);
    int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
    if (convresult != widesize)
    {
        throw std::exception("failed!");
    }
    return std::wstring(&resultstring[0]);
}

//Unicode 转 Utf8 
std::string Unicode2Utf8(const std::wstring& widestring) 
{
  
    int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
    if (utf8size == 0)
    {
        throw std::exception("Error in conversion.");
    }
    std::vector<char> resultstring(utf8size);
    int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
    if (convresult != utf8size)
    {
        throw std::exception("failed!");
    }
    return std::string(&resultstring[0]);
}

std::wstring to_wstring(const string& str, const locale& loc = locale())
{
    vector<wchar_t>buf(str.size());
    use_facet<ctype<wchar_t>>(loc).widen(str.data(), str.data() + str.size(), buf.data());
    return wstring(buf.data(), buf.size());
}
std::string to_string(const wstring& str, const locale& loc = locale())
{
    vector<char>buf(str.size());
    use_facet<ctype<wchar_t>>(loc).narrow(str.data(), str.data() + str.size(), '*', buf.data());
    return string(buf.data(), buf.size());
}
