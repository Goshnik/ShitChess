#include <QApplication>
#include <QtWidgets>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QRectF>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QImage>
#include <QMouseEvent>
#include <math.h>
#include <iostream>

#define BP 1
#define BB 2
#define BK 3
#define BKK 4
#define BQ 5
#define BR 6

#define WP 7
#define WB 8
#define WK 9
#define WKK 10
#define WQ 11
#define WR 12

static QImage blackBishopimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\blackBishop.png");
static QImage blackKnightimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\blackKnight.png");
static QImage blackKingimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\blackKing.png");
static QImage blackRookimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\blackRook.png");
static QImage blackQueenimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\blackQueen.png");
static QImage blackPawnimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\blackPawn.png");

static QImage whiteBishopimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\whiteBishop.png");
static QImage whiteKnightimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\whiteKnight.png");
static QImage whiteKingimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\whiteKing.png");
static QImage whiteRookimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\whiteRook.png");
static QImage whiteQueenimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\whiteQueen.png");
static QImage whitePawnimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\whitePawn.png");

static QImage chessBoardimg("C:\\Users\\Forsaan\\Documents\\untitled3\\figures\\chessboard.png");

static QGraphicsPixmapItem* chessboard;

bool isMovementPossible (int fig, QPointF startPos, QPointF endPos);

static bool moveOrder;

bool checkBlack(QPointF startPos, QPointF endPos);

bool checkWhite(QPointF startPos, QPointF endPos);

class Figure:QGraphicsPixmapItem{
private:
    bool grab;
    QPointF grabPosition;
public:
    int name;
    bool color;
    Figure(QImage figure, QGraphicsItem* parent, int figureName):QGraphicsPixmapItem(QPixmap::fromImage(figure),parent){
        grab = false;
        name = figureName;
        if (figureName<=6){
            color = true;
        }
        else {
            color = false;
        }
    }
    void mousePressEvent(QGraphicsSceneMouseEvent* event){
        grab = true;
        grabPosition = event->scenePos();
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
        grab = false;

        if (isMovementPossible(name, grabPosition, event->scenePos())){
            this->setPos( event->scenePos().x()-(int) event->scenePos().x()%80,event->scenePos().y()-(int) event->scenePos().y()%80);
            moveOrder = !moveOrder;
        } else {
            this->setPos( grabPosition.x()-(int) grabPosition.x()%80,grabPosition.y()-(int) grabPosition.y()%80);
        }
    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event){
        if (grab){
            this->setPos(event->scenePos().x()-40,event->scenePos().y()-40);
        }
    }
    void setPosition(int x, int y){
        this->setPos(x,y);
    }

    void remove(){
        delete this;
    }
};

static std::vector<std::vector<Figure*>>* matrix;


