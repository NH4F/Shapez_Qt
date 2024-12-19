#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <QString>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <unordered_map>

class ResourceManager {
public:
    static QPixmap getPixmap(const QString& path) {
        static std::unordered_map<QString, QPixmap> cache;
        if (cache.find(path) == cache.end()) {
            cache[path] = QPixmap(path);
        }
        return cache[path];
    }
};

enum class CellType {
    Empty,   // 空地块
    Mineral, // 矿物
    Center,  // 交付中心
    Facility // 设备（例如开采器）
};

// 前置声明
class Facility;

// 基础网格单元类
class GridCell {
protected:
    QString imagePath;
    int cellSize;
    CellType cellType;

public:
    int x, y;
    Facility* facility; // 改为原始指针，避免 `std::unique_ptr` 的析构问题

    GridCell(int x, int y, int cellSize, CellType type = CellType::Empty, const QString& imagePath = "");
    virtual ~GridCell();

    virtual void drawCell(QGraphicsScene* scene);

    CellType getCellType() const { return cellType; }
    void setCellType(CellType type) { cellType = type; }
    bool hasFacility() const;
    void removeFacility();
    void setFacility(Facility* newFacility); // 改用原始指针
};


// 中心点类
class Center : public GridCell {
public:
    Center(int x, int y, int cellSize);
};

// 矿物类
class Mineral : public GridCell {
protected:
    bool separable; // 是否可分离
    int value;      // 矿物价值

public:
    Mineral(int x, int y, int cellSize, bool separable, int value);
    int getValue() const { return value; }
};

// 圆形矿物类
class Circle : public Mineral {
public:
    Circle(int x, int y, int cellSize);
};

// 方形矿物类
class Square : public Mineral {
public:
    Square(int x, int y, int cellSize);
};

#endif // GRIDCELL_H
