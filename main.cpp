/**********************************************************************************************************
*
*       Assignment 4 , programming II , 2018
*       under supervision of DR. Mohmmed Nassef
*
*       Authers :
*                   # Ehab fawzy ibrahim        20170072
*                   # Thomas Wahid Hanna        20170081
*                   # Hussien Ashraf Feteiha    20170093
*
**********************************************************************************************************/

#include <iostream>
#include "Sequence.h"

#include "DNA.h"
#include "RNA.h"
#include "Protein.h"
#include "CodonsTable.h"

using namespace std;

void Menu1();  //the display menus
void Menu2_1();
void Menu2_2();
void Menu2_2_1();
void Menu2_2_2();
void Menu2_2_3();
void Menu3();
void Menu4();
void Menu5();
bool isValid_fileSyntax( string& fileName );
int find_id( string );
string id_input( string object );
int getId( string object );

vector < pair < Sequence * , string > > data; //vector where all sequences are stored
CodonsTable CTable;

int main()
{
    CTable.LoadCodonsFromFile("RNA_codon_table.txt");
    string first_choice, second_choice, third_choice , fourth_choice , idStr;
    string inputSeq , inputType , tempChoice , fileName;

    while (true)
    {
        system("CLS");
        cout <<"\n\t\t\t  Welcome to Biological Data"<<endl;
        Menu1();
        cin >> first_choice;
        system( "CLS" );
        if      ( first_choice == "1" )
        {
                do
                {
                    try
                    {
                        Menu2_1();
                        cin >> second_choice;

                        if ( second_choice != "1" && second_choice != "2" && second_choice != "3" && second_choice != "4" )
                            throw 0;

                        break;
                    }
                    catch( int )
                    {
                        cout << "\n>> ERROR: Invalid Input\n\n";
                        system( "pause" ); system( "CLS" );
                    }
                }
                while( true );

                system( "CLS" );
                Sequence * object;
                if      (second_choice == "1")
                {
                    try
                    {
                        object = new DNA;
                        cin >> object;

                        if ( object->getValid() == false )
                            throw 0;

                        idStr = id_input( "DNA" );
                        data.push_back( make_pair( object , idStr ) );
                        cout << ">> Success operation" << endl;
                    }
                    catch ( int ){}

                    system( "pause" );
                    system ("cls");
                }
                else if (second_choice == "2")
                {
                    try
                    {
                        object = new RNA;
                        cin >> object;

                        if ( object->getValid() == false )
                            throw 0;

                        idStr = id_input( "RNA" );
                        data.push_back( make_pair( object , idStr ) );
                        cout << ">> Success operation" << endl;
                    }
                    catch ( int ){}

                    system( "pause" );
                    system ("cls");
                }
                else if (second_choice == "3")
                {
                    try
                    {
                        object = new Protein;
                        cin >> object;

                        if ( object->getValid() == false )
                            throw 0;

                        idStr = id_input( "Protein" );
                        data.push_back( make_pair( object , idStr ) );
                        cout << ">> Success operation" << endl;
                    }
                    catch ( int ){}

                    system( "pause" );
                    system ("cls");
                }

        }
        else if ( first_choice == "2" )
        {
            /// valid input for the second menu
            do
            {
                try
                {
                    Menu2_2();
                    cin >> third_choice;

                    if ( third_choice != "1" && third_choice != "2" && third_choice != "3" && third_choice != "4" )
                        throw 0;

                    break;
                }
                catch( int )
                {
                    cout << "\n>> ERROR: Invalid Input\n\n";
                    system( "pause" ); system( "CLS" );
                }
            }
            while( true );

            system( "CLS" );
            if      ( third_choice == "1" )                 /// DNA Operation
            {
                    do
                    {
                        try
                        {
                            Menu2_2_1();
                            cin >> fourth_choice;

                            string valid = "12345678",chr = ""; bool isTrue = false;
                            for ( int i = 0; i < (int)valid.length(); i++ )
                            {
                                chr = ""; chr += valid[i];
                                fourth_choice == chr ? isTrue = true : 0;
                            }

                            if ( !isTrue )
                                throw 0;
                            else
                                break;
                        }
                        catch( int )
                        {
                            cout << "\n>> ERROR: Invalid Input\n\n";
                            system( "pause" ); system( "CLS" );
                        }
                    }
                    while( true );

                    system( "CLS" );

                    if ( fourth_choice == "8" ) continue;
                    /// get the password
                    int index = getId( "DNA" );
                    if      ( index == -1 ) break;

                    if      (fourth_choice == "1")
                    {
                        //data.Print();
                        cout << data[ index ].first;
                    }
                    else if (fourth_choice == "2")
                    {
                        ///build compl. strand
                        Sequence * object = data[ index ].first;
                        ((DNA*)object)->BuildComplementaryStrand();
                    }
                    else if (fourth_choice == "3")
                    {
                        ///transfer to rna
                        Sequence * object   = data[ index ].first;
                        Sequence * DNA_RNA  = ((DNA*)object)->ConvertToRNA();

                        idStr = id_input( "RNA" );
                        data.push_back( make_pair( DNA_RNA , idStr ) );
                    }
                    else if (fourth_choice == "4")
                    {
                        ///transfer to protein
                        Sequence * DNA_RNA;
                        Sequence * RNA_Protein;
                        Sequence * object = data[ index ].first;

                        DNA_RNA         = ((DNA*)object )->ConvertToRNA();
                        RNA_Protein     = ((RNA*)DNA_RNA)->ConvertToProtein( CTable );

                        idStr = id_input( "Protein" );
                        data.push_back( make_pair( RNA_Protein , idStr ) );
                    }
                    else if (fourth_choice == "5")
                    {
                        ///add 2 dna strands

                        int index2 = getId( "DNA" );
                        if ( index2 > 0 )
                        {
                            Sequence * object1 = data[ index  ].first;
                            Sequence * object2 = data[ index2 ].first;

                            Sequence * concatination = *object1 + object2;

                            idStr = id_input( "DNA" );
                            data.push_back( make_pair( concatination , idStr ) );
                        }
                    }
                    else if (fourth_choice == "6")
                    {
                        ///check equality

                        int index2 = getId( "DNA" );
                        if ( index2 > 0 )
                        {
                            Sequence * object1 = data[ index  ].first;
                            Sequence * object2 = data[ index2 ].first;

                            if ( *object1 == object2 )
                                cout << "Two DNA objects are equal " << endl;
                            else
                                cout << "Two DNA objects are not equal " << endl;

                            system( "pause" );
                            system( "CLS" );
                        }
                    }
                    else if (fourth_choice == "7")
                    {
                            /// Save;
                            fstream outFile;
                            do
                            {
                                try
                                {
                                    cout << "Enter the name of the file : ";
                                    cin  >> fileName;

                                    if ( isValid_fileSyntax( fileName ) == false )
                                        throw "Invalid File Name";

                                    outFile.open( fileName.c_str() , ios::in | ios::app );
                                    if ( outFile.fail() )
                                        throw "File Not Founded";
                                    break;
                                }
                                catch ( const char* mess )
                                {
                                    cout << "ERROR: " << mess << endl;
                                }

                            }
                            while( true );

                            data[ index ].first->Print( outFile );
                    }
            }
            else if ( third_choice == "2" )                 /// RNA Operation
            {

                    do
                    {
                        try
                        {
                            Menu2_2_2();
                            cin >> fourth_choice;

                            string valid = "1234567",chr = ""; bool isTrue = false;
                            for ( int i = 0; i < (int)valid.length(); i++ )
                            {
                                chr = ""; chr += valid[i];
                                fourth_choice == chr ? isTrue = true : 0;
                            }

                            if ( !isTrue )
                                throw 0;
                            else
                                break;
                        }
                        catch( int )
                        {
                            cout << "\n>> ERROR: Invalid Input\n\n";
                            system( "pause" ); system( "CLS" );
                        }
                    }
                    while( true );

                    system( "CLS" );
                    if ( fourth_choice == "7" ) continue;
                    /// get the password
                    int index = getId( "RNA" );
                    if      ( index == -1 ) break;

                    if      ( fourth_choice == "1" )
                    {
                        ///print
                        data[ index ].first->Print();
                    }
                    else if ( fourth_choice == "2" )
                    {
                        ///transfer to DNA
                        Sequence * object   = data[ index ].first;
                        Sequence * RNA_DNA  = ((RNA*)object)->ConvertToDNA();

                        idStr = id_input( "Protein" );
                        data.push_back( make_pair( RNA_DNA , idStr ) );
                    }
                    else if ( fourth_choice == "3" )
                    {
                        ///transfer to Protein
                        Sequence * object   = data[ index ].first;
                        Sequence * RNA_Protein  = ((RNA*)object)->ConvertToProtein( CTable );

                        idStr = id_input( "Protein" );
                        data.push_back( make_pair( RNA_Protein , idStr ) );
                    }
                    else if ( fourth_choice == "4" )
                    {
                        ///add 2 RNA strands

                        int index2 = getId( "RNA" );
                        if ( index2 > 0 )
                        {
                            Sequence * object1 = data[ index  ].first;
                            Sequence * object2 = data[ index2 ].first;

                            Sequence * concatination = *object1 + object2;

                            idStr = id_input( "RNA" );
                            data.push_back( make_pair( concatination , idStr ) );
                        }
                    }
                    else if ( fourth_choice == "5" )
                    {
                        ///check equality

                        int index2 = getId( "RNA" );
                        if ( index2 > 0 )
                        {
                            Sequence * object1 = data[ index  ].first;
                            Sequence * object2 = data[ index2 ].first;

                            if ( *object1 == object2 )
                                cout << "Two RNA objects are equal " << endl;
                            else
                                cout << "Two RNA objects are not equal " << endl;
                        }
                        system("Pause");
                        system("CLS");
                    }
                    else if ( fourth_choice == "6" )
                    {
                        /// Save;
                            fstream outFile;
                            do
                            {
                                try
                                {
                                    cout << "Enter the name of the file : ";
                                    cin  >> fileName;

                                    if ( isValid_fileSyntax( fileName ) == false )
                                        throw "Invalid File Name";

                                    outFile.open( fileName.c_str() , ios::in | ios::app );
                                    if ( outFile.fail() )
                                        throw "File Not Founded";
                                    break;
                                }
                                catch ( const char* mess )
                                {
                                    cout << "ERROR: " << mess << endl;
                                }

                            }
                            while( true );

                            data[ index ].first->Print( outFile );
                    }

            }
            else if ( third_choice == "3" )                 /// Protein Operation
            {
                    do
                    {
                        try
                        {
                            Menu2_2_3();
                            cin >> fourth_choice;

                            string valid = "123456",chr = ""; bool isTrue = false;
                            for ( int i = 0; i < (int)valid.length(); i++ )
                            {
                                chr = ""; chr += valid[i];
                                fourth_choice == chr ? isTrue = true : 0;
                            }

                            if ( !isTrue )
                                throw 0;
                            else
                                break;
                        }
                        catch( int )
                        {
                            cout << "\n>> ERROR: Invalid Input\n\n";
                            system( "pause" ); system( "CLS" );
                        }
                    }
                    while( true );

                    system( "CLS" );
                    if ( fourth_choice == "6" ) continue;

                    /// get the password
                    int index = getId( "Protein" );
                    if      ( index == -1 ) break;

                    if      (fourth_choice == "1")
                    {
                        ///print
                        data[ index ].first->Print();
                    }
                    else if (fourth_choice == "2")
                    {
                        ///get equivalent DNA(s)
                        cout << "Enter the ID of the DNA object" << endl;
                        int index2 = getId( "DNA" );

                        system("pause");
                        if ( index2 >= 0 )
                        {
                            DNA DNA_object;// = new DNA;//( *((DNA*)data[index].first) );
                            Sequence * p = data[index2].first;
                            DNA_object.setDNA_Type( ((DNA*)p)->getType() );
                            DNA_object.setDNA_sequence( ((DNA*)p)->getSequence() , ((DNA*)p)->getLength() );
                            DNA_object.setDNA_Start_index(-1);
                            DNA_object.setDNA_END_index(-1);

                            Sequence * protein_object   = data[ index  ].first;
                            DNA* result_array           = ((Protein*)protein_object)->GetDNAStrandsEncodingMe( DNA_object );

                            system( "CLS" ); string small_choice = "";
                            do
                            {
                                    try
                                    {
                                        cout << "(1) Print All the Sequences" << endl;
                                        cout << "(2) Save  All the Sequences" << endl;
                                        cout << "(3) Print and save "         << endl;
                                        cout << "Choice: "; cin >> small_choice;

                                        if ( small_choice != "1" && small_choice != "2" && small_choice != "3" )
                                            throw 0;
                                        else
                                            break;
                                    }
                                    catch( int )
                                    {
                                        cout << "ERROR: invalid Input" << endl;
                                        system("pause"); system("CLS");
                                    }
                            }
                            while( true );


                            if      ( small_choice == "1" || small_choice == "3" )
                            {
                                for ( int i = 0; i > -1 ; i++ )
                                {
                                    if ( result_array[ i ].getSequence() == nullptr ) break;
                                    else
                                    {
                                        result_array[ i ].Print();
                                    }
                                }
                            }
                            if      ( small_choice == "2" || small_choice == "3" )
                            {
                                    fstream outFile;
                                    do
                                    {
                                        try
                                        {
                                            cout << "Enter the name of the file : ";
                                            cin  >> fileName;

                                            if ( isValid_fileSyntax( fileName ) == false )
                                                throw "Invalid File Name";

                                            outFile.open( fileName.c_str() , ios::in | ios::app );
                                            if ( outFile.fail() )
                                                throw "File Not Founded";
                                            break;
                                        }
                                        catch ( const char* mess )
                                        {
                                            cout << "ERROR: " << mess << endl;
                                        }

                                    }
                                    while( true );

                                    for ( int i = 0; i > -1; i++ )
                                    {
                                        if ( result_array[ i ].getSequence() == nullptr )
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            result_array[ i ].Print( outFile );
                                        }
                                    }
                            }

                            system( "pause" );
                        }
                    }
                    else if (fourth_choice == "3")
                    {
                        ///add 2 protein strands
                        int index2 = getId( "Protein" );
                        if ( index2 > 0 )
                        {
                            Sequence * object1 = data[ index  ].first;
                            Sequence * object2 = data[ index2 ].first;

                            Sequence * concatination = *object1 + object2;

                            idStr = id_input( "Protein" );
                            data.push_back( make_pair( concatination , idStr ) );
                        }
                    }
                    else if (fourth_choice == "4")
                    {
                        ///check equality
                        int index2 = getId( "Protein" );
                        if ( index2 > 0 )
                        {
                            Sequence * object1 = data[ index  ].first;
                            Sequence * object2 = data[ index2 ].first;

                            if ( *object1 == object2 )
                                cout << "Two Protein objects are equal " << endl;
                            else
                                cout << "Two Protein objects are not equal " << endl;
                        }
                    }
                    else if ( fourth_choice == "5" )
                    {
                        /// Save;
                            fstream outFile;
                            do
                            {
                                try
                                {
                                    cout << "Enter the name of the file : ";
                                    cin  >> fileName;

                                    if ( isValid_fileSyntax( fileName ) == false )
                                        throw "Invalid File Name";

                                    outFile.open( fileName.c_str() , ios::in | ios::app );
                                    if ( outFile.fail() )
                                        throw "File Not Founded";
                                    break;
                                }
                                catch ( const char* mess )
                                {
                                    cout << "ERROR: " << mess << endl;
                                }

                            }
                            while( true );

                            data[ index ].first->Print( outFile );
                    }

            }

        }
        else if ( first_choice == "3" )
        {
            /// load
            do
            {
                try
                {
                    Menu3();
                    cin >> third_choice;

                    if ( third_choice != "1" && third_choice != "2" && third_choice != "3" && third_choice != "4" )
                        throw 0;

                    break;
                }
                catch( int )
                {
                    cout << "\n>> ERROR: Invalid Input\n\n";
                    system( "pause" ); system( "CLS" );
                }
            }
            while( true );
            system( "CLS" );

            fstream infile;
            if ( third_choice != "4" )
            {

                    do
                    {
                            try
                            {
                                cout << "Enter the file name : ";
                                cin  >> fileName;

                                if ( isValid_fileSyntax( fileName ) == false )
                                    throw "Invalid file name";

                                infile.open( fileName.c_str() , ios::in );

                                if ( infile.fail() == true )
                                    throw "File not founded";

                                break;

                            }
                            catch( const char* mess )
                            {
                                cout << "ERROR: " << mess << endl;
                                system("pause"); system("CLS");
                            }
                    }
                    while( true );

            }

            Sequence * object;
            if      ( third_choice == "1" )
            {
                /// load DNA
                object = new DNA;
                infile >> object;

                if ( object->getValid() )
                {
                    idStr = id_input( "DNA" );
                    data.push_back( make_pair( object , idStr ) );
                    cout << ">> Success operation" << endl;
                }
                system("pause");

            }
            else if ( third_choice == "2" )
            {
                /// load RNA
                object = new RNA;
                infile >> object;

                if ( object->getValid() )
                {
                    idStr = id_input( "RNA" );
                    data.push_back( make_pair( object , idStr ) );
                    cout << ">> Success operation" << endl;
                }
                system("pause");
            }
            else if ( third_choice == "3" )
            {
                /// load Protein
                object = new Protein;
                infile >> object;

                if ( object->getValid() )
                {
                    idStr = id_input( "Protein" );
                    data.push_back( make_pair( object , idStr ) );
                    cout << ">> Success operation" << endl;
                }
                system("pause");
            }
        }
        else if ( first_choice == "4" )
        {
            /// print
            do
            {
                try
                {
                    Menu4();
                    cin >> third_choice;

                    if ( third_choice != "1" && third_choice != "2" && third_choice != "3" && third_choice != "4" )
                        throw 0;

                    break;
                }
                catch( int )
                {
                    cout << "\n>> ERROR: Invalid Input\n\n";
                    system( "pause" ); system( "CLS" );
                }
            }
            while( true );
            system( "CLS" );

            if      ( third_choice == "4" ) continue;

            if      ( third_choice == "1" )
            {
                int index = getId( "DNA" );
                data[ index ].first->Print();
            }
            else if ( third_choice == "2" )
            {
                int index = getId( "RNA" );
                data[ index ].first->Print();
            }
            else if ( third_choice == "3" )
            {
                int index = getId( "Protein" );
                data[ index ].first->Print();
            }
        }
        else if ( first_choice == "5" )
        {
            /// alignment
            do
            {
                try
                {
                    Menu5();
                    cin >> third_choice;

                    if ( third_choice != "1" && third_choice != "2" && third_choice != "3" && third_choice != "4" )
                        throw 0;

                    break;
                }
                catch( int )
                {
                    cout << "\n>> ERROR: Invalid Input\n\n";
                    system( "pause" ); system( "CLS" );
                }
            }
            while( true );
            system( "CLS" );

            if      ( third_choice == "4" ) continue;

            char * result;
            if      ( third_choice == "1" )
            {
                int index1 = getId( "DNA" );
                int index2 = getId( "DNA" );

                Sequence * object1 = data[ index1 ].first;
                Sequence * object2 = data[ index2 ].first;
                result = Align( object1 , object2 );
            }
            else if ( third_choice == "2" )
            {
                int index1 = getId( "RNA" );
                int index2 = getId( "RNA" );

                Sequence * object1 = data[ index1 ].first;
                Sequence * object2 = data[ index2 ].first;
                result = Align( object1 , object2 );
            }
            else if ( third_choice == "3" )
            {
                int index1 = getId( "Protein" );
                int index2 = getId( "Protein" );

                Sequence * object1 = data[ index1 ].first;
                Sequence * object2 = data[ index2 ].first;
                result = Align( object1 , object2 );
            }

            string small_choice = "";
            do
            {
                system( "CLS" );
                cout << "(1) Print Alignment" << endl;
                cout << "(2) Save  Alignment" << endl;
                cout << "(3) Print and save"  << endl;
                cout << "Choice: "; cin >> small_choice;

                if ( small_choice == "1" || small_choice == "2" || small_choice == "3" )
                {
                    if      ( small_choice == "1" || small_choice == "3" )
                    {
                        cout << "Alignment Sequence : "  << result << endl;
                    }
                    if ( small_choice == "2" || small_choice == "3" )
                    {
                        fstream outFile;
                        do
                        {
                            try
                            {
                                cout << "Enter the name of the file : ";
                                cin  >> fileName;

                                if ( isValid_fileSyntax( fileName ) == false )
                                    throw "Invalid File Name";

                                outFile.open( fileName.c_str() , ios::in | ios::app );
                                if ( outFile.fail() )
                                    throw "File Not Founded";
                                break;
                            }
                            catch ( const char* mess )
                            {
                                cout << "ERROR: " << mess << endl;
                            }

                        }
                        while( true );

                        outFile << "Alignment Sequence : "  << result << endl;
                    }
                    system("pause");
                    break;
                }
                else
                {
                    cout << "Invalid input \n\n";
                    system( "pause" ); system( "CLS" );
                }
            }
            while( true );
        }
        else if ( first_choice == "6" )
        {
            break;
        }
        else
        {
            cout << "Invalid Input!" <<endl;
            system( "Pause" );
            system( "CLS" );
        }
    }

    cout << "\n\t\tGood Bye :)" << endl << endl;
    return 0;
}