bool checkBlack(QPointF startPos, QPointF endPos){
    std::vector<std::vector<Figure*>> temp = *matrix;
    std::vector<std::vector<Figure*>>* tempM = &temp;
    int xs = (int) startPos.x()/80;
    int ys = (int) startPos.y()/80;
    int xf = (int) endPos.x()/80;
    int yf = (int) endPos.y()/80;
    (*tempM)[xf][yf] = (*tempM)[xs][ys];
    (*tempM)[xs][ys] = nullptr;

    int xk = -1;
    int yk = -1;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ((*tempM)[i][j]->name == BKK){
                xk = i;
                yk = j;
                break;
            }
        }
        if (xk>=0){
            break;
        }

    }
    if (xk - 2 >= 0){
        if (yk-1 >= 0){
            if ((*tempM)[xk-2][yk-1]->name == WK)
                return true;
        }
        if (yk+1 <= 7){
            if ((*tempM)[xk-2][yk+1]->name == WK)
                return true;
        }
    }if (xk + 2 <= 7){
        if (yk-1 >= 0){
            if ((*tempM)[xk+2][yk-1]->name == WK)
                return true;
        }
        if (yk+1 <= 7){
            if ((*tempM)[xk+2][yk+1]->name == WK)
                return true;
        }
    }if (yk - 2 >= 0){
        if (xk-1 >= 0){
            if ((*tempM)[xk-1][yk-2]->name == WK)
                return true;
        }
        if (xk+1 <= 7){
            if ((*tempM)[xk+1][yk-2]->name == WK)
                return true;
        }
    }if (yk + 2 <= 7){
        if (xk-1 >= 0){
            if ((*tempM)[xk-1][yk+2]->name == WK)
                return true;
        }
        if (xk+1 <= 7){
            if ((*tempM)[xk+1][yk+2]->name == WK)
                return true;
        }
    }
    for (int i = xk-1; i > 0 ; i--){
        if ((*tempM)[i][yk]->color == (*tempM)[xk][yk]->color){
            break;
        }
        if ((*tempM)[i][yk]->name == WR || (*tempM)[i][yk]->name == WQ){
            return true;
        }
    }
    for (int i = xk+1; i < 8 ; i++){
        if ((*tempM)[i][yk]->color == (*tempM)[xk][yk]->color){
            break;
        }
        if ((*tempM)[i][yk]->name == WR || (*tempM)[i][yk]->name == WQ){
            return true;
        }
    }
    for (int i = yk-1; i > 0 ; i--){
        if ((*tempM)[xk][i]->color == (*tempM)[xk][i]->color){
            break;
        }
        if ((*tempM)[xk][i]->name == WR || (*tempM)[xk][i]->name == WQ){
            return true;
        }
    }
    for (int i = yk+1; i < 8 ; i++){
        if ((*tempM)[xk][i]->color == (*tempM)[xk][i]->color){
            break;
        }
        if ((*tempM)[xk][i]->name == WR || (*tempM)[xk][i]->name == WQ){
            return true;
        }
    }
    for (int i = 1; xk-i >= 0 && yk-i >= 0; i++){
        if ((*tempM)[xk-i][yk-i]->color == (*tempM)[xk][yk]->color){
            break;
    }
        if ((*tempM)[xk-i][yk-i]->name == WB || (*tempM)[xk-i][yk-i]->name == WQ){
            return true;
        }

    }for (int i = 1; xk+i < 8 && yk+i < 8; i++){
        if ((*tempM)[xk+i][yk+i]->color == (*tempM)[xk][yk]->color){
            break;
        }
        if ((*tempM)[xk+i][yk+i]->name == WB || (*tempM)[xk+i][yk+i]->name == WQ){
            return true;
        }
    }for (int i = 1; xk-i >= 0 && yk+i < 8; i++){
        if ((*tempM)[xk-i][yk+i]->color == (*tempM)[xk][yk]->color){
            break;
        }
        if ((*tempM)[xk-i][yk+i]->name == WB || (*tempM)[xk-i][yk+i]->name == WQ){
            return true;
        }

     }for (int i = 1; xk+i < 8 && yk-i >= 0; i++){
        if ((*tempM)[xk+i][yk-i]->color == (*tempM)[xk][yk]->color){
            break;
        }
        if ((*tempM)[xk+i][yk-i]->name == WB || (*tempM)[xk+i][yk-i]->name == WQ){
            return true;
        }
    }
    if ((*tempM)[xk+1][yk+1]->name == WP || (*tempM)[xk-1][yk+1]->name == WP)
        return true;
    return false;
}

bool checkWhite(QPointF startPos, QPointF endPos){
    std::vector<std::vector<Figure*>> temp = *matrix;
    std::vector<std::vector<Figure*>>* tempM = &temp;
    int xs = (int) startPos.x()/80;
    int ys = (int) startPos.y()/80;
    int xf = (int) endPos.x()/80;
    int yf = (int) endPos.y()/80;
    (*tempM)[xf][yf] = (*tempM)[xs][ys];
    (*tempM)[xs][ys] = nullptr;

    int xk = -1;
    int yk = -1;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ((*tempM)[i][j]) {
                if ((*tempM)[i][j]->name == WKK){
                    xk = i;
                    yk = j;
                    break;
                }
            }
        }
        if (xk>=0){
            break;
        }
    }

    if (xk - 2 >= 0){
        if (yk-1 >= 0){
            if ((*tempM)[xk-2][yk-1]->name == BK)
                return true;
        }
        if (yk+1 <= 7){
            if ((*tempM)[xk-2][yk+1]->name == BK)
                return true;
        }
    }if (xk + 2 <= 7){
        if (yk-1 >= 0){
            if ((*tempM)[xk+2][yk-1]->name == BK)
                return true;
        }
        if (yk+1 <= 7){
            if ((*tempM)[xk+2][yk+1]->name == BK)
                return true;
        }
    }if (yk - 2 >= 0){
        if (xk-1 >= 0){
            if ((*tempM)[xk-1][yk-2]->name == BK)
                return true;
        }
        if (xk+1 <= 7){
            if ((*tempM)[xk+1][yk-2]->name == BK)
                return true;
        }
    }if (yk + 2 <= 7){
        if (xk-1 >= 0){
            if ((*tempM)[xk-1][yk+2]->name == BK)
                return true;
        }
        if (xk+1 <= 7){
            if ((*tempM)[xk+1][yk+2]->name == BK)
                return true;
        }
    }

