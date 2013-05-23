#ifndef MMR_MMR_SYSTEM_UTILITIES_FSM_TRANSITIONCLUSTERMACROS_H__INCLUDED
#define MMR_MMR_SYSTEM_UTILITIES_FSM_TRANSITIONCLUSTERMACROS_H__INCLUDED


namespace MMR
{


//------------------------------------------------------------------------
// 
// Declare a transition cluster (in the .h).
// 
//------------------------------------------------------------------------
#define	MMR_DECLARE_TRANSITION_CLUSTER( ClusterName )\
    MMR::E_FsmStateResult ClusterName##_TransitionCluster(int __functionName)

#define	MMR_DECLARE_VIRTUAL_TRANSITION_CLUSTER( ClusterName )\
    virtual MMR_DECLARE_TRANSITION_CLUSTER( ClusterName )


//------------------------------------------------------------------------
// 
// Implement a transition cluster (in the .cpp).
// 
//------------------------------------------------------------------------
#define	MMR_IMPLEMENT_TRANSITION_CLUSTER_BEGIN( ClassName, ClusterName )\
    MMR::E_FsmStateResult ClassName::ClusterName##_TransitionCluster(int __functionName)\
    {

#define	MMR_IMPLEMENT_TRANSITION_CLUSTER_END\
        return MMR::FSR_FunctionHandled;\
    }


//------------------------------------------------------------------------
// 
// Call a transition cluster inside a state.
// 
//------------------------------------------------------------------------
#define MMR_CALL_TRANSITION_CLUSTER( ClusterName )\
    assert(__functionName != MMR::Fsm<FsmOwner>::Function_Constructor && __functionName != MMR::Fsm<FsmOwner>::Function_Destructor );\
    if (ClusterName##_TransitionCluster(__functionName) == MMR::FSR_FunctionInterrupted)\
    {\
        return MMR::FSR_FunctionInterrupted;\
    }


//------------------------------------------------------------------------
// 
// Call the parent transition cluster.
//
// Note: The cluster must be virtual.
//       The super typedef must exists.
// 
//------------------------------------------------------------------------
#define MMR_CALL_PARENT_TRANSITION_CLUSTER( ClusterName )\
    if (super::ClusterName##_TransitionCluster(__functionName) == MMR::FSR_FunctionInterrupted)\
    {\
        return MMR::FSR_FunctionInterrupted;\
    }


}


#endif
