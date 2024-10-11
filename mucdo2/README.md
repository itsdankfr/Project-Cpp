#include <graphics.h> // Thư viện đồ họa
#include <conio.h>    // Thư viện nhập/xuất từ bàn phím

// Hàm vẽ cây tại vị trí (x, y)
void drawTree(int x, int y) {
    setcolor(BROWN); // Đặt màu cho thân cây
    setfillstyle(SOLID_FILL, BROWN); // Đặt kiểu tô màu cho thân cây
    rectangle(x - 10, y, x + 10, y + 100); // Vẽ thân cây dưới dạng hình chữ nhật
    floodfill(x, y + 50, BROWN); // Tô màu nâu cho thân cây

    setcolor(GREEN); // Đặt màu cho lá cây
    setfillstyle(SOLID_FILL, GREEN); // Đặt kiểu tô màu cho lá cây
    fillellipse(x, y, 50, 50); // Vẽ phần chính của lá cây dưới dạng hình elip
    fillellipse(x - 30, y + 20, 40, 40); // Vẽ phần lá cây bên trái dưới dạng hình elip
    fillellipse(x + 30, y + 20, 40, 40); // Vẽ phần lá cây bên phải dưới dạng hình elip
}

int main() {
    int gd = DETECT, gm; // Biến để phát hiện và lưu trữ driver đồ họa và chế độ đồ họa
    initgraph(&gd, &gm, ""); // Khởi tạo chế độ đồ họa
    drawTree(250, 250); 
    getch(); // Chờ nhấn phím
    closegraph(); // Đóng chế độ đồ họa
    return 0; 
}

