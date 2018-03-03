#!/usr/bin/python

import itertools



# find the number of ways to reach a total with the given number of combinations

amount = 6
denominations = [60, 48, 24, 12, 6, 2, 0.5]
names = {60: "Half Crown(s)", 48: "Florin:(s)", 24 : "Shilling:(s)",  12 : "Sixpence:", 6 : "Threepence:", 2 : "pennies" , 0.5 : "half-pennies"}

def count_combs(amount, i, combination, add):
    permutation_array = []
    sum_to_check_if_even = 0
    name_index_position = 0
    if add: combination.append(add)
    # if the money is zero or if we have gone through all the dominations
    if amount == 0 or (i+1) == len(denominations):
        if (i+1) == len(denominations) and amount > 0:
            combination.append( (amount, denominations[i]) )
            i += 1
        # while we still have dominations to go through
        while i < len(denominations):
            combination.append((0, denominations[i]))
            i += 1
        for (name, comb) in combination:
            # check that first combination is even and can be split between two people
            sum_to_check_if_even = sum_to_check_if_even + name
            #care only about non zero denomination
            if (name!=0):
                j=0
                while(j<name):
                    print len(denominations)
                    permutation_array.append(name_index_position)
                    j+=1
                name_index_position = name_index_position +1
        if (sum_to_check_if_even % 2 == 0):
           #print list(itertools.permutations(permutation_array, len(permutation_array)/2))
           print " ".join("%d %s" % (name, names[comb]) for (name, comb) in combination)

        return 1
    cur = denominations[i]
    print cur
    return sum(count_combs(amount-x*cur, i+1, combination[:], (x,cur)) for x in range(0, int(amount/cur)+1))

print count_combs(amount, 0, [], None)
#print countChange(amount, denominations)