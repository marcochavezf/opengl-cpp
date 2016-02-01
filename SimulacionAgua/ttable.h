int triangle[256*4*3] = 
{ 0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0000 0000 XV
  0,4,8,  0,0,0,  0,0,0, 0,0,0,	// 0000 0001 XV
  0,9,5,  0,0,0,  0,0,0, 0,0,0,	// 0000 0010 XV
  4,9,5,  4,8,9,  0,0,0, 0,0,0,	// 0000 0011 XV
  1,10,4, 0,0,0,  0,0,0, 0,0,0,	// 0000 0100 XV
  1,10,8, 1,8,0,  0,0,0, 0,0,0,	// 0000 0101 XV
  0,9,5,  1,10,4, 0,0,0, 0,0,0,	// 0000 0110 XV
  1,10,8, 1,8,5,  5,8,9, 0,0,0,	// 0000 0111 XV

  1,5,11, 0,0,0,  0,0,0, 0,0,0,	// 0000 1000 XV
  0,4,8,  1,5,11, 0,0,0, 0,0,0,	// 0000 1001 XV
  0,9,11, 0,11,1, 0,0,0, 0,0,0,	// 0000 1010 XV
  9,11,1, 9,1,4,  9,4,8, 0,0,0, // 0000 1011 XV
  5,11,10,4,5,10, 0,0,0, 0,0,0,	// 0000 1100 XV
  10,5,11,10,0,5, 10,8,0,0,0,0,	// 0000 1101 XV
  11,10,4,11,4,0, 11,0,9,0,0,0,	// 0000 1110 XV
  9,11,10,8,9,10, 0,0,0, 0,0,0,	// 0000 1111 XV

  2,8,6,  0,0,0,  0,0,0, 0,0,0,	// 0001 0000 XV
  0,6,2,  0,4,6,  0,0,0, 0,0,0,	// 0001 0001 XV
  8,6,2,  9,5,0,  0,0,0, 0,0,0,	// 0001 0010 XV
  4,6,2,  4,2,9,  4,9,5, 0,0,0,	// 0001 0011 XV
  2,8,6,  1,10,4, 0,0,0, 0,0,0,	// 0001 0100 XV
  0,1,10, 0,10,6, 0,6,2, 0,0,0,	// 0001 0101 XV
  0,9,5,  1,10,4, 2,8,6, 0,0,0,	// 0001 0110 XV
  5,1,9,  6,2,10, 2,1,10,9,1,2,	// 0001 0111 XV

  2,8,6,  1,5,11, 0,0,0, 0,0,0,	// 0001 1000 XV
  1,5,11, 0,6,2,  0,4,6, 0,0,0,	// 0001 1001 XV
  2,8,6,  0,9,11, 0,11,1,0,0,0,	// 0001 1010 XV
  1,9,11, 1,4,9,  4,2,9, 2,4,6, // 0001 1011 XV
  2,8,6,  5,11,10,4,5,10,0,0,0,	// 0001 1100 XV
  5,11,10,5,10,0, 0,10,6,2,0,6,	// 0001 1101 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0001 1110 
  11,2,9, 11,10,6,11,6,2,0,0,0,	// 0001 1111 XV

  2,7,9,  0,0,0,  0,0,0, 0,0,0,	// 0010 0000 XV
  0,4,8,  2,7,9,  0,0,0, 0,0,0,	// 0010 0001 XV
  0,2,7,  0,7,5,  0,0,0, 0,0,0,	// 0010 0010 XV
  5,2,7,  5,8,2,  5,4,8, 0,0,0,	// 0010 0011 XV
  2,7,9,  4,1,10, 0,0,0, 0,0,0,	// 0010 0100 XV
  2,7,9,  1,10,8, 1,8,0, 0,0,0,	// 0010 0101 XV
  1,10,4, 0,2,7,  0,7,5, 0,0,0,	// 0010 0110 XV
  1,10,8, 8,5,1,  2,5,8, 2,7,5,	// 0010 0111 XV

  2,7,9,  1,5,11, 0,0,0, 0,0,0,	// 0010 1000 XV
  0,4,8,  1,5,11, 2,7,9, 0,0,0,	// 0010 1001 XV
  0,2,7,  0,7,11, 0,11,1,0,0,0,	// 0010 1010 XV
  7,11,2, 8,2,11, 8,11,1,8,1,4,	// 0010 1011 XV
  2,7,9,  5,11,10,4,5,10,0,0,0,	// 0010 1100 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0010 1101 
  10,4,11,4,0,11, 0,7,11,0,2,7,	// 0010 1110 XV
  10,7,11,10,2,7, 10,8,2,0,0,0,	// 0010 1111 XV

  8,6,7,  8,7,9,  0,0,0, 0,0,0,	// 0011 0000 XV
  6,7,9,  6,9,0,  6,0,4, 0,0,0,	// 0011 0001 XV
  7,5,0,  7,0,8,  7,8,6, 0,0,0,	// 0011 0010 XV
  7,5,4,  4,6,7,  0,0,0, 0,0,0,	// 0011 0011 XV
  8,6,7,  8,7,9,  1,10,4,0,0,0,	// 0011 0100 XV
  0,1,10, 0,10,6, 0,6,9, 6,7,9,	// 0011 0101 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0011 0110 
  7,5,1,  7,1,10, 7,10,6,0,0,0,	// 0011 0111 XV

  8,6,7,  8,7,9,  1,5,11,0,0,0,	// 0011 1000 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0011 1001 
  1,0,11, 7,11,0, 8,7,0, 6,7,8,	// 0011 1010 XV
  6,1,4,  6,11,1, 6,7,11,0,0,0,	// 0011 1011 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0011 1100 
  7,11,10,6,7,10, 0,5,9, 0,0,0,	// 0011 1101 XV
  7,11,10,6,7,10, 0,8,4, 0,0,0,	// 0011 1110 XV
  7,11,10,6,7,10, 0,0,0, 0,0,0,	// 0011 1111 XV

  3,6,10, 0,0,0,  0,0,0, 0,0,0,	// 0100 0000 XV
  3,6,10, 0,4,8,  0,0,0, 0,0,0,	// 0100 0001 XV
  3,6,10, 0,9,5,  0,0,0, 0,0,0,	// 0100 0010 XV
  3,6,10, 4,9,5,  4,8,9, 0,0,0,	// 0100 0011 XV
  1,3,6,  1,6,4,  0,0,0, 0,0,0,	// 0100 0100 XV
  1,3,6,  1,6,8,  1,8,0, 0,0,0,	// 0100 0101 XV
  1,3,6,  1,6,4,  0,9,5, 0,0,0,	// 0100 0110 XV
  6,1,3,  6,8,1,  8,5,1, 8,9,5,	// 0100 0111 XV

  3,6,10, 1,5,11, 0,0,0, 0,0,0,	// 0100 1000 XV
  0,4,8,  1,5,11, 3,6,10,0,0,0,	// 0100 1001 XV
  3,6,10, 0,9,11, 0,11,1,0,0,0,	// 0100 1010 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0100 1011 
  4,5,11, 4,11,3, 4,3,6, 0,0,0,	// 0100 1100 XV
  0,5,11, 0,11,3, 0,3,8, 8,3,6,	// 0100 1101 XV
  0,9,11, 4,0,11, 3,4,11,3,6,4,	// 0100 1110 XV
  9,6,8,  9,3,6,  9,11,3,0,0,0,	// 0100 1111 XV

  2,8,10, 2,10,3, 0,0,0, 0,0,0,	// 0101 0000 XV
  2,10,3, 2,4,10, 2,0,4, 0,0,0,	// 0101 0001 XV
  2,8,10, 2,10,3, 0,9,5, 0,0,0,	// 0101 0010 XV
  10,3,2, 4,10,2, 2,9,4, 4,9,5,	// 0101 0011 XV
  3,4,1,  3,8,4,  3,2,8, 0,0,0,	// 0101 0100 XV
  0,1,2,  3,2,1,  0,0,0, 0,0,0,	// 0101 0101 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0101 0110 
  3,5,1,  3,9,5,  3,2,9, 0,0,0,	// 0101 0111 XV

  2,8,10, 2,10,3, 1,5,11,0,0,0,	// 0101 1000 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0101 1001 
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0101 1010 
  3,2,9,  9,11,3, 4,10,1,0,0,0,	// 0101 1011 XV
  11,3,2, 2,5,11, 8,5,2, 4,5,8,	// 0101 1100 XV
  2,11,3, 2,5,11, 2,0,5, 0,0,0,	// 0101 1101 XV
  3,2,9,  9,11,3, 8,4,0, 0,0,0,	// 0101 1110 XV
  3,2,9,  9,11,3, 0,0,0, 0,0,0,	// 0101 1111 XV

  2,7,9,  3,6,10, 0,0,0, 0,0,0,	// 0110 0000 XV
  0,4,8,  2,7,9,  3,6,10,0,0,0,	// 0110 0001 XV
  3,6,10, 0,2,7,  0,7,5, 0,0,0,	// 0110 0010 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0, // 0110 0011 
  1,3,6,  1,6,4,  2,7,9, 0,0,0,	// 0110 0100 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0110 0101 
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0110 0110 
  7,5,1,  1,3,7,  2,6,8, 0,0,0,	// 0110 0111 XV

  1,5,11, 2,7,9,  3,6,10,0,0,0,	// 0110 1000 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0110 1001 
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0110 1010 
  4,10,1, 2,6,8,  7,11,3,0,0,0,	// 0110 1011 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0110 1100 
  0,5,9,  2,6,8,  7,11,3,0,0,0,	// 0110 1101 XV
  7,11,3, 0,2,6,  6,4,0, 0,0,0,	// 0110 1110 XV
  3,7,11, 2,6,8,  0,0,0, 0,0,0,	// 0110 1111 XV

  8,10,3, 8,3,7,  8,7,9, 0,0,0,	// 0111 0000 XV
  0,7,9,  0,3,7,  4,10,3,4,3,0,	// 0111 0001 XV
  0,8,10, 5,0,10, 10,3,5,7,5,3,	// 0111 0010 XV
  5,4,10, 5,10,3, 5,3,7, 0,0,0,	// 0111 0011 XV
  1,3,7,  1,7,9,  9,4,1, 9,8,4,	// 0111 0100 XV
  1,9,0,  1,7,9,  1,3,7, 0,0,0,	// 0111 0101 XV
  7,5,1,  1,3,7,  8,4,0, 0,0,0,	// 0111 0110 XV
  5,1,7,  7,1,3,  0,0,0, 0,0,0,	// 0111 0111 XV

  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 0111 1000 
  0,5,9,  4,10,1, 7,11,3,0,0,0,	// 0111 1001 XV
  7,11,3, 8,10,1, 8,1,0, 0,0,0,	// 0111 1010 XV
  7,11,3, 1,4,10, 0,0,0, 0,0,0,	// 0111 1011 XV
  7,11,3, 4,5,9,  9,8,4, 0,0,0,	// 0111 1100 XV
  3,7,11, 0,5,9,  0,0,0, 0,0,0,	// 0111 1101 XV
  3,7,11, 8,4,0,  0,0,0, 0,0,0,	// 0111 1110 XV
  3,7,11, 0,0,0,  0,0,0, 0,0,0,	// 0111 1111 XV

  3,11,7, 0,0,0,  0,0,0, 0,0,0,	// 1000 0000 XV
  3,11,7, 0,4,8,  0,0,0, 0,0,0,	// 1000 0001 XV
  3,11,7, 9,5,0,  0,0,0, 0,0,0,	// 1000 0010 XV
  3,11,7, 4,9,5,  4,8,9, 0,0,0,	// 1000 0011 XV
  3,11,7, 1,10,4, 0,0,0, 0,0,0,	// 1000 0100 XV
  3,11,7, 1,10,8, 1,8,0, 0,0,0,	// 1000 0101 XV
  0,9,5,  1,10,4, 3,11,7,0,0,0,	// 1000 0110 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1000 0111 

  1,5,7,  1,7,3,  0,0,0, 0,0,0,	// 1000 1000 XV
  1,5,7,  1,7,3,  0,4,8, 0,0,0,	// 1000 1001 XV
  1,0,9,  1,9,7,  1,7,3, 0,0,0,	// 1000 1010 XV
  7,3,1,  9,7,1,  1,4,9, 4,8,9,	// 1000 1011 XV
  5,10,4, 5,3,10, 5,7,3, 0,0,0,	// 1000 1100 XV
  8,0,10, 0,5,10, 10,5,3,3,5,7,	// 1000 1101 XV
  0,9,7,  0,7,3,  3,10,4,0,3,4,	// 1000 1110 XV
  8,3,10, 8,7,3,  8,9,7, 0,0,0,	// 1000 1111 XV

  3,11,7, 2,8,6,  0,0,0, 0,0,0,	// 1001 0000 XV
  3,11,7, 0,6,2,  0,4,6, 0,0,0,	// 1001 0001 XV
  0,9,5,  2,8,6,  3,11,7,0,0,0,	// 1001 0010 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1001 0011 
  1,10,4, 2,8,6,  3,11,7,0,0,0,	// 1001 0100 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1001 0101 
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1001 0110 
  5,1,11, 9,7,2,  6,3,10,0,0,0,	// 1001 0111 XV

  1,5,7,  1,7,3,  2,8,6, 0,0,0,	// 1001 1000 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1001 1001 
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1001 1010 
  6,3,1,  1,4,6,  9,7,2, 0,0,0,	// 1001 1011 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1001 1100 
  6,3,10, 7,2,0,  0,5,7, 0,0,0,	// 1001 1101 XV
  8,4,0,  9,7,2,  6,3,10,0,0,0,	// 1001 1110 XV
  9,7,2,  6,3,10, 0,0,0, 0,0,0,	// 1001 1111 XV

  2,3,9,  3,11,9, 0,0,0, 0,0,0,	// 1010 0000 XV
  2,3,9,  3,11,9, 0,4,8, 0,0,0,	// 1010 0001 XV
  2,3,11, 2,11,5, 2,5,0, 0,0,0,	// 1010 0010 XV
  11,2,3, 2,11,5, 2,5,8, 8,5,4,	// 1010 0011 XV
  2,3,9,  3,11,9, 1,10,4,0,0,0,	// 1010 0100 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1010 0101 
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1010 0110 
  8,2,10, 3,10,2, 5,1,11,0,0,0,	// 1010 0111 XV

  3,1,5,  3,5,9,  3,9,2, 0,0,0,	// 1010 1000 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1010 1001 
  2,1,0,  1,2,3,  0,0,0, 0,0,0,	// 1010 1010 XV
  3,1,4,  3,4,8,  3,8,2, 0,0,0,	// 1010 1011 XV
  2,3,10, 2,10,4, 2,4,9, 4,5,9,	// 1010 1100 XV
  8,2,10, 3,10,2, 0,5,9, 0,0,0,	// 1010 1101 XV
  2,3,10, 2,10,4, 2,4,0, 0,0,0,	// 1010 1110 XV
  8,2,10, 3,10,2, 0,0,0, 0,0,0,	// 1010 1111 XV

  9,8,6,  9,6,3,  9,3,11,0,0,0,	// 1011 0000 XV
  9,0,11, 0,4,11, 4,3,11,3,4,6,	// 1011 0001 XV
  5,0,11, 3,11,0, 8,3,0, 8,6,3,	// 1011 0010 XV
  4,11,5, 4,3,11, 4,6,3, 0,0,0,	// 1011 0011 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1011 0100 
  6,3,10, 9,0,11, 1,11,0,0,0,0,	// 1011 0101 XV
  8,4,0,  5,1,11, 6,3,10,0,0,0,	// 1011 0110 XV
  6,3,10, 1,11,5, 0,0,0, 0,0,0,	// 1011 0111 XV

  6,3,1,  1,8,6,  1,5,8, 8,5,9,	// 1011 1000 XV
  6,3,1,  1,4,6,  0,5,9, 0,0,0,	// 1011 1001 XV
  1,6,3,  1,8,6,  1,0,8, 0,0,0,	// 1011 1010 XV
  3,1,6,  6,1,4,  0,0,0, 0,0,0,	// 1011 1011 XV
  6,3,10, 4,5,9,  9,8,4, 0,0,0,	// 1011 1100 XV
  6,3,10, 0,5,9,  0,0,0, 0,0,0,	// 1011 1101 XV
  6,3,10, 8,4,0,  0,0,0, 0,0,0,	// 1011 1110 XV
  6,3,10, 0,0,0,  0,0,0, 0,0,0,	// 1011 1111 XV

  7,10,11,7,6,10, 0,0,0, 0,0,0,	// 1100 0000 XV
  7,10,11,7,6,10, 0,4,8, 0,0,0,	// 1100 0001 XV
  7,10,11,7,6,10, 0,9,5, 0,0,0,	// 1100 0010 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1100 0011 
  6,4,1,  6,1,11, 6,11,7,0,0,0,	// 1100 0100 XV
  0,1,11, 0,11,7, 0,7,8, 8,7,6,	// 1100 0101 X
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1100 0110 
  8,7,6,  7,8,9,  5,1,11,0,0,0,	// 1100 0111 XV

  7,1,5,  7,10,1, 7,6,10,0,0,0,	// 1100 1000 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1100 1001 
  1,0,10, 6,10,0, 9,6,0, 9,7,6,	// 1100 1010 XV
  8,7,6,  7,8,9,  4,10,1,0,0,0,	// 1100 1011 XV
  4,5,7,  4,7,6,  0,0,0, 0,0,0,	// 1100 1100 XV
  7,0,5,  7,8,0,  7,6,8, 0,0,0,	// 1100 1101 XV
  6,9,7,  6,0,9,  6,4,0, 0,0,0,	// 1100 1110 XV
  6,8,7,  7,8,9,  0,0,0, 0,0,0,	// 1100 1111 XV

  10,11,7,10,7,2, 10,2,8,0,0,0,	// 1101 0000 XV
  11,4,10,0,4,11, 7,0,11,7,2,0,	// 1101 0001 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1101 0010 
  9,7,2,  5,10,11,5,4,10,0,0,0,	// 1101 0011 XV
  2,11,7, 2,8,11, 1,11,8,8,4,1,	// 1101 0100 XV
  0,7,2,  0,11,7, 0,1,11,0,0,0,	// 1101 0101 XV
  8,4,0,  5,1,11, 9,7,2, 0,0,0,	// 1101 0110 XV
  9,7,2,  5,1,11, 0,0,0, 0,0,0,	// 1101 0111 XV

  8,10,1, 1,5,8,  8,5,2, 2,5,7,	// 1101 1000 XV
  4,10,1, 7,2,0,  0,5,7, 0,0,0,	// 1101 1001 XV
  9,7,2,  8,10,1, 8,1,0, 0,0,0,	// 1101 1010 XV
  9,7,2,  1,4,10, 0,0,0, 0,0,0,	// 1101 1011 XV
  5,7,2,  5,2,8,  5,8,4, 0,0,0,	// 1101 1100 XV
  2,0,7,  7,0,5,  0,0,0, 0,0,0,	// 1101 1101 XV
  8,4,0,  9,7,2,  0,0,0, 0,0,0,	// 1101 1110 XV
  7,2,9,  0,0,0,  0,0,0, 0,0,0,	// 1101 1111 XV

  11,9,2, 11,6,10,11,2,6,0,0,0,	// 1110 0000 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0,	// 1110 0001 
  5,10,11,0,10,5, 6,10,0,0,2,6,	// 1110 0010 XV
  2,6,8,  5,10,11,5,4,10,0,0,0,	// 1110 0011 XV
  9,1,11, 9,4,1,  2,4,9, 6,4,2, // 1110 0100 XV
  2,6,8,  9,0,11, 1,11,0,0,0,0,	// 1110 0101 XV
  5,1,11, 0,2,6,  6,4,0, 0,0,0,	// 1110 0110 XV
  8,2,6,  5,1,11, 0,0,0, 0,0,0,	// 1110 0111 XV

  1,5,9,  2,6,10, 1,2,10,9,2,1,	// 1110 1000 XV
  0,5,9,  4,10,1, 2,6,8, 0,0,0,	// 1110 1001 XV
  0,10,1, 0,6,10, 0,2,6, 0,0,0,	// 1110 1010 XV
  2,6,8,  1,4,10, 0,0,0, 0,0,0,	// 1110 1011 XV
  4,2,6,  4,9,2,  4,5,9, 0,0,0,	// 1110 1100 XV
  2,6,8,  0,5,9,  0,0,0, 0,0,0,	// 1110 1101 XV
  6,0,2,  4,0,6,  0,0,0, 0,0,0,	// 1110 1110 XV
  8,2,6,  0,0,0,  0,0,0, 0,0,0,	// 1110 1111 XV

  9,10,11,9,8,10, 0,0,0, 0,0,0,	// 1111 0000 XV
  11,4,10,11,0,4, 11,9,0,0,0,0,	// 1111 0001 XV
  10,11,5,10,5,0, 10,0,8,0,0,0,	// 1111 0010 XV
  5,10,11,5,4,10, 0,0,0, 0,0,0,	// 1111 0011 XV
  9,1,11, 9,4,1,  9,8,4, 0,0,0, // 1111 0100 XV
  9,0,11, 1,11,0, 0,0,0, 0,0,0,	// 1111 0101 XV
  8,4,0,  5,1,11, 0,0,0, 0,0,0,	// 1111 0110 XV
  5,1,11, 0,0,0,  0,0,0, 0,0,0,	// 1111 0111 XV

  8,10,1, 1,5,8,  8,5,9, 0,0,0,	// 1111 1000 XV
  0,5,9,  4,10,1, 0,0,0, 0,0,0,	// 1111 1001 XV
  8,10,1, 8,1,0,  0,0,0, 0,0,0,	// 1111 1010 XV
  4,10,1, 0,0,0,  0,0,0, 0,0,0,	// 1111 1011 XV
  4,5,9,  8,4,9,  0,0,0, 0,0,0,	// 1111 1100 XV
  0,5,9,  0,0,0,  0,0,0, 0,0,0,	// 1111 1101 XV
  0,8,4,  0,0,0,  0,0,0, 0,0,0,	// 1111 1110 XV
  0,0,0,  0,0,0,  0,0,0, 0,0,0	// 1111 1111 XV
};
