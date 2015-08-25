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


#include "konjue.h"
//#include "pref.h"
#include "searchtoolbar.h"
//#include "konjueview.h"
#include "conjugator.h"

#include <qdragobject.h>
#include <kglobal.h>
#include <klocale.h>
#include <kdeversion.h>
#include <kmenubar.h>
#include <kkeydialog.h>
#include <kaccel.h>
#include <kconfig.h>
#include <ktabwidget.h>
#include <kstdaccel.h>
#include <kaction.h>
#include <kstdaction.h>
#include <kapplication.h>
#include <kpushbutton.h>
#include <kiconloader.h>
#include <qtextedit.h>
#include <kmessagebox.h>


Konjue::Konjue()
    : KMainWindow( 0, "Konjue" ),
    m_tab( new KTabWidget( this, "tab" ) ),
    m_conjugator( new Conjugator() )
{
  // accept dnd
  setAcceptDrops(true);

  // @todo folowing code should be available for all classes, get it into KTabWidget/KTabBar?
  KPushButton* closeBtn = new KPushButton(m_tab);
  closeBtn->setPixmap(KGlobal::iconLoader()->loadIcon("tab_remove", KIcon::Small));
  closeBtn->resize(22, 22);
  closeBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  closeBtn->hide();
  m_tab->setCornerWidget(closeBtn);
  connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeCurrentTab()));

  // tell the KMainWindow that this is indeed the main widget
  setCentralWidget(m_tab);

  // then, setup our actions
  setupActions();


  new SearchToolBar( this, this, SLOT(displayVerb(const QString& )) );

  // apply the saved mainwindow settings, if any, and ask the mainwindow
  // to automatically save settings if changed: window size, toolbar
  // position, icon size, etc.
  setAutoSaveSettings();

  // but don't show mean toolbar!
  toolBar()->hide();


  /*
      // allow the view to change the caption
      connect( m_view, SIGNAL(signalChangeCaption(const QString&)),
              this,   SLOT(changeCaption(const QString&)));
  */

}

Konjue::~Konjue()
{}


void Konjue::setupActions()
{
  KStdAction::close(this, SLOT(closeCurrentTab()), actionCollection());
  KStdAction::quit(kapp, SLOT(quit()), actionCollection());

  KStdAction::copy(this, SLOT(editCopy()), actionCollection());
  KStdAction::selectAll(this, SLOT(editSelectAll()), actionCollection());

  new KAction( i18n("Close all"), 0, this, SLOT(closeAllTabs()), actionCollection(), "close-all" );
  new KAction( i18n("Close all others"), 0, this, SLOT(closeAllOtherTabs()), actionCollection(), "close-all-others" );

  KStdAction::keyBindings(this, SLOT(optionsConfigureKeys()), actionCollection());
  //// @todo support for other fonts, select what times to show, nr of rows, collums
  //  KStdAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

  createGUI();
}

static QWidget* findPage( const QTabWidget& tabWidget, const QString& label )
{
  for ( int i = 0; i < tabWidget.count(); ++i )
  {
    if ( tabWidget.label( i ).remove( '&' ) == label )
    {
      return tabWidget.page( i );
    }
  }
  return 0;
}

void Konjue::displayVerb( const QString & s )
{
  int entriesFound = 0;

  Conjugations conjugations = m_conjugator->getConjugations( (const char*)s );

  for ( Conjugations::iterator it = conjugations.begin();
        it != conjugations.end(); ++it )
  {
    ++entriesFound;
    QString infinitive( it->getInfinitive().c_str() );


    if ( QWidget* page = findPage( *m_tab, infinitive ) )
    {
      m_tab->showPage( page );
    }
    else
    {
      QTextEdit * display = new QTextEdit( m_tab,
                                           infinitive + "'s display" );
      display->setReadOnly( true );
      display->setText( it->getRendered().c_str() );

      m_tab->addTab( display, infinitive );
      m_tab->showPage( display );
      m_tab->cornerWidget()->show();
    }
  }
}

void Konjue::closeAllTabs()
{
  while ( m_tab->count() )
  {
    closeCurrentTab();
  }
}

void Konjue::closeAllOtherTabs()
{
  if ( QWidget* pageNotToRemove = m_tab->currentPage() )
  {
    int i = m_tab->count();
    while ( i-- > 0 )
    {
      m_tab->setCurrentPage( i );
      if ( m_tab->currentPage() != pageNotToRemove )
      {
        closeCurrentTab();
      }
    }
  }
}


void Konjue::closeCurrentTab()
{
  if ( QWidget* page = m_tab->currentPage() )
  {
    m_tab->removePage( page );
    delete page;
  }
  if ( m_tab->count() == 0 )
  {
    m_tab->cornerWidget()->hide();
  }
}

void Konjue::editCopy()
{
  if ( QTextEdit* te = dynamic_cast<QTextEdit*>( m_tab->currentPage() ) )
  {
    te->copy();
  }
}

void Konjue::editSelectAll()
{
  if ( QTextEdit* te = dynamic_cast<QTextEdit*>( m_tab->currentPage() ) )
  {
    te->selectAll();
  }
}


void Konjue::saveProperties(KConfig *config)
{
  if ( m_tab->count() )
  {
    config->writeEntry( "tabsOpen", m_tab->count() );
    for ( int i = 0; i < m_tab->count(); ++i )
    {
      config->writeEntry( QString( "tab%1" ).arg( i ), m_tab->label( i ).remove( '&' ) );
    }
    config->writeEntry( "currentTab", m_tab->currentPageIndex() );
  }
}

void Konjue::readProperties(KConfig *config)
{
  if ( int tabs = config->readNumEntry( "tabsOpen" ) )
  {
    for ( int i = 0; i < tabs; ++i )
    {
      displayVerb( config->readEntry( QString( "tab%1" ).arg( i ) ) );
    }
    m_tab->setCurrentPage( config->readNumEntry( "currentTab" ) );
  }
}

void Konjue::dragEnterEvent(QDragEnterEvent */*event*/)
{}

void Konjue::dropEvent(QDropEvent */*event*/)
{}

void Konjue::optionsConfigureKeys()
{
  KKeyDialog::configure(actionCollection());
}

void Konjue::optionsPreferences()
{
  /*
    // popup some sort of preference dialog, here
    KonjuePreferences dlg;
    if (dlg.exec())
    {
      // redo your settings
    }
  */
}

void Konjue::changeCaption(const QString& text)
{
  // display the text on the caption
  setCaption(text);
}
#include "konjue.moc"
