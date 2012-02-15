/* $Id: d_mos8.h,v 1.7 2010-09-07 07:46:21 felix Exp $ -*- C++ -*-
 * vim:ts=8:sw=2:et:
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
 * Berkeley BSIM3v3.3 model
 **********  derived from.........
 * Copyright 2004 Regents of the University of California. All rights reserved.
 * File: b3ld.c of BSIM3v3.3.0
 * Author: 1991 JianHui Huang and Min-Chie Jeng.
 * Modified by Mansun Chan (1995).
 * Author: 1997-1999 Weidong Liu.
 * Author: 2001 Xuemei Xi
 * Modified by Xuemei Xi, 10/05, 12/21, 2001.
 * Modified by Xuemei Xi, 07/29/2005.
 **********
 * Recoded for Gnucap model compiler, Al Davis, 2006
 */
/* This file is automatically generated. DO NOT EDIT */
#ifndef D_MOS8_H_INCLUDED
#define D_MOS8_H_INCLUDED

#include "d_mos_base.h"
#include "u_sdp.h"
#include "e_node.h"
#include "e_subckt.h"
#include "e_model.h"
/*--------------------------------------------------------------------------*/
class ADP_BUILT_IN_MOS8 :public ADP_BUILT_IN_MOS{
  double _hci_tr; //?
  ADP_BUILT_IN_MOS8( const ADP_BUILT_IN_MOS8& a);
public:
  explicit ADP_BUILT_IN_MOS8( COMPONENT* c, const std::string n):
    ADP_BUILT_IN_MOS(c,n), hci_node(0)
    {init(c);}

  virtual ADP_CARD* clone()const{ cout << "adp8 clone \n"; return new ADP_BUILT_IN_MOS8(*this); }
protected:
  void init(const COMPONENT*);
public:
  hp_float_t vthscale_hci;
  hp_float_t vthdelta_hci;
//  hp_float_t vthdelta; (ADP_BUILT_IN_MOS)

//  void tt_stress_apply( );?

  ADP_NODE* hci_node;

