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
    void addColumn(Column *column);

    vector<Column *> getColumns();

    const char *getId();

    const char *getColumnValue(const char *name);

    void updateColumnValue(const char *key, const char *value);

    void updateColumnValue(Column *updateColumn);

    void updateColumnValue(vector<Column *> updateColumns);

private:
    vector<Column *> ownColumns;
};