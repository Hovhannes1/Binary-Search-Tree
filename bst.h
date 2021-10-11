#ifndef BST_H
#define BST_H

#include <QPointF>
#include <iostream>
#include <QPair>
#include <vector>
#include <QPainter>
#include <cmath>

class BST
{
public:
    BST(int const& key);
    ~BST();

    int nbNode() const;
    void insert(int const& key);
    bool deleteNode(BST node);
    int getHeight() const;
    int nbChildrenAtHeight(int h) const;
    void placeNode(std::vector<QPair<int,int>>& Nh, int const& h);
    void draw(QPainter &painter);
    BST * findAndSelect(int key);
    BST * getNodeInPosition(int ix, int iy, QPainter *painter);

    BST* leftChild;
    BST* rightChild;
    BST* parent;
    bool selected = false;
    int key;

private:

    QPointF position;
    float radius = 30;
};

#endif // BST_H
