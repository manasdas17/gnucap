/* $Id: d_mos3.cc,v 1.3 2010-07-09 12:14:21 felix Exp $ -*- C++ -*-
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
 * mos model equations: spice level 3 equivalent
 */
/* This file is automatically generated. DO NOT EDIT */

#include "l_denoise.h"
#include "globals.h"
#include "e_elemnt.h"
#include "d_mos3.h"
/*--------------------------------------------------------------------------*/
const double NA(NOT_INPUT);
const double INF(BIGBIG);
/*--------------------------------------------------------------------------*/
int MODEL_BUILT_IN_MOS3::_count = 0;
/*--------------------------------------------------------------------------*/
const int LEVEL(3);
/*--------------------------------------------------------------------------*/
namespace MODEL_BUILT_IN_MOS3_DISPATCHER { 
  static DEV_BUILT_IN_MOS p1d;
  static MODEL_BUILT_IN_MOS3 p1(&p1d);
  static DISPATCHER<MODEL_CARD>::INSTALL
    d1(&model_dispatcher, "nmos3|pmos3", &p1);
}
/*--------------------------------------------------------------------------*/
void SDP_BUILT_IN_MOS3::init(const COMMON_COMPONENT* cc)
{
  assert(cc);
  SDP_BUILT_IN_MOS123::init(cc);
}
/*--------------------------------------------------------------------------*/

void ADP_BUILT_IN_MOS3::init(const COMPONENT* c)
{
  assert(c);
  std::cerr << "ADP_BUILT_IN_MOS3::init( " <<c <<" )\n";

  ADP_BUILT_IN_MOS123::init(c);


//  vto=m->vto;

}

/*--------------------------------------------------------------------------*/

