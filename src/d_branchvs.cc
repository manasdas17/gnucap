/*$Id: d_vs.cc,v 1.9 2010-07-29 12:37:21 felix Exp $ -*- C++ -*-
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
 * functions for fixed voltage sources
 * temporary kluge: it has resistance
 */
//testing=script 2006.07.17
#include "e_elemnt.h"
#define BR 2
/*--------------------------------------------------------------------------*/
namespace {
/*--------------------------------------------------------------------------*/
class DEV_VS : public ELEMENT {
private:
  explicit DEV_VS(const DEV_VS& p) :ELEMENT(p) {}
public:
  explicit DEV_VS()		:ELEMENT() {}
private: // state
  double _one0, _one1;
  double _source0, _source1;
private: // override virtual
  char	   id_letter()const	{return '\0';}
  std::string value_name()const {return "dc";}
  std::string dev_type()const	{return "vsb";}
  uint_t	   max_nodes()const	{return 3;}
  uint_t	   min_nodes()const	{return 2;}
  uint_t	   matrix_nodes()const	{return 3;}
  uint_t	   net_nodes()const	{return 3;}
  uint_t           int_nodes()const	{return 1;}
  uint_t           ext_nodes()const	{return 2;}
  bool	   is_source()const	{return true;}
  bool	   f_is_value()const	{return true;}
  bool	   has_iv_probe()const  {return true;}
  bool	   use_obsolete_callback_parse()const {return true;}
  CARD*	   clone()const		{return new DEV_VS(*this);}
  void     precalc_last();
  void	   tr_iwant_matrix();//	{ tr_iwant_matrix_passive();}
  void	   tr_begin();
  bool	   do_tr();
  void	   tr_load();
  void	   tr_unload();
  hp_float_t   tr_involts()const	{return 0.;}
  hp_float_t   tr_involts_limited()const {unreachable(); return 0.;}
  void	   ac_iwant_matrix()	{ac_iwant_matrix_passive();}
  void	   ac_begin();//	{_loss1 = _loss0 = 1./OPT::shortckt; _acg = _ev = 0.;}
  void	   do_ac();
  void	   ac_load();//		{ac_load_shunt(); ac_load_source();}
  COMPLEX  ac_involts()const	{return 0.;}
  COMPLEX  ac_amps()const	{return (_acg + ac_outvolts()* (double)_loss0);}

  std::string port_name(uint_t i)const {
    assert(i != INVALID_NODE);
    assert(i < 3);
    static std::string names[] = {"p", "n", "b"};
    return names[i];
  }

