#include "main_window.hpp"
#include "UIElements.hpp"
#include "imgui.h"
#include <format>

namespace main_window {

    void MainWindow() {
        int CraneNumber = 4;
        UIElements::CraneCards(CraneNumber);
    }

}
