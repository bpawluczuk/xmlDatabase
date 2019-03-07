//
// Created by Borys Pawluczuk on 24/02/2019.
//

#ifndef XMLDATABASE_COLUMN_H
#define XMLDATABASE_COLUMN_H

#endif //XMLDATABASE_COLUMN_H

#include <iostream>

using namespace std;

/**
 * class Column
 */
class Column {
public:

    /**
     *
     * @param key
     * @param value
     */
    Column(const char *key, const char *value, int index = 0);

    /**
     *
     * @param key
     */
    void setKey(const char *key);

    /**
     *
     * @param value
     */
    void setValue(const char *value);

    /**
     *
     * @return
     */
    const char *getKey() const;

    /**
     *
     * @return
     */
    const char *getValue() const;

    /**
     *
     * @param index
     */
    void setIndex(int index);

    /**
     *
     * @return
     */
    int getIndex() const;

private:

    /**
     *
     */
    const char *key;

    /**
     *
     */
    const char *value;

    /**
     *
    */
    int index;
};