//
// Created by Borys Pawluczuk on 26/02/2019.
//
#include "record.h"

Record::Record(int index) {
    Record::setIndex(index);
}

void Record::addColumn(Column *column) {
    Record::columns.push_back(column);
}

vector<Column *> Record::getColumns() {
    return Record::columns;
}

const char *Record::getId() {
    for (auto column : Record::columns) {
        if (strcmp(column->getKey(), "ID") == 0) {
            return column->getValue();
        }
    }
    return nullptr;
}

const char *Record::getColumnValue(const char *name) {
    for (auto column : Record::columns) {
        if (strcmp(column->getKey(), name) == 0) {
            return column->getValue();
        }
    }
    return "";
}

void Record::setIndex(int index) {
    Record::index = index;
}

int Record::getIndex() const {
    return index;
}
