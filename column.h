//
// Created by Borys Pawluczuk on 24/02/2019.
//

#ifndef XMLDATABASE_COLUMN_H
#define XMLDATABASE_COLUMN_H

#endif //XMLDATABASE_COLUMN_H

#include <iostream>

using namespace std;

class Column {
public:

    Column(const char *key, const char *value);

    void setKey(const char *key);

    void setValue(const char *value);

    const char *getKey() const;

    const char *getValue() const;

private:
    const char *key;
    const char *value;
};