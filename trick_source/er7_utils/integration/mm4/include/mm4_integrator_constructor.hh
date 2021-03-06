/**
 * @if Er7UtilsUseGroups
 * @addtogroup Er7Utils
 * @{
 * @addtogroup Integration
 * @{
 * @endif
 */

/**
 * @file
 * Defines the class MM4IntegratorConstructor, which constructs integrators
 * that use MM4 integration.
 */

/*
Purpose: ()
*/


#ifndef ER7_UTILS_MM4_INTEGRATOR_CONSTRUCTOR_HH
#define ER7_UTILS_MM4_INTEGRATOR_CONSTRUCTOR_HH

// System includes

// Interface includes
#include "er7_utils/interface/include/er7_class.hh"

// Model includes
#include "er7_utils/integration/core/include/integrator_constructor.hh"


namespace er7_utils {

/**
 * Create state and time integrators that propagate using standard MM4.
 */
class MM4IntegratorConstructor : public IntegratorConstructor {
ER7_UTILS_MAKE_SIM_INTERFACES(MM4IntegratorConstructor)

   // Note: The default constructor, copy constructor, assignment operator,
   // and destructor for this class are not declared.
   // The implicit C++ defaults suffice for this class.

public:
   // Static member functions.

   /**
    * Named constructor; create an MM4IntegratorConstructor instance.
    * The caller is responsible for deleting the returned object.
    * @return Newly created MM4IntegratorConstructor instance.
    */
   static IntegratorConstructor* create_constructor (void);


   // Member functions.

   /**
    * Return the class name.
    */
   virtual const char * get_class_name (void) const
   { return "MM4IntegratorConstructor"; }

   /**
    * Modified midpoint 4 is a second order technique; it provides but does not
    * implement a first order ODE integrator. It neither provides nor implements
    * a generalized step second order ODE integrator.
    */
   virtual bool implements (Integration::ODEProblemType problem_type) const
   {
      return (problem_type != Integration::FirstOrderODE) &&
             (problem_type != Integration::GeneralizedStepSecondOrderODE);
   }

   /**
    * Modified midpoint 4 does not provide a generalized step second order
    * ODE integrator.
    */
   virtual bool provides (Integration::ODEProblemType problem_type) const
   {
      return (problem_type != Integration::GeneralizedStepSecondOrderODE);
   }

   /**
    * Create a duplicate of the constructor.
    * The caller is responsible for deleting the returned object.
    * @return Duplicated constructor.
    */
   virtual IntegratorConstructor * create_copy (void) const;

   /**
    * Create an integration controls that guides the MM4 integration process.
    * The caller is responsible for deleting the created object.
    * @return Integration controls object
    */
   virtual IntegrationControls * create_integration_controls (void) const;

   /**
    * Create a surrogate integrator to solve a first order ODE.
    * The caller is responsible for deleting the created object.
    * @return State integrator
    * @param[in]     size      State size
    * @param[in,out] controls  Integration controls
    */
   virtual FirstOrderODEIntegrator * create_first_order_ode_integrator (
      unsigned int size,
      IntegrationControls & controls) const;

   /**
    * Create an MM4 state integrator for a simple second order ODE.
    * The caller is responsible for deleting the created object.
    * @return State integrator
    * @param[in]     size      State size
    * @param[in,out] controls  Integration controls
    */
   virtual SecondOrderODEIntegrator * create_second_order_ode_integrator (
      unsigned int size,
      IntegrationControls & controls) const;

   /**
    * Create an MM4 state integrator for a generalized second order ODE
    * where generalized position is advanced with the use of the
    * position derivative function.
    * The caller is responsible for deleting the created object.
    * @return State integrator
    * @param[in]     position_size  Size of the generalized position
    * @param[in]     velocity_size  Size of the generalized velocity
    * @param[in]     deriv_funs     Position derivative functions container
    * @param[in,out] controls       Integration controls
    */
   virtual SecondOrderODEIntegrator *
   create_generalized_deriv_second_order_ode_integrator (
      unsigned int position_size,
      unsigned int velocity_size,
      const GeneralizedPositionDerivativeFunctions & deriv_funs,
      IntegrationControls & controls) const;

   /**
    * Indicate whether the integration technique explicitly solves a second
    * order ODE. Modified midpoint 4 is such a technique.
    * @return Always returns true.
    */
   virtual bool is_second_order_ode_technique (void) const
   { return true; }


   /**
    * MM4 uses three steps per cycle.
    * \return Always returns 3.
    */
   virtual unsigned int get_transition_table_size (void) const
   { return 3; }
};

}


#ifdef ER7_UTILS_NEED_AUX_INCLUDES
#include "er7_utils/integration/core/include/single_cycle_integration_controls.hh"
#include "er7_utils/integration/rk2_midpoint/include/rk2_midpoint_first_order_ode_integrator.hh"
#include "mm4_second_order_ode_integrator.hh"
#endif


#endif
/**
 * @if Er7UtilsUseGroups
 * @}
 * @}
 * @endif
 */
