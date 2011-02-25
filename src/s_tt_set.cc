

#include "s_tt.h"

namespace TT {
	void TTT::setup(CS& Cmd)
	{
		_tstart.e_val(NOT_INPUT, _scope);
		_tstop.e_val(NOT_INPUT, _scope);
		_tstep.e_val(NOT_INPUT, _scope);
		_Tstop.e_val(NOT_INPUT, _scope);
		_Tstep.e_val(NOT_INPUT, _scope);


		// nonsense
		// TRANSIENT::setup( Cmd);

		_cont = true;
		_tt_cont = true;
		if (Cmd.match1("'\"({") || Cmd.is_pfloat()) {
			PARAMETER<double> arg1, arg2, arg3, arg4, arg5, arg6;
			Cmd >> arg1;
			arg1.e_val(0.0,_scope);
			if (Cmd.match1("'\"({") || Cmd.is_float()) {
				Cmd >> arg2;
				arg2.e_val(0.0,_scope);
			}else{itested();
			}
			if (Cmd.match1("'\"({") || Cmd.is_float()) {
				Cmd >> arg3;
				arg3.e_val(0.0,_scope);
			}else{
			}
			if (Cmd.match1("'\"({") || Cmd.is_float()) {
				Cmd >> arg4;
				arg4.e_val(0.0,_scope);
			}else{
			}
			if (Cmd.match1("'\"({") || Cmd.is_float()) {
				Cmd >> arg5;
			}else{
			}
			if (Cmd.match1("'\"({") || Cmd.is_float()) {
				Cmd >> arg6;
			}else{
			}

			trace4(("TTT::setup args " + std::string(Cmd)).c_str(), arg1, arg2 , arg3 , arg4);

			if (arg4.has_hard_value()) {	    /* 4 args: all */
				trace0("TTT::setup have 4");
				_tt_cont=false;
				assert(arg3.has_hard_value());
				assert(arg2.has_hard_value());
				assert(arg1.has_hard_value());
				arg1.e_val(0.,_scope);
				arg2.e_val(0.,_scope);
				arg3.e_val(0.,_scope);

				_tstep  = arg1;
				_tstop  = arg2;
				_Tstep  = arg3;
				_Tstop  = arg4;
				_Tstart = 0; //HACK?
				assert((double)_tstep!=0);

				trace4("TTT::setup ", _tstep, _tstop , _Tstep , _Tstop);

			} else if (arg3.has_hard_value() ) {
				trace0("TTT::setup have 3");
				_tt_cont = false;
				_Tstart = arg1;
				_Tstep = arg2;
				_Tstop = arg3;

			} else if (arg2.has_hard_value() ) {
				trace0("TTT::setup have 2");
				_Tstart = _sim->_last_Time;
				if ((double)_Tstart == 0){
					// there was no previous run.
					_tstep = arg1;
					_tstop = arg2;
					_Tstop = 0;

				}else{
					// there was a run already

					if(arg1<arg2){
						_Tstop  = arg2; 
						_Tstep = arg1;
					}else{
						_Tstop  = arg1; 
						_Tstep = arg2;
					}
				}


				trace4("TTT::setup 2 args ", _tstep, _tstop , _Tstep , _Tstop);


			} else if (arg1.has_hard_value() ) {
				trace0("TTT::setup have 1");
				_Tstart = _sim->_last_Time;
				_Tstop  = arg1; // as tran

				// to trigger prints... (hack?)
				if(double(_Tstop) == 0) _Tstop = double( _Tstart );

				if((!_Tstep.has_hard_value() )|| ((double)_Tstep == 0)) {
					trace1("set Tstep ", _Tstop);
					_Tstep=_Tstop;
				} else {
					trace1("set Tstep ", _Tstep);
				}

			} else {
				unreachable();
				assert (!arg1.has_hard_value());   // for now...

				double oldrange = _Tstop - _Tstart;
				_Tstart = _sim->_last_Time;
				_Tstop  = _sim->_last_Time + oldrange;
			}
		}else{ /* no args */
			// std::cerr << "setup ttt -- no args\n";
			double oldrange = _Tstop - _Tstart;
			_Tstart = _sim->_last_Time;
			_Tstop  = _sim->_last_Time + oldrange;
		}
		if (Cmd.match1("'\"({") || Cmd.is_pfloat()) {
			Cmd >> _dtmax_in;
		}else{
		}

		if(_trace>0 )
			_out << "* opt\n";
		options(Cmd);


		_tstart.e_val(0., _scope);
		_tstop.e_val(NOT_INPUT, _scope);
		_tstep.e_val(NOT_INPUT, _scope);

		//Time1 = 
		_sim->_Time0 = _Tstart;
		_Time1 = _Tstart;


		if (!_tstep.has_good_value()) {
			throw Exception("transient: Time step is required");
		}else if (_tstep==0.) {itested();
			throw Exception("Time step = 0");
		}else{
		}

		if (_dtmax_in.has_hard_value()) {
			_dtmax = _dtmax_in;
		}else if (_skip_in.has_hard_value()) {
			_dtmax = _tstep / double(_skip_in);
		}else{
			_dtmax = std::min(_dtmax_in, _tstep);
		}

		_dTmin= _tstop;
		_sim->_dTmin= _tstop;

		if (_dTmin_in.has_hard_value()) {
			_dTmin = _dTmin_in;
		}else if (_dtratio_in.has_hard_value()) {
			_dTmin = _dTmax / _dTratio_in;
		}else{
			// use larger of soft values
			// _dTmin = std::max(double(_dTmin_in), _dTmax/_dTratio_in);
			// _dTmin=0.5; // HACK
		}


		if  ( _Tstart < _sim->_last_Time  ||  _sim->_last_Time <= 0.) {
			//    _out << "* last_Time " << _sim->_last_Time << "\n";
			_tt_cont = false;
			_Time1 = _sim->_Time0 = 0.;
		}else{
			untested();
			_tt_cont = true;
			_Time1 = _sim->_Time0 = _sim->_last_Time;
		}

		// TRANSIENT setup

		_tstart.e_val(0., _scope);
		_tstop.e_val(NOT_INPUT, _scope);
		_tstep.e_val(NOT_INPUT, _scope);

		if  (_tt_cont){

		}else{
			_cont = false;
			time1 = _sim->_time0 = 0.;
		}
		//{}else{
		//  untested();
		// _cont = true;
		//  time1 = _sim->_time0 = _sim->_last_time;
		// }
		_sim->_freq = ((_tstop > _tstart) ? (1 / (_tstop - _tstart)) : (0.));

		if (!_tstep.has_good_value()) {
			throw Exception("transient: time step is required");
		}else if (_tstep==0.) {itested();
			throw Exception("time step = 0");
		}else{
		}

		if (_dtmax_in.has_hard_value()) {
			_dtmax = _dtmax_in;
		}else if (_skip_in.has_hard_value()) {
			_dtmax = _tstep / double(_skip_in);
		}else{
			_dtmax = std::min(_dtmax_in, _tstep);
		}

		if (_dtmin_in.has_hard_value()) {
			_sim->_dtmin = _dtmin_in;
		}else if (_dtratio_in.has_hard_value()) {
			_sim->_dtmin = _dtmax / _dtratio_in;
		}else{
			// use larger of soft values
			_sim->_dtmin = std::max(double(_dtmin_in), _dtmax/_dtratio_in);
		}

		steps_total_out_ = (int) (1 + ceil( ( (_tstop - _tstart ) / _tstep ) ));
		steps_total_out_ = steps_total_out_ ;
		trace4( "TTT::setup ",  steps_total_out_ , _tstep , _tstop ,_tstart );

	}
	/*--------------------------------------------------------------------------*/
}
