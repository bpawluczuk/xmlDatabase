//
// Created by Borys Pawluczuk on 24/02/2019.
//

#ifndef XMLDATABASE_RECORD_H
#define XMLDATABASE_RECORD_H

#endif //XMLDATABASE_RECORD_H

#include <map>
#include <vector>
#include "column.h"

class Record {
public:
    void addColumn(Column *column) {
        Record::ownColumns.push_back(column);
    }

    vector<Column *> getColumns() {
        return Record::ownColumns;
    }

    const char *getId() {
        for (auto column : Record::ownColumns) {
            if (strcmp(column->getKey(), "ID") == 0) {
                return column->getValue();
            }
        }
        return nullptr;
    }

    const char *getColumnValue(const char *name) {
        for (auto column : Record::ownColumns) {
            if (strcmp(column->getKey(), name) == 0) {
                return column->getValue();
            }
        }
        return nullptr;
    }

    void updateColumnValue(const char *key, const char *value) {
        for (auto column : Record::ownColumns) {
            if (strcmp(column->getKey(), key) == 0) {
                column->setValue(value);
            }
        }
    }

    void updateColumnValue(Column *updateColumn) {
        for (auto column : Record::ownColumns) {
            if (strcmp(column->getKey(), updateColumn->getKey()) == 0) {
                column->setValue(updateColumn->getValue());
            }
        }
    }

    void updateColumnValue(vector<Column *> updateColumns) {
        for (auto update : updateColumns) {
            for (auto column : Record::ownColumns) {
                if (strcmp(column->getKey(), update->getKey()) == 0) {
                    column->setValue(update->getValue());
                }
            }
        }
    }

private:
    vector<Column *> ownColumns;
};