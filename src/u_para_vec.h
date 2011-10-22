#include "e_cardlist.h"
#include "u_parameter.h"
#ifndef PV_H
#define PV_H

#include <vector>
#include "md.h"

using namespace std;

// this is just an experiment

//template <class T>
//class PARAVEC :  PARAMETER< vector<PARAMETER<T> > > {
//	public:
//
//	  std::string string()const;
//};
/*=========================*/
//struct dummy{};
//template <> inline dummy PARAMETER<dummy>::_NOT_INPUT() const { return dummy();}
//template <> inline dummy PARAMETER<dummy>::my_infty()const{ return dummy(); }
//inline string to_string(dummy){unreachable();return "";}

//template <>
template <class T>
class PARAMETER<vector<PARAMETER<T> > > : public PARA_BASE{
	private:
		mutable vector<PARAMETER<T> > _v;
		vector<PARAMETER<T> > _NOT_INPUT() const;
	public:
		operator vector<PARAMETER<T> >()const {return _v;}
  //typedef std::vector< PARAMETER<T> > t;
		explicit PARAMETER(T v) : PARA_BASE("#"), _v(v) {}
		PARAMETER() : PARA_BASE(), _v(vector<PARAMETER<T> >()) {}
		PARAMETER(const PARAMETER<vector<PARAMETER<T> > >& p) :
			PARA_BASE(p), _v(p._v){ }

//		void	print(OMSTREAM& o)const		{o << string();}
//		void	print(ostream& o)const		{o << string();}

		std::string string()const;
		//vector<PARAMETER<T> >  _NOT_INPUT() const;
		void	operator=(const std::string& s);
		void	operator=(const PARAMETER<vector<PARAMETER<T> > >& p)	{_v = p._v; _s = p._s;}
		void	operator=(const vector<PARAMETER<T> >& v)		{_v = v; _s = "#";}
		vector<PARAMETER<T> >	e_val(const vector<PARAMETER<T> >& def,
		                              const CARD_LIST* scope)const;
		std::string to_string(vector< PARAMETER<T> > n) const;

		operator std::string()const;
		size_t size()const{return _v.size();}

};
//============================================================
template <class T>
PARAMETER<vector<PARAMETER<T> > >::operator  std::string()const{
	return " ";
}
/*===============================*/
#define TP PARAMETER<vector<PARAMETER<T> > >
template <class T>
inline std::string PARAMETER<vector<PARAMETER<T> > >::string()const{
  std::string ret("V");
  if (PARAMETER<vector<PARAMETER<T> > >::_s == "#") {
    ret+= "(";
  }else if (_s == "") {
    ret+= "NA(";
  }else{
    return _s;
  }
  for(unsigned  i=0; i<TP::_v.size()  ; i++){
    ret+= (i)?",":"";
    ret+= _v[i];
  }
  ret+=")";
  return ret;
}
/*===============================*/
//template <class T>
//std::string PARAMETER<vector<PARAMETER<T> > >::to_string(vector< PARAMETER<T> > n) const
//{
//  //t::iterator i = n.begin();
//  std::vector< PARAMETER<T> >::iterator i = n.begin();
//  string buf("");
//  // FIXME: remove one ,
//  if (n.size()==0){return "( )";}
//
//  buf += to_string("(")+ to_string(*i);
//  ++i;
//
//  while (i!=n.end()){
//    buf += std::string(", ") + to_string(*i);
//    ++i;
//  }
//  return buf + std::string(" )");;
//}

/*=========================*/
//template <>
//std::vector<double> PARAMETER<std::vector<double> >::e_val(const
//    std::vector<double>& , const CARD_LIST* )const;
/*--------------------------------------------------------------------------*/
typedef PARAMETER<double> dp;

//template <>
//template <class T>
//inline vector<PARAMETER<T> >
//           PARAMETER<vector<PARAMETER<T> > >::e_val(const vector<PARAMETER<T> >& , const CARD_LIST* )const{
//				  incomplete();
//
//			  }
///*--------------------------------------------------------------------------*/
/*=========================*/

//template <>
//std::string PARAMETER<vector<PARAMETER<vector<PARAMETER<double> > > > >::string()const;
/*=========================*/

