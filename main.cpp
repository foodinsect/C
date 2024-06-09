#include <string>
#include <array>
#include <vector>
#include "pclaf.h"


const int tilesize = 50; // ü���� Ÿ��ũ��
const int boardsize = 8; // ü������ ũ�� 
const int totalsize = tilesize * boardsize + 40; // ��ü ũ��

//ü�� ���� �������
enum class Unit {
    Empty,
    W_pawn, W_knight, W_Bishop, W_Rook, W_Queen, W_King,
    B_pawn, B_Knight, B_Bishop, B_Rook, B_Queen, B_King
};

//ü�� ���� ����
enum class GameState {
    Empty,
    Atwar,
    White_Victory,
    Black_Victory
};

class ChessGame : public Application
{
    std::array<std::array<Unit, boardsize>, boardsize> board;
    std::pair<int, int> UnitPosition;
    bool Unit_onoff;
    enum class Gamer { White, Black } currentGamer;
    std::vector<std::pair<int, int>> attackpath;
    GameState gameState;

public:
    ChessGame(const TCHAR* name) : Application(name, totalsize, totalsize, CW_USEDEFAULT, CW_USEDEFAULT)
    {
        setupChessBoard();
        Unit_onoff = false;
        UnitPosition = { -1, -1 };
        currentGamer = Gamer::White; // ����� ���� ����
        gameState = GameState::Atwar;
    }
    void computeAttackpath(int x, int y)
    {
        attackpath.clear(); //�ʱ�ȭ
        for (int i = 0; i < boardsize; ++i)
        {
            for (int j = 0; j < boardsize; ++j)
            {
                if (confirmed_Move({ x, y }, { i, j }))
                {
                    attackpath.push_back({ i, j });
                }
            }
        }
    }

    void setupChessBoard()

    {
        board[0][7] = board[7][7] = Unit::W_Rook;
        board[1][7] = board[6][7] = Unit::W_knight;
        board[2][7] = board[5][7] = Unit::W_Bishop;
        board[3][7] = Unit::W_Queen;
        board[4][7] = Unit::W_King;
        for (int col = 0; col < boardsize; ++col) {
            board[col][6] = Unit::W_pawn;
        }

        board[0][0] = board[7][0] = Unit::B_Rook;
        board[1][0] = board[6][0] = Unit::B_Knight;
        board[2][0] = board[5][0] = Unit::B_Bishop;
        board[3][0] = Unit::B_Queen;
        board[4][0] = Unit::B_King;
        for (int col = 0; col < boardsize; ++col) {
            board[col][1] = Unit::B_pawn;
        }

    }

    void toggleCurrentPlayer()
    {
        currentGamer = (currentGamer == Gamer::White) ? Gamer::Black : Gamer::White;
    }

    std::wstring fetch_status() const {
        return (currentGamer == Gamer::White) ? L"����� ����" : L"����� ����";
    }


    void paint() 
    {
        for (int i = 0; i < boardsize; ++i) {
            for (int j = 0; j < boardsize; ++j) {
                Color color = ((i + j) % 2 == 0) ? white : black;
                setPen(color, solidLine);
                setBrush(color);
                rectangle(i * tilesize, j * tilesize, tilesize, tilesize);

                Unit unit = board[i][j];
                if (unit != Unit::Empty) {
                    renderChessUnit(unit, i, j);
                }

                //���ù��� unit
                if (Unit_onoff && UnitPosition.first == i && UnitPosition.second == j) {
                    setPen(brightYellow, dashedLine, 4);
                    rectangle(i * tilesize, j * tilesize, tilesize, tilesize);
                }

                //���ݵ���
                for (const auto& move : attackpath) {
                    if (isUnitBlack(board[i][j])) {
                        setPen(blue, dashedLine, 4);
                    }
                    else {
                        setPen(blue, dashedLine, 4);
                    }
                    rectangle(move.first * tilesize, move.second * tilesize, tilesize, tilesize);
                }
            }
        }

        // ���� ���¿� ���� �޽��� ǥ��
        std::wstring statusMessage;
        if (gameState == GameState::Atwar)
        {
            statusMessage = fetch_status();
            if (checkKingThreat())
            {
                statusMessage += L"äũ";
            }
        }
        else if (gameState == GameState::White_Victory)
        {
            statusMessage = L"����� �¸�!";
        }
        else if (gameState == GameState::Black_Victory)
        {
            statusMessage = L"����� �¸�!";
        }

        setTextColor(red);
        TextOut(device, 10, 410, statusMessage.c_str(), statusMessage.length());
    }

