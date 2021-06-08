#include "datapacket.h"

#include <cJSON.h>
#include <string>
#include <QDir>
#include <vector>
#include <iostream>
#include <QFileInfo>

using namespace std;

string getDirList(const string &path)
{
    QDir dir(QString::fromStdString(path));
    dir.setFilter(QDir::Files | QDir::Dirs);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList infos = dir.entryInfoList();

    if (!dir.exists() || path.empty()) {
        return "";
    }

    cJSON *root = cJSON_CreateObject();
    cJSON *array = cJSON_CreateArray();

    for (QFileInfo info : infos) {

        cJSON *obj = cJSON_CreateObject();
        cJSON_AddStringToObject(obj, "name", info.fileName().toStdString().c_str());
        if (info.isDir()) {
            cJSON_AddStringToObject(obj, "type", "dir");
            cJSON_AddBoolToObject(obj, "haveChild", false);
        } else {

            cJSON_AddStringToObject(obj, "type", "file");
            cJSON_AddBoolToObject(obj, "haveChild", true);
        }

        cJSON_AddItemToArray(array, obj);
    }
    cJSON_AddItemToObject(root, "fileVector", array);

    string response = cJSON_PrintUnformatted(root);

    return  response;
}

bool copyDirToDir(const QString &src, const QString &tar)
{
    QDir source(src);
    QDir target(tar);

    if (!target.exists())
        target.mkpath(tar);
    if (source.exists() && target.exists()) {
        QFileInfoList fileList = source.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

        foreach (QFileInfo file, fileList) {
            if (file.isDir()) {
                copyDirToDir(file.filePath(), target.filePath(file.fileName()));
            } else {
                if (!QFile::copy(file.filePath(), target.filePath(file.fileName())))
                    cout << "file copy failed" << endl;
            }
        }

    }
}

vector<string> stringSplit(string str, char ch)
{
    vector<string> res;
    str += ch;
    int start = 0;

    int last = str.find(ch);

    while (last < str.size()) {
        if (start != last)
            res.push_back(str.substr(start, last - start));
        else
            res.push_back("");

        start = last + 1;

        last = str.find(ch, start);
    }

    return  res;
}





















