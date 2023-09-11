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
public:
    Piece(PieceColor color) : m_color(color) {}
    ~Piece() {
        cout << "~Piece(): " << this << endl;
    }
    virtual void draw() = 0;
};

class BlackPiece : public Piece {
public:
    BlackPiece(PieceColor color) : Piece(color) {}
    ~BlackPiece(){}
    void draw() {
        cout << "piece: black" << endl;
    }
};

class WhitePiece : public Piece {
public:
    WhitePiece(PieceColor color) : Piece(color) {}
    ~WhitePiece(){}
    void draw() {
        cout << "piece: white" << endl;
    }
};

class PieceBoard {
public:
    PieceBoard(string black, string white) : m_black(black), m_white(white) {
        m_blackPiece = nullptr;
        m_whitePiece = nullptr;
    }
    ~PieceBoard() {
        clear();
    }
    void clear() {
        delete m_blackPiece;
        delete m_whitePiece;
    }
    void setPiece(PieceColor color, PiecePos pos) {
        if (color == BLACK) {
            if (m_blackPiece == nullptr) {
                m_blackPiece = new BlackPiece(color);
            }
            m_blackPiece->draw();
            cout << "*************** black pos: " << pos.m_x << ":" << pos.m_y << endl;
        } else { //(color == WHITE)
            if (m_whitePiece == nullptr) {
                m_whitePiece = new WhitePiece(color);
            }
            m_whitePiece->draw();
            cout << "*************** white pos: " << pos.m_x << ":" << pos.m_y << endl;
        }
        m_pieces.push_back(pos);
    }
private:
    //黑白棋都一样，就颜色不一样
    vector<PiecePos> m_pieces;
    string m_black;
    string m_white;
    Piece *m_blackPiece;
    Piece *m_whitePiece;
};


int main() {

    PieceBoard PieceBoard("Demo", "loading");
    PieceBoard.setPiece(BLACK, PiecePos(11, 22));
    PieceBoard.setPiece(WHITE, PiecePos(33, 44));
    PieceBoard.setPiece(BLACK, PiecePos(55, 66));
    PieceBoard.setPiece(WHITE, PiecePos(77, 88));

    return 0;
}
