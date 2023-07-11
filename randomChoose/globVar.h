#include <random>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#ifndef GLOBVAR_H
#define GLOBVAR_H

extern int N; // the num of total students.
extern std::mt19937_64 mt_rand; // the overall random generator
extern QJsonObject settObj;
extern bool locked;
QJsonObject getSettFrom(QString str);
void writeSett();
void getSett();
#endif // GLOBVAR_H
