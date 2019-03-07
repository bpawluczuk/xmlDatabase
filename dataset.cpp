//
// Created by Borys Pawluczuk on 07/03/2019.
//

#include "dataset.h"

void DataSet::setRecordList(list<Record *> records) {

    DataSet::records = records;
    vector<const char *> headerVector;

    for (auto record: records) {
        vector<const char *> columnVector;
        for (auto column: record->getColumns()) {
            columnVector.push_back(column->getValue());
        }
        DataSet::rows.push_back(columnVector);
    }

    for (auto record: records) {
        for (auto column: record->getColumns()) {
            headerVector.push_back(column->getKey());
        }
        break;
    }

    DataSet::rowsCount = records.size();
    DataSet::columnCount = headerVector.size();
    DataSet::columnNames = headerVector;
}

int DataSet::getRowCount() {
    return DataSet::rowsCount;
}

int DataSet::getColumnCount() {
    return DataSet::columnCount;
}

const char *DataSet::getColumnName(int indexColumn) {
    if (indexColumn < DataSet::columnCount) {
        return DataSet::columnNames[indexColumn];
    }
    return nullptr;
}

const char *DataSet::getCellValue(int indexRow, int indexColumn) {
    if (indexColumn < DataSet::columnCount && indexRow < DataSet::rowsCount) {
        return DataSet::rows[indexRow][indexColumn];
    }
    return nullptr;
}