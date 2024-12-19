#include "gridcell.h"
#include "facility.h"

// ------------------------- GridCell 实现 -------------------------
GridCell::GridCell(int x, int y, int cellSize, CellType type, const QString& imagePath)
    : imagePath(imagePath), cellSize(cellSize), cellType(type), x(x), y(y), facility(nullptr) {}

GridCell::~GridCell() {
    delete facility; // 确保释放内存
}

void GridCell::drawCell(QGraphicsScene* scene) {
    QPixmap pixmap = ResourceManager::getPixmap(imagePath);

    if (!pixmap.isNull()) {
        QGraphicsPixmapItem* item = scene->addPixmap(pixmap);

        // 将图片拉伸到网格大小
        item->setPos(x * cellSize, y * cellSize);
        item->setScale(1.0);

        item->setTransformationMode(Qt::SmoothTransformation);
        item->setPixmap(pixmap.scaled(cellSize, cellSize, Qt::IgnoreAspectRatio));
    }
}
bool GridCell::hasFacility() const {
    return facility != nullptr;
}

void GridCell::removeFacility() {
    delete facility; // 释放当前设施
    facility = nullptr;
}

void GridCell::setFacility(Facility* newFacility) {
    removeFacility(); // 先删除旧设施
    facility = newFacility;
}

// ------------------------- Center 实现 -------------------------
Center::Center(int x, int y, int cellSize)
    : GridCell(x, y, cellSize, CellType::Center, ":/mines/pics/center_black.png") {}

// ------------------------- Mineral 实现 -------------------------
Mineral::Mineral(int x, int y, int cellSize, bool separable, int value)
    : GridCell(x, y, cellSize, CellType::Mineral), separable(separable), value(value) {}

// ------------------------- Circle 实现 -------------------------
Circle::Circle(int x, int y, int cellSize)
    : Mineral(x, y, cellSize, true, 10) {
    imagePath = ":/mines/pics/circle.png";
}

// ------------------------- Square 实现 -------------------------
Square::Square(int x, int y, int cellSize)
    : Mineral(x, y, cellSize, false, 10) {
    imagePath = ":/mines/pics/square.png";
}
