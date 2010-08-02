// $Id$

#ifndef HILTI_EXCEPTIONS_H
#define HILTI_EXCEPTIONS_H

#include "continuation.h"
#include "threading.h"

struct __hlt_type_info;

    // %doc-hlt_exception-start

/// The type of an exception.
typedef struct hlt_exception_type {
    const char* name;                  //< Name of the exception. 
    struct hlt_exception_type* parent; //< The type this one derives from.
    const struct __hlt_type_info* argtype;   //< The type of the exception's argument, or 0 if no argument.
} hlt_exception_type;

typedef struct hlt_exception {
    hlt_exception_type* type;        //< The type of the exeception.
    hlt_continuation* cont;          //< If the exeption is resumable, the continuation for doing so.
    void *arg;                       //< The arguments of type ``type.argtype``, or 0 if none.
    const char* location;            //< A string describing the location where the exception was raised.
    void *fptr;                      //< Saved frame pointer for resuming later.
    void *eoss;                      //< Saved end-of-stack segment for resuming later. 
    hlt_vthread_id vid;              //< If a virtual thread raised the exeception, it's ID. 
} hlt_exception;

    // %doc-hlt_exception-end

///////////////////////////////////////////////////////////////////////////////
// Predefined exception types.
///////////////////////////////////////////////////////////////////////////////

    // %doc-std-exceptions-start

// Fall-back exception if nothing else is specified.
extern hlt_exception_type hlt_exception_unspecified;

// No exception.
extern hlt_exception_type hlt_exception_none;

// A division by zero has occured.
extern hlt_exception_type hlt_exception_division_by_zero;

// A value looks different than expected. 
extern hlt_exception_type hlt_exception_value_error;

// A function received different arguments than it expected. 
extern hlt_exception_type hlt_exception_wrong_arguments;

// An memory allocation has failed due to resource exhaustion.
extern hlt_exception_type hlt_exception_out_of_memory;

// An undefined value has been attempted to use. 
extern hlt_exception_type hlt_exception_undefined_value;

// An internal error that indicates a bug in HILTI.
extern hlt_exception_type hlt_exception_internal_error;

// An operation could not be performed without blocking. 
extern hlt_exception_type hlt_exception_would_block;

// A worker thread threw an exception.
extern hlt_exception_type hlt_exception_uncaught_thread_exception;

// An operation that depends on having threads was attempted even though we
// aren't configured for threading. 
extern hlt_exception_type hlt_exception_no_threading;

// A system or libc function returned an unexpected error.
extern hlt_exception_type hlt_exception_os_error;

// An overlay instruction has been used on a not yet attached overlay.
extern hlt_exception_type hlt_exception_overlay_not_attached;

// An invalid container index.
extern hlt_exception_type hlt_exception_index_error;

// A container item was attempted to read which isn't there. 
extern hlt_exception_type hlt_exception_underflow;

// An interator is used which is not valid for the operation.
extern hlt_exception_type hlt_exception_invalid_iterator;

// An error in a regular expression.
extern hlt_exception_type hlt_exception_pattern_error;

// Functionality not yet implemented.
extern hlt_exception_type hlt_exception_not_implemented;

// Base class for all resumable exceptions.
extern hlt_exception_type hlt_exception_yield;

// A resumable exception generated by the Yield statement to temporarily
// suspend execution.
extern hlt_exception_type hlt_exception_yield;

// Raised when debug.assert fails.
extern hlt_exception_type hlt_exception_assertion_error;

// Raised when we encounter an unexpected null reference. 
extern hlt_exception_type hlt_exception_null_reference;

// Raised when a timer is associated with multiple timer managers. 
extern hlt_exception_type hlt_exception_timer_already_scheduled;
    
// Raised when a timer is must be scheduled for an operation but is not.
extern hlt_exception_type hlt_exception_timer_not_scheduled;

// Raised when expiration is requested for a container with which no timer
// manager has been associated.
extern hlt_exception_type hlt_exception_no_timer_manager;

// Raised when a packet source cannot provide any further packets.
extern hlt_exception_type hlt_exception_iosrc_exhausted;

// Raised when a packet source encounters an error condition.
extern hlt_exception_type hlt_exception_iosrc_error;

// Raised when an I/O operation failed.
extern hlt_exception_type hlt_exception_io_error;

///////////////////////////////////////////////////////////////////////////////
// Exception-related functions.
///////////////////////////////////////////////////////////////////////////////

extern hlt_exception* __hlt_exception_new(hlt_exception_type* type, void* arg, const char* location);
extern hlt_exception* __hlt_exception_new_yield(hlt_continuation* cont, int32_t arg, const char* location);

extern void __hlt_exception_print_uncaught_abort(hlt_exception* exception); 

extern void hlt_exception_print(hlt_exception* exception); 
extern void hlt_exception_print_uncaught(hlt_exception* exception); 
extern void hlt_exception_print_uncaught_in_thread(hlt_exception* exception, hlt_vthread_id vid);

#define __hlt_stringify2(arg) #arg
#define __hlt_stringify(arg) __hlt_stringify2(arg)
#define hlt_set_exception(dst, type, arg) __hlt_set_exception(dst, type, arg, __FILE__ ":" __hlt_stringify(__LINE__))
extern void __hlt_set_exception(hlt_exception** dst, hlt_exception_type* type, void* arg, const char* location);

#endif
