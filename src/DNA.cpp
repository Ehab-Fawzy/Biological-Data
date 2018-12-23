#include "DNA.h"
#include "RNA.h"

using namespace std;
// constructors and destructor
DNA::DNA()
{
    /** Default constructor Set the two indices with value (-2)
        this value to let the user input the start and the end
        of the segment he/she want to get the complementary strand of it
    **/
    this->startIndex = -2;
    this->endIndex   = -2;
}


/**
        Default constructor get DNA sequence and type and the length
        then copy all this data with deep copy technique
**/
DNA::DNA(char * seq, DNA_Type atype , int sequence_length )
: Sequence( seq , sequence_length )
{
    this->type = atype;
    this->startIndex = -2;
    this->endIndex   = -2;
}

DNA :: DNA (char * seq , int sequence_length )
: Sequence ( seq , sequence_length )
{
    /// default type.
    this->type = promoter;
}


/**
        constructor take DNA object and copy it use Deep copy
**/
DNA::DNA(DNA& rhs)
{
    this->startIndex = rhs.getStartIndex();
    this->endIndex   = rhs.getEndIndex();
    this->seq_length = rhs.getLength();
    this->type       = rhs.getType();

    this->seq = new char [ this->seq_length ];
    char * deepCopy_seq = rhs.getSequence();
    //cout << "F1:: " << strlen( deepCopy_seq ) << endl;

    for ( int i = 0; i < this->seq_length; i++ )
        this->seq[ i ] = deepCopy_seq [ i ];
    this->seq[ this->seq_length ] = '\0';

    this->complementary_strand_length = rhs.getComplementary_strand_length();

    /**
            this part for get Complementary strand info
    **/
    if ( this->complementary_strand_length > 0 )
    {
        char * deepCopy_Complementary_strand = rhs.getComplementary_strand();
        this->complementary_strand = new char[ complementary_strand_length ];

        //cout << "F2:: " << strlen( deepCopy_Complementary_strand ) << endl;
        for ( int i = 0; i < this->complementary_strand_length; i++ )
            this->complementary_strand[ i ] = deepCopy_Complementary_strand[ i ];
        this->complementary_strand[ this->complementary_strand_length ] = '\0';
        //delete[] deepCopy_Complementary_strand;
    }
    //delete[] deepCopy_seq;
}

/*********************
            Destructor for deallocate the memory
*********************/
DNA::~DNA()
{
    if ( this->complementary_strand != nullptr )
    {
        delete[] this->complementary_strand;
        this->complementary_strand = nullptr;
    }
}

/*********************
            Setters and getters
*********************/
void DNA :: setDNA_Type( DNA_Type Type )
{
    this->type = Type;
}

DNA_Type DNA::getType()
{
    return this->type;
}

char* DNA::getComplementary_strand()
{
    return this->complementary_strand;
}

int DNA::getStartIndex()
{
    return this->startIndex;
}

int DNA::getEndIndex()
{
    return this->endIndex;
}

int DNA :: getComplementary_strand_length()
{
    return this->complementary_strand_length;
}

void DNA :: setDNA_sequence( char* seq , int len )
{
    this->seq_length = len;
    this->seq = new char[ len ];
    for ( int i = 0; i < len; i++ )
        this->seq[ i ] = seq[ i ];
    this->seq[ len ] = '\0';
}

void DNA :: setDNA_Start_index( int index )
{
    this->startIndex = index;
}
void DNA :: setDNA_END_index( int index )
{
    this->endIndex = index;
}

/// function printing DNA sequence information to user According to ostream value
void DNA::Print( ostream& out )
{
    system( "CLS" );
    out << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    out << "|||              The DNA                |||" << endl;
    out << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    out << '\n';

    this->seq[ this->seq_length ] = '\0';
    out << "\nDNA Strand :  ";
    out << this->seq << endl << endl;

    out << "DNA Type   :   ";
    switch ( this->type )
    {
        case 0 :
            out << "promoter" << endl;
            break;

        case 1:
            out << "motif" << endl;
            break;

        case 2:
            out << "tail" << endl;
            break;

        case 3:
            out << "noncoding" << endl;
            break;

        default:
            out << "Unknowing" << endl;
    }

    out << "DNA Complementary Strand  ";
    if ( (this->startIndex == -2 && this->endIndex == -20) || this->complementary_strand == nullptr )
    {
        out << " ( unknowing ) " << endl;
    }
    else
    {
        out << "in range [ " << this->startIndex << " , "
             << this->endIndex << " ] is :  \n"
             << this->complementary_strand << endl;
    }

    out << endl << endl;
    //cout << "\n*******************************************" << endl << endl;
    system( "Pause" );
}

