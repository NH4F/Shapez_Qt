#ifndef FACILITY_H
#define FACILITY_H

#include "qdebug.h"
#include <QString>

// 前置声明
class GridCell;
//--------------------------Base-------------------------
class Facility {
protected:
    int rate;                 // 处理速率
    bool isActive;            // 是否启用
    QString direction;        // 方向
    QString facilityType;     // 设施类型标识
    GridCell* parentCell;     // 绑定网格

public:
    Facility(GridCell* cell);
    virtual ~Facility();

    // 属性接口
    QString getDirection() const;
    QString getFacilityType() const;
    void setDirection(const QString& newDirection);
    GridCell* getParentCell() const;

    virtual void operate() = 0;
};
//--------------------------Subclass------------------------

//--------------------------Test----------------------------
class TestFacility : public Facility {
public:
    TestFacility(GridCell* cell) : Facility(cell) {}
    void operate() override {
        // 测试实现，输出日志或模拟行为
        qDebug() << "TestFacility operating";
    }
};


#endif // FACILITY_H
