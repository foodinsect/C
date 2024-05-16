#include "pclaf.h"
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include "Piece.h"

class ChessBoard : public Application {
public:
    // 체스판 생성자
    ChessBoard(const TCHAR* title, int windowSize)
        : Application(title, windowSize, windowSize, CW_USEDEFAULT, CW_USEDEFAULT) {
        initializeBoard(); // 체스판 초기화
    }

    // 그리기 이벤트 처리
    virtual void paint() override {
        drawChessBoard(); // 체스판 그리기
        drawPieces();     // 체스 말 그리기
    }

protected: // 상속 함수에서 사용할 수 있도록 Protected로 선언함
    std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize> board;
    
    // 체스판 그리기
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

    // 체스판 초기화 : 말 배치
    void initializeBoard() {
        // 흰색 말 배치 (하단)
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

        // 검은색 말 배치 (상단)
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

    // 개별 체스 말 그리기
    void drawPieces() {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if (board[i][j]) {
                    drawPiece(board[i][j].get(), i, j); // 포인터를 전달
                }

            }
        }
    }

    void drawText(const TCHAR* text, int length, int x, int y) {
        // 문자를 그릴 색상 설정
        setTextColor(black);
        // 문자 그리기
        TextOut(device, x, y, text, length);
    }

    void drawPiece(const Piece* piece, int x, int y) {
        // 체스판에서 각 칸의 중심 좌표 계산
        int centerX = x * tileSize + tileSize / 2;
        int centerY = y * tileSize + tileSize / 2;

        TCHAR symbol = TEXT(' ');
        if (piece) {
            switch (piece->type) { // '->' 연산자를 사용
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

        // 문자의 크기를 고려하여 중심 위치에서 조정
        int charWidth = avgCharWidth(); // 체스판 클래스에 해당 메서드가 있어야 함
        int charHeight = textHeight();  // 마찬가지로 체스판 클래스에 해당 메서드가 있어야 함

        drawText(&symbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
    }


};

