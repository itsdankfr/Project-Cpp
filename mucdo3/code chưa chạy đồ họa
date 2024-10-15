#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

void clearConsole() {
#ifdef _WIN32
    system("cls");  // Dành cho Windows
#else
    system("clear"); // Dành cho Unix/Linux
#endif
}

std::string getColor(int second) {
    // Thay đổi màu sắc dựa trên giây
    switch (second % 3) {
        case 0: return "\033[31m"; // Đỏ
        case 1: return "\033[32m"; // Xanh lá
        case 2: return "\033[34m"; // Xanh dương
        default: return "\033[0m";  // Mặc định
    }
}

void displayTime(int hours, int minutes, int seconds) {
    clearConsole();
    
    std::string color = getColor(seconds);
    std::cout << color << std::setw(2) << std::setfill('0') << hours << ":"
              << std::setw(2) << std::setfill('0') << minutes << ":"
              << std::setw(2) << std::setfill('0') << seconds << "\033[0m" << std::endl;
}

int main() {
    int totalSeconds;
    std::cout << "enter time: ";
    std::cin >> totalSeconds;

    for (int i = totalSeconds; i >= 0; --i) {
        int hours = i / 3600;
        int minutes = (i % 3600) / 60;
        int seconds = i % 60;

        displayTime(hours, minutes, seconds);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    clearConsole();
    std::cout << "Time's up'" << std::endl;
    return 0;
}
