//
// Created by Borys Pawluczuk on 26/02/2019.
//
#include "record.h"

void Record::addColumn(Column *column) {
    Record::ownColumns.push_back(column);
}

vector<Column *> Record::getColumns() {
    return Record::ownColumns;
}

const char *Record::getId() {
    for (auto column : Record::ownColumns) {
        if (strcmp(column->getKey(), "ID") == 0) {
            return column->getValue();
        }
    }
    return nullptr;
}

const char *Record::getColumnValue(const char *name) {
    for (auto column : Record::ownColumns) {
        if (strcmp(column->getKey(), name) == 0) {
            return column->getValue();
        }
    }
    return nullptr;
}

void Record::updateColumnValue(const char *key, const char *value) {
    for (auto column : Record::ownColumns) {
        if (strcmp(column->getKey(), key) == 0) {
            column->setValue(value);
        }
    }
}

void Record::updateColumnValue(Column *updateColumn) {
    for (auto column : Record::ownColumns) {
        if (strcmp(column->getKey(), updateColumn->getKey()) == 0) {
            column->setValue(updateColumn->getValue());
        }
    }
}

void Record::updateColumnValue(vector<Column *> updateColumns) {
    for (auto update : updateColumns) {
        for (auto column : Record::ownColumns) {
            if (strcmp(column->getKey(), update->getKey()) == 0) {
                column->setValue(update->getValue());
            }
        }
    }
}