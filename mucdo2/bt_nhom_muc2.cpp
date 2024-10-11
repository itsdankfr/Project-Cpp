#include <graphics.h>
#include <conio.h>
void drawTree(int x, int y) {
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    rectangle(x - 10, y, x + 10, y + 100);
    floodfill(x, y + 50, BROWN);
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(x, y, 50, 50);
    fillellipse(x - 30, y + 20, 40, 40);
    fillellipse(x + 30, y + 20, 40, 40);
}
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    drawTree(250, 250);
    getch();
    closegraph();
    return 0;
}
