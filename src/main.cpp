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
#include <kapplication.h>
#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
  I18N_NOOP("A KDE Application to conjugate and deconjugate French verbs");

static const char version[] = "0.4.0";

static KCmdLineOptions options[] =
  {
    { I18N_NOOP( "+[word]" ), I18N_NOOP( "Word to conjugate or deconjugate" ), 0 },
    KCmdLineLastOption
  };

int main(int argc, char **argv)
{
  KAboutData about("konjue", I18N_NOOP("Konjue"), version, description,
                   KAboutData::License_GPL, "(C) 2005 Pieter Pareit", 0, 0, "pieter.pareit@scarlet.be");
  about.addAuthor( "Pieter Pareit", 0, "pieter.pareit@scarlet.be" );
  about.addCredit( "Pierre Sarrazin", I18N_NOOP("Programmer of Verbiste, backend used by Konjue."),
                   "sarrazip AT sarrazip DOT com", "http://sarrazip.com" );
  about.addCredit( "Sebastian Sariego Benitez", I18N_NOOP("Artist that created the icon for Konjue."),
                   "segfault AT kde DOT cl", "http://segfault.kde.cl" );
  KCmdLineArgs::init(argc, argv, &about);
  KCmdLineArgs::addCmdLineOptions(options);
  KApplication app;

  // register ourselves as a dcop client
  app.dcopClient()->registerAs(app.name(), false);

  // see if we are starting with session management
  if (app.isRestored())
  {
    RESTORE(Konjue);
  }
  else
  {
    // no session.. just start up normally, create window
    Konjue *widget = new Konjue;
    widget->show();
    // load all verbs that were give as arguments
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    for (int i = 0; i < args->count(); i++)
    {
      widget->displayVerb( args->arg( i ) );
    }
    args->clear();
  }

  return app.exec();
}
