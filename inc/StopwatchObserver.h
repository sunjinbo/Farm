/* ====================================================================
 * File: StopwatchObserver.h
 * Created: 01/26/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef M_STOPWATCHOBSERVER_H
#define M_STOPWATCHOBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
class MStopwatchObserver
    {
public: // New methods
    virtual void ExpiredL() = 0;
    };

#endif // M_STOPWATCHOBSERVER_H

// End of File
