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
#include "conjugator.h"

#include <utility>

#include <verbiste/FrenchVerbDictionary.h>

Conjugator::Conjugator()
{
  fvd = new verbiste::FrenchVerbDictionary();
}


Conjugator::~Conjugator()
{
  delete fvd;
}

Conjugations Conjugator::getConjugations( const std::string name )
{
  Conjugations conjs;

  typedef std::vector<InflectionDesc> InflectionDescs;
  InflectionDescs inflDescs;
  fvd->deconjugate( name, inflDescs );

  for (InflectionDescs::const_iterator it = inflDescs.begin();
       it != inflDescs.end(); ++it )
  {
    conjs.push_back( Conjugation( fvd, it->infinitive, name ) );
  }

  return conjs;
}

Conjugation::Conjugation(verbiste::FrenchVerbDictionary * fvd,
                         const std::string& infinitive,
                         const std::string& mark ) :
    fvd(fvd), infinitive(infinitive), mark(mark)
{}

const std::string Conjugation::getInfinitive()
{
  return infinitive;
}

struct TenseName
{
  TenseName( Mode mode, Tense tense, std::string name,
             std::string seq_pre = "",
             std::string title_pre = "<b><u>",
             std::string title_post = "</b></u><br>",
             std::string item_pre = "",
             std::string item_post = "<br>",
             std::string seq_post = "<br>" ) :
      mode(mode), tense(tense), name(name),
      seq_pre(seq_pre),
      title_pre(title_pre), title_post(title_post),
      item_pre(item_pre), item_post(item_post),
      seq_post(seq_post)
  {}
  Mode mode;
  Tense tense;
  std::string name;
  std::string seq_pre;
  std::string title_pre, title_post;
  std::string item_pre, item_post;
  std::string seq_post;
};


const std::string Conjugation::getRendered()
{
  std::string rendered;

  std::string verbTempl = fvd->getVerbTemplate( infinitive );

  typedef std::vector<TenseName> Items;
  Items tbl;
  tbl.push_back( TenseName( INFINITIVE_MODE, PRESENT_TENSE, "inf. pres.",
                            "<table><tr><td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td>" ) );
  tbl.push_back( TenseName( INDICATIVE_MODE, PRESENT_TENSE, "ind. pres.",
                            "<tr><td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td>") );
  tbl.push_back( TenseName( INDICATIVE_MODE, IMPERFECT_TENSE, "ind. imperf.",
                            "<td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td>") );
  tbl.push_back( TenseName( INDICATIVE_MODE, FUTURE_TENSE, "ind. fut.",
                            "<td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td></tr>") );
  tbl.push_back( TenseName( INDICATIVE_MODE, PAST_TENSE, "ind. past",
                            "<tr><td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td>") );
  tbl.push_back( TenseName( CONDITIONAL_MODE, PRESENT_TENSE, "cond. pres.",
                            "<td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td></tr>") );
  tbl.push_back( TenseName( SUBJUNCTIVE_MODE, PRESENT_TENSE, "subj. pres.",
                            "<tr><td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td>") );
  tbl.push_back( TenseName( SUBJUNCTIVE_MODE, IMPERFECT_TENSE, "subj. imperf.",
                            "<td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td></tr>") );
  tbl.push_back( TenseName( IMPERATIVE_MODE, PRESENT_TENSE, "imp. pres.",
                            "<tr><td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td>") );
  tbl.push_back( TenseName( PARTICIPLE_MODE, PRESENT_TENSE, "part. pres.",
                            "<td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td>") );
  tbl.push_back( TenseName( PARTICIPLE_MODE, PAST_TENSE, "part. past",
                            "<td>",
                            "<b><u>", "</b></u><br>",
                            "", "<br>",
                            "</td></tr></table>") );

  std::string radical = fvd->getRadical( infinitive, verbTempl );

  for ( Items::const_iterator it = tbl.begin(); it != tbl.end(); ++it )
  {

    std::vector<std::vector<std::string> > persons;
    fvd->generateTense( radical,
                        *fvd->getTemplate( verbTempl ),
                        it->mode,
                        it->tense,
                        persons );

    rendered += it->seq_pre + '\n';
    rendered += it->title_pre + it->name + it->title_post + '\n';

    std::vector<std::vector<std::string> >::const_iterator iit;
    for ( iit = persons.begin(); iit != persons.end(); ++iit )
    {
      rendered += it->item_pre;

      std::vector< string >::const_iterator iiit;

      for ( iiit = iit->begin(); iiit != iit->end(); ++iiit )
      {
        if ( iiit != iit->begin() ) rendered += ", ";
        if ( *iiit == mark )
        {
          rendered += "<i>" + *iiit + "</i>";
        }
        else
        {
          rendered += *iiit;
        }
      }

      rendered += it->item_post + '\n';
    }

    rendered += it->seq_post + '\n';
  }

  return rendered;
}











