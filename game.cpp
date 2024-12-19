#include "game.h"
#include "facility.h"
#include <QTimer>
#include <QDebug>

// ------------------- Game 类实现 -------------------

Game::Game(int rows, int cols, int cellSize)
    : rows(rows), cols(cols), cellSize(cellSize) {}

Game::~Game() {
    // 智能指针会自动释放资源
}

void Game::start() {
    qDebug() << "Game started";

    // 初始化场景和视图
    setupScene();
    setupView();

    // 创建地图
    map = std::make_unique<Map>(rows, cols, cellSize);
    map->generateMap();
    map->draw(scene.get());

    // 显示游戏窗口
    view->show();
}

void Game::stop() {
    qDebug() << "Game stopped";
    view->close();
}

void Game::reset() {
    qDebug() << "Game reset";
    // 清空场景并重新生成地图
    scene->clear();
    map->generateMap();
    map->draw(scene.get());
}

void Game::update() {
    // 游戏逻辑更新
    qDebug() << "Game updated";
    // 示例：地图中的内容可以在此更新
    // map->update(); // 如果 Map 类实现了 update 方法
}

void Game::setupScene() {
    scene = std::make_unique<QGraphicsScene>();
    scene->setBackgroundBrush(Qt::white); // 设置背景颜色
    qDebug() << "Scene setup completed";
}

void Game::setupView() {
    view = std::make_unique<QGraphicsView>(scene.get());
    view->setWindowTitle("Shapez-like Game with Minerals");
    view->resize(cols * cellSize + 50, rows * cellSize + 50);
    view->setRenderHint(QPainter::Antialiasing); // 抗锯齿
    qDebug() << "View setup completed";
}

void Game::test(){
    qDebug() << "Running Game::test()";

    // 创建测试地图
    map = std::make_unique<Map>(5, 5, 50); // 创建 5x5 的地图
    map->generateMap(); // 生成基础地图

    // 测试添加设施
    Facility* testFacility1 = new TestFacility(nullptr); // 使用派生类实例化
    if (map->addFacility(2, 2, testFacility1)) {
        qDebug() << "Successfully added facility at (2, 2)";
    } else {
        qDebug() << "Failed to add facility at (2, 2)";
    }

    // 测试重复添加设施（应失败）
    Facility* testFacility2 = new TestFacility(nullptr); // 使用派生类实例化
    if (map->addFacility(2, 2, testFacility2)) {
        qDebug() << "Unexpectedly succeeded in adding a second facility at (2, 2)";
    } else {
        qDebug() << "Correctly failed to add a second facility at (2, 2)";
    }

    // 测试删除设施
    if (map->removeFacility(2, 2)) {
        qDebug() << "Successfully removed facility from (2, 2)";
    } else {
        qDebug() << "Failed to remove facility from (2, 2)";
    }

    // 测试删除不存在的设施
    if (map->removeFacility(2, 2)) {
        qDebug() << "Unexpectedly succeeded in removing a non-existent facility from (2, 2)";
    } else {
        qDebug() << "Correctly failed to remove a non-existent facility from (2, 2)";
    }
}

