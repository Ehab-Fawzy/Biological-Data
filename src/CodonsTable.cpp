#include "CodonsTable.h"

CodonsTable::CodonsTable()
{
    //ctor
}

CodonsTable::~CodonsTable()
{
    //dtor
}

// function to load all codons from the given text file
void  CodonsTable::LoadCodonsFromFile(string codonsFileName)
{
    fstream file;
    file.open( codonsFileName.c_str() , ios::in );

    if ( file.fail() )
    {
        cout << "Can't open codons File\n\n";
        return;
    }
    else
    {
        char* input = new char[ 4 ];
        char  Amino; int index = 0;
        while ( file >> input >> Amino )
        {
            setCodon( input , Amino , index++ );
        }

        delete[] input;
    }
}

char  CodonsTable :: getAminoAcid_char(char * value)
{
    for ( int i = 0; i < 64; i++ )
    {
        bool flag = true;
        for ( int j = 0; j < (int)strlen( value ); j++ )
        {
            if ( value[j] != this->codons[i].value[j] )
                flag = false;
        }
        if ( flag == true )
        {
            return this->codons[i].AminoAcid;
        }
    }

    return ' ';
}


Codon CodonsTable::getAminoAcid(char * value) const
{
    for ( int i = 0; i < 64; i++ )
    {
        bool flag = true;
        for ( int j = 0; j < (int)strlen( value ); j++ )
        {
            if ( value[j] != this->codons[i].value[j] )
                flag = false;
        }
        if ( flag == true )
        {
            return this->codons[i];
        }
    }

    Codon empty_object;
    for ( int i = 0; i < 4; i++ )
        empty_object.value[ i ] = ' ';
    empty_object.AminoAcid = ' ';

    return empty_object;
}

void  CodonsTable::setCodon(char * value, char AminoAcid, int index)
{
    if ( AminoAcid == '*' )
    {
        AminoAcid = ' ';
    }
    this->codons[ index ].AminoAcid = AminoAcid;
    for ( int i = 0; i < 4; i++ )
        this->codons[ index ].value[ i ] = value[ i ];
}

