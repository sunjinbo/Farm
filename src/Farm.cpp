/* ====================================================================
 * File: Farm.cpp
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDS
#include "FarmApplication.h"
#include <eikstart.h>

// Create an application, and return a pointer to it
CApaApplication* NewApplication()
    {
    return new CFarmApplication;
    }

TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
    
// End of File
