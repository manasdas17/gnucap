/* vim:ts=8:sw=2:et:
 *
 * (c)2010 felix salfelder
 * nonGPL ?
 */


#include "e_aux.h"
#include "e_storag.h"
// #include "d_mos_base.h"

#include "globals.h"
#include "e_elemnt.h"
#include "u_adp.h"
#include "d_rcd_sym.h"

/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_RCD_SYM::do_stress_apply( COMPONENT*  ) const
{

}
/*--------------------------------------------------------------------------*/
void DEV_BUILT_IN_RCD_SYM::tr_stress() const
{
  const COMMON_BUILT_IN_RCD* c = static_cast<const COMMON_BUILT_IN_RCD*>(common());
  assert(c);
  assert(c->model());
  const MODEL_BUILT_IN_RCD* m = prechecked_cast<const MODEL_BUILT_IN_RCD*>(c->model());
  assert(m);
  assert(c->sdp());

  unreachable(); //obsolete.
  assert(false);

  if( m->positive) {
    if ( _Ccgfill->get_total() < 0 ){
      trace1(("DEV_BUILT_IN_RCD::tr_stress fill is negative: " + short_label()).c_str() ,  _Ccgfill->get_total() );
    }
    if (  _n[n_u].v0()  - _n[n_b].v0() < -1e-10 ){
      trace1(("DEV_BUILT_IN_RCD::tr_stress input is negative: " + 
            short_label()).c_str() ,   _n[n_u].v0()  - _n[n_b].v0() );
      assert (false );
    }
  }
  assert(!m->use_net());

  //double  fill = _n[n_ic].v0();
  double  fill = _Ccgfill->get_total();
  double  uin = _n[n_u].v0()  - _n[n_b].v0(); // FIXME,Uin/

  trace3("DEV_BUILT_IN_RCD::tr_stress ", _n[n_b].v0(), _n[n_u].v0(), _n[n_ic].v0() );

  // use positive values for pmos
  uin;

  double h = _sim->_dt0;
  double uend;
  double tau;

  double rc = c->__Rc(uin);
  if (fill < uin){
    trace2("DEV_BUILT_IN_RCD::tr_stress open", fill, uin);
    double re = c->__Re(uin);
    tau = ( rc / ( 1+rc/re )  ) ;
    uend = uin / (re/rc +1) ;
  }else{
    // diode closed.
    trace0("DEV_BUILT_IN_RCD::tr_stress closed");
    tau=rc;
    uend=0;
  }

  double newfill;
  switch(_sim->_stepno){
        case 0:
        case 1:
        default:
        newfill = (fill - uend) * exp(-h/tau) + uend;
  }

  // double bulkpot=_n[n_b].v0();

  trace6("DEV_BUILT_IN_RCD::tr_stress ", fill, h, tau, newfill, uin, uend );

//  _sim->_v0[_n[n_ic]->m_()] = newfill ; 
//  _sim->_vdc[_n[n_ic]->m_()] = newfill ; 

  _Ccgfill->tr_add(newfill-fill);
  assert(newfill==newfill);
  trace4("DEV_BUILT_IN_RCD::tr_stress ", fill, h, tau, (newfill-fill)/h );
}
///*--------------------------------------------------------------------------*/
namespace MODEL_BUILT_IN_RCD_DISPATCHER { 
  static DEV_BUILT_IN_RCD_SYM p2d;
  static MODEL_BUILT_IN_RCD_SYM p2(&p2d);
  static DISPATCHER<MODEL_CARD>::INSTALL
    d2(&model_dispatcher, "rcdsym", &p2);
}
///*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_RCD_SYM::do_expand(const  COMPONENT* ) const
{
}
/*--------------------------------------------------------------------------*/
std::string MODEL_BUILT_IN_RCD_SYM::dev_type()const
{
  return "rcdsym";
}
/*--------------------------------------------------------------------------*/
MODEL_BUILT_IN_RCD_SYM::MODEL_BUILT_IN_RCD_SYM(const BASE_SUBCKT* p) 
  : MODEL_BUILT_IN_RCD(p){ }