void Menu1()
{
    cout << "(1) Create "   << endl;
    cout << "(2) Operate"   << endl;
    cout << "(3) Load"      << endl;
    cout << "(4) print"     << endl;
    cout << "(5) Alignment" << endl;
    cout << "(6) Exit "     << endl;
    cout <<"Choice: " ;
}

void Menu2_1()
{
    cout << "(1) Create new DNA " << endl;
    cout << "(2) Create new RNA " << endl;
    cout << "(3) Create new Protein " << endl;
    cout << "(4) Go to Main Menu" << endl;
    cout << "Choice: " ;
}

void Menu2_2()
{
    cout << "(1) Operate on DNA " <<endl;
    cout << "(2) Operate on RNA " <<endl;
    cout << "(3) Operate on Protein " <<endl;
    cout << "(4) Go to Main Menu" << endl;
    cout << "Choice: ";
}

void Menu2_2_1()
{
    cout << "(1) Print"                         << endl;
    cout << "(2) Build complementary strand "   << endl;
    cout << "(3) Transfer to RNA "              << endl;
    cout << "(4) Transfer to Protein"           << endl;
    cout << "(5) Add 2 DNA strands "            << endl;
    cout << "(6) Check equaltiy"                << endl;
    cout << "(7) Save"                          << endl;
    cout << "(8) Go to Main Menu"               << endl;
    cout <<"Choice: " ;

}

