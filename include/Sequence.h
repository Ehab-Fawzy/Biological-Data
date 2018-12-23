#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "CodonsTable.h"

#ifndef SEQUENCE_H
#define SEQUENCE_H

using namespace std;
class CodonsTable;

class Sequence
{
  	protected:

        int     seq_length;
        string  tempFileName = "SYSTEM&&temp.txt";
        bool    valid;

    public:
        char *  seq = nullptr;
        CodonsTable codonT;
 	 	// constructors and destructor
        Sequence();
        Sequence( int length );
        Sequence( Sequence& rhs );
        Sequence( char* SEQ , int sequence_length );
        virtual ~Sequence();

        /// setters and getters area
        int     getStrLen();
        int     getLength();
        char*   getSequence();
        bool    getValid();

        void input();
        void create_inputFile_from_input( string , string );
        void create_inputFile_from_file ( string );
        void calculate_inputFile_length (  );
        virtual bool readFromFile() = 0;

        /// validate functions
        bool isValid_fileSyntax( string& );
        string deleteSpace( string );
        char* get_upper( char * seq , int len );

 	 	// pure virtual function that should be overridden because every
        // type of sequence has its own details to be printed
        virtual void Print( ostream& out = cout )= 0;
 	 	// friend function that will find the LCS (longest common
        // subsequence) between 2 sequences of any type, according to
        // polymorphism
        friend char* Align(Sequence * s1, Sequence * s2);

        /*virtual bool         operator == ( Sequence * object ){};
        virtual bool         operator != ( Sequence * object ){};
        virtual Sequence *   operator +  ( Sequence * object ){};*/

        virtual Sequence* operator +  ( Sequence * object ) = 0;
        virtual bool      operator == ( Sequence * object ) = 0;
        virtual bool      operator != ( Sequence * object ) = 0;

        friend ostream& operator << ( ostream& out , Sequence * s );
        friend istream& operator >> ( istream& in  , Sequence * s );
};

//char* Align(Sequence * s1, Sequence * s2);


#endif // SEQUENCE_H
