#include <QApplication>
#include "Game.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Game game(10, 10, 50);

    game.start();
    // test
    game.test();

    return app.exec();
}
