# Midterm 1 Review Exercises:
For each of the following problems, write a syntactically correct C++ program
that accomplishes the described task. You should write functions for each task
and test them with sample inputs to ensure their correctness.

1. Given a vector of integers, compute the minimum, maximum, and median value.
   Write each as a separate function. Recall that the median is the "middle"
   value of the sorted list. If there is an even number of elements, then the
   median is simply the average of the two middle elements. You can use the
   `sort` function covered in the labs to compute the median.
2. Given a vector of strings with mixed capitalization, modify this vector such
   that all the strings have their capitalization inverted. So if a character is
   lowercase, it should be converted to uppercase and vice-versa.
3. Given two strings with mixed case, write a function that returns true if both
   strings are equal, false otherwise. The comparison must be done in the same
   case (be it upper or lowercase). Note that the capitalization may not be
   consistent between strings. For example, `HeLlO` should be equal as `hElLo`.
4. Given a string, return another string that contains the result of
   incrementing each character by one. Note that if we have `char c{'a'};`, then
   `char d = c + 1;` makes `d = 'b'` and so forth.
5. Given a string and a range of indices, return the portion of the string that
   exists between these indices. For example, given the string "hello" and
   indices 0, 2, the function would return "hel".
6. Design a program that prints out the current time as entered by the user.
   First design a struct that will hold hours, minutes, and whether it is am or
   pm. Parse the input from the user, which you may assume will be in 24-hour
   format (so 1pm is 13:00) and print out the final time.
7. Given a vector of integers and two values a and b, return a vector whose
   values are in the range [a, b]. 
8. Given a vector of strings, write a function that checks if *any* string
   appears more than once.
9. Extend the above program to do the following: given a vector of strings,
   return a new vector that contains any string that appears more than once. The
   new vector must contain only one occurrence of each word.
10. Given a vector of strings, modify this vector such that the first letter of
    each word is capitalized. You may assume that the strings are all lowercase,
    and are separated by one or more spaces. There are no hyphens or extra
    punctuation.
11. Given a vector of numbers (they can be of any type) return a new vector that
    contains only the values that are positive.
12. Extend the above function to return a new vector with numbers that are
    greater than a provided value.
