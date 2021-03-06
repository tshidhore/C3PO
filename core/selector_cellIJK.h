/*-----------------------------------------------------------------------------*\
                  ___   _____   _____   _____     ___   
                 / ___\/\  __`\/\  __`\/\  __`\  / __`\ 
                /\ \__/\ \ \_\ \ \ \_\ \ \ \_\ \/\ \_\ \
                \ \____\\ \  __/\ \  __/\ \  __/\ \____/
                 \/____/ \ \ \/  \ \ \/  \ \ \/  \/___/ 
                          \ \_\   \ \_\   \ \_\         
                           \/_/    \/_/    \/_/         

         A Compilation for Fluid-Particle Data Post PrOcessing

Copyright (C): 2014 DCS Computing GmbH (www.dcs-computing.com), Linz, Austria
               2014 Graz University of Technology (ippt.tugraz.at), Graz, Austria
---------------------------------------------------------------------------------
License
    CPPPO is licensed under the GNU LESSER GENERAL PUBLIC LICENSE (LGPL).

    Everyone is permitted to copy and distribute verbatim copies of this license
    document, but changing it is not allowed.

    This version of the GNU Lesser General Public License incorporates the terms
    and conditions of version 3 of the GNU General Public License, supplemented
    by the additional permissions listed below.

    You should have received a copy of the GNU Lesser General Public License
    along with CPPPO. If not, see <http://www.gnu.org/licenses/lgpl.html>.

	This code is designed for on-the-fly post processing of fluid-particle
	data (e.g., of velocity, pressure, concentration, temperature field).

	Parts of the code were developed in the frame of the NanoSim project funded
	by the European Commission through FP7 Grant agreement no. 604656.
\*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------
Description
  This class contains the functions needed to select one or more cells (position to cellId)
  using an OpenFOAM fully structured mesh. All cell volumes have to be equal! 
-----------------------------------------------------------------------------------*/

#ifdef SELECTOR_CLASS

SelectorStyle(cellIJK, SelectorCellIJK)

#else


#ifndef C3PO_SELECTOR_CELLIJK_H
#define C3PO_SELECTOR_CELLIJK_H

#include "c3po_base_accessible.h"
#include "selector_base.h"

namespace C3PO_NS
{


class SelectorCellIJK : public SelectorBase
{
    public:

      SelectorCellIJK(c3po *ptr,const char *_name);
      ~SelectorCellIJK();


    void begin_of_step();
    void middle_of_step() {};
    void end_of_step() {};

      
    int findNearestCell(double x, double y, double z);

      
    private:
    
   
    double tolerance_;

    int* max_;
    int* min_;
    double* cellCoord_;
    
    int* IJKlist_;
    
    
    
    bool checkPosition(double posA, double max, double min );
    bool checkPositionPeriodic(double posA, double max, double min );
    
    bool checkPositionSphere(double i_ijk, double j_ijk, double k_ijk, double r_, int cell_, double * delta_);
    bool checkPositionPeriodicSphere(double i_ijk, double j_ijk, double k_ijk, double r_, int cell_, double * delta_);
    
    bool checkPositionSphereDummy(double i_ijk, double j_ijk, double k_ijk, double r_, int cell_, double * delta_) {return true;};
   
    bool (SelectorCellIJK::*checkR)(double,double,double,double,int,double*);
    
    bool periodic_[3];
         
    void RunSelector();
    
    void fillArrays();
    void boundaryCorrections();
    
    int ijk2CellIDOF(int i_add_correct, int j_add_correct, int k_add_correct);
    void CellID2ijk(int center_Cell_ID, int* result); 
    
   
};

} //end c3po_NS

#endif
#endif
