#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"
// create a struct for AdptArray
typedef struct AdptArray_
{
    DEL_FUNC _DelFunc;
    COPY_FUNC _CopyFunc;
    PRINT_FUNC _PrintFunc;
    int size;//array size
    PElement *_pElement;
} ArrayAdpt;

// create a new AdptArray
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func)
{
    // PAdptArray is a pointer to AdptArray
    PAdptArray new_Array = (PAdptArray)calloc(1, sizeof(ArrayAdpt));
    if (new_Array == NULL) // if failed
    {
        return NULL;
    }
    new_Array->_CopyFunc = copy_func;
    new_Array->_DelFunc = del_func;
    new_Array->_PrintFunc = print_func;
    new_Array->_pElement = (PElement)calloc(1, sizeof(PElement));
    if (new_Array->_pElement == NULL) // if failed
    {
        return NULL;
    }
    new_Array->size = 0;
    return new_Array;
}
// FAIL = 0, SUCCESS=1
Result SetAdptArrayAt(PAdptArray pAdpt, int index, PElement p_Elem)
{
    if (pAdpt == NULL) //if empty
    {
        return FAIL;
    }
    if (index < 0) // must be positive or zero
    {
        return FAIL;
    }
    // if index is after size array
    if (pAdpt->size <= index)
    {
        PElement *dest = (PElement *)realloc((pAdpt->_pElement), (sizeof(PElement)) * (index + 1));
        if (dest == NULL)//if realloc failed
        {
            return FAIL;
        }
        (pAdpt->_pElement) = dest;
        // put NULL in element array after previues array size
        // pElements[data,data,...,data,NULL,...,NULL]
        for (int i = pAdpt->size; i < index; i++)
        {
            (pAdpt->_pElement)[i] = NULL;
        }
        (pAdpt->size) = index + 1; // increase size
    }

    // typedef PElement(*COPY_FUNC)(PElement);
    (pAdpt->_pElement)[index] = pAdpt->_CopyFunc(p_Elem);
    return SUCCESS;
}



void DeleteAdptArray(PAdptArray pAdpt)
{
    if (pAdpt == NULL) // check
    {
        return;
    }
    for (int i = 0; i < pAdpt->size; i++)
    {
        if ((pAdpt->_pElement)[i] != NULL)
        {
            // typedef void(*DEL_FUNC)(PElement);
            pAdpt->_DelFunc((pAdpt->_pElement)[i]);
        }
    }
    // memory free
    free(pAdpt->_pElement);
    free(pAdpt);
}
// return copy of element at index
PElement GetAdptArrayAt(PAdptArray pAdpt, int index)
{
    // if ADPT empty
    if (pAdpt == NULL)
    {
        return NULL;
    }
    // index must be positive
    else if (index < 0)
    {
        return NULL;
    }
    // if Elements at index is empty
    else if ((pAdpt->_pElement)[index] == NULL)
    {
        return NULL;
    }
    else
        return pAdpt->_CopyFunc((pAdpt->_pElement)[index]);
}
// return size of ADPT
int GetAdptArraySize(PAdptArray pAdpt)
{
    if (pAdpt == NULL)
    {
        return 0;
    }
    return pAdpt->size;
}
// print the elemNts of ADPT
void PrintDB(PAdptArray pAdpt)
{
    if (pAdpt == NULL)
    {
        return;
    }
    //print loop
    for (int i = 0; i < pAdpt->size; i++)
    {
        if ((pAdpt->_pElement)[i] != NULL)
        {
            // typedef void(*PRINT_FUNC)(PElement);
            pAdpt->_PrintFunc((pAdpt->_pElement)[i]);
        }
    }
}
