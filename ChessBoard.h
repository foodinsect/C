#include "pclaf.h"
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include "Piece.h"

class ChessBoard : public Application {
public:
    // ü���� ������
    ChessBoard(const TCHAR* title, int windowSize)
        : Application(title, windowSize, windowSize, CW_USEDEFAULT, CW_USEDEFAULT) {
        initializeBoard(); // ü���� �ʱ�ȭ
    }

    // �׸��� �̺�Ʈ ó��
    virtual void paint() override {
        drawChessBoard(); // ü���� �׸���
        drawPieces();     // ü�� �� �׸���
    }

protected: // ��� �Լ����� ����� �� �ֵ��� Protected�� ������
    std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize> board;
    
    // ü���� �׸���
    void drawChessBoard() {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                Color color = ((i + j) % 2 == 0) ? white : black;
                setPen(color, solidLine);
                setBrush(color);
                rectangle(i * tileSize, j * tileSize, tileSize, tileSize);
            }
        }
    }

    // ü���� �ʱ�ȭ : �� ��ġ
    void initializeBoard() {
        // ��� �� ��ġ (�ϴ�)
        board[0][7] = std::make_unique<Rook>(Piece::Color::White);
        board[7][7] = std::make_unique<Rook>(Piece::Color::White);
        board[1][7] = std::make_unique<Knight>(Piece::Color::White);
        board[6][7] = std::make_unique<Knight>(Piece::Color::White);
        board[2][7] = std::make_unique<Bishop>(Piece::Color::White);
        board[5][7] = std::make_unique<Bishop>(Piece::Color::White);
        board[3][7] = std::make_unique<Queen>(Piece::Color::White);
        board[4][7] = std::make_unique<King>(Piece::Color::White);
        for (int col = 0; col < boardSize; ++col) {
            board[col][6] = std::make_unique<Pawn>(Piece::Color::White);
        }

        // ������ �� ��ġ (���)
        board[0][0] = std::make_unique<Rook>(Piece::Color::Black);
        board[7][0] = std::make_unique<Rook>(Piece::Color::Black);
        board[1][0] = std::make_unique<Knight>(Piece::Color::Black);
        board[6][0] = std::make_unique<Knight>(Piece::Color::Black);
        board[2][0] = std::make_unique<Bishop>(Piece::Color::Black);
        board[5][0] = std::make_unique<Bishop>(Piece::Color::Black);
        board[3][0] = std::make_unique<Queen>(Piece::Color::Black);
        board[4][0] = std::make_unique<King>(Piece::Color::Black);
        for (int col = 0; col < boardSize; ++col) {
            board[col][1] = std::make_unique<Pawn>(Piece::Color::Black);
        }


    }

    // ���� ü�� �� �׸���
    void drawPieces() {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if (board[i][j]) {
                    drawPiece(board[i][j].get(), i, j); // �����͸� ����
                }

            }
        }
    }

    void drawText(const TCHAR* text, int length, int x, int y) {
        // ���ڸ� �׸� ���� ����
        setTextColor(black);
        // ���� �׸���
        TextOut(device, x, y, text, length);
    }

    void drawPiece(const Piece* piece, int x, int y) {
        // ü���ǿ��� �� ĭ�� �߽� ��ǥ ���
        int centerX = x * tileSize + tileSize / 2;
        int centerY = y * tileSize + tileSize / 2;

        TCHAR symbol = TEXT(' ');
        if (piece) {
            switch (piece->type) { // '->' �����ڸ� ���
            case Piece::Type::Pawn:
                symbol = piece->color == Piece::Color::White ? TEXT('P') : TEXT('p');
                break;
            case Piece::Type::Knight:
                symbol = piece->color == Piece::Color::White ? TEXT('N') : TEXT('n');
                break;
            case Piece::Type::Bishop:
                symbol = piece->color == Piece::Color::White ? TEXT('B') : TEXT('b');
                break;
            case Piece::Type::Rook:
                symbol = piece->color == Piece::Color::White ? TEXT('R') : TEXT('r');
                break;
            case Piece::Type::Queen:
                symbol = piece->color == Piece::Color::White ? TEXT('Q') : TEXT('q');
                break;
            case Piece::Type::King:
                symbol = piece->color == Piece::Color::White ? TEXT('K') : TEXT('k');
                break;
            default:
                break;
            }

        }

        // ������ ũ�⸦ ����Ͽ� �߽� ��ġ���� ����
        int charWidth = avgCharWidth(); // ü���� Ŭ������ �ش� �޼��尡 �־�� ��
        int charHeight = textHeight();  // ���������� ü���� Ŭ������ �ش� �޼��尡 �־�� ��

        drawText(&symbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
    }


};

