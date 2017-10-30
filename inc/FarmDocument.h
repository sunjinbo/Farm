/* ====================================================================
 * File: FarmDocument.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __FARM_DOCUMENT_H__
#define __FARM_DOCUMENT_H__

// INCLUDS
#include <akndoc.h>

// FORWARD DECLARATIONS
class CFarmAppUi;
class CEikApplication;


/*! 
  @class CFarmDocument
  
  @discussion An instance of class CFarmDocument is the Document part of the AVKON
  application framework for the Farm example application
  */
class CFarmDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CFarmDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CFarmDocument
  */
    static CFarmDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CFarmDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CFarmDocument
  */
    static CFarmDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CFarmDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CFarmDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CFarmAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CFarmDocument object
  */
    void ConstructL();

/*!
  @function CFarmDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CFarmDocument(CEikApplication& aApp);

    };


#endif // __FARM_DOCUMENT_H__

// End of File

