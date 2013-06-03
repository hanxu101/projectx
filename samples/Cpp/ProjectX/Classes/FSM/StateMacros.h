#ifndef MMR_MMR_SYSTEM_UTILITIES_FSM_STATEMACROS_H__INCLUDED
#define MMR_MMR_SYSTEM_UTILITIES_FSM_STATEMACROS_H__INCLUDED


namespace MMR
{


//------------------------------------------------------------------------
// 
// State accessor.
// 
//------------------------------------------------------------------------
#define	MMR_STATE( StateName )\
    (MMR::Fsm<FsmOwner>::State)&FsmThisClass::StateName##_State


//------------------------------------------------------------------------
// 
// Declare a state (in the .h).
// 
//------------------------------------------------------------------------
#define	MMR_DECLARE_STATE( StateName )\
    MMR::E_FsmStateResult StateName##_State(int __functionName)

#define	MMR_DECLARE_VIRTUAL_STATE( StateName )\
    virtual MMR_DECLARE_STATE(StateName)


//------------------------------------------------------------------------
// 
// Implement a state (in the .cpp).
// 
//------------------------------------------------------------------------
#define	MMR_IMPLEMENT_STATE_BEGIN( ClassName, StateName )\
    MMR::E_FsmStateResult ClassName::StateName##_State(int __functionName)\
    {\
        MMR::E_FsmStateResult __returnCode = MMR::FSR_FunctionNotHandled;\
        if (false)

#define	MMR_IMPLEMENT_STATE_END\
        \
        return __returnCode;\
    }


//------------------------------------------------------------------------
// 
// Implement the Constructor, Destructor and Update functions of a state.
// 
//------------------------------------------------------------------------
#define	MMR_STATE_CONSTRUCTOR_BEGIN    MMR_STATE_FUNCTION_BEGIN_INTERNAL( Constructor )
#define	MMR_STATE_CONSTRUCTOR_END      MMR_STATE_FUNCTION_END

#define	MMR_STATE_DESTRUCTOR_BEGIN     MMR_STATE_FUNCTION_BEGIN_INTERNAL( Destructor )
#define	MMR_STATE_DESTRUCTOR_END       MMR_STATE_FUNCTION_END

#define	MMR_STATE_UPDATE_BEGIN         MMR_STATE_FUNCTION_BEGIN_INTERNAL( Update )
#define	MMR_STATE_UPDATE_END           MMR_STATE_FUNCTION_END

#define	MMR_STATE_FUNCTION_BEGIN_INTERNAL( FunctionName ) \
        } else if (__functionName == MMR::Fsm<FsmOwner>::Function_##FunctionName)\
        {\
            __returnCode = MMR::FSR_FunctionHandled;

//------------------------------------------------------------------------
// 
// Implement a custom function of a state.
// 
//------------------------------------------------------------------------
#define	MMR_STATE_FUNCTION_BEGIN( FunctionName ) \
        } else if (__functionName == FunctionName)\
        {\
            __returnCode = MMR::FSR_FunctionHandled;\

#define MMR_STATE_FUNCTION_END



//------------------------------------------------------------------------
// 
// Call the parent state of this state for the current function.
//
// Note: The state must be virtual.
//       The super typedef must exists.
// 
//------------------------------------------------------------------------
#define MMR_CALL_PARENT_STATE( StateName )\
    if (super::StateName##_State(__functionName) == MMR::FSR_FunctionInterrupted)\
    {\
        return MMR::FSR_FunctionInterrupted;\
    }


}


#endif
