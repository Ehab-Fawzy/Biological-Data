#include "RNA.h"
#include "DNA.h"
#include "Protein.h"

using namespace std;

/** Default constructor **/
RNA::RNA()
{
    type = mRNA;
    //ctor
}

/** Parameterize constructors to make Deep Copy **/
RNA::RNA(char * seq , int sequence_length )
: Sequence( seq , sequence_length )
{
    type = mRNA;
}

/** Default destructor **/
RNA::~RNA()
{
    //dtor

}

/** Parameterize constructors to make Deep Copy **/
RNA::RNA(char * seq, RNA_Type atype , int sequence_length )
: Sequence( seq , sequence_length )
{
    type = atype;
}

/***********************************************************************************
**
**                               Setters and Getters
**
************************************************************************************/
RNA_Type RNA :: getType()
{
    return this->type;
}

void RNA::setType(RNA_Type atype)
{
    type = atype;
}

/**
        constructor take RNA object and copy it
**/
RNA::RNA(RNA& rhs) : Sequence( rhs.getSequence() , rhs.getLength() )
{
    this->type = rhs.type;
}

/// function printing All RNA object information to user According to ostream value
/// in file or in console
void RNA::Print( ostream& out )
{
    system( "CLS" );
    out << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    out << "|||              The RNA                |||" << endl;
    out << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    out << '\n';

    out << "RNA Strand :  \n";
    out << this->seq << endl << endl;

    out << "RNA Type   :   ";
    switch ( this->type )
    {
        case 0 :
            out << "mRNA" << endl;
            break;

        case 1:
            out << "pre_mRNA" << endl;
            break;

        case 2:
            out << "mRNA_exon" << endl;
            break;

        case 3:
            out << "mRNA_intron" << endl;
            break;

        default:
            out << "Unknowing" << endl;
    }

    out << endl << endl;
    system( "Pause" );
    ///cout << "\n*******************************************" << endl << endl;
}


DNA* RNA::ConvertToDNA()
{
    char * temp = new char [ this->seq_length ];        /// set size of the sequence

    for ( int i = 0; i < this->seq_length; i++ )        /// replace (U) with (T)
    {
        if ( this->seq[ i ] == 'U' )
        {
            temp[ i ] = 'T';
        }
        else
            temp[ i ] = this->seq[ i ];
    }
    temp[ this->seq_length ] = '\0';                    /// set end of the sequence

    DNA* object = new DNA( temp , promoter , this->seq_length );
    return object;
}

/**
        function for converting RNA to protein using codons table uploaded from file
**/

Protein* RNA::ConvertToProtein( CodonsTable & table )
{
    char * comparer = new char[4];
    Codon temp[seq_length];
    char * transfered = new char [this->seq_length/3];  /// set size of the sequence
    int j=0;
    for (int i=0; i<seq_length; i=i+3)                  /// get the amino acid
    {
        for (int j=0; j<3; j++)
        {
            comparer[j] = seq[i+j];
        }
        comparer[3] = '\0';
        temp[i] = table.getAminoAcid(comparer);
    }
    for (int i=0; i <= seq_length-3; i=i+3)
    {
            if (temp[i].AminoAcid == ' ')
            {break;}
            transfered[j++] = temp[i].AminoAcid;
    }
    transfered[j] = '\0';
    Protein *returner = new Protein ( transfered , Cellular_Function , j+1);
    return returner;
}


bool RNA :: readFromFile()
{
    fstream infile;
    infile.open( this->tempFileName.c_str() , ios::in );

    string typeStr = "";
    char *temporary = new char[seq_length];
    typeStr = deleteSpace( typeStr );
    getline( infile , typeStr );

    if ( typeStr == "mRNA"        ) this->type = mRNA;
    else if ( typeStr == "pre_mRNA"    ) this->type = pre_mRNA;
    else if ( typeStr == "mRNA_exon"   ) this->type = mRNA_exon;
    else if ( typeStr == "mRNA_intron" ) this->type = mRNA_intron;
    else
    {
        this->valid = false;
        cout << "Invalid Type \n";

        remove( this->tempFileName.c_str() );
        return false;
    }
    for ( int i = 0; i < this->seq_length; i++ )
    {
        infile >> temporary[ i ];
    }
    temporary[seq_length] = '\0';

    remove( this->tempFileName.c_str() );
    if (isValid(temporary , seq_length))
    {
        this->seq = temporary;
        this->seq[ this->seq_length ] = '\0';
        return true;
    }
    else
    {
        return false;
    }
}
/**********************
            Operators over loaded ( + , >> , << )
**********************/
Sequence* RNA :: operator + ( Sequence * object )
{
    int length = this->getLength() + object->getLength()+1; /// set double size
    char * concatination = new char [ length ];

    for ( int i = 0; i < this->getLength(); i++ )   /// sum two sequence
        concatination [ i ] = this->seq [ i ];

    char * a = object->getSequence();
    for ( int i = this->getLength(),j = 0; i < length; i++,j++ )
        concatination[ i ] = a[ j ];
    concatination [ length ] = '\0';

    Sequence * ob = new DNA( concatination , length );
    return ob;
}

bool RNA :: operator == ( Sequence * object ) /// check for equality
{
    if ( this->type != ((RNA*)object)->getType() )
        return false;

    bool isFlag = true;
    char * a = object->getSequence();
    for ( int i = 0; i < this->seq_length; i++ )
    {
        if ( this->seq[i] != a[i] )
            isFlag = false;
    }
    return isFlag;
}

bool RNA :: operator != ( Sequence * object )
{
    if ( *this == object )
        return false;
    return true;
}

/**
    function for check a valid input
**/
bool RNA::isValid(char *temporary , int seq_length )
{
    temporary = get_upper( temporary , seq_length );

    for (int i=0; i<seq_length; i++)
    {
        if (temporary[i] != 'A' && temporary[i] != 'G' && temporary[i] != 'C' && temporary[i] != 'U')
        {
            cout <<"Error : Invalid sequence!" << endl;
            return false;
        }
    }
    this->valid = true;
    return true;
}

