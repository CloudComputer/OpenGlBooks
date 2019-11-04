//--------------------------------------------------------------------------------------------------------------------//
//                                                EXTRA DATA CLASS                                                    //
// written by Frederic My                                                                                             //
// fmy@fairyengine.com                                                                                                //
//                                                                                                                    //
// this empty base class is intended to be derived                                                                    //
//--------------------------------------------------------------------------------------------------------------------//

#ifndef   _GPG4_EXTRADATA_H_
#define   _GPG4_EXTRADATA_H_

//----------------------------------------------- CLASSES ------------------------------------------------------------//

#include  "RTTI.h"

//--------------------------------------------------------------------------------------------------------------------//
//                                                CExtraData                                                          //
//--------------------------------------------------------------------------------------------------------------------//

namespace GPG4
{
  class CExtraData
  {
  DECLARE_ROOT_RTTI;

  // public methods

  public:
                    CExtraData          (void)              {}
    virtual        ~CExtraData          (void)              {}
  };
}

//--------------------------------------------------------------------------------------------------------------------//

#endif // _GPG4_EXTRADATA_H_
