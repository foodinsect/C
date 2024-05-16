#pragma once
#pragma once
#include "pclaf.h"
#include <array>
#include <vector>
#include <string>
#include <iostream>

const int tileSize = 50; // 체스판 타일 하나의 크기
const int boardSize = 8; // 체스판의 크기 (8x8)
const int windowSize = tileSize * boardSize + 40; // 창 크기

class Piece {
public:
    enum class Color { White, Black }; // 체스 말의 색상
    enum class Type {
        Pawn, Knight, Bishop, Rook, Queen, King // 체스 말의 종류
    };

    Color color; // 말의 색상
    Type type;   // 말의 종류

    Piece(Color color, Type type) : color(color), type(type) {}
    virtual ~Piece() = default;

    // 체스 말의 유효한 이동 확인을 위한 순수 가상 함수
    virtual bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const = 0;
};



// 폰 클래스
class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color, Type::Pawn) {}
    // 폰의 이동 규칙 구현
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        // 흰색 폰의 움직임 규칙
        if (this->color == Color::White) {
            if (from.second == 6 && dy == -2 && dx == 0 && board[from.first][from.second - 1] == nullptr && board[to.first][to.second] == nullptr) {
                return true;
            }
            if (dy == -1 && dx == 0 && board[to.first][to.second] == nullptr) {
                return true;
            }
            if (dy == -1 && abs(dx) == 1 && board[to.first][to.second] != nullptr && board[to.first][to.second]->color == Color::Black) {
                return true;
            }
        }
        // 검은색 폰의 움직임 규칙
        else {
            if (from.second == 1 && dy == 2 && dx == 0 && board[from.first][from.second + 1] == nullptr && board[to.first][to.second] == nullptr) {
                return true;
            }
            if (dy == 1 && dx == 0 && board[to.first][to.second] == nullptr) {
                return true;
            }
            if (dy == 1 && abs(dx) == 1 && board[to.first][to.second] != nullptr && board[to.first][to.second]->color == Color::White) {
                return true;
            }
        }

        return false;
    }
};


// 나이트 클래스
class Knight : public Piece {
public:
    Knight(Color color) : Piece(color, Type::Knight) {}
    // 나이트의 이동 규칙 구현
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to, const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
    int dx = to.first - from.first;
    int dy = to.second - from.second;
    if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
        if (board[to.first][to.second] == nullptr || board[to.first][to.second]->color != this->color) return true;
    }
    return false;
    }

};

// 비숍 클래스
class Bishop : public Piece {
public:
    Bishop(Color color) : Piece(color, Type::Bishop) {}
    // 비숍의 이동 규칙 구현
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        // 비숍은 대각선 방향으로만 이동 가능
        if (abs(dx) != abs(dy)) {
            return false;
        }

        int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
        int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;
        int x = from.first + stepX;
        int y = from.second + stepY;

        while (x != to.first || y != to.second) {
            if (board[x][y] != nullptr) {
                return false;
            }
            x += stepX;
            y += stepY;
        }

        return board[to.first][to.second] == nullptr || board[to.first][to.second]->color != this->color;
    }


};

// 룩 클래스
class Rook : public Piece {
public:
    Rook(Color color) : Piece(color, Type::Rook) {}
    // 룩의 이동 규칙 구현
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        if (dx != 0 && dy != 0) { // 룩은 수직 또는 수평으로만 이동 가능
            return false;
        }

        // 경로상의 장애물 확인
        int stepX = (dx == 0) ? 0 : (dx > 0) ? 1 : -1;
        int stepY = (dy == 0) ? 0 : (dy > 0) ? 1 : -1;
        int x = from.first + stepX;
        int y = from.second + stepY;

        while (x != to.first || y != to.second) {
            if (board[x][y] != nullptr) { // 경로상에 다른 기물이 존재
                return false;
            }
            x += stepX;
            y += stepY;
        }

        // 도착지에 적의 기물이 있거나 빈 공간인지 확인
        return board[to.first][to.second] == nullptr || board[to.first][to.second]->color != this->color;
    }

};

// 퀸 클래스
class Queen : public Piece {
public:
    Queen(Color color) : Piece(color, Type::Queen) {}
    // 퀸의 이동 규칙 구현
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        // 퀸은 수직, 수평, 대각선으로 이동 가능
        if (dx != 0 && dy != 0 && abs(dx) != abs(dy)) {
            return false;
        }

        int stepX = (dx == 0) ? 0 : (dx > 0) ? 1 : -1;
        int stepY = (dy == 0) ? 0 : (dy > 0) ? 1 : -1;
        int x = from.first + stepX;
        int y = from.second + stepY;

        while (x != to.first || y != to.second) {
            if (board[x][y] != nullptr) {
                return false;
            }
            x += stepX;
            y += stepY;
        }

        return board[to.first][to.second] == nullptr || board[to.first][to.second]->color != this->color;
    }

};


// 킹 클래스
class King : public Piece {
public:
    King(Color color) : Piece(color, Type::King) {}
    // 킹의 이동 규칙 구현
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to, const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        if (abs(dx) <= 1 && abs(dy) <= 1) {
            if (board[to.first][to.second] == nullptr || board[to.first][to.second]->color != this->color) return true;
        }
        return false;
    }

};
