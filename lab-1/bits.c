/* 
 * Harry Minsky hm2536 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* using demorgan's laws return x xor y using strictly & and ~ */
  return ~(~(x & ~y) & ~(y & ~x));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* since integers are 32 bits, get minimum two's complmement
  * via shifting 1 bit 31 places left
  */
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  /* The Logic of this program is basically to make sure that x
      does not wrap to negative if you add one to it */
  /*Negate the xor of x and x + 1 */
  int a = ~((x + 1) ^ x);
  /* 
    get logical negation of x + 1, which should give
    0 unless x is maximum two's complement
  */
  int b = !(x + 1); 
  /* 
    If either a or b are 1, return 1, else return 0
  */
  int c = !(a + b);
  return c;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /*
    generate a mask with all 1s in odd bits
  */
  int m = 0x55;
  int mask = m | (m << 8);
  mask = ~(mask+(mask<<16));
  /* now that we have mask, check if odd bits
      in x clear the mask
  */
  return !((x & mask) + ~mask + 1);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {  
  /* -x in c is just bit inverse of x + 1 (def of 2's complement) */
  return ~x+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /* preserve sign bit of x */
  int sign = 1 << 31;
  /* create upper and lower bounds for ascii digit range*/
  int upper = ~(sign | 0x39);
  int lower = ~0x30;
  /*check if x clears out our lower or upper bounds */
  upper = sign & (upper+x) >> 31;
  lower = sign & (lower+1+x) >> 31;
  
  return !(upper | lower);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
    get double logical negation of x to either get a 0 or a 1
    (if x is non zero, we get back 1, if it's 0 we get back 0)
  */
  int a = !!x;
  /* bit invert to either get minimum two's complment or 1 */
  int b = ~a + 1;
  /* return bit or of y or z depending on value of b */
  return ((b&y) | (~b&z));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* first we get the inverse of difference of the sign bit between both ints */
  int sign = !(x >> 31) ^ !(y >> 31);
  
  //check if x is negative
  int a = sign & (x >> 31);
  //check if x-y is either negative, positive or 0
  int b = !sign & !((y+(~x+1))>>31);
  //if either of these conditions is true, return true
  int c = a | b;
  return c;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  //we check if x is either 0 or non zero, our or gate returning -1 unless x is equal to 0
  //then we add 1: if x is 0, we get back 1, if x is anything besides 0, we get back -1+1 = 0
  return ((x >> 31) | ((~x+1) >> 31 )) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  //basically, this is just an incredibly convolouted way to check
  // how many 1s are in each 4bit segment of a 32 bit integer
  int sign, b0, b1, b2, b4, b8, b16;
  //get sign bit of x
  sign = x >> 31;
  // we get the absolute value of x
  x = (sign & ~x) | (~sign & x);
  // repeatdely halve the length of x and get back either a 1 or a 0, storing the binary value in 
  // our variables
  b16 = !!(x >> 16) << 4;
  x = x >> b16;
  b8 = !!(x >> 8) << 3;
  x = x >> b8;
  b4 = !!(x >> 4) << 2;
  x = x >> b4;
  b2 = !!(x >> 2) << 1;
  x = x >> b2;
  b1 = !!(x >> 1);
  x = x >> b1;
  b0 = x;
  //add one to our final result as we must account for sign bit
  return b16+b8+b4+b2+b1+b0+1;
}
//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  //we tackle three cases:
  // case 1: uf is normalized
  // case 2: uf is denormalized
  // case 3: uf is NaN

  //we yank out the exponent of our IEEE float
  int x = (uf >> 23) & 0xFF;
  //Case 1: uf is denormalized
  if(!x)
    {
      // note that our exponent is now all 1s
      x = 0xFF;
      //we normalize the number
      uf = ((uf & 0x80000000) | (uf << 1));
    }
  // Case 2: uf is normalized
  if(!(x ^ 0xFE))
    {
      //make exponent all 1s
      x = 0xFF;
      // uf is infinity if there is overflow
      uf = (uf & 0x80000000) | (x << 23);
    }
  // If the exponent is already all 1s, then we know we are dealing with infinty
  if(x ^ 0xFF)
    {
      //simply increase exponent with 1(raise by power of 2)
      uf = uf + (1 << 23);
    }
  //return our value
  return uf;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  // We treat x as an integer 
  //initialize a series of 0 ints as trackers for our while loops
  int y = 0, d = 0, c = 0; 
  // our empty variable to be tuned into IEEE formated
  unsigned int r = 0x00000000;
  //we account for the arithemetic shift in the case that x is negative
  unsigned int t = x; 
  unsigned f = x;
  // Check if MSB x = 1
  if(x >> 31)
    {
      // r is now negative
      r = 0x80000000;
      // make t and f bit inversions of x
      t = f = (~x) + 1;
    }

 
  // check how many digits in our t variable
  while(t)
    {
      // add one to y to track number of digits
      y = y + 1;
      // right shift t
      t = t >> 1;
    }
  // d is now how many digits we need to fill in in our mantissa
  d = 24 - y;
  // check value of d, then account for digit loss in terms of single point precision
  if(d < 0)
    {
      d = 0;
      while(f >> 25)
	    {
	      c = c | (f & 1);
	      f = f >> 1;
	    }
      f = (f >> 1) + (f & (c | (f >> 1)) & 1);
      if(f >> 24)
	    {
	      y = y + 1;
	    }
  }
  // if x is 0, we need our exponent to also be all 0s 
  if(!y)
    {
      y = -126;
    }
  // "OR" r with a bit mask that accounts for overflow
  r = r | ((f << d) & 0x007FFFFF);
  // "or" r with a properly biased exponent
  r = r | ((y + 126) << 23);
  return r;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  //since we are interpreting uf as an IEEE float, we need to account for three cases
  // Case 1: Denormalized
  // Case 2: Normalized
  // Case 3: NaN/Infinity

  //Our exponent is the first 8 bits of our uf, excluding the sign bit
  int exp = (uf & 0x7F800000) >> 23;
  //sign is our first bit
  int sign = uf & 0x80000000;
  //frac/mantissa is the last 23 bits of uf
  int frac = uf & 0x007FFFFF;
  //unbias exponent based on bias of 32-bit float(127 bits)
  int unbiasedExp = exp - 127; 
   
  // if our unbiased exponent is negative then we return 0
  if (unbiasedExp < 0) return 0;
  // if our unbiased exponent is greater than 30 than we are dealing with a float out of range
  if (unbiasedExp > 30) return 0x80000000u;

  // | our frac with a bit mask to preserve everything but the first bit
  frac = frac | 0x800000;
  //if our unbiased exponenet is less than 23 than we must adjust our mantissa
  if (unbiasedExp < 23) {
    frac = frac >> (23 - unbiasedExp);
  }
  //if not, we left-shift the mantissa the difference between the unbiased exponent and the length
  // of the mantissa
  else {
    frac = frac << (unbiasedExp - 23);
  }
  //if our number is negative, we invert the mantissa and add 1
  if (sign) {
    return (~frac) + 1;
    }
  return frac;
}
