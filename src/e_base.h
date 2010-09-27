/*$Id: e_base.h,v 1.12 2010-09-17 12:25:58 felix Exp $ -*- C++ -*-
 * vim:ts=8:sw=2:et
 * Copyright (C) 2001 Albert Davis
 * Author: Albert Davis <aldavis@gnu.org>
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *------------------------------------------------------------------
 * real base for anything to do with a circuit
 */
//testing=obsolete
#ifndef E_BASE_H
#define E_BASE_H
#include "md.h"
/*--------------------------------------------------------------------------*/
// external
class XPROBE;
class WAVE;
class OMSTREAM;
class SIM_DATA;
/*--------------------------------------------------------------------------*/
class INTERFACE CKT_BASE {
private:
  mutable int	_probes;		/* number of probes set */
  std::string	_label;
public:
  static SIM_DATA* _sim;
  //--------------------------------------------------------------------
protected: // create and destroy
  explicit CKT_BASE()			  :_probes(0), _label() {}
  explicit CKT_BASE(const std::string& s) :_probes(0), _label(s) {}
  explicit CKT_BASE(const CKT_BASE& p)	  :_probes(0), _label(p._label) {}
  virtual  ~CKT_BASE();
  //--------------------------------------------------------------------
public: // user stuff
  virtual void	      help(CS&, OMSTREAM&)const {untested();}
  virtual std::string status()const {return "";}
  //--------------------------------------------------------------------
public: // probes
	  double      probe_num(const std::string&)const;
	  double      ac_probe_num(const std::string&)const;
  virtual double      tr_probe_num(const std::string&)const;
  virtual XPROBE      ac_probe_ext(const std::string&)const;
	  void	      inc_probes()const	{++_probes;}
	  void	      dec_probes()const	{assert(_probes>0); --_probes;}
	  bool	      has_probes()const	{return _probes > 0;}
	  int	      probes()const	{return _probes;}
  static  double      probe(const CKT_BASE*,const std::string&);
  static  WAVE*	      find_wave(const std::string& probe_name);
  //--------------------------------------------------------------------
public: // label
  bool operator!=(const std::string& n)const {return strcasecmp(_label.c_str(),n.c_str())!=0;}
  virtual const std::string long_label()const;
  const std::string&  short_label()const {return _label;}
  void	set_label(const std::string& s) {_label = s;}
public:
  static double tr_behaviour_del;
  static double tr_behaviour_rel;
  static double tt_behaviour;
  static double tt_behaviour_del;
  static double tt_behaviour_rel;
  void tt_prepare();
  virtual void tr_stress_last() {}
  virtual double      tt_probe_num(const std::string&)const;
};
/*--------------------------------------------------------------------------*/
inline bool exists(const CKT_BASE* c) {return c!=0;}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif
