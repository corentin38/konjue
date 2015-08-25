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
#include "searchtoolbar.h"

#include <kmainwindow.h>
#include <klocale.h>
#include <kaction.h>
#include <qlabel.h>
#include <kcombobox.h>
#include <qwhatsthis.h>


SearchToolBar::SearchToolBar(KMainWindow* parent, QObject* receiver, const char* slot, const char* name)
    : KToolBar(parent, DockTop, false, name, true)
{
  // support for clearing the search
  KAction *clearAction = new KAction(i18n("Clear"), QString::fromLatin1("locationbar_erase"), 0,
                                     this, SLOT(clear()), new KActionCollection(this),
                                     "clear" );
  clearAction->plug(this);

  // display label
  QLabel* label = new QLabel(i18n("Search:") + QString::fromLatin1(" "), this);
  insertWidget(-1, -1, label);

  // the editable combo box
  m_combo = new KComboBox(this);
  m_combo->setEditable(true);
  m_combo->setInsertionPolicy(QComboBox::AtTop);
  insertWidget(-1, -1, m_combo);
  connect(m_combo, SIGNAL(activated(const QString& )),
          this, SIGNAL(find(const QString& )));
  connect(m_combo, SIGNAL(returnPressed()),
          m_combo->lineEdit(), SLOT(selectAll()));
  setStretchableWidget(m_combo);
  m_combo->setFocus();
  QWhatsThis::add( m_combo, i18n( "Enter word to conjugate here" ) );

  // extra, a button to do the search
  KAction *findAction = new KAction(i18n("Find"), QString::fromLatin1("find"), 0,
                                    this, SLOT( find() ), new KActionCollection(this),
                                    "find");
  findAction->plug(this);

  // connect the arguments
  connect(this, SIGNAL(find(const QString& )), receiver, slot);
}

void SearchToolBar::clear()
{
  m_combo->clearEdit();
  m_combo->setFocus();
}

void SearchToolBar::find()
{
  // search button was clicked, forward it
  emit find(m_combo->currentText());
  m_combo->lineEdit()->selectAll();
}
