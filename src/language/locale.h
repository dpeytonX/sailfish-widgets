/***************************************************************************
** This file is part of SailfishWidgets
**
** Copyright (c) 2015 Dametrious Peyton
**
** $QT_BEGIN_LICENSE:GPLV3$
** SailfishWidgets is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** SailfishWidgets is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with SailfishWidgets.  If not, see <http://www.gnu.org/licenses/>.
** $QT_END_LICENSE$
**
**************************************************************************/
#ifndef LOCALE_H
#define LOCALE_H

#include <QObject>
#include <QLocale>
#include <QString>

/*!
 * Represents a locale in a UI friendly manner
 */
class Locale : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language)
    Q_PROPERTY(QString country READ country)
    Q_PROPERTY(QString pretty READ pretty)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged)
public:
    explicit Locale(QObject *parent = 0);
    Locale(const QString& locale, QObject *parent=0);
    QString locale() const;
    void setLocale(const QString& locale);
    virtual QString pretty() const;
    QString language() const;
    QString country();
    friend bool operator==(const Locale& lhs, const Locale& rhs);

signals:
    void localeChanged();

protected:
    QString m_locale;
};

#endif // LOCALE_H
