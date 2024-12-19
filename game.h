#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <memory>
#include "map.h"

// 游戏类
class Game {
public:
    Game(int rows, int cols, int cellSize);
    ~Game();

    void start();      // 启动游戏
    void stop();       // 停止游戏
    void reset();      // 重置游戏
    void test();
public slots:
    void update();     // 游戏更新逻辑（用于每帧或周期性更新）

private:
    int rows, cols, cellSize;
    std::unique_ptr<QGraphicsScene> scene; // 使用智能指针管理资源
    std::unique_ptr<QGraphicsView> view;   // 使用智能指针管理资源
    std::unique_ptr<Map> map;              // 地图对象

    void setupScene(); // 初始化场景
    void setupView();  // 初始化视图
    void connectEvents(); // 连接事件处理
};

#endif // GAME_H