/// function to convert the DNA sequence to RNA sequence
/// It starts by building the complementary_strand of the current
/// DNA sequence (starting from the startIndex to the endIndex);
/*********************
            replace All (T) With (U)
*********************/
RNA* DNA::ConvertToRNA()
{
    char * temp = new char [ this->seq_length ];

    for ( int i = 0; i < this->seq_length; i++ )
    {
        if ( this->seq[ i ] == 'T' )
        {
            temp[ i ] = 'U';
        }
        else
            temp[ i ] = this->seq[ i ];
    }

    temp[ this->seq_length ] = '\0';

    //RNA object;
    RNA * object = new RNA( temp , mRNA , this->seq_length );
    return object;//object;
}

/// function to build the second strand/pair of DNA sequence
/// To build a complementary_strand (starting from the startIndex to
/// the endIndex), convert each A to T, each T to A, each C to G, and
/// each G to C. Then reverse the resulting sequence.
void DNA :: BuildComplementaryStrand()
{

    if ( this->startIndex == -2 || this->endIndex == -2 )
    {
        /// take st && ed as input from user
        cout << "Enter the start index :  ";
        cin  >> this->startIndex;

        cout << "Enter the end index   :  ";
        cin  >> this->endIndex;
    }
    if ( this->startIndex == -1 && this->endIndex == -1 )
        this->startIndex = 0 , this->endIndex = this->getLength();

    /**
            Converting process
    **/
    if ( this->startIndex >= 0 && this->endIndex <= this->getLength() )
    {
        int length = this->endIndex - this->startIndex + 1 ;

        this->complementary_strand = new char [ length ];
        for ( int i = this->startIndex , index = 0; i <= this->endIndex; i++,index++ )
        {
            if      ( this->seq[ i ] == 'T' )
                this->complementary_strand[ index ] = 'A';
            else if ( this->seq[ i ] == 'A' )
                this->complementary_strand[ index ] = 'T';
            else if ( this->seq[ i ] == 'C' )
                this->complementary_strand[ index ] = 'G';
            else if ( this->seq[ i ] == 'G' )
                this->complementary_strand[ index ] = 'C';
        }
        this->complementary_strand[ this->endIndex ] = '\0';
        reverse( complementary_strand , complementary_strand + length-1 );
    }
    else
    {
        cout << "Invalid Input \n\n";
        return;
    }
}


bool DNA :: readFromFile()
{
    /************
            Open the file
    ************/
    fstream infile;
    infile.open( this->tempFileName.c_str() , ios::in );


    /************
            initialize some variables
    ************/
    string typeStr = "";
    char *temporary = new char[seq_length];
    typeStr = deleteSpace( typeStr );
    getline( infile , typeStr );


    /************
            Check for Type
    ************/
    if      ( typeStr == "promoter"  ) this->type = promoter;
    else if ( typeStr == "motif"     ) this->type = motif;
    else if ( typeStr == "tail"      ) this->type = tail;
    else if ( typeStr == "noncoding" ) this->type = noncoding;
    else
    {
        this->valid = false;
        cout << "Invalid Type \n";

        remove( this->tempFileName.c_str() );
        return false;
    }

    /************
            read the sequence
    ************/
    for ( int i = 0; i < this->seq_length; i++ )
    {
        infile >> temporary[ i ];
    }
    temporary[seq_length] = '\0';


    /************
            Valid the input
    ************/
    remove( this->tempFileName.c_str() );
    if ( isValid(temporary , seq_length))
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

Sequence* DNA :: operator + ( Sequence * object )
{
    int length = this->getLength() + object->getLength()+1;
    char * concatination = new char [ length ];

    for ( int i = 0; i < this->getLength(); i++ )
        concatination [ i ] = this->seq [ i ];

    char * a = object->getSequence();
    for ( int i = this->getLength(),j = 0; i < length; i++,j++ )
        concatination[ i ] = a[ j ];
    concatination [ length ] = '\0';

    Sequence * ob = new DNA( concatination , length );
    return ob;
}

bool DNA :: operator == ( Sequence * object )
{
    if ( this->type != ((DNA*)object)->getType() )
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
bool DNA :: operator != ( Sequence * object )
{
    if ( *this == object )
        return false;
    return true;
}

/**
    Function to valid the sequence
**/
bool DNA::isValid(char *temporary , int seq_length )
{
    temporary = get_upper( temporary , seq_length );

    for (int i=0; i<seq_length; i++)
    {
        if (temporary[i] != 'A' && temporary[i] != 'G' && temporary[i] != 'C' && temporary[i] != 'T')
        {
            cout <<"Error : Invalid sequence!" << endl;
            return false;
        }
    }
    this->valid = true;
    return true;
}

/**
    Function to valid the type
**/
bool DNA :: isValid_DNA_type( string type )
{
    /// enum DNA_Type{promoter, motif, tail, noncoding};
    bool flag = false;
    if ( type == "promoter"  ) flag = true;
    if ( type == "motif"     ) flag = true;
    if ( type == "tail"      ) flag = true;
    if ( type == "noncoding" ) flag = true;
    return flag;
}