void Menu2_2_2()
{
    cout << "(1) Print"                         << endl;
    cout << "(2) Transfer to DNA "              << endl;
    cout << "(3) Transfer to Protein"           << endl;
    cout << "(4) Add 2 RNA strands "            << endl;
    cout << "(5) Check equaltiy"                << endl;
    cout << "(6) Save"                          << endl;
    cout << "(7) Go to Main Menu"               << endl;
    cout <<"Choice: ";

}

void Menu2_2_3()
{
    cout << "(1) Print"                         << endl;
    cout << "(2) Get Equivelent DNA(s)"         << endl;
    cout << "(3) Add 2 Protein strands"         << endl;
    cout << "(4) Check equaltiy"                << endl;
    cout << "(5) Save"                          << endl;
    cout << "(6) Go to Main Menu"               << endl;
    cout << "Choice: ";

}

void Menu3()
{
    cout << "(1) Load DNA "         << endl;
    cout << "(2) Load RNA "         << endl;
    cout << "(3) Load Protein "     << endl;
    cout << "(4) Go to Main Menu"   << endl;
    cout << "Choice: ";
}


void Menu4()
{
    cout << "(1) Print DNA" << endl;
    cout << "(2) Print RNA" << endl;
    cout << "(4) Print Protein" << endl;
    cout << "(5) Go to Main Menu" << endl;
    cout << "Choice: ";
}
void Menu5()
{
    cout << "(1) Alignment DNA" << endl;
    cout << "(2) Alignment RNA" << endl;
    cout << "(3) Alignment Protein" << endl;
    cout << "(4) Go to Main Menu" << endl;
    cout << "Choice: ";
}

