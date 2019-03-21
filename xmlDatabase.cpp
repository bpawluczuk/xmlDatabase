//
// Created by Borys Pawluczuk on 23/02/2019.
//
#include <iostream>
#include <map>
#include <sys/stat.h>
#include "xmlDatabase.h"
#include "tinyxml2-master/tinyxml2.h"
#include "tinyxml2-master/tinyxml2.cpp"
#include <stdio.h>
#include <string.h>
#include "dirent.h"

using namespace std;
using namespace tinyxml2;

XMLNode *XmlDatabase::xmlGetRootNode() {
    XMLNode *pRoot = XmlDatabase::xmlDocument.FirstChild();
    return pRoot;
}

const char *XmlDatabase::getDatabasePath() {
    return XmlDatabase::dbPath;
}

void XmlDatabase::setDatabasePath(const char *path) {
    XmlDatabase::dbPath = path;
}

int XmlDatabase::connect(const char *path) {

    XmlDatabase::setDatabasePath(path);

    XMLError result = XmlDatabase::xmlDocument.LoadFile(path);
    if (result != XML_SUCCESS) {
        cout << "Unable connect to database " << XmlDatabase::getDatabasePath() << endl;
        return false;
    }

    XMLNode *root = XmlDatabase::xmlGetRootNode();
    if (root == nullptr) {
        cout << "Wrong format database " << XmlDatabase::getDatabasePath() << endl;
        return false;
    }

    cout << "Connect to database " << XmlDatabase::getDatabasePath() << endl;
    return true;
}

int XmlDatabase::create(const char *name) {

    XmlDatabase::setDatabasePath(name);
    XMLNode *pRoot = XmlDatabase::xmlDocument.NewElement("Database");
    XmlDatabase::xmlDocument.InsertFirstChild(pRoot);

    XMLElement *pShema = XmlDatabase::xmlDocument.NewElement("Schema");
    pRoot->InsertFirstChild(pShema);
    pShema->SetAttribute("autoincrement", "0");

    XMLNode *pId = XmlDatabase::xmlDocument.NewElement("ID");
    pShema->InsertFirstChild(pId);

    XmlDatabase::saveFile();

    return true;
}

vector<string> XmlDatabase::getDatabaseList(const char *path){

    struct dirent *entry;
    vector<string> fileList;

    DIR *dir = opendir(path);
    if (dir == nullptr) {
        return fileList;
    }

    while ((entry = readdir(dir)) != nullptr) {
        printf("%s\n",entry->d_name);
        fileList.push_back(string(entry->d_name));
    }

    closedir(dir);
    return fileList;
}

void XmlDatabase::saveFile() {

    XMLError error = XmlDatabase::xmlDocument.SaveFile(XmlDatabase::getDatabasePath());
    if (error) {
        cout << "Can't save file: " << XmlDatabase::getDatabasePath() << endl;
    }
}

int XmlDatabase::getIndexCount(){

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    XMLElement *node = pRoot->FirstChildElement("Schema");
    const char *increment = node->Attribute("autoincrement");

    int inc = atoi(increment);
    inc++;

    node->SetAttribute("autoincrement",  inc);
    XmlDatabase::saveFile();

    return inc;
}

int XmlDatabase::insert(Record *record) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();
    int count = XmlDatabase::getIndexCount();

    XMLElement *pNode = XmlDatabase::xmlDocument.NewElement("Record");
    pNode->SetAttribute("type", "record");
    pRoot->InsertEndChild(pNode);

    for (auto schema : XmlDatabase::getSchema()) {

        XMLElement *pElement = XmlDatabase::xmlDocument.NewElement(schema);

        if (strcmp(schema, "ID") == 0) {
            pElement->SetText(count); // Autoincrement
        }

        for (auto column : record->getColumns()) {
            if (strcmp(schema, column->getKey()) == 0 && column->getValue() && strcmp(schema, "ID") != 0) {
                pElement->SetText(column->getValue());
            }
        }

        pNode->InsertEndChild(pElement);
    }

    XmlDatabase::saveFile();

    return true;
}

int XmlDatabase::columnCount() {
    return XmlDatabase::getSchema().size();
}

bool XmlDatabase::columnExist(const char *name) {

    vector<const char *> schema = XmlDatabase::getSchema();

    for (auto column : schema) {
        if (strcmp(column, name) == 0) {
            return true;
        }
    }
    return false;
}

vector<const char *> XmlDatabase::getSchema() {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    vector<const char *> result;

    for (XMLElement *node = pRoot->FirstChildElement("Schema"); node != nullptr; node = node->NextSiblingElement()) {
        for (XMLElement *child = node->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
            result.push_back(child->Name());
        }
        break;
    }

    return result;
}

