#pragma once
#pragma once
#include "pclaf.h"
#include <array>
#include <vector>
#include <string>
#include <iostream>

const int tileSize = 50; // ü���� Ÿ�� �ϳ��� ũ��
const int boardSize = 8; // ü������ ũ�� (8x8)
const int windowSize = tileSize * boardSize + 40; // â ũ��

class Piece {
public:
    enum class Color { White, Black }; // ü�� ���� ����
    enum class Type {
        Pawn, Knight, Bishop, Rook, Queen, King // ü�� ���� ����
    };

    Color color; // ���� ����
    Type type;   // ���� ����

    Piece(Color color, Type type) : color(color), type(type) {}
    virtual ~Piece() = default;

    // ü�� ���� ��ȿ�� �̵� Ȯ���� ���� ���� ���� �Լ�
    virtual bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const = 0;
};



// �� Ŭ����
class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color, Type::Pawn) {}
    // ���� �̵� ��Ģ ����
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        // ��� ���� ������ ��Ģ
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
        // ������ ���� ������ ��Ģ
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


// ����Ʈ Ŭ����
class Knight : public Piece {
public:
    Knight(Color color) : Piece(color, Type::Knight) {}
    // ����Ʈ�� �̵� ��Ģ ����
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to, const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
    int dx = to.first - from.first;
    int dy = to.second - from.second;
    if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
        if (board[to.first][to.second] == nullptr || board[to.first][to.second]->color != this->color) return true;
    }
    return false;
    }

};

// ��� Ŭ����
class Bishop : public Piece {
public:
    Bishop(Color color) : Piece(color, Type::Bishop) {}
    // ����� �̵� ��Ģ ����
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        // ����� �밢�� �������θ� �̵� ����
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

// �� Ŭ����
class Rook : public Piece {
public:
    Rook(Color color) : Piece(color, Type::Rook) {}
    // ���� �̵� ��Ģ ����
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        if (dx != 0 && dy != 0) { // ���� ���� �Ǵ� �������θ� �̵� ����
            return false;
        }

        // ��λ��� ��ֹ� Ȯ��
        int stepX = (dx == 0) ? 0 : (dx > 0) ? 1 : -1;
        int stepY = (dy == 0) ? 0 : (dy > 0) ? 1 : -1;
        int x = from.first + stepX;
        int y = from.second + stepY;

        while (x != to.first || y != to.second) {
            if (board[x][y] != nullptr) { // ��λ� �ٸ� �⹰�� ����
                return false;
            }
            x += stepX;
            y += stepY;
        }

        // �������� ���� �⹰�� �ְų� �� �������� Ȯ��
        return board[to.first][to.second] == nullptr || board[to.first][to.second]->color != this->color;
    }

};

// �� Ŭ����
class Queen : public Piece {
public:
    Queen(Color color) : Piece(color, Type::Queen) {}
    // ���� �̵� ��Ģ ����
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to,
        const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        // ���� ����, ����, �밢������ �̵� ����
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


// ŷ Ŭ����
class King : public Piece {
public:
    King(Color color) : Piece(color, Type::King) {}
    // ŷ�� �̵� ��Ģ ����
    bool isValidMove(const std::pair<int, int>& from, const std::pair<int, int>& to, const std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize>& board) const override {
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        if (abs(dx) <= 1 && abs(dy) <= 1) {
            if (board[to.first][to.second] == nullptr || board[to.first][to.second]->color != this->color) return true;
        }
        return false;
    }

};