//    for (int i = xk; i > 0 ; i--){
//        if ((*tempM)[i][yk]->color == (*tempM)[xk][yk]->color){
//            break;
//        }
//        if ((*tempM)[i][yk]->name == BR || (*tempM)[i][yk]->name == BQ){
//            return true;
//        }
//    }
//    for (int i = xk; i < 8 ; i++){
//        if ((*tempM)[i][yk]->color == (*tempM)[xk][yk]->color){
//            break;
//        }
//        if ((*tempM)[i][yk]->name == BR || (*tempM)[i][yk]->name == BQ){
//            return true;
//        }
//    }
//    for (int i = yk; i > 0 ; i--){
//        if ((*tempM)[xk][i]->color == (*tempM)[xk][i]->color){
//            break;
//        }
//        if ((*tempM)[xk][i]->name == BR || (*tempM)[xk][i]->name == BQ){
//            return true;
//        }
//    }
//    for (int i = yk; i < 8 ; i++){
//        if ((*tempM)[xk][i]->color == (*tempM)[xk][i]->color){
//            break;
//        }
//        if ((*tempM)[xk][i]->name == BR || (*tempM)[xk][i]->name == BQ){
//            return true;
//        }
//    }
//    for (int i = 1; xk-i >= 0 && yk-i >= 0; i++){
//        if ((*tempM)[xk-i][yk-i]->color == (*tempM)[xk][yk]->color){
//            break;
//    }
//        if ((*tempM)[xk-i][yk-i]->name == BB || (*tempM)[xk-i][yk-i]->name == BQ){
//            return true;
//        }

//    }for (int i = 1; xk+i < 8 && yk+i < 8; i++){
//        if ((*tempM)[xk+i][yk+i]->color == (*tempM)[xk][yk]->color){
//            break;
//        }
//        if ((*tempM)[xk+i][yk+i]->name == BB || (*tempM)[xk+i][yk+i]->name == BQ){
//            return true;
//        }
//    }for (int i = 1; xk-i >= 0 && yk+i < 8; i++){
//        if ((*tempM)[xk-i][yk+i]->color == (*tempM)[xk][yk]->color){
//            break;
//        }
//        if ((*tempM)[xk-i][yk+i]->name == BB || (*tempM)[xk-i][yk+i]->name == BQ){
//            return true;
//        }

//     }for (int i = 1; xk+i < 8 && yk-i >= 0; i++){
//        if ((*tempM)[xk+i][yk-i]->color == (*tempM)[xk][yk]->color){
//            break;
//        }
//        if ((*tempM)[xk+i][yk-i]->name == BB || (*tempM)[xk+i][yk-i]->name == BQ){
//            return true;
//        }
//    }
//    if ((*tempM)[xk+1][yk-1]->name == BP || (*tempM)[xk-1][yk-1]->name == BP)
//        return true;
    return false;
}