bool XmlDatabase::removeColumn(const char *name) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    if (strcmp(name, "ID") == 0) {
        return false;
    }

    for (XMLElement *pSchema = pRoot->FirstChildElement("Schema"); pSchema != nullptr; pSchema = pSchema->NextSiblingElement()) {
        XMLElement *child = pSchema->FirstChildElement(name);
        if (child) {
            pSchema->DeleteChild(child);
        }
    }

    XmlDatabase::saveFile();

    return true;
}

bool XmlDatabase::insertColumn(const char *name) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    if (XmlDatabase::columnExist(name)) {
        return false;
    }

    for (XMLElement *node = pRoot->FirstChildElement("Schema"); node != nullptr; node = node->NextSiblingElement()) {
        XMLElement *pElement = XmlDatabase::xmlDocument.NewElement(name);
        node->InsertEndChild(pElement);
    }

    XmlDatabase::saveFile();

    return true;
}

void XmlDatabase::remove(const char *id) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();
    XMLNode *node = XmlDatabase::xmlFindRecordById(id);

    if (node) {
        pRoot->DeleteChild(node);
        XmlDatabase::saveFile();
    }
}

XMLNode *XmlDatabase::xmlFindRecordById(const char *id) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    for (XMLElement *node = pRoot->FirstChildElement("Record"); node != nullptr; node = node->NextSiblingElement()) {
        XMLElement *child = node->FirstChildElement("ID");
        if (child->GetText() && strcmp(child->GetText(), id) == 0) {
            return child->Parent();
        }
    }

    return nullptr;
}

Record *XmlDatabase::findRecordById(const char *id) {

    XMLNode *node = XmlDatabase::xmlFindRecordById(id);

    if (!node) {
        return nullptr;
    }

    Record *record = new Record();

    for (XMLElement *child = node->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        Column *column = new Column(child->Name(), child->GetText());
        record->addColumn(column);
    }

    return record;
}

void XmlDatabase::update(Record *record) {

    const char *id = record->getId();
    XMLNode *node = XmlDatabase::xmlFindRecordById(id);

    if (node) {
        vector<Column *> columns = record->getColumns();
        for (auto column : columns) {
            for (XMLElement *child = node->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
                if (strcmp(child->Name(), column->getKey()) == 0 && column->getValue()) {
                    child->SetText(column->getValue());
                }
            }
        }

        XmlDatabase::saveFile();
    }
}

list<Record *> XmlDatabase::select() {

    int indexColumn = 0;
    int indexRow = 0;

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();
    list<Record *> result;

    for (XMLElement *node = pRoot->FirstChildElement("Record"); node != nullptr; node = node->NextSiblingElement()) {
        Record *record = new Record(indexRow++);
        indexColumn = 0;
        for (XMLElement *child = node->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {

            Column *column = new Column(child->Name(), child->GetText(), indexColumn++);
            record->addColumn(column);
        }
        result.push_back(record);
    }

    XmlDatabase::dataSet.setRecordList(result);

    return result;
}

list<Record *> XmlDatabase::select(Record *where) {

    list<Record *> result;
    bool addRecord = false;
    bool isEmptyWhere = true;
    bool isDiferenceWhere = true;
    string word;
    string columnValue;
    const char *columnKey;
    vector<bool> compareWhere;

    for (auto column: where->getColumns()) {
        if(!string(column->getValue()).empty() && strcmp(column->getKey(), "ID") != 0){
            isEmptyWhere = false;
        }
    }

    for (auto record: XmlDatabase::select()) {
        addRecord = false;

        for (auto column: record->getColumns()) {
            columnKey = column->getKey();
            columnValue = string(column->getValue());
            word = string(where->getColumnValue(columnKey));
            if (strcmp(columnKey, "ID") == 0) {
                continue;
            }

            if (columnValue.find(word) != string::npos && !word.empty()) {
                addRecord = true;
            }
        }

        isDiferenceWhere = false;
        for (auto column: record->getColumns()) {
            columnKey = column->getKey();
            columnValue = string(column->getValue());
            word = string(where->getColumnValue(columnKey));
            if(columnValue.find(word) == string::npos && !word.empty() && strcmp(column->getKey(), "ID") != 0){
                isDiferenceWhere = true;
            }
        }

        if ((addRecord  && !isDiferenceWhere) || isEmptyWhere){
            result.push_back(record);
        }
    }

    return result;
}

DataSet XmlDatabase::getDataSet() {
    return XmlDatabase::dataSet;
}
