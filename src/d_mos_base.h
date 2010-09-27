/* $Id: d_mos_base.h,v 1.8 2010-09-07 07:46:21 felix Exp $ -*- C++ -*-
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
 * MOS model - base for levels 1,2,3,6
 */ 
/* This file is automatically generated. DO NOT EDIT */
#ifndef D_MOS_BASE_H_INCLUDED
#define D_MOS_BASE_H_INCLUDED

#include "d_mos.h"
#include "u_sdp.h"
#include "u_adp.h"
#include "e_node.h"
#include "e_subckt.h"
#include "e_model.h"
/*--------------------------------------------------------------------------*/
class SDP_BUILT_IN_MOS_BASE
  :public SDP_BUILT_IN_DIODE{
public:
  explicit SDP_BUILT_IN_MOS_BASE(const COMMON_COMPONENT* c) : SDP_BUILT_IN_DIODE(c) {init(c);}
  void init(const COMMON_COMPONENT*);
public:
  double l_eff;	// -23-c- actual (electrical) channel length
  double w_eff;	// --3-c- actual (electrical) channel width
  double ad;	// ----c- drain area, actual
  double as;	// ----c- source area, actual
  double cgate;	// -----b gate to channel capacitance
  double idsat;	// -----b drain junction saturation current
  double issat;	// -----b source junction saturation current
  double rd;	// -----b ohmic drain resistance
  double rs;	// -----b ohmic source resistance
  double phi;	// surface potential at strong inversion
  double cgso;	// 
  double cgdo;	// 
  double cgbo;	// 
};
/*--------------------------------------------------------------------------*/
class DEV_BUILT_IN_MOS;
class TDP_BUILT_IN_MOS_BASE{
public:
  explicit TDP_BUILT_IN_MOS_BASE(const DEV_BUILT_IN_MOS*);
public:
};
/*--------------------------------------------------------------------------*/
class MODEL_BUILT_IN_MOS_BASE
  :public MODEL_BUILT_IN_DIODE{
protected:
  explicit MODEL_BUILT_IN_MOS_BASE(const MODEL_BUILT_IN_MOS_BASE& p);
public:
  explicit MODEL_BUILT_IN_MOS_BASE(const BASE_SUBCKT*);
  ~MODEL_BUILT_IN_MOS_BASE() {--_count;}
public: // override virtual
  std::string dev_type()const;
  void      set_dev_type(const std::string& nt);
  CARD*     clone()const {return new MODEL_BUILT_IN_MOS_BASE(*this);}
  void      precalc_first();
  void      precalc_last();
  SDP_CARD* new_sdp(COMMON_COMPONENT* c)const;
  virtual ADP_CARD* new_adp(const COMPONENT* c)const {unreachable(); return NULL;}
  void tt_prepare( COMPONENT* c) const;
  void      set_param_by_index(int, std::string&, int);
  bool      param_is_printable(int)const;
  std::string param_name(int)const;
  std::string param_name(int,int)const;
  std::string param_value(int)const;
  int param_count()const {return (35);}
  bool      is_valid(const COMPONENT*)const;
  void      tr_eval(COMPONENT*)const;
public: // not virtual
  static int count() {return _count;}
private: // strictly internal
  bool _use_bti;
  static int _count;
public: // input parameters
  PARAMETER<int> level;	// dummy
  PARAMETER<double> wmax;	// max width
  PARAMETER<double> wmin;	// min width
  PARAMETER<double> lmax;	// max length
  PARAMETER<double> lmin;	// min length
  PARAMETER<double> is;	// bulk jct sat current
  PARAMETER<double> js;	// bulk jct sat current per sq meter
  PARAMETER<double> rsh;	// D & S diffusion sheet resistance
  PARAMETER<double> rd;	// drain ohmic resistance
  PARAMETER<double> rs;	// source ohmic resistance
  PARAMETER<double> cbd;	// 0-bias BD jct capacitance
  PARAMETER<double> cbs;	// 0-bias BS jct capacitance
  PARAMETER<double> cgso;	// GS overlap capacitance
  PARAMETER<double> cgdo;	// GD overlap capacitance
  PARAMETER<double> cgbo;	// GB overlap capacitance
  PARAMETER<int> cmodel;	// which capacitor model to use (2 or 3)
  PARAMETER<double> xl;	// length bias accounts for masking and etching effects
  PARAMETER<double> xw;	// width bias accounts for masking and etching effects
  PARAMETER<double> lmlt;	// length shrink factor
  PARAMETER<double> wmlt;	// width shrink factor
  PARAMETER<double> del;	// channel length reduction each side
  PARAMETER<double> ld;	// lateral length diffusion
  PARAMETER<double> wd;	// width diffusion
  PARAMETER<std::string> bti_model_name;	// bmn
public: // calculated parameters
  polarity_t polarity;	// 
  double tnom_k;	// nominal temperature, kelvin
  double egap;	// energy gap at tnom
  bool needs_isub;	// 
  bool use_bti()const {return _use_bti;}
public: // other thiongs
  virtual void stress_apply( const COMPONENT* C ) const;
  // virtual??
  virtual void tr_stress( const COMPONENT* C ) const ;
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif
