//
// Created by Borys Pawluczuk on 26/02/2019.
//

#include "column.h"

Column::Column(const char *key, const char *value, int index){
    Column::setKey(key);
    Column::setValue(value);
    Column::setIndex(index);
}

void Column::setKey(const char *key) {
    if(key){
        Column::key = key;
    }else{
        Column::key = "";
    }
}

void Column::setValue(const char *value) {
    if(value){
        Column::value = value;
    }else{
        Column::value = "";
    }
}

const char *Column::getKey() const {
    return key;
}

const char *Column::getValue() const {
    return value;
}

void Column::setIndex(int index) {
    Column::index = index;
}

int Column::getIndex() const {
    return index;
}