  void expand();
};
/*--------------------------------------------------------------------------*/
inline void DEV_VS::ac_begin()
{
  _acg = _ev = 0.;
}
/*--------------------------------------------------------------------------*/
inline void DEV_VS::ac_load()
{
  trace0("DEV_VS::ac_load");
  //_sim->_acx.load_symmetric(_n[OUT1].m_(), _n[OUT2].m_(), mfactor() * _loss0);
  double d=1;
  _sim->_acx.load_point(_n[OUT1].m_(), _n[BR].m_(), d);
  _sim->_acx.load_point(_n[OUT2].m_(), _n[BR].m_(), -d);
  _sim->_acx.load_point(_n[BR].m_(), _n[OUT1].m_(), d);
  _sim->_acx.load_point(_n[BR].m_(), _n[OUT2].m_(), -d);

  assert (_n[BR].m_() != 0);
  _n[BR].iac() += _acg; // mfactor() * _acg;
}
/*--------------------------------------------------------------------------*/
void DEV_VS::expand(){

    if (!(_n[BR].n_())) {
        _n[BR].new_model_node( long_label() + ".br", this);
    }
    COMPONENT::expand();

}
/*--------------------------------------------------------------------------*/
void DEV_VS::tr_iwant_matrix()
{
/*
 *   +  -  b
 * +       1    u+
 * -      -1    u-   
 * b 1 -1  0    ib  val
 */


  assert(matrix_nodes() == 3);
  assert(is_device());
  //assert(!subckt()); ok for subckt to exist for logic

  if (_n[OUT1].m_() == INVALID_NODE) {
    std::cerr << "ELEMENT::tr_iwant_matrix_passive " << long_label() << "\n";
    exit(4);
  }
  assert(_n[OUT1].m_() != INVALID_NODE);
  assert(_n[OUT2].m_() != INVALID_NODE);
  assert(_n[BR].m_() != INVALID_NODE);

  trace3("DEV_VS::tr_iwant_matrix ", _n[OUT1].m_(),_n[OUT2].m_(),_n[BR].m_());

  _sim->_aa.iwant(_n[OUT1].m_(),_n[BR].m_());
  _sim->_aa.iwant(_n[OUT2].m_(),_n[BR].m_());
  _sim->_lu.iwant(_n[OUT1].m_(),_n[BR].m_());
  _sim->_lu.iwant(_n[OUT2].m_(),_n[BR].m_());
  _sim->_acx.iwant(_n[OUT1].m_(),_n[BR].m_());
  _sim->_acx.iwant(_n[OUT2].m_(),_n[BR].m_());
//  ac_iwant_matrix_extended();
//  tr_iwant_matrix_extended();
}
/*--------------------------------------------------------------------------*/
inline void DEV_VS::tr_load()
/*----------shunt---------------------------------------------------------------*/
{
  trace1("DEV_VS::tr_load", _sim->_time0);
  trace3("DEV_VS::tr_load", _n[OUT1].m_(), _n[OUT2].m_(), _n[BR].m_());
  assert(_one0 == _one0);
  double d = _one0 - _one1;
  if (d != 0.) {
    trace1("DEV_VS::tr_load 4 times",d);
    _sim->_aa.load_point(_n[OUT1].m_(), _n[BR].m_(), d);
    _sim->_aa.load_point(_n[OUT2].m_(), _n[BR].m_(), -d);
    _sim->_aa.load_point(_n[BR].m_(), _n[OUT1].m_(), d);
    _sim->_aa.load_point(_n[BR].m_(), _n[OUT2].m_(), -d);
  }

  _one1=_one0;

/*--load_source------------------------------------------------------------------------*/
  assert(_m0.c0 == _m0.c0);
  assert (_n[BR].m_() != 0);
  d = dampdiff(&_m0.c0, _m1.c0); // hmmm
  trace1("DEV_VS::tr_load source",d);
  if (d != 0.) {
    _n[BR].i() += d;
  }else{
  }
  _m1 = _m0;
}
/*--------------------------------------------------------------------------*/
inline void DEV_VS::tr_unload()
{
  _m0.c0 = 0; _source0 = 0;
  _one0 = 0;

  tr_load();
}
/*--------------------------------------------------------------------------*/
void DEV_VS::precalc_last()
{
  trace0("DEV_VS::precalc_last()");
  ELEMENT::precalc_last();
  set_constant(!has_tr_eval());
  set_converged(!has_tr_eval());
}
/*--------------------------------------------------------------------------*/
void DEV_VS::tr_begin()
{
  ELEMENT::tr_begin();
  // _y1.f0 = _y[0].f0 = 0.; // override
  _m0.x  = 0.;
  _m0.c0 = value() ; //  -_loss0 * _y[0].f1;
  _m0.c1 = 0.;
  _source0 = value();
  _source1 = 0;
  _one0 = 1;
  _one1 = 0;
  // _m1 = _m0;    
  if (!using_tr_eval()) {

  }else{
    incomplete();
  }
}
/*--------------------------------------------------------------------------*/
bool DEV_VS::do_tr()
{
  assert(_m0.x == 0.);
  if (using_tr_eval()) {
    incomplete();
  }else{itested();
    // assert(false); //??
    assert(conchk(_loss0, 1./OPT::shortckt));
    assert(_y[0].x == 0.);
    assert(_y[0].f0 == 0.);
    assert(_y[0].f1 == value());
    assert(_m0.x == 0.);
    assert(conchk(_m0.c0, -_loss0 * _y[0].f1));
    assert(_m0.c1 == 0.);
    assert(_y1 == _y[0]);
    assert(converged());
  }
  return converged();
}
/*--------------------------------------------------------------------------*/
void DEV_VS::do_ac()
{
  if (using_ac_eval()) {
    assert(false); // no common
    ac_eval();
    _acg = _ev;
  }else{itested();
    assert(_acg == 0.);
  }
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
DEV_VS p1;
DISPATCHER<CARD>::INSTALL d1(&device_dispatcher, "vsb|branchvs", &p1);
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