bool isMovementPossible (int fig, QPointF startPos, QPointF endPos){ //задание условий хождения фигур

    int xs = (int) startPos.x()/80;
    int ys = (int) startPos.y()/80;
    int xf = (int) endPos.x()/80;
    int yf = (int) endPos.y()/80;
    if (moveOrder != (*matrix)[xs][ys]->color){
        return false;
    }
    if ((*matrix)[xf][yf]){
        if( (*matrix)[xf][yf]->color == (*matrix)[xs][ys]->color){
            return false;
        }
    }
    if (!(*matrix)[xs][ys]->color) {
        checkWhite(startPos, endPos);
    } else {
        checkBlack(startPos, endPos);
    }
    switch(fig){
        case BP:{
            if (xs == xf){
                if ((yf - ys ) == 1){
                    if ((*matrix)[xf][yf]){
                        return false;
                    }
                    if (yf == 7){

                        (*matrix)[xs][ys]->remove();
                        Figure* blackQueen = new Figure(blackQueenimg,chessboard, BQ);
                        blackQueen->setPosition(xf*80,yf*80);
                        (*matrix)[xf][yf] = blackQueen;
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }

                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                else if ((yf - ys) == 2){
                    if ((*matrix)[xf][yf] || (*matrix)[xf][yf-1]){
                        return false;
                    }

                    else{

                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                }
                else {
                    return false;
                }

            } else{
                if (abs(xs-xf) == 1 && (yf-ys) == 1){

                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;

                        if (yf == 7){
                            (*matrix)[xf][yf]->remove();
                            Figure* blackQueen = new Figure(blackQueenimg,chessboard, BQ);
                            blackQueen->setPosition(xf*80,yf*80);
                            (*matrix)[xf][yf] = blackQueen;
                            (*matrix)[xs][ys] = nullptr;
                            return true;
                        }
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                return false;
            }
        }
        case WP:{
            if (xs == xf){
                if ((ys - yf ) == 1){
                    if ((*matrix)[xf][yf]){
                        return false;
                    }
                    if (yf == 0){

                        (*matrix)[xs][ys]->remove();
                        Figure* whiteQueen = new Figure(whiteQueenimg,chessboard, WQ);
                        whiteQueen->setPosition(xf*80,yf*80);
                        (*matrix)[xf][yf] = whiteQueen;
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    else{

                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                    }
                }
                else if ((ys - yf) == 2 && ys == 6){
                    if ((*matrix)[xf][yf] || (*matrix)[xf][yf+1]){
                        return false;
                    }

                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }

                else {
                    return false;
                }

            } else{
                if (abs(xs-xf) == 1 && (ys-yf) == 1){

                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        if (yf == 0){

                            (*matrix)[xf][yf]->remove();
                            Figure* whiteQueen = new Figure(whiteQueenimg,chessboard, WQ);
                            whiteQueen->setPosition(xf*80,yf*80);
                            (*matrix)[xf][yf] = whiteQueen;
                            (*matrix)[xs][ys] = nullptr;
                            return true;
                        }
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                return false;
            }
        }
        case BR:{
            if ((xs == xf) && (yf != ys)){
                if (ys > yf){
                    for (int i = yf+1; i < ys; i++){
                        if ((*matrix)[xs][i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    else{
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                    }
                }

                else if (ys < yf){
                    for (int i = ys+1; i < yf; i++){
                        if ((*matrix)[xs][i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    else{
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                    }
                }
            }
            if ((ys == yf) && (xf != xs)){
                if (xs > xf){
                    for (int i = xf+1; i < xs; i++){
                        if ((*matrix)[i][ys]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                else if (xs < xf){
                    for (int i = xs+1; i < xf; i++){
                        if ((*matrix)[i][ys]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
            }
        }
        case WR:{
            if ((xs == xf) && (yf != ys)){
                if (ys > yf){
                    for (int i = yf+1; i < ys; i++){
                        if ((*matrix)[xs][i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    else{
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                    }
                }
                else if (ys < yf){
                    for (int i = ys+1; i < yf; i++){
                        if ((*matrix)[xs][i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    else{
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                    }
                }
            }
            if ((ys == yf) && (xf != xs)){
                if (xs > xf){
                    for (int i = xf+1; i < xs; i++){
                        if ((*matrix)[i][ys]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                else if (xs < xf){
                    for (int i = xs+1; i < xf; i++){
                        if ((*matrix)[i][ys]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }

            }

        }
        case BB:{
            if (abs(xs-xf) == abs(ys-yf)){
                if (xs > xf && ys > yf){
                    for (int i = 1; i < (xs-xf); i++){
                        if ((*matrix)[xf+i][yf+i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xf > xs && yf > ys){
                    for (int i = 1; i < (xf-xs); i++){
                        if ((*matrix)[xs+i][ys+i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xs > xf && ys < yf){
                    for (int i = 1; i < (xs-xf); i++){
                        if ((*matrix)[xf+i][yf-i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xf > xs && yf < ys){
                    for (int i = 1; i < (xf-xs); i++){
                        if ((*matrix)[xs+i][ys-i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
            }
        }
        case WB:{
            if (abs(xs-xf) == abs(ys-yf)){
                if (xs > xf && ys > yf){
                    for (int i = 1; i < (xs-xf); i++){
                        if ((*matrix)[xf+i][yf+i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xf > xs && yf > ys){
                    for (int i = 1; i < (xf-xs); i++){
                        if ((*matrix)[xs+i][ys+i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xs > xf && ys < yf){
                    for (int i = 1; i < (xs-xf); i++){
                        if ((*matrix)[xf+i][yf-i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xf > xs && yf < ys){
                    for (int i = 1; i < (xf-xs); i++){
                        if ((*matrix)[xs+i][ys-i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
            }
        }
        case BK:{
            if ((abs(xf-xs) == 2 && abs(yf-ys) == 1) || (abs(xf-xs) == 1 && abs(yf-ys) == 2)){
                if ((*matrix)[xf][yf]){
                    (*matrix)[xf][yf]->remove();
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                (*matrix)[xf][yf] = (*matrix)[xs][ys];
                (*matrix)[xs][ys] = nullptr;
                return true;
            }
        }
        case WK:{
            if ((abs(xf-xs) == 2 && abs(yf-ys) == 1) || (abs(xf-xs) == 1 && abs(yf-ys) == 2)){
                if ((*matrix)[xf][yf]){
                    (*matrix)[xf][yf]->remove();
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                (*matrix)[xf][yf] = (*matrix)[xs][ys];
                (*matrix)[xs][ys] = nullptr;
                return true;
            }
        }
        case BQ:{
            if (abs(xs-xf) == abs(ys-yf)){
                if (xs > xf && ys > yf){
                    for (int i = 1; i < (xs-xf); i++){
                        if ((*matrix)[xf+i][yf+i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xf > xs && yf > ys){
                    for (int i = 1; i < (xf-xs); i++){
                        if ((*matrix)[xs+i][ys+i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xs > xf && ys < yf){
                    for (int i = 1; i < (xs-xf); i++){
                        if ((*matrix)[xf+i][yf-i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xf > xs && yf < ys){
                    for (int i = 1; i < (xf-xs); i++){
                        if ((*matrix)[xs+i][ys-i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
            }
            if ((xs == xf) && (yf != ys)){
                if (ys > yf){
                    for (int i = yf+1; i < ys; i++){
                        if ((*matrix)[xs][i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    else{
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                    }
                }

                else if (ys < yf){
                    for (int i = ys+1; i < yf; i++){
                        if ((*matrix)[xs][i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    else{
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                    }
                }
            }
            if ((ys == yf) && (xf != xs)){
                if (xs > xf){
                    for (int i = xf+1; i < xs; i++){
                        if ((*matrix)[i][ys]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                else if (xs < xf){
                    for (int i = xs+1; i < xf; i++){
                        if ((*matrix)[i][ys]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
            }
        }
        case WQ:{
            if (abs(xs-xf) == abs(ys-yf)){
                if (xs > xf && ys > yf){
                    for (int i = 1; i < (xs-xf); i++){
                        if ((*matrix)[xf+i][yf+i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xf > xs && yf > ys){
                    for (int i = 1; i < (xf-xs); i++){
                        if ((*matrix)[xs+i][ys+i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xs > xf && ys < yf){
                    for (int i = 1; i < (xs-xf); i++){
                        if ((*matrix)[xf+i][yf-i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                if (xf > xs && yf < ys){
                    for (int i = 1; i < (xf-xs); i++){
                        if ((*matrix)[xs+i][ys-i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
            }
            if ((xs == xf) && (yf != ys)){
                if (ys > yf){
                    for (int i = yf+1; i < ys; i++){
                        if ((*matrix)[xs][i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    else{
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                    }
                }

                else if (ys < yf){
                    for (int i = ys+1; i < yf; i++){
                        if ((*matrix)[xs][i]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    else{
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                    }
                }
            }
            if ((ys == yf) && (xf != xs)){
                if (xs > xf){
                    for (int i = xf+1; i < xs; i++){
                        if ((*matrix)[i][ys]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
                else if (xs < xf){
                    for (int i = xs+1; i < xf; i++){
                        if ((*matrix)[i][ys]){
                            return false;
                        }
                    }
                    if ((*matrix)[xf][yf]){
                        (*matrix)[xf][yf]->remove();
                        (*matrix)[xf][yf] = (*matrix)[xs][ys];
                        (*matrix)[xs][ys] = nullptr;
                        return true;
                    }
                    (*matrix)[xf][yf] = (*matrix)[xs][ys];
                    (*matrix)[xs][ys] = nullptr;
                    return true;
                }
            }
        }
        case BKK:{
            if (abs(xf-xs) >1 || abs(yf-ys) > 1){
                return false;
            }

            if ((*matrix)[xf][yf]){
                (*matrix)[xf][yf]->remove();
                (*matrix)[xf][yf] = (*matrix)[xs][ys];
                (*matrix)[xs][ys] = nullptr;
                return true;
            }
            (*matrix)[xf][yf] = (*matrix)[xs][ys];
            (*matrix)[xs][ys] = nullptr;
            return true;
        }
        case WKK:{
            if (abs(xf-xs) >1 || abs(yf-ys) > 1){
                return false;
            }
            if (checkWhite(startPos, endPos))
                return false;
            if ((*matrix)[xf][yf]){
                (*matrix)[xf][yf]->remove();
                (*matrix)[xf][yf] = (*matrix)[xs][ys];
                (*matrix)[xs][ys] = nullptr;
                return true;
            }
            (*matrix)[xf][yf] = (*matrix)[xs][ys];
            (*matrix)[xs][ys] = nullptr;
            return true;
        }
    default: return false;
    }
}




int main(int argc, char *argv[])
{
    matrix = new std::vector<std::vector<Figure*>>();
    for (size_t i = 0; i < 8; i++){
        (*matrix).push_back(std::vector<Figure*> ());
        for (int j = 0; j <8; j++){
            (*matrix)[i].push_back(nullptr);
        }
        if (i == 0 || i == 7){
            (*matrix)[i].push_back(nullptr);
        }
    }
    moveOrder = false;

    QApplication a(argc, argv);


    chessboard = new QGraphicsPixmapItem(QPixmap::fromImage(chessBoardimg));
    QGraphicsScene scene(0,0,640,640);
    scene.addItem(chessboard);
    QGraphicsView view(&scene);
    std::vector<std::vector<QGraphicsRectItem*>> vectr;

    for (int i = 0; i < 8; i++){ //начальная расстановка фигур на доску
        for (int j = 0; j < 8; j++){
            if (j == 6){
                Figure* whitePawn = new Figure(whitePawnimg,chessboard, WP);
                whitePawn->setPosition(i*80,j*80);
                (*matrix)[i][j] = whitePawn;
            }
            if (j == 1){
                Figure* blackPawn = new Figure(blackPawnimg,chessboard, BP);
                blackPawn->setPosition(i*80,j*80);
                (*matrix)[i][j] = blackPawn;
            }
            if (j == 0){
                if (i == 0 || i == 7){
                    Figure* blackRook = new Figure(blackRookimg,chessboard, BR);
                    blackRook->setPosition(i*80,j*80);
                    (*matrix)[i][j] = blackRook;
                }
                if (i == 2 || i == 5){
                    Figure* blackBishop = new Figure(blackBishopimg,chessboard, BB);
                    blackBishop->setPosition(i*80,j*80);
                    (*matrix)[i][j] = blackBishop;
                }
                if (i == 1 || i == 6){
                    Figure* blackKnight = new Figure(blackKnightimg,chessboard, BK);
                    blackKnight->setPosition(i*80,j*80);
                    (*matrix)[i][j] = blackKnight;
                }
                if (i == 3){
                    Figure* blackQueen = new Figure(blackQueenimg,chessboard, BQ);
                    blackQueen->setPosition(i*80,j*80);
                    (*matrix)[i][j] = blackQueen;
                }
                if (i == 4){
                    Figure* blackKing = new Figure(blackKingimg,chessboard, BKK);
                    blackKing->setPosition(i*80,j*80);
                    (*matrix)[i][j] = blackKing;
                }
            }
            if (j == 7 ){
                if (i == 0 || i == 7){
                    Figure* whiteRook = new Figure(whiteRookimg,chessboard, WR);
                    whiteRook->setPosition(i*80,j*80);
                    (*matrix)[i][j] = whiteRook;
                }
                if (i == 2 || i == 5){
                    Figure* whiteBishop = new Figure(whiteBishopimg,chessboard, WB);
                    whiteBishop->setPosition(i*80,j*80);
                    (*matrix)[i][j] = whiteBishop;
                }
                if (i == 1 || i == 6){
                    Figure* whiteKnight = new Figure(whiteKnightimg,chessboard, WK);
                    whiteKnight->setPosition(i*80,j*80);
                    (*matrix)[i][j] = whiteKnight;
                }
                if (i == 3){
                    Figure* whiteQueen = new Figure(whiteQueenimg,chessboard, WQ);
                    whiteQueen->setPosition(i*80,j*80);
                    (*matrix)[i][j] = whiteQueen;
                }
                if (i == 4){
                    Figure* whiteKing = new Figure(whiteKingimg,chessboard, WKK);
                    whiteKing->setPosition(i*80,j*80);
                    (*matrix)[i][j] = whiteKing;
                }
            }
        }
    }
    view.show();
    return a.exec();
}
