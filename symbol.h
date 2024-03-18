//
// Created by surya on 04-03-2024.
//

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HASH_TABLE_SIZE         100 /**< Size of the hash table */
#define CONSTRAINED_CONSTANT    104729 /**< A prime number used for hashing */
#define RANDOM_A                24587 /**< Random constant A used for hashing */
#define RANDOM_B                86931 /**< Random constant B used for hashing */
#define C_SYMBOL_PUBLIC(type)   __declspec(dllexport) __attribute__((unused)) type __stdcall /**< Macro for symbol visibility */
#define SYMBOL_CONST_TYPE const __restrict__ /**< Macro for constant symbol _Tp */
#define __int64 long long
#ifdef _WIN64
__MINGW_EXTENSION typedef unsigned __int64 uintptr_t;
#else
typedef unsigned int uintptr_t;
#endif
/*
 * Macro for throwing exceptions.
 */
#define throw fprintf(stderr,"Exception at Line : %d in File : %s\n",__LINE__,__FILE__);

#define OverflowException() fprintf(stderr, " Number out of range\n"); exit(EXIT_FAILURE)
#define ParseException() fprintf(stderr, " Number is not a digit\n"); exit(EXIT_FAILURE)
#define AllocationFailedException() fprintf(stderr," Memory Allocation Failed\n"); exit(EXIT_FAILURE)
#define NullPointerException() fprintf(stderr,"Null Pointer Found"); exit(EXIT_FAILURE)
#define IllegalArgumentException() fprintf(stderr, "IllegalArgumentException"); exit(EXIT_FAILURE)

#ifndef __C_defined_type
#define __C_defined_type

    typedef enum {
        Integer,
        Float,
        Long,
        LongInt,
        Double,
        String
    } _Dtype;

#endif


typedef struct _pair{
    void *dataValue;
    char var_identifier[20];
    _Dtype _Tp;
    struct _pair *next;
} EntryPair; /**< Structure representing a pair of data, name and its _Tp */

typedef struct {
    EntryPair *table[HASH_TABLE_SIZE]; /**< Hash table array */
    int count; /**< Count of entries in the hash table */
} __c_tbl_hash; /**< Structure representing a hash table */

typedef struct _symbolNode {
    __c_tbl_hash *local;
    struct _symbolNode *next;
    struct _symbolNode *prev;
} _node_symbol; /**< Structure representing a node in a symbol table */

struct _sys_linked {
    _node_symbol *start;
    _node_symbol *curr;
    bool init;
} _link_symbol; /**< Structure representing linked symbol tables */



inline C_SYMBOL_PUBLIC(int) _AtomicComplexity(char* SYMBOL_CONST_TYPE _valueString);
C_SYMBOL_PUBLIC(void) _imgTypeUndefined();
C_SYMBOL_PUBLIC(void) _InitScope_();
C_SYMBOL_PUBLIC(void) _EndScope_();
C_SYMBOL_PUBLIC(void) _ToScope_(char *SYMBOL_CONST_TYPE _valueString, void* SYMBOL_CONST_TYPE _data, _Dtype dtype);
C_SYMBOL_PUBLIC(int) string_parse_int(const char* string);
C_SYMBOL_PUBLIC(double) string_parse_decimal(const char* string);
C_SYMBOL_PUBLIC(void) AssignValue(char *SYMBOL_CONST_TYPE _Variable, char *SYMBOL_CONST_TYPE _Value, _Dtype dtype);
C_SYMBOL_PUBLIC(void*) _LookScope_(char* SYMBOL_CONST_TYPE _valueString);

/**
 * @brief Structure representing a raw object.
 */
typedef struct {
    int integerValue;
    char* stringValue;
    double decimalValue;
    bool isNull;
} Fields;

C_SYMBOL_PUBLIC(Fields *) _LookScopeTypeOptional_(char* SYMBOL_CONST_TYPE _valueString);

/**
 * @brief Structure representing a set of entry pairs.
 */
typedef struct _set {
    EntryPair *pairSet;
    int size;
}EntrySet;

/**
 * @brief Function to retrieve the current scope set.
 * @return The current scope set.
 */
C_SYMBOL_PUBLIC(EntrySet*) _CurrentScopeSet_();

#define assign(_T,_V,_U)     AssignValue(_V,_U,_T)
#define begin               _InitScope_();
#define end                 _EndScope_();
#define read(_V)            _LookScope_(_V)
#define fetch(_V)           _LookScopeTypeOptional_(_V)
#define collect()           _CurrentScopeSet_()

C_SYMBOL_PUBLIC(int) string_parse_int(const char* string);
C_SYMBOL_PUBLIC(double) string_parse_decimal(const char* string);


#endif //SYMBOL_TABLE_H
