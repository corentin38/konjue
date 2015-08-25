/***************************************************************************
 *   Copyright (C) 2005 by Pieter Pareit                                   *
 *   pieter.pareit@scarlet.be                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SEARCHTOOLBAR_H
#define SEARCHTOOLBAR_H

#include <ktoolbar.h>

class KMainWindow;
class KComboBox;

/**
@author Pieter Pareit
*/
class SearchToolBar : public KToolBar
{
	Q_OBJECT
public:
    SearchToolBar(KMainWindow* parent, QObject* receiver, const char* slot, const char* name = "search-bar");

signals:
    void find(const QString& );

private slots:
    void clear();
    void find();

private:
    KComboBox* m_combo;
};

#endif