    void displayTextOnBoard(const TCHAR* text, int length, int x, int y)
    {
        setTextColor(black);
        TextOut(device, x, y, text, length);
    }

    void renderChessUnit(Unit unit, int x, int y)
    {
        // ü���ǿ��� �� ĭ�� �߽� ��ǥ ���
        int centerX = x * tilesize + tilesize / 2;
        int centerY = y * tilesize + tilesize / 2;

        //unit�� ���忡 ǥ���Ǵ� ���
        switch (unit) {
        case Unit::B_pawn: {
            TCHAR pawnSymbol = TEXT('p');
            displayTextOnBoard(&pawnSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::B_Knight: {
            TCHAR knightSymbol = TEXT('n');
            displayTextOnBoard(&knightSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::B_Bishop: {
            TCHAR bishopSymbol = TEXT('b');
            displayTextOnBoard(&bishopSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::B_Rook: {
            TCHAR rookSymbol = TEXT('r');
            displayTextOnBoard(&rookSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::B_Queen: {
            TCHAR queenSymbol = TEXT('q');
            displayTextOnBoard(&queenSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::B_King: {
            TCHAR kingSymbol = TEXT('k');
            displayTextOnBoard(&kingSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::W_pawn: {
            TCHAR w_pawnSymbol = TEXT('P');
            displayTextOnBoard(&w_pawnSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::W_knight: {
            TCHAR w_knightSymbol = TEXT('N');
            displayTextOnBoard(&w_knightSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::W_Bishop: {
            TCHAR w_BishopSymbol = TEXT('B');
            displayTextOnBoard(&w_BishopSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::W_Rook: {
            TCHAR w_RookSymbol = TEXT('R');
            displayTextOnBoard(&w_RookSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::W_Queen: {
            TCHAR w_QueenSymbol = TEXT('Q');
            displayTextOnBoard(&w_QueenSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        case Unit::W_King: {
            TCHAR w_KingSymbol = TEXT('K');
            displayTextOnBoard(&w_KingSymbol, 1, centerX - charWidth / 2, centerY - charHeight / 2);
            break;
        }
        default: {
            break;
        }
        }
    }

    bool executeUnitMovement(const std::pair<int, int>& from, const std::pair<int, int>& to) {
        // �̵� ���ɼ� �˻�
        if (confirmed_Move(from, to)) {
            // ŷ�� ������ ���� ���� ���·� ����
            if (board[to.first][to.second] == Unit::W_King) {
                gameState = GameState::Black_Victory;
            }
            else if (board[to.first][to.second] == Unit::B_King) {
                gameState = GameState::White_Victory;
            }

            // ���� �̵� ����
            board[to.first][to.second] = board[from.first][from.second];
            board[from.first][from.second] = Unit::Empty;
            toggleCurrentPlayer();
            attackpath.clear();
            return true;
        }
        return false;
    }

    bool isEnemyUnit(const std::pair<int, int>& from, const std::pair<int, int>& to) {
        if (currentGamer == Gamer::White) {
            return isUnitBlack(board[to.first][to.second]);
        }
        else {
            return isUnitWhite(board[to.first][to.second]);
        }
    }

    bool confirmed_Move(const std::pair<int, int>& from, const std::pair<int, int>& to) {
        // �̵��� ü���� ���� ������ Ȯ��
        if (to.first < 0 || to.first >= boardsize || to.second < 0 || to.second >= boardsize) return false;

        // ������ ���� �ִ� ��� �̵��� �����մϴ�.
        if (board[to.first][to.second] != Unit::Empty && !isEnemyUnit(from, to)) return false;

        Unit unit = board[from.first][from.second];
        int dx = to.first - from.first;
        int dy = to.second - from.second;

        switch (unit) {
        case Unit::W_pawn:
            if (from.second == 6 && // ù �̵� ��
                dy == -2 && dx == 0 &&
                board[from.first][from.second - 1] == Unit::Empty &&
                board[to.first][to.second] == Unit::Empty) return true;
            if (dy == -1 && dx == 0 && // �Ϲ� �̵�
                board[to.first][to.second] == Unit::Empty) return true;
            if (dy == -1 && abs(dx) == 1 && // �밢�� ����
                isUnitBlack(board[to.first][to.second])) return true;
            break;

        case Unit::B_pawn:
            if (from.second == 1 && // ù �̵� ��
                dy == 2 && dx == 0 &&
                board[from.first][from.second + 1] == Unit::Empty &&
                board[to.first][to.second] == Unit::Empty) return true;
            if (dy == 1 && dx == 0 && // �Ϲ� �̵�
                board[to.first][to.second] == Unit::Empty) return true;
            if (dy == 1 && abs(dx) == 1 && // �밢�� ����
                isUnitWhite(board[to.first][to.second])) return true;
            break;

        case Unit::W_knight:
            // Knight �̵� ��Ģ
            if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
                return true; // ����Ʈ�� �ٸ� ���� �پ���� �� �ֽ��ϴ�.
            }
            break;
        case Unit::B_Knight:
            // Knight �̵� ��Ģ
            if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
                return true; // ����Ʈ�� �ٸ� ���� �پ���� �� �ֽ��ϴ�.
            }
            break;

        case Unit::W_Bishop:
            if (abs(dx) == abs(dy)) { // �밢�� �̵� Ȯ��
                return verifyClearpath(from, to); // �̵� ��λ� �ٸ� ���� ������ Ȯ��
            }
            break;
        case Unit::B_Bishop:
            if (abs(dx) == abs(dy)) { // �밢�� �̵� Ȯ��
                return verifyClearpath(from, to); // �̵� ��λ� �ٸ� ���� ������ Ȯ��
            }
            break;

        case Unit::W_Rook:
            if (dx == 0 || dy == 0) { // ���� �Ǵ� ���� �̵�
                return verifyClearpath(from, to); // �̵� ��λ� �ٸ� ���� ������ Ȯ��
            }
            break;
        case Unit::B_Rook:
            // Rook �̵� ��Ģ
            if (dx == 0 || dy == 0) { // ���� �Ǵ� ���� �̵�
                return verifyClearpath(from, to); // �̵� ��λ� �ٸ� ���� ������ Ȯ��
            }
            break;

        case Unit::W_Queen:
            if (dx == 0 || dy == 0 || abs(dx) == abs(dy)) { // ����, ����, �밢�� �̵� Ȯ��
                return verifyClearpath(from, to); // �̵� ��λ� �ٸ� ���� ������ Ȯ��
            }
            break;
        case Unit::B_Queen:
            if (dx == 0 || dy == 0 || abs(dx) == abs(dy)) { // ����, ����, �밢�� �̵� Ȯ��
                return verifyClearpath(from, to); // �̵� ��λ� �ٸ� ���� ������ Ȯ��
            }
            break;

        case Unit::W_King:
            if (abs(dx) <= 1 && abs(dy) <= 1 && to.first >= 0 && to.first < boardsize && to.second >= 0 && to.second < boardsize) {
                return true; // �� ĭ �̵�
            }
            break;
        case Unit::B_King:
            // King �̵� ��Ģ
            if (abs(dx) <= 1 && abs(dy) <= 1 && to.first >= 0 && to.first < boardsize && to.second >= 0 && to.second < boardsize) {
                return true; // �� ĭ �̵�
            }
            break;

        default:
            break;
        }

        return false;
    }

    // �̵� ��λ� �ٸ� ���� ������ Ȯ���ϴ� �Լ�
    bool verifyClearpath(const std::pair<int, int>& from, const std::pair<int, int>& to) {
        int dx = (to.first > from.first) ? 1 : (to.first < from.first) ? -1 : 0;
        int dy = (to.second > from.second) ? 1 : (to.second < from.second) ? -1 : 0;

        int x = from.first + dx;
        int y = from.second + dy;

        while (x >= 0 && x < boardsize && y >= 0 && y < boardsize && (x != to.first || y != to.second)) {
            if (board[x][y] != Unit::Empty) return false;
            x += dx;
            y += dy;
        }
        return true;
    }

    void mouseDown(int x, int y) override {
        if (gameState != GameState::Atwar) {
            return;
        }

        // Ŭ���� ��ġ ó��
        if (x < 0 || x >= totalsize || y < 0 || y >= totalsize) return;
        int col = x / tilesize; // �� ���
        int row = -((boardsize - 1) - y) / tilesize;

        if (Unit_onoff) {
            if (UnitPosition.first == col && UnitPosition.second == row) {
                // ���� ���� �ٽ� Ŭ���ϸ� ���� ���
                Unit_onoff = false;
                attackpath.clear(); // �̵� ������ ��ġ ����� ���ϴ�.
            }
            else if (isUnitSelectable(UnitPosition.first, UnitPosition.second) &&
                confirmed_Move(UnitPosition, { col, row })) {
                // �ٸ� ���� �����ϰų� ��ȿ�� �̵��� �õ��� ��
                executeUnitMovement(UnitPosition, { col, row });
                Unit_onoff = false; // �� �̵� �� ���� ����
            }
        }
        else {
            // ���� �����մϴ�.
            if (board[col][row] != Unit::Empty && isUnitSelectable(col, row)) {
                UnitPosition = { col, row };
                Unit_onoff = true;
                computeAttackpath(col, row); // �̵� ������ ��ġ ���
            }
        }
        update(); // ȭ�� ����
    }

    bool isUnitSelectable(int row, int col) {
        // ���� �÷��̾ �ش� ��ġ�� ���� ������ �� �ִ��� Ȯ��
        if (board[row][col] == Unit::Empty) return false;


        if (currentGamer == Gamer::White) {
            return isUnitWhite(board[row][col]);
        }
        else {
            return isUnitBlack(board[row][col]);
        }

        // �� �÷��̾�� �ڽ��� ���� ������ �� ����
        return false;
    }

    std::pair<int, int> locateKingOnBoard(Gamer currentGamer)
    {
        for (int x = 0; x < boardsize; ++x)
        {
            for (int y = 0; y < boardsize; ++y)
            {
                Unit unit = board[x][y];
                if ((currentGamer == Gamer::White && unit == Unit::W_King) || (currentGamer == Gamer::Black && unit == Unit::B_King))
                {
                    return { x, y }; // ŷ�� ��ġ ��ȯ
                }
            }
        }
        return { -1, -1 }; // ŷ�� �߰ߵ��� ���� ���
    }

    bool checkKingThreat() {
        std::pair<int, int> kingPosition = locateKingOnBoard(currentGamer);
        // ��� ���� ���� ���� üũ
        for (int x = 0; x < boardsize; ++x)
        {
            for (int y = 0; y < boardsize; ++y)
            {
                Unit unit = board[x][y];
                if ((currentGamer == Gamer::White && isUnitBlack(unit)) || (currentGamer == Gamer::Black && isUnitWhite(unit)))
                {
                    if (confirmed_Move({ x, y }, kingPosition)) {
                        return true; // ŷ�� ���ݹ��� �� �ִ� ��ġ�� ����
                    }
                }
            }
        }
        return false; // üũ ��Ȳ�� �ƴ�
    }

    bool the_king(Unit unit) {
        return unit == Unit::W_King || unit == Unit::B_King;
    }

    bool isUnitWhite(Unit unit) {
        return unit == Unit::W_pawn || unit == Unit::W_knight || unit == Unit::W_Bishop ||
            unit == Unit::W_Rook || unit == Unit::W_Queen || unit == Unit::W_King;
    }

    bool isUnitBlack(Unit unit) {
        return unit == Unit::B_pawn || unit == Unit::B_Knight || unit == Unit::B_Bishop ||
            unit == Unit::B_Rook || unit == Unit::B_Queen || unit == Unit::B_King;
    }

};

int mainLAF() {
    ChessGame theGame(TEXT("ü�� ����"));
    theGame.run();
    return 0;
}