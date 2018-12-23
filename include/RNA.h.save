#include <iostream>

#ifndef RNA_H
#define RNA_H

#include "Sequence.h"
using namespace std;

class DNA;
class Protein;

enum RNA_Type {mRNA, pre_mRNA, mRNA_exon, mRNA_intron};

class RNA : public Sequence
{
  	private:
        RNA_Type type;
  	public:
 	 	// constructors and destructor
        RNA();
        RNA(char * seq, RNA_Type atype , int sequence_length );
        RNA(char * seq , int sequence_length );
        RNA(RNA& rhs);

        /// setters and getters
        RNA_Type getType();
        void setType(RNA_Type atype);

        ~RNA();
 	 	/// function to be overridden to print all the RNA information
        void Print(ostream& out = cout);
        bool readFromFile();

        bool isValid(char * temporary , int length );
 	 	/// function to convert the RNA sequence into protein sequence
        /// using the codonsTable object
        Protein* ConvertToProtein( CodonsTable & table );
 	 	/// function to convert the RNA sequence back to DNA
        DNA* ConvertToDNA();

        /// operators overloaded
        Sequence*       operator +  ( Sequence * object );
        bool            operator == ( Sequence * object );
        bool            operator != ( Sequence * object );

};


#endif // RNA_H
