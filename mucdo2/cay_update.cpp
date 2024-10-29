#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>

// Ðịnh nghĩa màu LIME
#define LIME RGB(0, 255, 0)

// Hàm vẽ cây
void tree(float x, float y, float len, float a, float b) {
    if (len < 20) {
        delay(50);
        setcolor(GREEN); // Màu cho lá
        circle(x, y, 5); // Vẽ lá
        setcolor(LIME); // Màu cho viền lá
        circle(x, y, 6); // Vẽ viền lá
        return;
    }

    float x1, y1;
 

    setcolor(BROWN); // Màu cho thân cây
    x1 = x + len * cos(3.1428 * a / 180);
    y1 = y - len * sin(3.1428 * a / 180);
    line(x, y, x1, y1); // Vẽ thân cây

    // Ðệ quy để vẽ các nhánh
    tree(x1, y1, len * 0.75, a - b, b);
    tree(x1, y1, len * 0.75, a + b, -b);
}

int main() {
    int gd = DETECT, gm;
    float x = 320, y = 550, t = 140; // Tạo độ gốc và chiều dài của cây
    initgraph(&gd, &gm, ""); // Khởi tạo đồ họa

    // Vẽ nhiều cây
    for (int i = 0; i <= 3; i++) {
        tree(x + i * 30, y, t, 90, 30); // Cây bên trái
        tree(x + i * 30, y, t, 90, -30); // Cây bên phải
    }

    getch(); // Chờ người dùng nhấn phím
    closegraph(); // Ðóng đồ họa
    return 0; // Trả về 0
}

