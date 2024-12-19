#include "map.h"
#include <QGraphicsRectItem>
#include <random>

// ------------------- GridCellFactory 实现 -------------------
std::unique_ptr<GridCell> GridCellFactory::createCell(int x, int y, int cellSize, const QString& type) {
    if (type == "circle") {
        return std::make_unique<Circle>(x, y, cellSize);
    } else if (type == "square") {
        return std::make_unique<Square>(x, y, cellSize);
    } else if (type == "center") {
        return std::make_unique<Center>(x, y, cellSize);
    } else {
        return std::make_unique<GridCell>(x, y, cellSize); // 默认空地块
    }
}

// ------------------- Map 类实现 -------------------
// construct and destruct
Map::Map(int rows, int cols, int cellSize)
    : rows(rows), cols(cols), cellSize(cellSize) {
    // 初始化网格
    for (int i = 0; i < rows; ++i) {
        std::vector<GridCell*> row;
        for (int j = 0; j < cols; ++j) {
            row.push_back(new GridCell(i, j, cellSize)); // 默认创建空地块
        }
        cells.push_back(std::move(row));
    }
}

Map::~Map() {
    // 清理网格内存
    for (auto& row : cells) {
        for (auto& cell : row) {
            delete cell;
        }
    }
}

GridCell* Map::getCell(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        qDebug() << "Error: Out-of-bounds access to cell (" << row << ", " << col << ")";
        return nullptr;
    }
    return cells[row][col];
}

bool Map::addFacility(int row, int col, Facility* facility) {
    GridCell* cell = getCell(row, col);
    if (!cell) return false;

    if (cell->hasFacility()) {
        qDebug() << "Error: Cell (" << row << ", " << col << ") already has a facility.";
        return false;
    }

    cell->setFacility(facility);
    return true;
}

bool Map::removeFacility(int row, int col) {
    GridCell* cell = getCell(row, col);
    if (!cell) return false;

    if (!cell->hasFacility()) {
        qDebug() << "Error: Cell (" << row << ", " << col << ") has no facility to remove.";
        return false;
    }

    cell->removeFacility();
    return true;
}

void Map::generateMap() {
    generateMinerals();
    generateCenter();
}

void Map::generateMinerals() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 4);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int type = distrib(gen);

            if (type == 3) {
                delete cells[i][j];
                cells[i][j] = new Circle(i, j, cellSize);
            } else if (type == 4) {
                delete cells[i][j];
                cells[i][j] = new Square(i, j, cellSize);
            }
        }
    }
}

void Map::generateCenter() {
    int midX = cols / 2 - 1, midY = rows / 2 - 1;

    // 创建 2x2 交付中心
    for (int i = midY; i < midY + 2; ++i) {
        for (int j = midX; j < midX + 2; ++j) {
            delete cells[i][j];
            cells[i][j] = new Center(i, j, cellSize);
        }
    }
}

void Map::draw(QGraphicsScene* scene) {
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            // 绘制网格单元格
            cell->drawCell(scene);

            // 绘制网格边框
            scene->addRect(
                cell->x * cellSize,
                cell->y * cellSize,
                cellSize,
                cellSize,
                QPen(Qt::black)
                );
        }
    }
}


