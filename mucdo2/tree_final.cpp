#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>

// ??nh ngh?a màu LIME
#define LIME RGB(0, 255, 0)
int randomColor() {
    return (rand() % 15) + 1; // Ch?n màu t? 1 ð?n 15 (trong b?ng màu)
}

// Hàm v? cây
void tree(float x, float y, float len, float a, float b) {
    if (len < 15) {
        delay(10);
        setcolor(GREEN); // Màu cho lá
        circle(x, y, 5); // V? lá
        setcolor(LIME); // Màu cho vi?n lá
        circle(x, y, 6); // V? vi?n lá
        return;
    }

    float x1, y1;
 

    setcolor(randomColor()); // Màu cho thân cây
    x1 = x + len * cos(3.1428 * a / 180);
    y1 = y - len * sin(3.1428 * a / 180);
    line(x, y, x1, y1); // V? thân cây

    // ?? quy ð? v? các nhánh
    tree(x1, y1, len * 0.7, a - b, b);
    tree(x1, y1, len * 0.7, a + b, -b);
}

int main() {
    int gd = DETECT, gm;
    float x = 400, y = 700, t = 200; // T?o ð? g?c và chi?u dài c?a cây
    initgraph(&gd, &gm, ""); // Kh?i t?o ð? h?a

    // V? nhi?u cây
    for (int i = 0; i <= 3; i++) {
        tree(x + i * 30, y, t, 90, 30); // Cây bên trái
        tree(x + i * 30, y, t, 90, -30); // Cây bên ph?i
    }

    getch(); // Ch? ngý?i dùng nh?n phím
    closegraph(); // ?óng ð? h?a
    return 0; // Tr? v? 0
}

