#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "core.h"
#include "CL.h"
#include "BST.h"
#include "HT.h"
#include "test.h"

int maxSizeLine = 0;

int main(){
    maxSizeLine = maxSizeOfLine()+1;
    testFirstLastElement();
    mainTest_CL();
    mainTest_HT();
    mainTest_BST();
//    mainTest_BST_RB(); // not implemented
    testDiffBetweenBST_BSTRB();

    return 0;

}
