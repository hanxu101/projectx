#ifndef MMR_MMR_SYSTEM_UTILITIES_FSM_FSMMACROS_H__INCLUDED
#define MMR_MMR_SYSTEM_UTILITIES_FSM_FSMMACROS_H__INCLUDED


namespace MMR
{


//------------------------------------------------------------------------
// 
// Declare a Finite State Machine (Fsm) in a class.
//
// Note: Must be call before all state and superstate.
//       And only in the base class.
// 
//------------------------------------------------------------------------
#define MMR_DECLARE_FSM( ThisClassName )\
    typedef ThisClassName FsmOwner;\
    typedef ThisClassName FsmThisClass;\
    const MMR::Fsm<FsmOwner>& GetFsm() const {return __fsm;}\
    MMR::Fsm<FsmOwner>& GetFsm() {return __fsm;}\
    MMR::Fsm<FsmOwner> __fsm


//------------------------------------------------------------------------
// 
// Overload a Fsm in a derived class.
//
// Note: Must be call before all state and superstate.
//       The base class must contains the Fsm.
// 
//------------------------------------------------------------------------
#define MMR_OVERLOAD_FSM( ThisClassName )\
    typedef ThisClassName FsmThisClass


//------------------------------------------------------------------------
// 
// Initialize the Fsm with an initial state.
// 
//------------------------------------------------------------------------
#define MMR_INIT_FSM( InitialStateName )\
    GetFsm().Init(this, MMR_STATE(InitialStateName))


//------------------------------------------------------------------------
// 
// Update the Fsm.
// 
//------------------------------------------------------------------------
#define MMR_UPDATE_FSM()\
    GetFsm().Update()


}


#endif
