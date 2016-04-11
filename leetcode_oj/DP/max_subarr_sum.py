#!/usr/bin/python
#Kadane's algo
def max_subarray_sum(A):
    max_ending_here = max_so_far = 0
    for x in A:
        max_ending_here = max(0, max_ending_here + x)
        max_so_far = max(max_so_far, max_ending_here)
    return max_so_far

'''
Or you can initialize with nums[0] and max_ending_here = max(x, max...)
'''
A = [1,4,0,-3,-5,8]
sum_A = max_subarray_sum(A)
print "max_subarray_sum for: ", A, " is= ", sum_A
A = [1,4,0,3,5,8]
sum_A = max_subarray_sum(A)
print "max_subarray_sum for: ", A, " is= ", sum_A
