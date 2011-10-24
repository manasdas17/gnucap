/* $Id: d_mos3.h,v 1.2 2010-04-15 07:42:56 felix Exp $ -*- C++ -*-
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
 * mos model equations: spice level 3 equivalent
 */
/* This file is automatically generated. DO NOT EDIT */
#ifndef D_MOS3_H_INCLUDED
#define D_MOS3_H_INCLUDED

#include "d_mos123.h"
#include "u_sdp.h"
#include "e_node.h"
#include "e_subckt.h"
#include "e_model.h"
/*--------------------------------------------------------------------------*/
class SDP_BUILT_IN_MOS3
  :public SDP_BUILT_IN_MOS123{
public:
  explicit SDP_BUILT_IN_MOS3(const COMMON_COMPONENT* c) : SDP_BUILT_IN_MOS123(c) {init(c);}
  void init(const COMMON_COMPONENT*);
public:
};
/*--------------------------------------------------------------------------*/
class DEV_BUILT_IN_MOS;
class TDP_BUILT_IN_MOS3
  :public TDP_BUILT_IN_MOS123{
public:
  explicit TDP_BUILT_IN_MOS3(const DEV_BUILT_IN_MOS*);
public:
  double vt;	// 
  double phi;	// 
  double sqrt_phi;	// 
  double beta;	// 
  double uo;	// 
  double vbi;	// 
};
/*--------------------------------------------------------------------------*/
//class ADP_BUILT_IN_MOS3
 // :public ADP_BUILT_IN_MOS123{
//public:
//  explicit ADP_BUILT_IN_MOS3(const COMMON_COMPONENT* c) : ADP_BUILT_IN_MOS123(c) {init(c);}
//  void init(const COMMON_COMPONENT*);
//public:
//   double vto;  // replace m->vto

//  double ids_stress; // base

//};
/*--------------------------------------------------------------------------*/
class ADP_BUILT_IN_MOS3 :public ADP_BUILT_IN_MOS123{
public:
  explicit ADP_BUILT_IN_MOS3( COMPONENT* c, const std::string n) :
	  ADP_BUILT_IN_MOS123(c,n) { init(c);}
  void init(const COMPONENT* );
public:
//  double vto;	// replace m->vto
//  double ids_stress;
//  double ids_Stress;
};
/*--------------------------------------------------------------------------*/
class MODEL_BUILT_IN_MOS3
  :public MODEL_BUILT_IN_MOS123{
protected:
  explicit MODEL_BUILT_IN_MOS3(const MODEL_BUILT_IN_MOS3& p);
public:
  explicit MODEL_BUILT_IN_MOS3(const BASE_SUBCKT*);
  ~MODEL_BUILT_IN_MOS3() {--_count;}
public: // override virtual
  std::string dev_type()const;
  void      set_dev_type(const std::string& nt);
  CARD*     clone()const {return new MODEL_BUILT_IN_MOS3(*this);}
  void      precalc_first();
  void      precalc_last();
  SDP_CARD* new_sdp(COMMON_COMPONENT* c)const; //y !const COMMON_COMPONENT*?
  virtual ADP_CARD* new_adp(COMPONENT* c)const;
  void      set_param_by_index(int, std::string&, int);
  bool      param_is_printable(int)const;
  std::string param_name(int)const;
  std::string param_name(int,int)const;
  std::string param_value(int)const;
  int param_count()const {return (15 + MODEL_BUILT_IN_MOS123::param_count());}
  bool      is_valid(const COMPONENT*)const;
  void      tr_eval(COMPONENT*)const;

public: // stress and tt
  virtual void do_stress_apply( COMPONENT* ) const;
  virtual void do_tt_prepare( COMPONENT* ) const;
public: // not virtual
  static int count() {return _count;}
private: // strictly internal
  static int _count;
public: // input parameters
  PARAMETER<double> kp;	// transconductance parameter
  PARAMETER<double> nfs_cm;	// fast surface state density
  PARAMETER<double> vmax;	// max drift velocity of carriers
  PARAMETER<double> theta;	// mobility modulation
  PARAMETER<double> eta;	// static feedback
  PARAMETER<double> kappa;	// saturation field vector
  PARAMETER<double> delta;	// width effect on threshold voltage
public: // calculated parameters
  double nfs;	// 
  bool calc_kp;	// 
  double alpha;	// 
  double xd;	// coeffDepLayWidth
  double cfsox;	// 
  double delta3;	// narrow factor
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif
