// Copyright 2004 Michael E. Stillman

#ifndef _comp_hpp_
#define _comp_hpp_

extern char system_interruptedFlag;
extern int gbTrace;

#include "engine.h"
/* engine.h includes definitions of the stop conditions
   and of the status return values */
#include "hash.hpp"
#include "stop.hpp"

class GBComputation;
class ResolutionComputation;
class buffer;

class Computation : public mutable_object
{
private:
  enum ComputationStatusCode computation_status;
protected:
  StopConditions stop_;

  Computation();

  void set_status(enum ComputationStatusCode c);
  
  virtual bool stop_conditions_ok() = 0;
  // If the stop conditions in stop_ are inappropriate,
  // return false, and use ERROR(...) to provide an error message.

  virtual ~Computation();
public:
  ComputationOrNull *
  set_stop_conditions(M2_bool always_stop,
		      M2_bool stop_after_degree,
		      M2_arrayint degree_limit,
		      int basis_element_limit,
		      int syzygy_limit,
		      int pair_limit,
		      int codim_limit,
		      int subring_limit,
		      M2_bool just_min_gens,
		      M2_arrayint length_limit);
  // returns NULL if there is a general problem with one of the stop 
  // conditions.

  enum ComputationStatusCode status() const { return computation_status; }

  virtual int complete_thru_degree() const = 0;
  // This is computation specific information.  However, for homogeneous
  // GB's, the GB coincides with the actual GB in degrees <= the returned value.
  // For resolutions of homogeneous modules, the resolution 
  // coincides with the actual one in (slanted) degrees <= the returned value.

  virtual void start_computation() = 0;
  // Do the computation as specified by the stop conditions.
  // This routine should set the status of the computation.

  virtual GBComputation * cast_to_GBComputation() { return 0; }
  virtual ResolutionComputation * cast_to_ResolutionComputation() { return 0; }

  virtual void text_out(buffer &o) const;
};

#endif

// Local Variables:
// compile-command: "make -C $M2BUILDDIR/Macaulay2/e "
// End:
