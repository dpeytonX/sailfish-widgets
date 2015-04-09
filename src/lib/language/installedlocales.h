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

#ifndef INSTALLEDLOCALES_H
#define INSTALLEDLOCALES_H

#include <QObject>
#include <QLocale>

class QQmlListProperty;
class QList;
class Locale;

class InstalledLocales : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Locale> locales READ locales NOTIFY localesChanged)
    Q_PROPERTY(bool includeAppDefault READ includeAppDefault WRITE setIncludeAppDefault)
public:
    InstalledLocales(QObject* parent=0);
    Locale* localeAt(QQmlListProperty<Locale> *property, int index);
    int localeCount(QQmlListProperty<Locale> *property);
    bool includeAppDefault() const;
    void setIncludeAppDefault(bool includeAppDefault);
    QQmlListProperty<Locale> locales() const;

signals:
    void localesChanged();

private:
    QList<Locale> m_availableLocales;
    bool m_includeAppDefault;
};

#endif // LOCALEHELPER_H
