#ifndef INTERNALS_H
#define INTERNALS_H

#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

// DEFINES FOR CONSTANTS


//TYPEDEFS
// Time in 100ns intervals since 01.01.1601;
typedef int64_t IG_DateTime;

// Internal Identification number
typedef uint32_t IG_Id; 

typedef bool IG_Bool;
typedef uint32_t IG_UInt32;
typedef uint64_t IG_UInt64;
typedef int32_t IG_Int32;
typedef int64_t IG_Int64;
typedef float IG_Float;
typedef double IG_Double;
//TODO: ... noch mehr?

// IG Statuscode
// TODO: 
typedef enum {
    IG_STATUS_GOOD, 
    IG_STATUS_BAD,
    IG_STATUS_QUEUE_FULL
    /*add more as needed*/
} IG_Status;

//TODO: insert relevant Datatypes (floatingpoint, integer, )
typedef enum {
    IG_DOUBLE, 
    IG_NULL,
    /*...*/
} IG_Datatype;


// IG Data
typedef struct{
	IG_Id id;
	IG_Datatype datatype;
	void * data;
	IG_DateTime timestamp;
} IG_Data;

static const IG_Data IG_DATA_EMPTY = (IG_Data){0, IG_NULL, NULL, 0};

//TODO: functions for working with IG_Data : 
// -init(creates new on the heap), 
// -delete(frees memory), 
// -take_data (returns pointer and deletes IG_Data after after)

#endif
