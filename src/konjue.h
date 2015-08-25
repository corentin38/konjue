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


#ifndef _KONJUE_H_
#define _KONJUE_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kmainwindow.h>

class Conjugator;

class KTabWidget;

/**
 * This class serves as the main window for Konjue.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Pieter Pareit <pieter.pareit@scarlet.be>
 * @version 0.1
 */
class Konjue : public KMainWindow
{
  Q_OBJECT
public:
  /**
   * Default Constructor
   */
  Konjue();

  /**
   * Default Destructor
   */
  virtual ~Konjue();

protected:
  /**
   * Overridden virtuals for Qt drag 'n drop (XDND)
   */
  virtual void dragEnterEvent(QDragEnterEvent *event);
  virtual void dropEvent(QDropEvent *event);

protected:
  /**
   * This function is called when it is time for the app to save its
   * properties for session management purposes.
   */
  void saveProperties(KConfig *);

  /**
   * This function is called when this app is restored.  The KConfig
   * object points to the session management config file that was saved
   * with @ref saveProperties
   */
  void readProperties(KConfig *);

public slots:
  /**
   * The function display verb will load a tab page with the given verb,
   * if the tab page was already opened, it will set focus to that tab.
   * @param verb Maybe conjugated verb.
   */
  void displayVerb(const QString& verb);

private slots:

  void changeCaption(const QString& text);

  void editCopy();
  void editSelectAll();

  void closeCurrentTab();
  void closeAllTabs();
  void closeAllOtherTabs();

  void optionsConfigureKeys();
  void optionsPreferences();

private:
  void setupAccel();
  void setupActions();

private:
  KTabWidget *m_tab;
  Conjugator *m_conjugator;
};

#endif // _KONJUE_H_