TDP_BUILT_IN_MOS3::TDP_BUILT_IN_MOS3(const DEV_BUILT_IN_MOS* d)
  :TDP_BUILT_IN_MOS123(d)
{
  assert(d);
  const COMMON_BUILT_IN_MOS* c = prechecked_cast<const COMMON_BUILT_IN_MOS*>(d->common());
  assert(c);
  const SDP_BUILT_IN_MOS3* s = prechecked_cast<const SDP_BUILT_IN_MOS3*>(c->sdp());
  assert(s);
  const ADP_BUILT_IN_MOS3* a = (const ADP_BUILT_IN_MOS3*)(d->adp());
  assert(a);
  const MODEL_BUILT_IN_MOS3* m = prechecked_cast<const MODEL_BUILT_IN_MOS3*>(c->model());
  assert(m);
  const CARD_LIST* par_scope = d->scope();
  assert(par_scope);
    // final adjust: code_pre

      double temp = d->_sim->_temp_c + P_CELSIUS0;
      double tempratio  = temp / m->tnom_k; // ratio
      double tempratio4 = tempratio * sqrt(tempratio);
      double kt = temp * P_K;
      double egap = 1.16 - (7.02e-4*temp*temp) / (temp+1108.);
      double arg = (m->egap*tempratio - egap) / (2*kt);
    // final adjust: override
    // final adjust: raw
    // final adjust: mid
    // final adjust: calculated
    vt = temp * P_K_Q;
    phi = m->phi*tempratio + (-2*vt*(1.5*log(tempratio)+P_Q*(arg)));
    sqrt_phi = sqrt(phi);
    beta = (m->kp / tempratio4) * s->w_eff / s->l_eff;
    uo = m->uo * tempratio4;

//    std::cerr << "TDP_BUILT_IN_MOS3::TDP_BUILT_IN_MOS3( " << d << " )\n";

//    std::cerr << d->short_label() << " " <<  m->vto  << "\n";
//    std::cerr << "device " << d << " has ADP_CARD @" <<  a << " : " <<  d->adp() <<  "\n";
 //   std::cerr << a->vto << "\n";

    vbi = (fixzero(
	(a->vto - m->gamma * sqrt(m->phi)
	 +.5*(m->egap-egap) + m->polarity* .5 * (phi-m->phi)), m->phi));
    // final adjust: post
    // final adjust: done
}
/*--------------------------------------------------------------------------*/
MODEL_BUILT_IN_MOS3::MODEL_BUILT_IN_MOS3(const BASE_SUBCKT* p)
  :MODEL_BUILT_IN_MOS123(p),
   kp(NA),
   nfs_cm(0.0),
   vmax(NA),
   theta(0.0),
   eta(0.0),
   kappa(0.2),
   delta(0.0),
   nfs(NA),
   calc_kp(false),
   alpha(NA),
   xd(NA),
   cfsox(NA),
   delta3(NA)
{
  if (ENV::run_mode != rPRE_MAIN) {
    ++_count;
  }else{
  }
  set_default(&mjsw, .33);
  set_default(&tox, 1e-7);
  set_default(&cox, NA);
  set_default(&vto, NA);
  set_default(&gamma, NA);
  set_default(&phi, NA);
  set_default(&mos_level, LEVEL);
}
/*--------------------------------------------------------------------------*/
MODEL_BUILT_IN_MOS3::MODEL_BUILT_IN_MOS3(const MODEL_BUILT_IN_MOS3& p)
  :MODEL_BUILT_IN_MOS123(p),
   kp(p.kp),
   nfs_cm(p.nfs_cm),
   vmax(p.vmax),
   theta(p.theta),
   eta(p.eta),
   kappa(p.kappa),
   delta(p.delta),
   nfs(p.nfs),
   calc_kp(p.calc_kp),
   alpha(p.alpha),
   xd(p.xd),
   cfsox(p.cfsox),
   delta3(p.delta3)
{
  if (ENV::run_mode != rPRE_MAIN) {
    ++_count;
  }else{untested();//194
  }
}
/*--------------------------------------------------------------------------*/
std::string MODEL_BUILT_IN_MOS3::dev_type()const
{
  if (polarity == pN) {
    return "nmos3";
  }else if (polarity == pP) {
    return "pmos3";
  }else{untested();//235
    return MODEL_BUILT_IN_MOS123::dev_type();
  }
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS3::set_dev_type(const std::string& new_type)
{
  if (Umatch(new_type, "nmos3 ")) {
    polarity = pN;
  }else if (Umatch(new_type, "pmos3 ")) {
    polarity = pP;
  }else{
    MODEL_BUILT_IN_MOS123::set_dev_type(new_type);
  }
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS3::precalc_first()
{
    const CARD_LIST* par_scope = scope();
    assert(par_scope);
    MODEL_BUILT_IN_MOS123::precalc_first();
    e_val(&(this->kp), NA, par_scope);
    e_val(&(this->nfs_cm), 0.0, par_scope);
    e_val(&(this->vmax), NA, par_scope);
    e_val(&(this->theta), 0.0, par_scope);
    e_val(&(this->eta), 0.0, par_scope);
    e_val(&(this->kappa), 0.2, par_scope);
    e_val(&(this->delta), 0.0, par_scope);
    // final adjust: code_pre
      
      if (!has_good_value(tox)) {
	tox = 1e-7;
      }
      cox = P_EPS_OX / tox;
      if (kp == NA) {
	kp = uo * cox;
	calc_kp = true;
      }
      if (nsub != NA) {
	if (phi == NA) {
	  phi = (2. * P_K_Q) * tnom_k * log(nsub/NI);
	  if (phi < .1) {
	    untested();
	    error(((!_sim->is_first_expand()) ? (bDEBUG) : (bWARNING)),
		  long_label() + ": calculated phi too small, using .1\n");
	    phi = .1;
	  }
	  calc_phi = true;
	}
	if (gamma == NA) {
	  gamma = sqrt(2. * P_EPS_SI * P_Q * nsub) / cox;
	  calc_gamma = true;
	}
	if (vto == NA) {
	  double phi_ms = (tpg == gtMETAL)
	    ? polarity * (-.05 - (egap + polarity * phi) / 2.)
	    : -(tpg * egap + phi) / 2.;
	  double vfb = phi_ms - polarity * P_Q * nss / cox;
	  vto = vfb + phi + gamma * sqrt(phi);
	  calc_vto = true;
	}
      }
    // final adjust: override
    if (cox == NA) {
      cox = P_EPS_OX/tox;
    }else{
    }
    if (vto == NA) {
      vto = 0.0;
    }else{
    }
    if (gamma == NA) {
      gamma = 0.0;
    }else{
    }
    if (phi == NA) {
      phi = 0.6;
    }else{
    }
    // final adjust: raw
    e_val(&(this->kp), 2e-5, par_scope);
    e_val(&(this->nfs_cm), 0.0, par_scope);
    e_val(&(this->vmax), NA, par_scope);
    e_val(&(this->theta), 0.0, par_scope);
    e_val(&(this->eta), 0.0, par_scope);
    e_val(&(this->kappa), 0.2, par_scope);
    e_val(&(this->delta), 0.0, par_scope);
    // final adjust: mid
    // final adjust: calculated
    nfs = nfs_cm*ICM2M2;
    alpha = ((nsub != NA)
	? (2. * P_EPS_SI) / (P_Q * nsub)
	: 0.);
    xd = sqrt(alpha);
    cfsox = P_Q * nfs / cox;
    delta3 = delta * M_PI_2 * P_EPS_SI / cox;
    // final adjust: post
    // final adjust: done
}
/*--------------------------------------------------------------------------*/
ADP_CARD* MODEL_BUILT_IN_MOS3::new_adp(DEV_BUILT_IN_MOS* c)const
{
  std::cerr << "MODEL_BUILT_IN_MOS3::new_adp\n";

  return MODEL_BUILT_IN_MOS123::new_adp(c);
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS3::precalc_last()
{
    MODEL_BUILT_IN_MOS123::precalc_last();
}
/*--------------------------------------------------------------------------*/
SDP_CARD* MODEL_BUILT_IN_MOS3::new_sdp(COMMON_COMPONENT* c)const
{
  assert(c);
  if (COMMON_BUILT_IN_MOS* cc = dynamic_cast<COMMON_BUILT_IN_MOS*>(c)) {
    if (cc->_sdp) {
      cc->_sdp->init(cc);
      return cc->_sdp;
    }else{
      delete cc->_sdp;
      return new SDP_BUILT_IN_MOS3(c);
    }
  }else{
    return MODEL_BUILT_IN_MOS123::new_sdp(c);
  }
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS3::set_param_by_index(int i, std::string& value, int offset)
{
  switch (MODEL_BUILT_IN_MOS3::param_count() - 1 - i) {
  case 0: level = value; break; //3
  case 1: unreachable(); break;
  case 2: unreachable(); break;
  case 3: unreachable(); break;
  case 4: unreachable(); break;
  case 5: unreachable(); break;
  case 6: unreachable(); break;
  case 7: mos_level = value; break;
  case 8: kp = value; break;
  case 9: nfs_cm = value; break;
  case 10: vmax = value; break;
  case 11: theta = value; break;
  case 12: eta = value; break;
  case 13: kappa = value; break;
  case 14: delta = value; break;
  default: MODEL_BUILT_IN_MOS123::set_param_by_index(i, value, offset); break;
  }
}
/*--------------------------------------------------------------------------*/
bool MODEL_BUILT_IN_MOS3::param_is_printable(int i)const
{
  switch (MODEL_BUILT_IN_MOS3::param_count() - 1 - i) {
  case 0:  return (true);
  case 1:  return (false);
  case 2:  return (false);
  case 3:  return (false);
  case 4:  return (false);
  case 5:  return (false);
  case 6:  return (false);
  case 7:  return (mos_level != LEVEL);
  case 8:  return (!calc_kp);
  case 9:  return (true);
  case 10:  return (vmax.has_hard_value());
  case 11:  return (true);
  case 12:  return (true);
  case 13:  return (true);
  case 14:  return (true);
  default: return MODEL_BUILT_IN_MOS123::param_is_printable(i);
  }
}
/*--------------------------------------------------------------------------*/
std::string MODEL_BUILT_IN_MOS3::param_name(int i)const
{
  switch (MODEL_BUILT_IN_MOS3::param_count() - 1 - i) {
  case 0:  return "level";
  case 1:  return "=====";
  case 2:  return "=====";
  case 3:  return "=====";
  case 4:  return "=====";
  case 5:  return "=====";
  case 6:  return "=====";
  case 7:  return "diodelevel";
  case 8:  return "kp";
  case 9:  return "nfs";
  case 10:  return "vmax";
  case 11:  return "theta";
  case 12:  return "eta";
  case 13:  return "kappa";
  case 14:  return "delta";
  default: return MODEL_BUILT_IN_MOS123::param_name(i);
  }
}
/*--------------------------------------------------------------------------*/
std::string MODEL_BUILT_IN_MOS3::param_name(int i, int j)const
{
  if (j == 0) {
    return param_name(i);
  }else if (j == 1) {
    switch (MODEL_BUILT_IN_MOS3::param_count() - 1 - i) {
    case 0:  return "";
    case 1:  return "";
    case 2:  return "";
    case 3:  return "";
    case 4:  return "";
    case 5:  return "";
    case 6:  return "";
    case 7:  return "";
    case 8:  return "";
    case 9:  return "";
    case 10:  return "";
    case 11:  return "";
    case 12:  return "";
    case 13:  return "";
    case 14:  return "";
    default: return MODEL_BUILT_IN_MOS123::param_name(i, j);
    }
  }else if (i < 15) {
    return "";
  }else{
    return MODEL_BUILT_IN_MOS123::param_name(i, j);
  }
}
/*--------------------------------------------------------------------------*/
std::string MODEL_BUILT_IN_MOS3::param_value(int i)const
{
  switch (MODEL_BUILT_IN_MOS3::param_count() - 1 - i) {
  case 0:  return "3";
  case 1:  unreachable(); return "";
  case 2:  unreachable(); return "";
  case 3:  unreachable(); return "";
  case 4:  unreachable(); return "";
  case 5:  unreachable(); return "";
  case 6:  unreachable(); return "";
  case 7:  return mos_level.string();
  case 8:  return kp.string();
  case 9:  return nfs_cm.string();
  case 10:  return vmax.string();
  case 11:  return theta.string();
  case 12:  return eta.string();
  case 13:  return kappa.string();
  case 14:  return delta.string();
  default: return MODEL_BUILT_IN_MOS123::param_value(i);
  }
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS3::tt_prepare( COMPONENT* c)
{

	std::cerr << "MODEL_BUILT_IN_MOS3::tt_prepare\n";
        MODEL_BUILT_IN_MOS123::tt_prepare(c);

}

/*--------------------------------------------------------------------------*/
bool MODEL_BUILT_IN_MOS3::is_valid(const COMPONENT* d)const
{
  assert(d);
  return MODEL_BUILT_IN_MOS123::is_valid(d);
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_MOS3::stress_apply(COMPONENT* brh) const
{
  MODEL_BUILT_IN_MOS123::stress_apply(brh);

  DEV_BUILT_IN_MOS* d = prechecked_cast<DEV_BUILT_IN_MOS*>(brh);
  assert(d);
  COMMON_BUILT_IN_MOS* c = (COMMON_BUILT_IN_MOS*)(d->common());
  assert(c);
  SDP_BUILT_IN_MOS3* s = (SDP_BUILT_IN_MOS3*)(c->sdp());
  assert(s);
  ADP_BUILT_IN_MOS3* a = (ADP_BUILT_IN_MOS3*)(d->adp());
  assert(a);

  const MODEL_BUILT_IN_MOS3* m = this;


  std::cerr << "MODEL_BUILT_IN_MOS123::stress_apply ids_stress now: " << a->ids_stress->get() << "\n";

  a->vto = m->vto * exp ( 10000. * a->ids_stress->get() / c->w_in );

  std::cerr << "MODEL_BUILT_IN_MOS123::stress_apply: " <<  d->short_label() << " vto now: " << a->vto << "\n";


}
/*--------------------------------------------------------------------------*/
//void DEV_BUILT_IN_MOS3::tr_stress( )
//{
//  //const COMMON_BUILT_IN_MOS* c = prechecked_cast<const COMMON_BUILT_IN_MOS*>(common());
//  //assert(c);
//  //const SDP_BUILT_IN_MOS_BASE* s = prechecked_cast<const SDP_BUILT_IN_MOS_BASE*>(c->sdp());
//  //assert(s);
//
//  SDP_BUILT_IN_MOS_BASE* s= (  SDP_BUILT_IN_MOS_BASE* )  (( COMMON_BUILT_IN_MOS* ) common())->sdp();
//
//  s->ids_stress += ids * ids*( SIM::time0-SIM::time1);
//
//  std::cerr << "DEV_BUILT_IN_MOS3::tr_stress of "<<  short_label()  << ": ids: " << ids <<  "\n";
//  std::cerr << "DEV_BUILT_IN_MOS3::tr_stress of "<<  short_label()  << ": ids_stress: " << s->ids_stress <<  "\n";
//}
/*--------------------------------------------------------------------------*/


void MODEL_BUILT_IN_MOS3::tr_eval(COMPONENT* brh)const
{
  DEV_BUILT_IN_MOS* d = prechecked_cast<DEV_BUILT_IN_MOS*>(brh);
  assert(d);
  const COMMON_BUILT_IN_MOS* c = prechecked_cast<const COMMON_BUILT_IN_MOS*>(d->common());
  assert(c);
  const SDP_BUILT_IN_MOS3* s = prechecked_cast<const SDP_BUILT_IN_MOS3*>(c->sdp());
  assert(s);
  const MODEL_BUILT_IN_MOS3* m = this;
  const TDP_BUILT_IN_MOS3 T(d);
  const TDP_BUILT_IN_MOS3* t = &T;

    #define short_channel	(m->xj != NOT_INPUT  &&  m->xj > 0.)
    #define do_subthreshold	(m->nfs != 0.)
    #define use_vmax		(m->vmax != NOT_INPUT)
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    //trace1(d->long_label().c_str(), d->evaliter());
    trace3("", d->vds, d->vgs, d->vbs);
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    d->reverse_if_needed();
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* square root term */
    double sarg, v_phi_s, dsarg_dvbs;
    {
      if (d->vbs <= 0.) {
	v_phi_s = t->phi - d->vbs;
	sarg = sqrt(v_phi_s);
	dsarg_dvbs = -.5 / sarg;
	d->sbfwd = false;
	trace3("sb-ok", sarg, v_phi_s, dsarg_dvbs);
      }else{
	untested();
	sarg = t->sqrt_phi / (d->vbs / (2 * t->phi) + 1.);
	v_phi_s = sarg * sarg;
	dsarg_dvbs = -v_phi_s / (2 * t->phi*t->sqrt_phi);
	d->sbfwd = true;
	trace3("***sb-reversed***", sarg, v_phi_s, dsarg_dvbs);
      }
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* short channel effect, body effect */
    double fbody, dfbody_dvbs, qbonco, dqbdvb;
    {
      double fshort, dfs_dvbs;
      if (short_channel) {
	static const double D[3] = {.0631353, .8013292, -.01110777};
	double wp = m->xd * sarg;
	double wp_xj = wp / m->xj;
	double wc_xj = D[0] + D[1] * wp_xj + D[2] * wp_xj * wp_xj;
	double ld_xj = m->ld / m->xj;
	double xj_le = m->xj / s->l_eff;
	
	double arga = wc_xj + ld_xj;
	double argc = wp_xj / (wp_xj + 1.);
	double argb = sqrt(1. - argc * argc);
	fshort = 1. - xj_le * (arga * argb - ld_xj);
	
	double dwp_dvbs = m->xd * dsarg_dvbs;
	double darga_dvbs = (D[1] + D[2] * (wp_xj + wp_xj)) * dwp_dvbs / m->xj;
	double dargb_dvbs = -argc * argc * (1. - argc) * dwp_dvbs / (argb*wp);
	dfs_dvbs = -xj_le * (darga_dvbs * argb + arga * dargb_dvbs);
	trace2("short-channel", fshort, dfs_dvbs);
      }else{
	fshort = 1.;
	dfs_dvbs = 0.;
	trace2("not-short-channel", fshort, dfs_dvbs);
      }
      
      double gamma_fs = m->gamma * fshort;
      double fbodys = gamma_fs * .5 / (2 * sarg);
      double fnarrw = m->delta3 / s->w_eff;
      trace3("", gamma_fs, fbodys, fnarrw);
      
      fbody = fbodys + fnarrw;
      dfbody_dvbs = -fbodys * dsarg_dvbs / sarg + fbodys * dfs_dvbs / fshort;
      trace2("", fbody, dfbody_dvbs);
      
      qbonco = gamma_fs * sarg + fnarrw * v_phi_s;
      dqbdvb = gamma_fs * dsarg_dvbs + m->gamma * dfs_dvbs * sarg - fnarrw;
      trace2("", qbonco, dqbdvb);
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* threshold voltage */
    double vth, dvth_dvds, dvth_dvbs;
    {
      double sigma = m->eta * 8.15e-22 / (m->cox * s->l_eff*s->l_eff*s->l_eff);
      double vbix = t->vbi - sigma * d->vds;
      vth = vbix + qbonco;
      dvth_dvds = -(sigma);
      dvth_dvbs = dqbdvb;
      trace3("", vth, dvth_dvds, dvth_dvbs);
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* joint weak inversion and strong inversion */
    /* von */
    double xn, vtxn, dxn_dvbs, dvon_dvds, dvon_dvbs;
    {
      if (do_subthreshold) {
	xn = 1. + m->cfsox + qbonco / (2 * v_phi_s);
	vtxn = t->vt * xn;
	dxn_dvbs  = dqbdvb / (2*v_phi_s) - qbonco*dsarg_dvbs / (v_phi_s*sarg);
	trace3("do_sub", xn, vtxn, dxn_dvbs);
	
	d->von  = vth + vtxn;
	dvon_dvds = dvth_dvds;
	dvon_dvbs = dvth_dvbs + t->vt * dxn_dvbs;
	d->vgst = d->vgs - d->von;
	trace4("", d->von, dvon_dvds, dvon_dvbs, d->vgst);
	
	d->subthreshold = (d->vgs < d->von);
	d->cutoff = false;
      }else{
	xn = vtxn = dxn_dvbs = dvon_dvds = dvon_dvbs = 0.;
	d->von = vth;
	d->vgst = d->vgs - d->von;
	trace2("no_sub", vtxn, dxn_dvbs);
	trace4("", d->von, dvon_dvds, dvon_dvbs, d->vgst);
	
	d->subthreshold = false;
	d->cutoff = (d->vgs <= d->von);
	if (d->cutoff) {
	  trace0("***** cut off *****");
	  d->vdsat = 0.;
	  d->ids = 0.;
	  d->gmf = d->gmr = 0.;
	  d->gds = 0.;
	  d->gmbf = d->gmbr = 0.;
	  return;
	}
      }
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* device is on */
    /* mobility modulation by gate voltage */
    double vc, onfg, us, dfg_dvgs, dfg_dvds, dfg_dvbs, beta;
    {
      double vgsx = (d->subthreshold) ? d->von : d->vgs;
      vc = vgsx - vth;
      onfg = m->theta * vc + 1.;
      double fgate = 1. / onfg;
      trace3("", vc, onfg, fgate);
      
      us = t->uo * fgate;
      beta = t->beta * fgate;
      trace4("", t->beta, beta, t->uo, us);
      
      dfg_dvgs = -(m->theta) * fgate * fgate;
      dfg_dvds = -dfg_dvgs * dvth_dvds;
      dfg_dvbs = -dfg_dvgs * dvth_dvbs;
      trace3("", dfg_dvgs, dfg_dvds, dfg_dvbs);
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* saturation voltage */
    /* vdsat, saturated */
    double dvdsat_dvgs, dvdsat_dvds, dvdsat_dvbs;
    double onvdsc, vdsx;
    {
      double onfbdy = 1. / (fbody + 1.);
      double dvsdga = onfbdy;
      d->vdsat = vc * onfbdy;
      trace2("novm", d->vdsat, dvsdga);
      
      if (use_vmax) {
	double vdsc = s->l_eff * m->vmax / us;
	double argb = sqrt(d->vdsat * d->vdsat + vdsc * vdsc);
	d->vdsat += vdsc - argb;
	dvsdga *= (1. - d->vdsat / argb);
	trace2("vmax", d->vdsat, dvsdga);
	dvdsat_dvgs = dvsdga - (1. - vdsc / argb) * vdsc * dfg_dvgs * onfg;
	onvdsc = 1. / vdsc;
      }else{
	dvdsat_dvgs = dvsdga;
	onvdsc = NOT_VALID;
      }
      d->saturated = (d->vds > d->vdsat);
      vdsx =  (d->saturated) ? d->vdsat : d->vds;
      trace3("", d->vdsat, vdsx, onvdsc);
      
      dvdsat_dvds = -dvdsat_dvgs * dvth_dvds;
      dvdsat_dvbs = -dvdsat_dvgs * dvth_dvbs - d->vdsat * dfbody_dvbs * dvsdga;
      trace3("", dvdsat_dvgs, dvdsat_dvds, dvdsat_dvbs);
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* short cut exit if vds == 0 */
    if (vdsx == 0.) { /*900*/
      trace2("***** vdsx == 0 *****", d->vdsat, d->vds);
      d->ids = 0.;
      d->gmf = d->gmr = 0.;
      d->gds = beta * vc;
      d->gmbf = d->gmbr = 0.;
      if (d->subthreshold) {
	d->gds *= exp(d->vgst / vtxn);
      }
      return;
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* normalized drain current */
    {
      double cdo = vc - (fbody + 1.) * .5 * vdsx;
      double dcodvb = -dvth_dvbs - dfbody_dvbs * .5 * vdsx;
      trace3("", t->beta, cdo, dcodvb);
      
      trace4("", vc, fbody, dvth_dvds, vdsx);
      d->gmf  = vdsx;
      d->gds = vc - (fbody + 1. + dvth_dvds) * vdsx;
      d->gmbf = dcodvb * vdsx;
      d->ids = cdo * vdsx;
      trace4("1", d->ids, d->gmf, d->gds, d->gmbf);
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* scale, but without velocity saturation effect */
    {
      double cd1 = t->beta * d->ids;
      d->gmf  *= beta; d->gmf  += dfg_dvgs * cd1;
      d->gds *= beta; d->gds += dfg_dvds * cd1;
      d->gmbf *= beta;
      d->ids *= beta;
      trace4("2", d->ids, d->gmf, d->gds, d->gmbf);
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* velocity saturation factor */
    double fdrain, dfd_dvgs, dfd_dvds, dfd_dvbs;
    if (use_vmax) {
      assert(onvdsc != NOT_VALID);
      fdrain = 1. / (vdsx * onvdsc + 1.);
      double fd2 = fdrain * fdrain;
      double arga = fd2 * vdsx * onvdsc * onfg;
      dfd_dvgs = -dfg_dvgs * arga;
      dfd_dvds = -dfg_dvds * arga - fd2 * onvdsc;
      dfd_dvbs = -dfg_dvbs * arga;
      trace4("", fdrain, dfd_dvgs, dfd_dvds, dfd_dvbs);
      
      d->gmf  *= fdrain; d->gmf  += dfd_dvgs * d->ids;
      d->gds *= fdrain; d->gds += dfd_dvds * d->ids;
      d->gmbf *= fdrain; d->gmbf += dfd_dvbs * d->ids;
      d->ids *= fdrain;
      beta   *= fdrain;
      trace4("3", d->ids, d->gmf, d->gds, d->gmbf);
    }else{
      fdrain = 0.;	/* used only if use_vmax */
      dfd_dvgs = 0.;
      dfd_dvds = 0.;
      dfd_dvbs = 0.;
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* channel length modulation */
    double gds0;
    if (d->saturated) {
      double d_l, dl_dvd;
      double ddl_dvgs, ddl_dvds, ddl_dvbs;
      if (m->alpha == 0.) {
	d_l = dl_dvd = ddl_dvgs = ddl_dvds = ddl_dvbs = 0.;
      }else if (use_vmax) {	/* use_vmax && m->alpha != 0 */
	double gdsat = d->ids * (1. - fdrain) * onvdsc;
	gdsat = std::max(1e-12,gdsat);
	double gdoncd = gdsat / d->ids;
	double gdonfd = gdsat / (1. - fdrain);
	double gdonfg = gdsat * onfg;
	double dgdvg = gdoncd * d->gmf - gdonfd * dfd_dvgs + gdonfg * dfg_dvgs;
	double dgdvd = gdoncd * d->gds - gdonfd * dfd_dvds + gdonfg * dfg_dvds;
	double dgdvb = gdoncd *d->gmbf - gdonfd * dfd_dvbs + gdonfg * dfg_dvbs;
	
	double emax = d->ids / (s->l_eff * gdsat);
	double emax_o_ids   = emax / d->ids;
	double emax_o_gdsat = emax / gdsat;
	double demax_dvgs = emax_o_ids * d->gmf  - emax_o_gdsat * dgdvg;
	double demax_dvds = emax_o_ids * d->gds - emax_o_gdsat * dgdvd;
	double demax_dvbs = emax_o_ids * d->gmbf - emax_o_gdsat * dgdvb;
	
	double arga = emax * .5 * m->alpha;
	double argc = m->kappa * m->alpha;
	double argb = sqrt(arga * arga + argc * (d->vds - d->vdsat));
	d_l = argb - arga;
	dl_dvd = argc / (argb + argb);
	double dl_demax = (arga / argb - 1.) * .5 * m->alpha;
	ddl_dvgs = dl_demax * demax_dvgs;
	ddl_dvds = dl_demax * demax_dvds - dl_dvd;
	ddl_dvbs = dl_demax * demax_dvbs;
      }else{
	d_l = sqrt(m->kappa * (d->vds - d->vdsat) * m->alpha);
	dl_dvd = d_l * .5 / (d->vds - d->vdsat);
	ddl_dvgs = 0.;
	ddl_dvds = -dl_dvd;
	ddl_dvbs = 0.;
      }
      
      if (d_l > s->l_eff * .5) {	/* punch through approximation */
	d->punchthru = true;
	d_l = s->l_eff - s->l_eff*s->l_eff / (d_l*4.);
	double arga = (s->l_eff-d_l)*(s->l_eff-d_l) * 4./(s->l_eff*s->l_eff);
	ddl_dvgs *= arga;
	ddl_dvds *= arga;
	ddl_dvbs *= arga;
	dl_dvd *= arga;
      }else{
	d->punchthru = false;
      }
      
      if (m->alpha != 0) {
	double lfact = 1. / (1. - d_l / s->l_eff);
	d->ids *= lfact;
	double diddl = d->ids / (s->l_eff - d_l);
	d->gmf   = d->gmf  * lfact + diddl * ddl_dvgs;
	gds0    = d->gds * lfact + diddl * ddl_dvds;
	d->gmbf  = d->gmbf * lfact + diddl * ddl_dvbs;
	d->gmf  += gds0 * dvdsat_dvgs;
	d->gmbf += gds0 * dvdsat_dvbs;
	d->gds  = gds0 * dvdsat_dvds + diddl * dl_dvd;
      }else{
	gds0 = 0;
      }
      trace2("", d_l, dl_dvd);
      trace3("", ddl_dvgs, ddl_dvds, ddl_dvbs);
      trace3("4", d->ids, gds0, d_l);
    }else{
      d->punchthru = false;
      gds0 = 0;				/* not saturated */
    }
    trace4("4", d->ids, d->gmf, d->gds, d->gmbf);
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */ 
    /* weak inversion -- subthreshold region */
    if (d->subthreshold) {
      double wfact = exp(d->vgst / vtxn);
      d->ids *= wfact;
      double gms = d->gmf * wfact;
      double gmw = d->ids / vtxn;
      trace2("subth", gmw, gms);
      
      d->gmf   = gmw;
      d->gmf  += gds0 * dvdsat_dvgs * wfact;
      d->gds *= wfact;
      d->gds += (gms - gmw) * dvon_dvds;
      d->gmbf *= wfact;
      d->gmbf += (gms - gmw) * dvon_dvbs - gmw * d->vgst * dxn_dvbs / xn;
      trace4("5", d->ids, d->gmf, d->gds, d->gmbf);
    }
    if (d->reversed) {
      d->ids *= -1;
      d->gmr = d->gmf;
      d->gmbr = d->gmbf;
      d->gmf = d->gmbf = 0;
    }else{
      d->gmr = d->gmbr = 0.;
    }
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
