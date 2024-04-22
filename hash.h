#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>
#include <cstring>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {


        // array of 5 integers
        unsigned long long w[5]; 
        std::memset(w, 0, sizeof(w));  

        // calculate hashes of all 0-5 subsets of letters
        int cEnd = k.size(); 
        int cIndex = 4; 
        while(cEnd > 0) {
          int cStart = std::max(0, cEnd - 6);
          w[cIndex] = hash6(k.substr(cStart, cEnd - cStart)); 
          cEnd -= 6; 
          cIndex--;  
        }

        unsigned long long hash = 0; 
        for(int i = 0; i < 5; i++) {
          hash += rValues[i] * w[i]; 
        }

        return hash; 

        // Add your code here


    }

    // k is now a maximum of 6 letters
    unsigned long long hash6(const std::string& k) const {

      // multiplication factor
      unsigned long long m = 1; 
      unsigned long long hash6 = 0; 

      for(int index = k.size() - 1; index >= 0; index--) {
        int val = letterDigitToNumber(k[index]); 
        hash6 += val * m; 
        m *= 36; 
      }
      

      return hash6; 
      
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    int letterDigitToNumber(char letter) const
    {

        // upper case letters
        if(letter >= 65 && letter <= 90) return letter - 65; 
        // lower case letters
        if(letter >= 97 && letter <= 122) return letter - 97;
        // digits
        return (letter - 48) + 26; 


        // Add code here or delete this helper function if you do not want it

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
