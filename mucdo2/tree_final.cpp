#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>

// ??nh ngh?a m�u LIME
#define LIME RGB(0, 255, 0)
int randomColor() {
    return (rand() % 15) + 1; // Ch?n m�u t? 1 �?n 15 (trong b?ng m�u)
}

// H�m v? c�y
void tree(float x, float y, float len, float a, float b) {
    if (len < 15) {
        delay(10);
        setcolor(GREEN); // M�u cho l�
        circle(x, y, 5); // V? l�
        setcolor(LIME); // M�u cho vi?n l�
        circle(x, y, 6); // V? vi?n l�
        return;
    }

    float x1, y1;
 

    setcolor(randomColor()); // M�u cho th�n c�y
    x1 = x + len * cos(3.1428 * a / 180);
    y1 = y - len * sin(3.1428 * a / 180);
    line(x, y, x1, y1); // V? th�n c�y

    // ?? quy �? v? c�c nh�nh
    tree(x1, y1, len * 0.7, a - b, b);
    tree(x1, y1, len * 0.7, a + b, -b);
}

int main() {
    int gd = DETECT, gm;
    float x = 400, y = 700, t = 200; // T?o �? g?c v� chi?u d�i c?a c�y
    initgraph(&gd, &gm, ""); // Kh?i t?o �? h?a

    // V? nhi?u c�y
    for (int i = 0; i <= 3; i++) {
        tree(x + i * 30, y, t, 90, 30); // C�y b�n tr�i
        tree(x + i * 30, y, t, 90, -30); // C�y b�n ph?i
    }

    getch(); // Ch? ng�?i d�ng nh?n ph�m
    closegraph(); // ?�ng �? h?a
    return 0; // Tr? v? 0
}

