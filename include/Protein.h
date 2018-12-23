#include <iostream>

#ifndef PROTEIN_H
#define PROTEIN_H

#include "Sequence.h"
using namespace std;

class DNA;

enum Protein_Type { Hormon, Enzyme, TF, Cellular_Function };

class Protein : public Sequence
{
  	private:
        Protein_Type type;
    public:

 	 	/// constructors and destructor
 	 	Protein();
 	 	Protein(char * p , Protein_Type atype , int sequence_length );
 	 	~Protein();

 	 	void Print(ostream& out = cout );
 	 	bool readFromFile();

 	 	bool isValid(char * temporary , int length );
 	 	/// return an array of DNA sequences that can possibly
                /// generate that protein sequence
        char* convert_to_protein (char* rna , int len );
        DNA* GetDNAStrandsEncodingMe( DNA & bigDNA );

        /// operators overloaded
        Sequence*       operator +  ( Sequence * object );
        bool            operator == ( Sequence * object );
        bool            operator != ( Sequence * object );

        /// setters and getters
        Protein_Type getType();
        void setType( Protein_Type atype );
};


#endif // PROTEIN_H
