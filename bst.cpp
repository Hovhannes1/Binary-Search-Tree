#include "bst.h"
#include <QString>
#include <QDebug>

BST::BST(int const& key) :
      leftChild(nullptr),
      rightChild(nullptr),
      parent(nullptr),
      key(key),
      position()
{

}

BST::~BST()
{
    if (leftChild != nullptr)
    {
        delete leftChild;
        leftChild = nullptr;
    }
    if (rightChild != nullptr)
    {
        delete rightChild;
        rightChild = nullptr;
    }
}


int BST::nbNode() const
{
    int total = 0;
    if (leftChild != nullptr)
    {
        total +=  leftChild->nbNode();
    }
    if (rightChild != nullptr)
    {
        total +=  rightChild->nbNode();
    }
    return total + 1;
}

void BST::insert(const int &key)
{
    if (key < this->key)
    {
        if (leftChild !=nullptr)
        {
            leftChild->insert(key);
        }
        else
        {
            leftChild = new BST(key);
            leftChild->parent = this;
        }
    }
    else if (key > this->key)
    {
        if (rightChild !=nullptr)
        {
            rightChild->insert(key);
        }
        else
        {
            rightChild = new BST(key);
            rightChild->parent = this;
        }
    }
}

int BST::getHeight() const
{
    return std::max(
                this->rightChild == nullptr ? 0 : this->rightChild->getHeight(),
               this->leftChild == nullptr ? 0 : this->leftChild->getHeight()) + 1;

}

int BST::nbChildrenAtHeight(int h) const
{
    int total = 0;
    if(h == 0) return 1;
    if (this->leftChild != nullptr)
    {
        total +=  this->leftChild->nbChildrenAtHeight(h - 1);
    }
    if (this->rightChild != nullptr)
    {
        total +=  this->rightChild->nbChildrenAtHeight(h-1);
    }
    return total;
}


void BST::placeNode(std::vector<QPair<int,int>>& Nh, int const& h)
{
    if(this->parent == nullptr) {
        int height = this->getHeight();
        for (int i = 0; i < height; i++) {
            Nh.push_back({nbChildrenAtHeight(i), 0});
        }
    }

    if (leftChild != nullptr)
    {
        leftChild->placeNode(Nh, h + 1);
    }

    if (rightChild != nullptr)
    {
        rightChild->placeNode(Nh, h + 1);
    }

    this->position.setX((Nh[h].second + 0.5) / Nh[h].first);
    this->position.setY((h + 0.5) / ((float)Nh.size()));
    Nh[h].second++;
}

void drawInnerText(QPainter & painter, qreal x, qreal y, Qt::Alignment flags,
              const QString & text)
{
    const qreal size = 32767.0;
    QPointF corner(x, y - size);
    if (flags & Qt::AlignHCenter) corner.rx() -= size/2.0;
    else if (flags & Qt::AlignRight) corner.rx() -= size;

    if (flags & Qt::AlignVCenter) corner.ry() += size/2.0003;
    else if (flags & Qt::AlignTop) corner.ry() += size;
    else flags |= Qt::AlignBottom;
    QRectF rect{corner.x(), corner.y(), size, size};
    painter.drawText(rect, flags, text);
}

void BST::draw(QPainter &painter)
{
    QBrush greenBrush(Qt::green,Qt::SolidPattern);
    QBrush redBrush(Qt::red,Qt::SolidPattern);
    QPen bluePen(Qt::blue);
    QPen redPen(Qt::red);
    QPen blackPen(Qt::black);
    bluePen.setWidth(3);
    redPen.setWidth(3);
    blackPen.setWidth(2);



    QFont serifFont("Times", 16, QFont::Normal);
    painter.setFont(serifFont);
    painter.save();

    float x = position.x()*painter.device()->width();
    float y = position.y()*painter.device()->height();

    float xCh;
    float yCh;

    if (this->leftChild != nullptr)
    {
        xCh = this->leftChild->position.x()*painter.device()->width();
        yCh = this->leftChild->position.y()*painter.device()->height();
        painter.setPen(bluePen);
        painter.drawLine(x, y, xCh, yCh);
        this->leftChild->draw(painter);
    }
    if (this->rightChild != nullptr)
    {
        xCh = this->rightChild->position.x()*painter.device()->width();
        yCh = this->rightChild->position.y()*painter.device()->height();
        painter.setPen(redPen);
        painter.drawLine(x, y, xCh, yCh);
        this->rightChild->draw(painter);
    }
    if (this->selected) {
        painter.setBrush(redBrush);
    } else {
        painter.setBrush(greenBrush);
    }

    painter.setPen(blackPen);
    painter.drawEllipse(x - radius, y - radius, 2 * radius, 2 * radius);
    drawInnerText(painter, x, y + 2, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(this->key));
}

BST *BST::findAndSelect(int key)
{
    if (key == this->key) {
        this->selected = true;
        return this;
    } else if (key > this->key) {
        if (this->rightChild !=nullptr)
        {
            BST* res = this->rightChild->findAndSelect(key);
            if (res != nullptr)
            {
                return res;
            }
        }
    } else if (key < this->key) {
        if (this->leftChild !=nullptr)
        {
            BST* res = this->leftChild->findAndSelect(key);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}

BST *BST::getNodeInPosition(int ix, int iy, QPainter *painter)
{
    float px = this->position.x()*painter->device()->width();
    float py =  this->position.y()*painter->device()->height();
    if (std::pow(px-ix, 2) + std::pow(py-iy, 2) < radius*radius)
    {
        this->selected = true;
        return this;
    } else {
        if(this->leftChild != nullptr ) {
            BST* res = this->leftChild->getNodeInPosition(ix, iy, painter);
            if (res != nullptr)
            {
                return res;
            }
        }
        if(this->rightChild != nullptr ) {
             BST* res =  this->rightChild->getNodeInPosition(ix, iy, painter);
            if (res != nullptr)
            {
                return res;
            }
        }
    }

    return nullptr;
}

bool BST::deleteNode(BST )
{
    // TO be implemented in future
    return false;
}
