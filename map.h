#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include <QGraphicsScene>
#include "gridcell.h"

// 工厂类，用于创建各种类型的地块
class GridCellFactory {
public:
    static std::unique_ptr<GridCell> createCell(int x, int y, int cellSize, const QString& type);
};

// 地图类
class Map {
public:
    Map(int rows, int cols, int cellSize);
    ~Map();

    void generateMap(); // 生成地图
    void draw(QGraphicsScene* scene); // 绘制地图

    GridCell* getCell(int row, int col); // 获取指定单元格
    bool addFacility(int row, int col, Facility* facility); // 添加设施
    bool removeFacility(int row, int col); // 移除设施

private:
    int rows, cols, cellSize;
    std::vector<std::vector<GridCell*>> cells; // 使用原始指针存储网格

    void generateMinerals(); // 生成矿物
    void generateCenter();   // 生成交付中心
};


#endif // MAP_H
