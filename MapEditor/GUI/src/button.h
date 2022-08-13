#ifndef BLOCKJUMP_BUTTON_H
#define BLOCKJUMP_BUTTON_H

#include <string>
#include <functional>

namespace Button
{

void Show(const std::string& text, const std::function<void()>& callback, bool isDisabled = false)
{
    if (isDisabled) ImGui::BeginDisabled(true);

    if (ImGui::Button(text.c_str(), ImVec2(120, 0)))
    {
        callback();
    }

    if (isDisabled) ImGui::EndDisabled();
}

}  // namespace Button

#endif  // BLOCKJUMP_BUTTON_H
