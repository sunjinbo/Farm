/* ====================================================================
 * File: FarmAppUi.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __FARM_APPUI_H__
#define __FARM_APPUI_H__

#include <aknappui.h>

// FORWARD DECLARATIONS
class CFarmAppView;

/*! 
  @class CFarmAppUi
  
  @discussion An instance of class CFarmAppUi is the UserInterface part of the AVKON
  application framework for the Farm example application
  */
class CFarmAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CFarmAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CFarmAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CFarmAppUi();


/*!
  @function ~CFarmAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CFarmAppUi();


public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
/*! @var iAppView The application view */
    CFarmAppView* iAppView;
    };

#endif // __FARM_APPUI_H__
