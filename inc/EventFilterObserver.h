/* ====================================================================
 * File: EventFilterObserver.h
 * Created: 01/18/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef __EVENTFILTEROBSERVER_H
#define __EVENTFILTEROBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
class MEventFilterObserver
    {
public: // New methods
    virtual void EventFilterEvent(  const TPoint& aStart, const TPoint& aEnd ) = 0;
    };

#endif // __EVENTFILTEROBSERVER_H

// End of File