bool isValid_fileSyntax( string& fileName )
{
    bool isValid = true;
    for ( int i = 0; i < (int)fileName.length(); i++ )
    {
        if ( fileName[i] == '\\' ) isValid = false;
        if ( fileName[i] == '/'  ) isValid = false;
        if ( fileName[i] == '*'  ) isValid = false;
        if ( fileName[i] == ':'  ) isValid = false;
        if ( fileName[i] == '?'  ) isValid = false;
        if ( fileName[i] == '<'  ) isValid = false;
        if ( fileName[i] == '>'  ) isValid = false;
        if ( fileName[i] == '"'  ) isValid = false;
        if ( fileName[i] == '|'  ) isValid = false;
    }

    if      ( (int)fileName.length() <  4 )
        fileName += ".txt";
    else if ( (int)fileName.length() == 4 )
    {
        if ( fileName == ".txt" )
            return false;
        else
            fileName += ".txt";
    }
    else
    {
        string temp = "";
        int len = (int)fileName.length();

        for ( int i =  len-4 ; i < len; i++ )
            temp += fileName[ i ];

        temp == ".txt" ? 0 : fileName += ".txt";
    }
    return isValid;
}

string id_input( string object )
{
    do
    {
        try
        {
            string id = "";
            cout << "Enter the ID of the " << object << " : "; cin >> id;

            if ( find_id( id ) != -1 )
                throw id;

            return id;
        }
        catch( string idStr )
        {
            cout << "ERROR: ID ( " << idStr << " ) has been chosen before" << endl;
            system( "Pause"); system( "CLS" );
        }
    }
    while( true );
}

int find_id( string idStr )
{
    int index = -1;
    for ( int i = 0; i < (int)data.size(); i++ )
        data[i].second == idStr ? index = i : 0;
    return index;
}

int getId( string object )
{
    do
    {
            try
            {
                    string id = "";
                    cout << "Enter the ID of the " << object << " : ";
                    cin  >> id;
                    int index = find_id( id );

                    if ( index == -1 )
                        throw id;

                    return index;
            }
            catch( string id )
            {
                cout << "ERROR: ID ( " << id << " ) Not founded" << endl;
                system( "Pause" ); system( "CLS" );
            }

            string choice = "";
            cout << "(1) Enter another one"         << endl;
            cout << "Enter any key to go back"      << endl;
            cout << ">> Choice :: "; cin >> choice;

            if ( choice != "1" )
                return -1;
            system( "CLS" );
    }
    while( true );
}
