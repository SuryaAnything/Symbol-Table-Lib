#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "symbol.h"

inline C_SYMBOL_PUBLIC(int)
_AtomicComplexity(char* SYMBOL_CONST_TYPE _valueString) {
    int hashcode = 0;
    int shift, multiplier = 1;
    for (int iterator = 0; _valueString[iterator] != '\0'; ++iterator) {
        hashcode += _valueString[iterator] * multiplier;
        shift = multiplier << 5;
        multiplier = shift - multiplier;
    }
    return (((hashcode * RANDOM_A) + RANDOM_B)
    % CONSTRAINED_CONSTANT)
    % HASH_TABLE_SIZE;
}

C_SYMBOL_PUBLIC(void)
_imgTypeUndefined() {
    _link_symbol.start = NULL;
    _link_symbol.curr = NULL;
    _link_symbol.init = 1;
}

C_SYMBOL_PUBLIC(void)
    _InitScope_() {

        if (!_link_symbol.init) {
            _imgTypeUndefined();
        }
        _node_symbol *_Np = (
                _node_symbol*)
                        malloc(sizeof(_node_symbol));

        __c_tbl_hash *table = (
                __c_tbl_hash*)
                        malloc(sizeof(__c_tbl_hash));

        _Np->local = table;
        _Np->next = NULL;
        for (int iterator = 0; iterator < HASH_TABLE_SIZE; ++iterator) {
            table->table[iterator] = NULL;
        }
        if (_link_symbol.curr) {
            _Np->prev = _link_symbol.curr;
            _link_symbol.curr->next = _Np;
            _link_symbol.curr = _Np;
        }
        else {
            _Np->prev = NULL;
            _link_symbol.curr = _Np;
            _link_symbol.start = _Np;
        }
    }

C_SYMBOL_PUBLIC(void)
_EndScope_() {
    _node_symbol *tp = _link_symbol.curr;
    for (int iterator = 0; iterator < HASH_TABLE_SIZE; ++iterator) {
        if (tp->local->table[iterator]) {
            free(tp->local->table[iterator]);
        }
    }
    _link_symbol.curr = _link_symbol.curr->prev;
    free(tp);
}

C_SYMBOL_PUBLIC(void)
_ToScope_(char *SYMBOL_CONST_TYPE _valueString, void* SYMBOL_CONST_TYPE _data, _Dtype dtype) {
    int offset = _AtomicComplexity(_valueString);
    EntryPair *brace = (EntryPair *)malloc(sizeof(EntryPair));
    if (!brace) {
        throw AllocationFailedException();
    }
    else {
        brace->dataValue = _data;
        brace->_Tp = dtype;
        strcpy(brace->var_identifier, _valueString);
        if (_link_symbol.curr->local->table[offset]) {
            EntryPair *temp = _link_symbol.curr->local->table[offset];
            if (!strcmp(temp->var_identifier,_valueString)) {
                brace->next = temp->next;
                _link_symbol.curr->local->table[offset] = brace;
                return;
            }
            while (temp->next && strcmp(temp->next->var_identifier, _valueString)) { temp = temp->next; }
            if (temp->next) {
                
                brace->next = temp->next->next;
                free(temp->next);
                temp->next = brace;
            }
            else {
                temp->next = brace;
            }
        }
        else {
            _link_symbol.curr->local->table[offset] = brace;
            _link_symbol.curr->local->count++;
        }
    }
}

C_SYMBOL_PUBLIC(void)
AssignValue(char *SYMBOL_CONST_TYPE _Variable, char *SYMBOL_CONST_TYPE _Value, _Dtype dtype) {
    void *_data;
    if (dtype == String) {
        _data = malloc(strlen(_Value)+1);
        strcpy((char*)_data, _Value);
    }
    else {
        _data = malloc(dtype);
        if (dtype == Integer || dtype == Long) {
            long data = string_parse_int(_Value);
            memcpy(_data, &data, sizeof(int));
        }
        else {
            double data = string_parse_decimal(_Value);
            memcpy(_data, &data, sizeof(double));
        }
    }
    _ToScope_(_Variable, _data, dtype);
}

C_SYMBOL_PUBLIC(void*)
_LookScope_(char* SYMBOL_CONST_TYPE _valueString) {
    _node_symbol *tp = _link_symbol.curr;
    int offset = _AtomicComplexity(_valueString);
    while (tp){
        if (tp->local->table[offset]) {
            EntryPair *temp = tp->local->table[offset];
            while (temp) {
                if (strcmp(temp->var_identifier, _valueString)==0) {
                    return tp->local->table[offset]->dataValue;
                }
                temp = temp->next;
            }
        }
        tp = tp->prev;
    }
    return NULL;
}


