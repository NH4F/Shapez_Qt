#include "facility.h"
#include "gridcell.h"

// construct and destruct
Facility::Facility(GridCell* cell) : parentCell(cell) {
}

Facility::~Facility() {
    if (parentCell) {
        parentCell->removeFacility();
    }
}
// -----------------------get attribute----------------------
QString Facility::getDirection() const {
    return direction;
}

QString Facility::getFacilityType() const {
    return facilityType;
}
GridCell* Facility::getParentCell() const{
    return parentCell;
}
// ------------------------method------------------------
void Facility::setDirection(const QString& newDirection) {
    direction = newDirection;
}



