//
// Created by Borys Pawluczuk on 24/02/2019.
//

#ifndef XMLDATABASE_COLUMN_H
#define XMLDATABASE_COLUMN_H

#endif //XMLDATABASE_COLUMN_H
#include <iostream>

using namespace std;

class Column{
public:

    Column(const char *key, const char *value){
        Column::setKey(key);
        Column::setValue(value);
    }

    void setKey(const char *key) {
        Column::key = key;
    }
    void setValue(const char *value) {
        Column::value = value;
    }
    const char *getKey() const {
        return key;
    }
    const char *getValue() const {
        return value;
    }

private:
    const char *key;
    const char *value;
};