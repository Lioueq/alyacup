//
// Created by abss on 23.01.2026.
//

#ifndef ALYACUP_UTILS_H
#define ALYACUP_UTILS_H

void onContextMenu(HWND hwnd, LPARAM lParam);

namespace alyacup::tools {
    enum optionID {
        EXIT_ID = 100,
        RESIZE_ID = 101
    };
}

#endif //ALYACUP_UTILS_H