#ifndef DATAPACKET_H
#define DATAPACKET_H

#include <string>
#include <QString>

std::string getDirList(const std::string &path);

bool copyDirToDir(const QString &src, const QString &tar);

#endif // DATAPACKET_H
