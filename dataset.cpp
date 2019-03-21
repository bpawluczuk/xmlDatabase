//
// Created by Borys Pawluczuk on 07/03/2019.
//

#include "dataset.h"

void DataSet::setRecordList(list<Record *> records) {

    DataSet::records = records;


    for (auto record: records) {
        vector<string> columnVector;
        for (auto column: record->getColumns()) {
            columnVector.push_back(string(column->getValue()));
        }
        DataSet::rows.push_back(columnVector);
    }

    for (auto record: records) {
        for (auto column: record->getColumns()) {
            DataSet::columnNames.push_back(string(column->getKey()));
        }
        break;
    }

    DataSet::rowsCount = records.size();
    DataSet::columnCount = DataSet::columnNames.size();
}

int DataSet::getRowCount() {
    return DataSet::rowsCount;
}

int DataSet::getColumnCount() {
    return DataSet::columnCount;
}

string DataSet::getColumnName(int indexColumn) {

    if (indexColumn < DataSet::columnCount) {
        return DataSet::columnNames[indexColumn];
    }
    return "";
}

string DataSet::getCellValue(int indexRow, int indexColumn) {
    if (indexColumn < DataSet::columnCount && indexRow < DataSet::rowsCount) {
        return DataSet::rows[indexRow][indexColumn];
    }
    return "";
}

string DataSet::getRecordId(int indexRow) {
    if (indexRow < DataSet::rowsCount) {
        return DataSet::rows[indexRow][0];
    }
    return "0";
}