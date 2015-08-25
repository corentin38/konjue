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


#ifndef _KONJUEVIEW_H_
#define _KONJUEVIEW_H_

#include <qwidget.h>
#include <kparts/part.h>
#include <konjueiface.h>

class QPainter;
class KURL;

/**
 * This is the main view class for Konjue.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 *
 * @short Main view
 * @author Pieter Pareit <pieter.pareit@scarlet.be>
 * @version 0.1
 */
class KonjueView : public QWidget, public KonjueIface
{
    Q_OBJECT
public:
	/**
	 * Default constructor
	 */
    KonjueView(QWidget *parent);

	/**
	 * Destructor
	 */
    virtual ~KonjueView();

signals:
    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);

private slots:
    void slotSetTitle(const QString& title);

private:
};

#endif // _KONJUEVIEW_H_