C_SYMBOL_PUBLIC(int)
string_parse_int(const char* string) {
    int val_int = 0;
    int iterable;
    for (iterable = 0; iterable < 30 && string[iterable]!='\0' ; ++iterable) {
        if (string[iterable] < 48 || string[iterable] > 57) {
            throw ParseException();
        }
        val_int = val_int * 10 + (string[iterable] - 48);
    }
    if (iterable == 31) { throw OverflowException(); }
    else { return val_int; }
}


C_SYMBOL_PUBLIC(double)
string_parse_decimal(const char* string) {
    double val_double = 0;
    int iterable;
    for (iterable = 0; iterable < 30 && string[iterable]!='\0' && string[iterable]!='.' ; ++iterable) {
        if (string[iterable] < 48 || string[iterable] > 57) {
            throw ParseException();
        }
        val_double = val_double * 10 + (string[iterable] - 48);
    }

    if (string[iterable] == '.') {
        iterable++;
        int count = 0;
        int decimal = 10;
        while (string[iterable]!='\0' && count < 8) {
            if (string[iterable] < 48 || string[iterable] > 57) {
                throw ParseException();
            }
            val_double = val_double * 10 + (string[iterable] - 48);
            count++;
            iterable++;
            decimal = decimal * 10;
        }
        decimal /= 10;
        val_double = val_double / decimal;
    }
    return val_double;
}

C_SYMBOL_PUBLIC(Fields *)
_LookScopeTypeOptional_(char* SYMBOL_CONST_TYPE _valueString) {

    _node_symbol *temp = _link_symbol.curr;
    int offset = _AtomicComplexity(_valueString);

    Fields *object = (Fields*)malloc(sizeof(Fields));

    while (temp){
        if (temp->local->table[offset]) {

            _Dtype type = temp->local->table[offset]->_Tp;
            if (type == Integer || type == Long) {
                object->integerValue = *(int*)temp->local->table[offset]->dataValue;
            }
            else if (type == Float || type == Double) {
                object->decimalValue = *(double *)temp->local->table[offset]->dataValue;
            }
            else {
                object->stringValue = (char*)malloc(sizeof(char) * strlen((char*)temp->local->table[offset]->dataValue));
                strcpy(object->stringValue, (char*)temp->local->table[offset]->dataValue);
            }
            return object;
        }
        temp = temp->prev;
    }

    object->isNull = true;
    return object;
}


C_SYMBOL_PUBLIC(EntrySet*)
_CurrentScopeSet_() {
    EntrySet* _p_set = (EntrySet*)malloc(sizeof(EntrySet));
    _p_set->pairSet = (EntryPair*)malloc(sizeof(EntryPair) * _link_symbol.curr->local->count + 1);
    _p_set->size = _link_symbol.curr->local->count;
    for (int iterator = 0, itr = 0; iterator < HASH_TABLE_SIZE; ++iterator) {
        if (_link_symbol.curr->local->table[iterator]) {
            _p_set->pairSet[itr++] = *_link_symbol.curr->local->table[iterator];
        }
    }
    return _p_set;
}


C_SYMBOL_PUBLIC(int)
    integer_cast(void *_src) {
        if (!_src) {
            throw NullPointerException();
        }
        if ((uintptr_t)_src % sizeof(int) != 0 ) {
            throw ParseException();
        }
        int *_cast = (int*) _src;
        int val = *(_cast);
        free(_cast);
        return val;
    }

C_SYMBOL_PUBLIC(double)
double_cast(void* _src) {
    if (!_src) {
        throw NullPointerException();
    }
    if ((uintptr_t)_src % sizeof(double ) != 0 ) {
        throw ParseException();
    }
    double *_cast = (double*) _src;
    double val = *(_cast);
    free(_cast);
    return val;
}

C_SYMBOL_PUBLIC(float)
float_cast(void* _src) {
    if (!_src) {
        throw NullPointerException();
    }
    if ((uintptr_t)_src % sizeof(float ) != 0 ) {
        throw ParseException();
    }
    float *_cast = (float*) _src;
    float val = *(_cast);
    free(_cast);
    return val;
}

C_SYMBOL_PUBLIC(long)
long_cast(void* _src) {
    if (!_src) {
        throw NullPointerException();
    }
    if ((uintptr_t)_src % sizeof(long) != 0 ) {
        throw ParseException();
    }
    long *_cast = (long*) _src;
    long val = *(_cast);
    free(_cast);
    return val;
}

C_SYMBOL_PUBLIC(char*)
    string_cast(void* _src) {
        if (!_src) {
            throw NullPointerException();
        }
        return (char*)_src;
    }
