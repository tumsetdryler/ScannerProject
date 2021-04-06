#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: Michael Allard 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Michael Allard
// RE:   (vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+
bool word (string s)
{

  int state = 0; //state 0 is q0
  int charpos = 0;

  while(s[charpos] != '\0')
    {
      //initial transitions from state 0 or q0
      if(state == 0 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
	state = 1; //state 1 is q0q1
      else if(state == 0 && (s[charpos] == 'b' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r'))
	state = 4; //state 4 is qy
      else if(state == 0 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
	state = 5; //state 5 is qsa
      else if(state == 0 && s[charpos] == 'c')
	state = 3; //state 3 is qc
      else if(state == 0 && s[charpos] =='s')
	state = 6; //state 6 is qs
      else if(state == 0 && s[charpos] == 't')
	state = 7; //state 7 is qt
      
      //transitions from q0q1
      else if(state == 1 && (s[charpos] == 'b' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r'))
	state = 4; //state 4 is qy
      else if(state == 1 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
	state = 5; //state 5 is qsa
      else if(state == 1 && s[charpos] == 'c')
	state = 3; //state 3 is qc
      else if(state == 1 && s[charpos] == 's')
	state = 6; //state 6 is qs
      else if(state == 1 && s[charpos] == 't')
	state = 7; //state 7 is qt
      
      //transitions from q0qy
      else if(state == 2 && (s[charpos] == 'b' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r'))
	state = 4; //state 4 is qy
      else if(state == 2 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
	state = 5; //state 5 is qsa
      else if(state == 2 && s[charpos] == 'c')
	state = 3; //state 3 is qc
      else if(state == 2 && s[charpos] == 's')
	state = 6; //state 6 is qs
      else if(state == 2 && s[charpos] == 't')
	state = 7; //state 7 is qt

      else if(state == 1 && s[charpos] == 'n')
	state = 2;//state 2 is q0qy
      else if(state == 2 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
	state = 1;
      else if(state == 1 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
	state = 1; //account for the loop on q0q1

      //to get qsa qy qt and qs back to q0q1
      else if(state == 5 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
	state = 1;
      else if(state == 4 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
	state = 1;
      else if(state == 7 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
	state = 1;
      else if(state == 6 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
	state = 1;

      //the different letters that can get to qsa
      else if(state == 3 && s[charpos] == 'h')
	state = 5;
      else if(state == 6 && s[charpos] == 'h')
	state = 5;
      else if(state == 7 && s[charpos] == 's')
	state = 5;
      else if(state == 4 && s[charpos] == 'y')
	state = 5;

      //returns false if no character fits any definition
      else
	return (false);
      charpos++;
    }
  //final check of where we are
  if(state == 0 || state == 1 || state == 2) return(true);
  else return(false);

  /* replace the following todo the word dfa(vowel | vowel n | consonant vowel | etc......  **
 
     where vowel = a,e,i,o,e,I, E    refer to Project-partA_w8A10A.doc for RE   
    while (s[charpos] != '\0') 
    {
      if (state == 0 && s[charpos] == 'a')
      state = 1;
      else
      if (state == 1 && s[charpos] == 'b')
      state = 2;
      else
      if (state == 2 && s[charpos] == 'b')
      state = 2;
      else
	  return(false);
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 2) return(true);  // end in a final state
   else return(false);
  */
}

// PERIOD DFA 
// Done by: Michael Allard
bool period (string s)
{  // check if the character is a period and return true if it is
  if(s == ".")
    return (true);
  else
    return(false);
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Michael Allard

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, SUBJECT, OBJECT, DESTINATION, PRONOUN, CONNECTOR};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "SUBJECT", "OBJCT", "DESTINATION", "PRONOUN", "CONNECTOR" }; 

string reservedWords[30] = {"masu", "masen", "mashita", "masendeshita", "desu", "deshita", "o", "wa", "ni", "watashi", "anata", "kare", "kanojo", "sore", "mata", "soshite", "shikashi", "dakara", "eofm"};
// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.


// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Michael Allard
void scanner(tokentype& tt, string& w)
{
  int count = -1;
  if(w == "eofm")
    return;
  else if(word(w))
    {
      for(int i = 0; i < 19; i++)
	{
	  if(reservedWords[i] == w)
	    count = i;
	}
      if(count < 0)
	{
	  if(w[w.size()-1] == 'I' || w[w.size()-1] == 'E')
	    tt = WORD2;
	  else
	    tt = WORD1;
	}
      else if(count == 0)
	tt = VERB;
      else if(count == 1)
	tt = VERBNEG;
      else if(count == 2)
	tt = VERBPAST;
      else if(count == 3)
	tt = VERBPASTNEG;
      else if(count == 4)
	tt = IS;
      else if(count == 5)
	tt = WAS;
      else if(count == 6)
	tt = OBJECT;
      else if(count == 7)
	tt = SUBJECT;
      else if(count == 8)
	tt = DESTINATION;
      else if(count == 9 || count == 10 || count == 11 || count == 12 || count == 13)
	tt = PRONOUN;
      else if(count == 14 || count == 15 || count == 16 || count == 17)
	tt = CONNECTOR;
    }
  else if(period(w))
    tt = PERIOD;
  else 
    {
      cout << "Lexical error: " << w << " is not a valid token" << endl;
      tt = ERROR;
    }
      
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   

  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */

}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis
int main()
{
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;   
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end

