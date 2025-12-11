#include "utils.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>

namespace main_window {

    static std::u32string* utf8_to_u32(const std::string& s) {
        std::u32string* out = new std::u32string();
        for (std::size_t i = 0; i < s.size();) {
            unsigned char c = s[i];
            char32_t cp = 0;
            std::size_t bytes = 0;

            if ((c & 0x80u) == 0) {
                cp = c;
                bytes = 1;
            } else if ((c & 0xE0u) == 0xC0u) {
                cp = (c & 0x1Fu) << 6;
                cp |= (s[i + 1] & 0x3Fu);
                bytes = 2;
            } else if ((c & 0xF0u) == 0xE0u) {
                cp = (c & 0x0Fu) << 12;
                cp |= (s[i + 1] & 0x3Fu) << 6;
                cp |= (s[i + 2] & 0x3Fu);
                bytes = 3;
            } else if ((c & 0xF8u) == 0xF0u) {
                cp = (c & 0x07u) << 18;
                cp |= (s[i + 1] & 0x3Fu) << 12;
                cp |= (s[i + 2] & 0x3Fu) << 6;
                cp |= (s[i + 3] & 0x3Fu);
                bytes = 4;
            } else {
                // invalid byte ??
                cp = 0xFFFD;
                bytes = 1;
            }

            out->push_back(cp);
            i += bytes;
        }
        return out;
    }

    static const char* u32_to_utf8(const std::u32string& v) {
        std::string* out = new std::string();
        for (char32_t cp : v) {
            if (cp <= 0x7Fu) {
                out->push_back(static_cast<char>(cp));
            } else if (cp <= 0x7FFu) {
                out->push_back(static_cast<char>(0xC0u | ((cp >> 6) & 0x1Fu)));
                out->push_back(static_cast<char>(0x80u | (cp & 0x3Fu)));
            } else if (cp <= 0xFFFFu) {
                out->push_back(static_cast<char>(0xE0u | ((cp >> 12) & 0x0Fu)));
                out->push_back(static_cast<char>(0x80u | ((cp >> 6) & 0x3Fu)));
                out->push_back(static_cast<char>(0x80u | (cp & 0x3Fu)));
            } else {
                out->push_back(static_cast<char>(0xF0u | ((cp >> 18) & 0x07u)));
                out->push_back(static_cast<char>(0x80u | ((cp >> 12) & 0x3Fu)));
                out->push_back(static_cast<char>(0x80u | ((cp >> 6) & 0x3Fu)));
                out->push_back(static_cast<char>(0x80u | (cp & 0x3Fu)));
            }
        }
        return out->c_str();
    }

    std::string reverse_utf8(std::string s) {
        std::u32string* codepoints = utf8_to_u32(s);
        std::reverse(codepoints->begin(), codepoints->end());
        return u32_to_utf8(*codepoints);
    }
    const char* reverse_utf8_c_str(std::string s) {
        std::u32string* codepoints = utf8_to_u32(s);
        std::reverse(codepoints->begin(), codepoints->end());
        auto a =  u32_to_utf8(*codepoints);
        return a;
    }


    std::string GetTimeStr() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    ImVec4 GetStatusColor(AgoranStatus status) {
        switch (status) {
            case AgoranStatus::StandBy: return ImVec4(0.4f, 0.7f, 1.0f, 1.0f); 
            case AgoranStatus::Working: return ImVec4(0.95f, 0.85f, 0.25f, 1.0f);
            case AgoranStatus::Error: return ImVec4(0.8f, 0.2f, 0.2f, 1.0f); 
            case AgoranStatus::Disabled: return ImVec4(0.5f, 0.5f, 0.5f, 1.0f); 
            default: return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }

    const char* GetStatusStr(AgoranStatus status) {
        switch (status) {
            case AgoranStatus::StandBy: return "Stand-By";
            case AgoranStatus::Working: return "Working";
            case AgoranStatus::Error: return "Error";
            case AgoranStatus::Disabled: return "Disabled";
            default: return "Unknown";
        }
    }

    const char* GetModeStr(AgoranMode mode) {
        switch (mode) {
            case AgoranMode::Automatic: return "Automatic";
            case AgoranMode::Manual: return "Manual";
            default: return "Unknown";
        }
    }

}
