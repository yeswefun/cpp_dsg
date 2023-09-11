#include <iostream>
#include <vector>

using namespace std;

enum PieceColor {BLACK, WHITE};

struct PiecePos {
    int m_x;
    int m_y;

    PiecePos(int x, int y) : m_x(x), m_y(y) {}
};

class Piece {
protected:
    PieceColor m_color;
    PiecePos m_pos;
public:
    Piece(PieceColor color, PiecePos pos) : m_color(color), m_pos(pos) {}
    ~Piece() {
        cout << "~Piece(): " << this << endl;
    }
    virtual void draw();
};

class BlackPiece : public Piece {
public:
    BlackPiece(PieceColor color, PiecePos pos) : Piece(color, pos) {}
    ~BlackPiece(){}
    void draw() {
        cout << "piece: black" << endl;
    }
};

class WhitePiece : public Piece {
public:
    WhitePiece(PieceColor color, PiecePos pos) : Piece(color, pos) {}
    ~WhitePiece(){}
    void draw() {
        cout << "piece: white" << endl;
    }
};

class PieceBoard {
public:
    PieceBoard(string black, string white) : m_black(black), m_white(white) {}
    ~PieceBoard() {
        clear();
    }
    void clear() {
        for (auto it = m_pieces.begin(); it != m_pieces.end(); it++) {
            delete (*it);
        }
    }
    void setPiece(PieceColor color, PiecePos pos) {
        Piece *p;
        if (color == BLACK) {
            p = new BlackPiece(color, pos);
        } else { //(color == WHITE)
            p = new WhitePiece(color, pos);
        }
        m_pieces.push_back(p);
    }
private:
    //黑白棋都一样，就颜色不一样
    vector<Piece*> m_pieces;
    string m_black;
    string m_white;
};


int main() {

    return 0;
}
