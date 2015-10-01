"""
# ************************************************************************* #
#          Copyright (c) 2015 Oscar Riveros. All rights reserved.           #
#                         oscar.riveros@gmail.com                           #
#                                                                           #
#      Without any restriction, Oscar Riveros reserve the rights,           #
# patents and marketing this knowledge and directly derived from this work. #
# ************************************************************************* #
"""

__author__ = 'Oscar Riveros'

import random

limit = 10000

def gen_universe(ss, file_name='universe.txt'):    
    U = sorted(list(set(random.sample(range(1, limit), k=ss))))
    zz = sum(list(set(random.sample(U, k=random.randint(1, ss)))))

    with open(file_name, 'w') as file:
        print(zz, file=file)
        for n in U:
            print(n, file=file)


gen_universe(1000)