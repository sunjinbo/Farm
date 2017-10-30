/* ====================================================================
 * File: RollpackerObserver.h
 * Created: 01/23/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef M_ROLLPACKEROBSERVER_H
#define M_ROLLPACKEROBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
class MRollpackerObserver
    {
public: // New methods
    virtual void FinishedL() = 0;
    };

#endif // M_ROLLPACKEROBSERVER_H

// End of File
