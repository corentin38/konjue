/***************************************************************************
 *   Copyright (C) 2004 by Pieter Pareit                                   *
 *   ppareit@localhost                                                     *
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
#ifndef CONJUGATOR_H
#define CONJUGATOR_H

#include <vector>
#include <string>

namespace verbiste
{
  class FrenchVerbDictionary;
}

class Conjugation
{
public:
  Conjugation( verbiste::FrenchVerbDictionary * fvd,
               const std::string& infinitive, const std::string& mark );

  const std::string getInfinitive();
  const std::string getRendered();
private:
  verbiste::FrenchVerbDictionary * fvd;
  std::string infinitive;
  std::string mark;
};

typedef std::vector<Conjugation> Conjugations;

/**
@author Pieter Pareit
*/
class Conjugator
{
public:
  Conjugator();
  ~Conjugator();

  Conjugations getConjugations( const std::string name );

private:
  verbiste::FrenchVerbDictionary * fvd;
};

#endif
