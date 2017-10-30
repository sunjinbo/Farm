/* ====================================================================
 * File: ButtonObserver.h
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef M_BUTTONOBSERVER_H
#define M_BUTTONOBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
class MButtonObserver
    {
public: // New methods
    virtual void HandleClickedL() = 0;
    };

#endif // M_BUTTONOBSERVER_H

// End of File