/*--------------------------------------------------------------------------*/
MODEL_BUILT_IN_RCD_SYM::MODEL_BUILT_IN_RCD_SYM(const MODEL_BUILT_IN_RCD_SYM& p)  
  : MODEL_BUILT_IN_RCD(p){ }
/*--------------------------------------------------------------------------*/
void DEV_BUILT_IN_RCD_SYM::expand() {
  assert(_n);
  assert(common());
  const COMMON_BUILT_IN_RCD* c = static_cast<const COMMON_BUILT_IN_RCD*>(common());
  assert(c);
  assert(c->model());
  const MODEL_BUILT_IN_RCD* m = prechecked_cast<const MODEL_BUILT_IN_RCD*>(c->model());
  assert(m);
  assert(c->sdp());
  const SDP_BUILT_IN_RCD* s = prechecked_cast<const SDP_BUILT_IN_RCD*>(c->sdp());
  assert(s);

  trace0("DEV_BUILT_IN_RCD_SYM::expand()");

  if (_sim->is_first_expand()) {
    precalc_first();
    precalc_last();
    // local nodes
    //assert(!(_n[n_ic].n_()));
    //BUG// this assert fails on a repeat elaboration after a change.
    //not sure of consequences when new_model_node called twice.
    if (!(_n[n_ic].n_())) {
      if (false) {
        _n[n_ic] = _n[n_b];
      }else{
        _n[n_ic].new_model_node("." + long_label() + ".ic", this);
      }
    }else{
      if (false) {
        assert(_n[n_ic] == _n[n_b]);
      }else{
        //_n[n_ic].new_model_node("ic." + long_label(), this);
      }
    }
  }
}
/*--------------------------------------------------------------------------*/
void MODEL_BUILT_IN_RCD_SYM::do_tr_stress( const COMPONENT* brh) const {

  const DEV_BUILT_IN_RCD* c = (const DEV_BUILT_IN_RCD*) brh;
  const COMMON_BUILT_IN_RCD* cc = static_cast<const COMMON_BUILT_IN_RCD*>(c->common());
  //double  fill = _n[n_ic].v0();
  //

  double  fill = c->_Ccgfill->get_total();
  double  ueff = c->involts();

  trace1("MODEL_BUILT_IN_RCD_SYM::tr_stress ", c->involts() );

  // use positive values for pmos
  ueff=ueff;

  double h = _sim->_dt0;
  double uend;
  double tau;
  double re=0;

  double rc = cc->__Rc(ueff);

  if (fill < ueff){
    trace2("DEV_BUILT_IN_RCD::tr_stress open", fill, ueff);
    re = cc->__Re(ueff);
    tau = ( rc / ( 1+rc/re )  ) ;
    uend = ueff / (re/rc +1) ;
  }else{
    // diode closed.
    trace3("DEV_BUILT_IN_RCD::tr_stress closed", rc, fill, ueff);
    tau=rc;
    uend=0;
  }

  double newfill;
  switch(_sim->_stepno){
        case 0:
        case 1:
        default:
        newfill = (fill - uend) * exp(-h/tau) + uend;
  }

  trace6("DEV_BUILT_IN_RCD::tr_stress ", fill, h, tau, (newfill-fill)/h, rc, re );
  assert(newfill == newfill);
  c->_Ccgfill->tr_add(newfill-fill);
}
/*--------------------------------------------------------------------------*/
DEV_BUILT_IN_RCD_SYM::DEV_BUILT_IN_RCD_SYM()
  :DEV_BUILT_IN_RCD()
{
//  _n = _nodes;
//  attach_common(&Default_BUILT_IN_RCD);

//  ++_count;
  // overrides
}
/*--------------------------------------------------------------------------*/
int  MODEL_BUILT_IN_RCD_SYM::tt_region(const COMPONENT* brh) const{
  const DEV_BUILT_IN_RCD* c = (const DEV_BUILT_IN_RCD*) brh;

  assert(c);
  return ( (c->_Ccgfill)->region() );
}


/*--------------------------------------------------------------------------*/
ADP_NODE* MODEL_BUILT_IN_RCD_SYM::new_adp_node(const COMPONENT* c) const{
  return new ADP_NODE_RCD(c);
}
