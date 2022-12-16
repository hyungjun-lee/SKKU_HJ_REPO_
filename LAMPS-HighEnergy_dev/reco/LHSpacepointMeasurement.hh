#ifndef LHSPACEPOINTMEASUREMENT_HH
#define LHSPACEPOINTMEASUREMENT_HH

#include "/Users/ihyeongjun/LAMPS/GenFit/GenFit_src/core/include/AbsMeasurement.h"
#include "/Users/ihyeongjun/LAMPS/GenFit/GenFit_src/measurements/include/SpacepointMeasurement.h"
#include "/Users/ihyeongjun/LAMPS/GenFit/GenFit_src/core/include/TrackCandHit.h"

#include "KBHit.hh"

namespace genfit {
  //////////////////////////////////////////////////////////////////////////////////

  class LHSpacepointMeasurement : public SpacepointMeasurement
  {
    public:
      LHSpacepointMeasurement();
      LHSpacepointMeasurement(const KBHit* detHit, const TrackCandHit* hit);

      virtual LHSpacepointMeasurement* clone() const { return new LHSpacepointMeasurement(*this); }

    ClassDef(LHSpacepointMeasurement, 1)
  };

  //////////////////////////////////////////////////////////////////////////////////
}
#endif
