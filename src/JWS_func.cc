/******************************************************************************
* Copyright (c) 2020  Ericsson AB
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v2.0
* which accompanies this distribution, and is available at
* https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
*
* Contributors:
*   Gabor Szalai - initial implementation and initial documentation
******************************************************************************/
//
//  File:               JWS_func.cc
//  Description:	      Type definitions for JWS, PASSporT and SHAKEN
/////////////////////////////////////////////// 
#include <map>
#include <string>

#include "JWS_Types.hh"



namespace JWS__Types{


JWS__JSON__Object f__sort__JWS__JSON__Object(const JWS__JSON__Object& pl_unsorted){
  std::map<std::string,int> smap;
  for(int i=0; i<pl_unsorted.lengthof();i++){
    TTCN_Buffer buf;
    pl_unsorted[i].key().encode_utf8(buf);
    smap[std::string((const char *)buf.get_data(),buf.get_len())]=i;
  }
  
  JWS__JSON__Object ret_val=NULL_VALUE;
  int a=0;
  for( std::map<std::string,int>::iterator it=smap.begin(); it!=smap.end(); it++){
    ret_val[a].key()=pl_unsorted[it->second].key();
    if(pl_unsorted[it->second].val().ischosen(JSON__Generic::JSON__generic__val::ALT_JSON__object)){
      ret_val[a].val().JSON__object()=f__sort__JWS__JSON__Object(pl_unsorted[it->second].val().JSON__object());
    } else {
      ret_val[a].val()=pl_unsorted[it->second].val();
    }
    a++;
  }
  return ret_val;
}

}