//template <>
//std::string PARAMETER<vector<PARAMETER<double> > >::string()const;
/*=========================*/
//template <> 
//template <class T>
//inline vector<PARAMETER<T> > PARAMETER<vector<PARAMETER<T> > >::_NOT_INPUT() const {
//  untested();
//  return std::vector< PARAMETER<T> >(0);
//}
//============================================================
template <class T>
inline vector<PARAMETER<T> > PARAMETER<vector<PARAMETER<T> > >::_NOT_INPUT() const {
  	return vector<PARAMETER< T> > ();
}
//============================================================
/*--------------------------------------------------------------------------*/
//template <> 
//inline std::vector<double> PARAMETER< std::vector<double> >::_NOT_INPUT() const {
//  untested();
//  return std::vector<double>(0);
//}
/*=========================*/
/*--------------------------------------------------------------------------*/
template<class T>
void PARAMETER<vector<PARAMETER<T> > >::operator=(const std::string& s){
  trace1("PARAMETER dvv =" , s);

  CS cmd(CS::_STRING,s);
  //typedef std::vector<PARAMETER<T> > TT;
  // TT::iterator a;
  //std::vector<PARAMETER<T> >::iterator a;
  //a = _v.begin();
  _v.clear();
 // (_v.begin(),_v.end());
  // FIXME: accept strings and parse...
  std::string vect;

  cmd.skipbl();

  for(;;){
    //if (! cmd.umatch("(")){
	 //   untested();
	 //   break;
	 //}
	 if(!cmd.more()) break;

  //  cmd >> vect;
    trace1("PARAMETER matrix loop", cmd.tail());
    vect = cmd.ctos(",","(",")","");
    trace1("PARAMETER matrix ctosd", vect);

    PARAMETER<T > d;
    //d =  '(' + vect + ')'; 
     d = vect;
    _v.push_back( d );

    cmd.skip1b(')');
    trace1("PARAMETER matrix loop pushed back ", d);
  }
  _s = "#";
  trace2("PARAMETER done matrix loop", cmd.tail(), *this);
}
// FIXME: templatify
// template<class T>
//string to_string(vector<PARAMETER<double> > n);
//string to_string(vector< PARAMETER< vector< PARAMETER<double> > > > n);
/*--------------------------------------------------------------------------*/

typedef vector<PARAMETER<double> > dpv;
typedef vector<PARAMETER<dpv> > dpvv;

//#include "u_parameter.h"
template<>
inline CS&     CS::operator>>(vector<PARAMETER<vector<PARAMETER<double> > > >& x);
//----------------------------------------------------------------
/*--------------------------------------------------------------------------*/
template<class T>
inline string to_string(vector<PARAMETER<T> > n)
{

 return n; // use operator.
//  string buf("");
//  // FIXME: remove one ,
//  if (n.size()==0){return "( )";}
//
//  vector<PARAMETER<T> >::iterator i=n.begin();
//  buf += string("(")+ftos((double)*i, 0, 7, 0);
//  ++i;
//
//  while (i!=n.end()){
//    buf += std::string(", ") + ftos((double)*i, 0, 7, 0);
//    ++i;
//  }
//  return buf + std::string(" )");;
}
//========================================================================
//template<class T>
//inline vector<PARAMETER<T> > PARAMETER<vector<PARAMETER<T> > >::e_val(
//    const vector<PARAMETER<T> >& def, const CARD_LIST* scope)const{
//
//  trace2("dp::e_val", _s, _v.size());
//  assert(def.size() >= _v.size());
//  assert(_s=="" ||  _v.size());
//
//  for(unsigned  i=0; i<_v.size()  ; i++){
//    _v[i].e_val(def[i], scope);
//  }
//
//  return _v;
//
//}
/*-----------------------------------*/
//template<class T>
//CS&     CS::operator>>(vector<PARAMETER<vector<PARAMETER<double> > > >& ){
//
//  trace0("CS::operator");
//  incomplete();
//  return *this;
//}
/*-----------------------------------*/
template <class T>
inline vector<PARAMETER<T> >
PARAMETER<vector<PARAMETER<T> > >::e_val(const vector<PARAMETER<T> >& def, const CARD_LIST* scope)const
{
  trace2("PARAMETER dvv::e_val", _s, _v.size());
  trace1("PARAMETER dvv::e_val", (std::string)(*this));
  trace1("PARAMETER dvv::e_val", def.size() );

  //  CS c(CS::_STRING,_s);
  // FIXME: accept strings and parse...
  for(unsigned  i=0; i<_v.size()  ; i++){
    PARAMETER<T>  D;
	 if (i < def.size()){
		 D = def[i];
	 }
	 trace2("PARAMETER vector eval", i,_v[i]);
    _v[i].e_val(D, scope);
  }
  trace0("PARAMETER vector eval done");
  return _v;
}
/*===============================*/
#endif
