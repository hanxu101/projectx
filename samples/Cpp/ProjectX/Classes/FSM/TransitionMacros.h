#ifndef MMR_MMR_SYSTEM_UTILITIES_FSM_TRANSITIONMACROS_H__INCLUDED
#define MMR_MMR_SYSTEM_UTILITIES_FSM_TRANSITIONMACROS_H__INCLUDED


namespace MMR
{


//------------------------------------------------------------------------
// 
// Switch to a new state.
// 
//------------------------------------------------------------------------
#define MMR_SWITCH_TO_STATE( DestinationStateName )\
    {\
        assert(__functionName != MMR::Fsm<FsmOwner>::Function_Constructor && __functionName != MMR::Fsm<FsmOwner>::Function_Destructor);\
        GetFsm().SwitchState(MMR_STATE(DestinationStateName));\
        return MMR::FSR_FunctionInterrupted;\
    }


//------------------------------------------------------------------------
// 
// Switch to the previous state.
// 
//------------------------------------------------------------------------
#define MMR_SWITCH_TO_PREVIOUS_STATE()\
    {\
        assert(__functionName != MMR::Fsm<FsmOwner>::Function_Constructor && __functionName != MMR::Fsm<FsmOwner>::Function_Destructor);\
        GetFsm().SwitchToPreviousState();\
        return MMR::FSR_FunctionInterrupted;\
    }


//------------------------------------------------------------------------
// 
// Implement a transitions block.
// 
//------------------------------------------------------------------------
#define MMR_STATE_TRANSITION_BEGIN

#define NoTransitionAction ((void)0)

#define MMR_TRANSIT_TO_STATE( Expression, DoAction, DestinationStateName )\
    if (Expression)\
    {\
        DoAction;\
        MMR_SWITCH_TO_STATE(DestinationStateName);\
    }

#define MMR_STATE_TRANSITION_END


}


#endif
