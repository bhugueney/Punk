"""
///////////////////////////////////////////////////////////////////////////////////
//             Copyright (c) 2015+ Oscar Riveros. All rights reserved.           //
//                            oscar.riveros@gmail.com                            //
//                                                                               //
//      Without any restriction, Oscar Riveros reserved rights, patents and      //
// commercialization of this knowledge and which derive directly from this work. //
///////////////////////////////////////////////////////////////////////////////////
"""

__author__ = 'Oscar Riveros'

import sha3

hash = sha3.sha3_224

def key(message):
    return hash(message.encode('utf-8')).hexdigest()

print(key(str('54321')))