  virtual double tt_probe_num(const std::string& x)const;
  virtual double tr_probe_num(const std::string& x)const;

private: // overrides
  void tt_begin();
  void tt_accept();
  void tt_advance();
  void tr_accept();
  void tr_stress_last();
  void stress_apply();
};
/*--------------------------------------------------------------------------*/
class SDP_BUILT_IN_MOS8
  :public SDP_BUILT_IN_MOS_BASE{
public:
  explicit SDP_BUILT_IN_MOS8(const COMMON_COMPONENT* c) : SDP_BUILT_IN_MOS_BASE(c) {init(c);}
  void init(const COMMON_COMPONENT*);
public:
  // double h0;	// some hci paramater
  double cdsc;	// Drain/Source and channel coupling capacitance Q/V/m^2
  double cdscb;	// Body-bias dependence of cdsc Q/V/m^2
  double cdscd;	// Drain-bias dependence of cdsc Q/V/m^2
  double cit;	// Interface state capacitance Q/V/m^2
  double nfactor;	// Subthreshold swing Coefficient
  double xj;	// Junction depth in meters
  double vsat;	// Saturation velocity at tnom m/s
  double at;	// Temperature coefficient of vsat m/s
  double a0;	// Non-uniform depletion width effect coefficient.
  double ags;	// Gate bias  coefficient of Abulk.
  double a1;	// Non-saturation effect coefficient
  double a2;	// Non-saturation effect coefficient
  double keta;	// Body-bias coefficient of non-uniform depletion width effect. 1/v
  double nsub;	// Substrate doping concentration 1/cm3
  double npeak;	// Channel doping concentration 1/cm3
  double ngate;	// Poly-gate doping concentration 1/cm3
  double gamma1;	// Vth body coefficient
  double gamma2;	// Vth body coefficient
  double vbx;	// Vth transition body Voltage
  double vbm;	// Maximum body voltage
  double xt;	// Doping depth
  double k1;	// Bulk effect coefficient 1
  double kt1;	// Temperature coefficient of Vth
  double kt1l;	// Temperature coefficient of Vth
  double kt2;	// Body-coefficient of kt1
  double k2;	// Bulk effect coefficient 2
  double k3;	// Narrow width effect coefficient
  double k3b;	// Body effect coefficient of k3
  double w0;	// Narrow width effect parameter
  double nlx;	// Lateral non-uniform doping effect
  double dvt0;	// Short channel effect coeff. 0
  double dvt1;	// Short channel effect coeff. 1
  double dvt2;	// Short channel effect coeff. 2 1/v
  double dvt0w;	// Narrow Width coeff. 0
  double dvt1w;	// Narrow Width effect coeff. 1
  double dvt2w;	// Narrow Width effect coeff. 2
  double drout;	// DIBL coefficient of output resistance
  double dsub;	// DIBL coefficient in the subthreshold region
  double vth0;	// Threshold voltage
  double ua1;	// Temperature coefficient of ua m/v
  double ua;	// Linear gate dependence of mobility m/v
  double ub1;	// Temperature coefficient of ub (m/V)**2
  double ub;	// Quadratic gate dependence of mobility (m/V)**2
  double uc1;	// Temperature coefficient of uc
  double uc;	// Body-bias dependence of mobility
  double u0;	// Low-field mobility at Tnom
  double ute;	// Temperature coefficient of mobility
  double voff;	// Threshold voltage offset
  double delta;	// Effective Vds parameter
  double rdsw;	// Source-drain resistance per width
  double prwg;	// Gate-bias effect on parasitic resistance
  double prwb;	// Body-effect on parasitic resistance
  double prt;	// Temperature coefficient of parasitic resistance
  double eta0;	// Subthreshold region DIBL coefficient
  double etab;	// Subthreshold region DIBL coefficient 1/v
  double pclm;	// Channel length modulation Coefficient
  double pdibl1;	// Drain-induced barrier lowering coefficient
  double pdibl2;	// Drain-induced barrier lowering coefficient
  double pdiblb;	// Body-effect on drain-induced barrier lowering 1/v
  double pscbe1;	// Substrate current body-effect coefficient
  double pscbe2;	// Substrate current body-effect coefficient
  double pvag;	// Gate dependence of output resistance parameter
  double wr;	// Width dependence of rds
  double dwg;	// Width reduction parameter
  double dwb;	// Width reduction parameter
  double b0;	// Abulk narrow width parameter
  double b1;	// Abulk narrow width parameter
  double alpha0;	// substrate current model parameter
  double beta0;	// substrate current model parameter
  double elm;	// Non-quasi-static Elmore Constant Parameter
  double vfbcv;	// Flat Band Voltage parameter for capmod=0 only
  double cgsl;	// New C-V model parameter
  double cgdl;	// New C-V model parameter
  double ckappa;	// New C-V model parameter
  double cf;	// Fringe capacitance parameter
  double clc;	// Vdsat parameter for C-V model
  double cle;	// Vdsat parameter for C-V model
  double vfb;	// Flat Band Voltage
  double acde;	// Exponential coefficient for finite charge thickness, capmod=3
  double moin;	// Coefficient for gate-bias dependent surface potential, capmod=3
  double noff;	// C-V turn-on/off parameter, capmod=1,2,3
  double voffcv;	// C-V lateral-shift parameter, capmod=1,2,3
  double alpha1;	// substrate current model parameter
  double dl;	// 
  double dlc;	// 
  double dw;	// 
  double dwc;	// 
  double leff;	// 
  double weff;	// 
  double leffCV;	// 
  double weffCV;	// 
  double abulkCVfactor;	// 
  double litl;	// 
  double ldeb;	// 
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

class DEV_BUILT_IN_MOS;
class TDP_BUILT_IN_MOS8
  :public TDP_BUILT_IN_MOS_BASE{
public:
  explicit TDP_BUILT_IN_MOS8(const DEV_BUILT_IN_MOS*);
  // double    tr_probe_num(const std::string&)const;
public:
  double temp;	// 
  double tempratio;	// 
  double tempratio_1;	// 
  double vtm;	// vtm
  double ua;	// 
  double ub;	// 
  double uc;	// 
  double u0temp;	// 
  double vsattemp;	// 
  double rds0;	// 
  double phi;	// 
  double sqrtPhi;	// 
  double phis3;	// 
  double Xdep0;	// 
  double vbi;	// 
  double cdep0;	// 
  double k1;	// 
  double k2;	// 
  double vbsc;	// 
  double vth0;	// 
  double vfb;	// 
  double theta0vb0;	// 
  double thetaRout;	// 
  double k1ox;	// 
  double k2ox;	// 
  double vfbzb;	// 
};
/*--------------------------------------------------------------------------*/
class MODEL_BUILT_IN_MOS8
  :public MODEL_BUILT_IN_MOS_BASE{
protected:
  explicit MODEL_BUILT_IN_MOS8(const MODEL_BUILT_IN_MOS8& p);
public:
  explicit MODEL_BUILT_IN_MOS8(const BASE_SUBCKT*);
  ~MODEL_BUILT_IN_MOS8() {--_count;}
  virtual ADP_CARD* new_adp( COMPONENT* c)const; //alles const. attach vielleicht !const
public: // override virtual
  void do_stress_apply(COMPONENT* c)const;
  void do_tr_stress( const COMPONENT* c ) const;
  std::string dev_type()const;
  void      set_dev_type(const std::string& nt);
  CARD*     clone()const {return new MODEL_BUILT_IN_MOS8(*this);}
  void      precalc_first();
  void      precalc_last();
  SDP_CARD* new_sdp(COMMON_COMPONENT* c)const;
  void      set_param_by_index(int, std::string&, int);
  bool      param_is_printable(int)const;
  std::string param_name(int)const;
  std::string param_name(int,int)const;
  std::string param_value(int)const;
  int param_count()const {return (394 + MODEL_BUILT_IN_MOS_BASE::param_count());}
  bool      is_valid(const COMPONENT*)const;
  void      tr_eval(COMPONENT*)const;
public: // not virtual
  bool use_hci() const;
  static int count() {return _count;}
private: // strictly internal
  static int _count;
public: // input parameters
  // SDP h0;	
  SDP cdsc;	// Drain/Source and channel coupling capacitance Q/V/m^2
  SDP cdscb;	// Body-bias dependence of cdsc Q/V/m^2
  SDP cdscd;	// Drain-bias dependence of cdsc Q/V/m^2
  SDP cit;	// Interface state capacitance Q/V/m^2
  SDP nfactor;	// Subthreshold swing Coefficient
  SDP xj;	// Junction depth in meters
  SDP vsat;	// Saturation velocity at tnom m/s
  SDP at;	// Temperature coefficient of vsat m/s
  SDP a0;	// Non-uniform depletion width effect coefficient.
  SDP ags;	// Gate bias  coefficient of Abulk.
  SDP a1;	// Non-saturation effect coefficient
  SDP a2;	// Non-saturation effect coefficient
  SDP keta;	// Body-bias coefficient of non-uniform depletion width effect. 1/v
  SDP nsub;	// Substrate doping concentration 1/cm3
  SDP npeak;	// Channel doping concentration 1/cm3
  SDP ngate;	// Poly-gate doping concentration 1/cm3
  SDP gamma1;	// Vth body coefficient
  SDP gamma2;	// Vth body coefficient
  SDP vbx;	// Vth transition body Voltage
  SDP vbm;	// Maximum body voltage
  SDP xt;	// Doping depth
  SDP k1;	// Bulk effect coefficient 1
  SDP kt1;	// Temperature coefficient of Vth
  SDP kt1l;	// Temperature coefficient of Vth
  SDP kt2;	// Body-coefficient of kt1
  SDP k2;	// Bulk effect coefficient 2
  SDP k3;	// Narrow width effect coefficient
  SDP k3b;	// Body effect coefficient of k3
  SDP w0;	// Narrow width effect parameter
  SDP nlx;	// Lateral non-uniform doping effect
  SDP dvt0;	// Short channel effect coeff. 0
  SDP dvt1;	// Short channel effect coeff. 1
  SDP dvt2;	// Short channel effect coeff. 2 1/v
  SDP dvt0w;	// Narrow Width coeff. 0
  SDP dvt1w;	// Narrow Width effect coeff. 1
  SDP dvt2w;	// Narrow Width effect coeff. 2
  SDP drout;	// DIBL coefficient of output resistance
  SDP dsub;	// DIBL coefficient in the subthreshold region
  SDP vth0;	// Threshold voltage
  SDP ua1;	// Temperature coefficient of ua m/v
  SDP ua;	// Linear gate dependence of mobility m/v
  SDP ub1;	// Temperature coefficient of ub (m/V)**2
  SDP ub;	// Quadratic gate dependence of mobility (m/V)**2
  SDP uc1;	// Temperature coefficient of uc
  SDP uc;	// Body-bias dependence of mobility
  SDP u0;	// Low-field mobility at Tnom
  SDP ute;	// Temperature coefficient of mobility
  SDP voff;	// Threshold voltage offset
  SDP delta;	// Effective Vds parameter
  SDP rdsw;	// Source-drain resistance per width
  SDP prwg;	// Gate-bias effect on parasitic resistance
  SDP prwb;	// Body-effect on parasitic resistance
  SDP prt;	// Temperature coefficient of parasitic resistance
  SDP eta0;	// Subthreshold region DIBL coefficient
  SDP etab;	// Subthreshold region DIBL coefficient 1/v
  SDP pclm;	// Channel length modulation Coefficient
  SDP pdibl1;	// Drain-induced barrier lowering coefficient
  SDP pdibl2;	// Drain-induced barrier lowering coefficient
  SDP pdiblb;	// Body-effect on drain-induced barrier lowering 1/v
  SDP pscbe1;	// Substrate current body-effect coefficient
  SDP pscbe2;	// Substrate current body-effect coefficient
  SDP pvag;	// Gate dependence of output resistance parameter
  SDP wr;	// Width dependence of rds
  SDP dwg;	// Width reduction parameter
  SDP dwb;	// Width reduction parameter
  SDP b0;	// Abulk narrow width parameter
  SDP b1;	// Abulk narrow width parameter
  SDP alpha0;	// substrate current model parameter
  SDP beta0;	// substrate current model parameter
  SDP elm;	// Non-quasi-static Elmore Constant Parameter
  SDP vfbcv;	// Flat Band Voltage parameter for capmod=0 only
  SDP cgsl;	// New C-V model parameter
  SDP cgdl;	// New C-V model parameter
  SDP ckappa;	// New C-V model parameter
  SDP cf;	// Fringe capacitance parameter
  SDP clc;	// Vdsat parameter for C-V model
  SDP cle;	// Vdsat parameter for C-V model
  SDP vfb;	// Flat Band Voltage
  SDP acde;	// Exponential coefficient for finite charge thickness, capmod=3
  SDP moin;	// Coefficient for gate-bias dependent surface potential, capmod=3
  SDP noff;	// C-V turn-on/off parameter, capmod=1,2,3
  SDP voffcv;	// C-V lateral-shift parameter, capmod=1,2,3
  SDP alpha1;	// substrate current model parameter
  PARAMETER<int> capMod;	// Capacitance model selector (0, 1, 2, other?)
  PARAMETER<int> nqsMod;	// Non-quasi-static model selector (0, !0)
  PARAMETER<int> mobMod;	// Mobility model selector (1,2,3,other?)
  PARAMETER<int> noiMod;	// Noise model selector (not used)
  PARAMETER<int> paramChk;	// Model parameter checking selector (not used)
  PARAMETER<int> binUnit;	// Bin unit selector (1, !1)
  PARAMETER<double> version;	// parameter for model version (not used)
  PARAMETER<double> tox;	// Gate oxide thickness in meters
  PARAMETER<double> xpart;	// Channel charge partitioning
  PARAMETER<double> jctSidewallSatCurDensity;	// Sidewall junction reverse saturation current density
  PARAMETER<double> mjswg;	// Source/drain (gate side) sw junction capacitance grading coefficient
  PARAMETER<double> pbswg;	// Source/drain (gate side) sw junction capacitance built in potential
  PARAMETER<double> unitLengthGateSidewallJctCap;	// Source/drain (gate side) sidewall junction capacitance per unit width
  PARAMETER<double> jctEmissionCoeff;	// Source/drain junction emission coefficient
  PARAMETER<double> jctTempExponent;	// Junction current temperature exponent
  PARAMETER<double> Lint;	// Length reduction parameter
  PARAMETER<double> Ll;	// Length reduction parameter
  PARAMETER<double> Lln;	// Length reduction parameter
  PARAMETER<double> Lw;	// Length reduction parameter
  PARAMETER<double> Lwn;	// Length reduction parameter
  PARAMETER<double> Lwl;	// Length reduction parameter
  PARAMETER<double> Wint;	// Width reduction parameter
  PARAMETER<double> Wl;	// Width reduction parameter
  PARAMETER<double> Wln;	// Width reduction parameter
  PARAMETER<double> Ww;	// Width reduction parameter
  PARAMETER<double> Wwn;	// Width reduction parameter
  PARAMETER<double> Wwl;	// Width reduction parameter
  PARAMETER<double> dwc;	// Delta W for C-V model
  PARAMETER<double> dlc;	// Delta L for C-V model
  PARAMETER<double> noia;	// Flicker noise parameter, oxide trap density A
  PARAMETER<double> noib;	// Flicker noise parameter, oxide trap density B
  PARAMETER<double> noic;	// Flicker noise parameter, oxide trap density C
  PARAMETER<double> em;	// Flicker noise parameter V/m
  PARAMETER<double> ef;	// Flicker noise frequency exponent
  PARAMETER<int> acnqsMod;	// AC NQS model selector
  PARAMETER<double> toxm;	// Gate oxide thickness used in extraction
  PARAMETER<double> lintnoi;	// lint offset for noise calculation
  PARAMETER<double> ijth;	// Diode limiting current
  PARAMETER<double> tpb;	// Temperature coefficient of pb
  PARAMETER<double> tcj;	// Temperature coefficient of cj
  PARAMETER<double> tpbsw;	// Temperature coefficient of pbsw
  PARAMETER<double> tcjsw;	// Temperature coefficient of cjsw
  PARAMETER<double> tpbswg;	// Temperature coefficient of pbswg
  PARAMETER<double> tcjswg;	// Temperature coefficient of cjswg
  PARAMETER<double> Llc;	// Length reduction parameter for CV
  PARAMETER<double> Lwc;	// Length reduction parameter for CV
  PARAMETER<double> Lwlc;	// Length reduction parameter for CV
  PARAMETER<double> Wlc;	// Width reduction parameter for CV
  PARAMETER<double> Wwc;	// Width reduction parameter for CV
  PARAMETER<double> Wwlc;	// Width reduction parameter for CV
  PARAMETER<int> acm;	// area calculation method, ignored
  PARAMETER<double> h0;	// H for Hci
public: // calculated parameters
  double cox;	// 
  double factor1;	// 
  double vt_at_tnom;	// 
  double ni;	// 

};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
class DEV_BUILT_IN_MOS8 : public DEV_BUILT_IN_MOS {
  protected: // override virtual
    virtual double tr_probe_num(const std::string&)const;
    virtual double tt_probe_num(const std::string& x)const;
    double probe_num(const std::string& what)const
    {
      double x;
      if (_sim->analysis_is_tt()) {
        x = tt_probe_num(what);
      }else if (_sim->analysis_is_ac()) {
        x = ac_probe_num(what);
      }else{
        x = tr_probe_num(what);
      }
      return (std::abs(x)>=1) ? x : floor(x/OPT::floor + .5) * OPT::floor;
    }
};
/*--------------------------------------------------------------------------*/
#endif
