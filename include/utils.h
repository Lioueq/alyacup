//
// Created by abss on 23.01.2026.
//

#ifndef ALYACUP_UTILS_H
#define ALYACUP_UTILS_H

#define IDI_ICON 200

void onContextMenu(HWND hwnd, LPARAM lParam);
std::wstring onDialogMenu();
void FatalError(HWND hwnd, PWSTR error);

namespace alyacup::tools {
    enum optionID {
        EXIT_ID = 100,
        RESIZE_ID = 101,
        OPEN_ID = 102,
        FIXED_ID = 103
    };
}

#endif //ALYACUP_UTILS_H