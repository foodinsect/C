#include "pclaf.h"

class ChessApplication : public Application {
public:
    ChessApplication() : Application(TEXT("Chess Game"), 800, 800) {}

    void paint() override {
        drawBoard();
    }

    void drawBoard() {
        const int tileSize = 100; // ü���� �� ĭ�� ũ��
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if ((row + col) % 2 == 0) {
                    setBrush(white);
                }
                else {
                    setBrush(black);
                }
                rectangle(col * tileSize, row * tileSize, (col + 1) * tileSize, (row + 1) * tileSize);
            }
        }
    }

    void mouseDown(int x, int y) override {
        // ���⿡ ����� Ŭ�� �̺�Ʈ ó�� ������ ����
    }
};
