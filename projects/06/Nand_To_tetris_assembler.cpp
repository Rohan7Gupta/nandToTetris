/*
    This is an assemble for the hack assembly language used for Nand to Tetris course
    An assumption has been taken that the hack assembly code supplied is error free
    The code can contain whitespaces, comments , variables and labels
    there are 2 types of instructions - A type and C type in the Hack assembly language

*/



#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <regex> //for regexReplace
#include <cctype> // For isdigit function
#include <bitset>
#include <vector>
#include <utility>
using namespace std;

vector<pair<string, int>> symbols;

string decimalToBinary16Bit(string atype)
{
    int decimal = stoi(atype);//string to integer
    if (decimal >= 0 && decimal <= 65535)
    {
        return bitset<16>(decimal).to_string();//convert to 16 bit binary and format it to string
    }
    else
    {
        cout<<"error in atype instruction processing - decimalToBinary16bit";
        exit(0);
    }
}

bool ContainsOnlyNumbers(string str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false; // Return true if a digit is foundfalse if some non digit found
        }
    }
    return true; // No digits were found
}

string destination(string d)
{
    if(d=="")
    return "000";
    else if(d=="M")
    return "001";
    else if(d=="D")
    return "010";
    else if(d=="DM"||d=="MD")
    return "011";
    else if(d=="A")
    return "100";
    else if(d=="AM"||d=="MA")
    return "101";
    else if(d=="AD"||d=="DA")
    return "110";
    else if(d=="ADM"||d=="AMD"||d=="DAM"||d=="DMA"||d=="MAD"||d=="MDA")
    return "111";
    else{
        cout<<"error in dest";
        exit(0);
    }
}
string jump_instruction(string d)
{
    if(d=="")
    return "000";
    else if(d=="JGT")
    return "001";
    else if(d=="JEQ")
    return "010";
    else if(d=="JGE")
    return "011";
    else if(d=="JLT")
    return "100";
    else if(d=="JNE")
    return "101";
    else if(d=="JLE")
    return "110";
    else if(d=="JMP")
    return "111";
    else{
        cout<<"error in jump";
        exit(0);
    }
}
string computation(string d)
{
    if(d=="0")
    return "0101010";

    else if(d=="1")
    return "0111111";

    else if(d=="-1")
    return "0111010";

    else if(d=="D")
    return "0001100";

    else if(d=="A")
    return "0110000";
    else if(d=="M")
    return "1110000";

    else if(d=="!D")
    return "0001101";

    else if(d=="!A")
    return "0110001";
    else if(d=="!M")
    return "1110001";

    else if(d=="-D")
    return "0001111";

    else if(d=="-A")
    return "0110011";
    else if(d=="-M")
    return "1110011";

    else if(d=="D+1")
    return "0011111";

    else if(d=="A+1")
    return "0110111";
    else if(d=="M+1")
    return "1110111";

    else if(d=="D-1")
    return "0001110";

    else if(d=="A-1")
    return "0110010";
    else if(d=="M-1")
    return "1110010";

    else if(d=="D+A")
    return "0000010";
    else if(d=="D+M")
    return "1000010";

    else if(d=="D-A")
    return "0010011";
    else if(d=="D-M")
    return "1010011";

    else if(d=="A-D")
    return "0000111";
    else if(d=="M-D")
    return "1000111";

    else if(d=="D&A")
    return "0000000";
    else if(d=="D&M")
    return "1000000";

    else if(d=="D|A")
    return "0010101";
    else if(d=="D|M")
    return "1010101";

    else{
        cout<<"error in comp";
        exit(0);
    }
}
void parse_c(string ctype,string&  dest,string&  comp,string&  jump)
{

    int pos1=ctype.find('=');

    int pos2=ctype.find(';');
    if(pos1==string::npos)
    {
        dest="";
        comp=ctype.substr(0,pos2);
    }
    else
    {
        dest=ctype.substr(0,pos1);
        comp=ctype.substr(pos1+1,pos2-pos1);
    }
    //cout<<comp;
    if(pos2==string::npos)
    {
        jump="";
    }
    else
    jump=ctype.substr(pos2+1);
    //cout<<jump;
}

void LabelHandler(){

    ifstream File_withLabel("cleanedAsm.txt"); 

    if (!File_withLabel.is_open()) {
        cerr << "Failed to open the cleaned ASM file." << endl;
        
    }
    string line;
    string noLabel;
    int line_cnt=0;//line count

    while (getline(File_withLabel, line)) {
        if(line[0]=='(')
        {
            int pos=line.find(')');
            string label=line.substr(1,pos-1);
            symbols.push_back(make_pair(label, line_cnt));
        }
        else
        {
            line_cnt++;
            noLabel+=line+"\n";
        }
    }
    File_withLabel.close();
    ofstream outputFile("no_Label.txt");
    if (outputFile.is_open()) {
        outputFile << noLabel; // Write the content to the file
    }
    outputFile.close();  

}


int main(){

//cleaning file
    cout<<"enter file name: ";
    string name;
    cin>>name;
    cout<<"\n";

    ifstream asmFile(name); // Open the ASM file

    if (!asmFile.is_open()) {
        cerr << "Failed to open the ASM file." << endl;
        return 1;
    }

    string line;
    string cleanedAsm;

    // Regular expression pattern to match comments (//...) and whitespace

/*    //.*: This part of the expression matches any sequence of characters that starts with //, which is the typical syntax for comments in many programming languages including C++. The .* matches any characters after the //, effectively capturing the entire comment.
|: This vertical bar represents the logical OR operation in regular expressions. It allows you to match either the pattern before the | or the pattern after it.
\\s+: This part matches one or more whitespace characters. The \\ is used to escape the backslash, as backslashes have special meaning in regular expressions. */
    regex commentWhitespacePattern("(//.*|\\s+)");


    /*regex_replace is a function provided by many programming languages and libraries, including C++'s Standard Library (<regex> header), that allows you to search for a specific pattern defined by a regular expression and replace it with a new string.
In the context of C++, the regex_replace function takes three main arguments:
Input string: The original string in which you want to search and replace.
Regular expression pattern: The regular expression that defines the pattern you want to find.
Replacement string: The string that will replace the matched pattern.*/
   
   
    while (getline(asmFile, line)) {
        // Remove comments and whitespace using regex_replace
        string cleanedLine = regex_replace(line, commentWhitespacePattern, "");

        // If the cleaned line is not empty, append it to the cleanedAsm
        if (!cleanedLine.empty()) {
            cleanedAsm += cleanedLine + "\n";
        }
    }
    asmFile.close();

    ofstream outputFile("cleanedAsm.txt");
    if (outputFile.is_open()) {
        outputFile << cleanedAsm; // Write the content to the file
    }
    outputFile.close();  



//cout<<"Cleaning done";

//handling labels and symbols



symbols.push_back(make_pair("R0", 0));
symbols.push_back(make_pair("R1", 1));
symbols.push_back(make_pair("R2", 2));
symbols.push_back(make_pair("R3", 3));
symbols.push_back(make_pair("R4", 4));
symbols.push_back(make_pair("R5", 5));
symbols.push_back(make_pair("R6", 6));
symbols.push_back(make_pair("R7", 7));
symbols.push_back(make_pair("R8", 8));
symbols.push_back(make_pair("R9", 9));
symbols.push_back(make_pair("R10", 10));
symbols.push_back(make_pair("R11", 11));
symbols.push_back(make_pair("R12", 12));
symbols.push_back(make_pair("R13", 13));
symbols.push_back(make_pair("R14", 14));
symbols.push_back(make_pair("R15", 15));
symbols.push_back(make_pair("SCREEN", 16384));
symbols.push_back(make_pair("KBD", 24576));
symbols.push_back(make_pair("SP", 0));
symbols.push_back(make_pair("LCL", 1));
symbols.push_back(make_pair("ARG", 2));
symbols.push_back(make_pair("THIS", 3));
symbols.push_back(make_pair("THAT", 4));

int addr=16;


LabelHandler();
//cout<<"Label Handled";
//cout<<symbols[24].first<<symbols[24].second;

//parsing and conversion to binary(atype and ctype)

    ifstream cleanFile("no_Label.txt"); // Open the ASM file

    if (!cleanFile.is_open()) {
        cerr << "Failed to open the no_label ASM file." << endl;
        return 1;
    }
    //cout<<"done 1";
    string dest,comp,jump,ctype,atype,binary;

    while(getline(cleanFile, line))
    {   //cout<<line<<"\n";
        if(line[0]=='@')//A-type
        {   //cout<<line<<" Atype \n";
            atype = line.substr(1);
            if(ContainsOnlyNumbers(atype))
            {
                binary += decimalToBinary16Bit(atype) +"\n";
            }
            else
            {
                //cout<<line<<" Atype with symbol\n";
                // Label and variable handling
                bool check=true;
                int i;
                for( i=0;i<symbols.size();i++)
                {
                    if(symbols[i].first==atype)
                    {   
                        binary+= decimalToBinary16Bit(to_string(symbols[i].second))+"\n";
                        check=false;
                        break;
                    }
                }
                //cout << "Symbol: " << symbols[i].first << ", Quantity: " << symbols[i].second << endl;

                if(check)
                {
                    symbols.push_back(make_pair(atype, addr));
                    binary+= decimalToBinary16Bit(to_string(addr))+"\n";
                    addr++;
                    
                }
            }

        }
        

        else//C-type
        {
        //cout<<line<<" Ctype \n";
            parse_c(line,dest,comp,jump);
            //cout<<"\nparsing "<<dest<<comp<<jump;
            binary +="111"+ computation(comp) + destination(dest) + jump_instruction(jump)+"\n";
        }
        //cout<<binary;
    }
    //cout<<"done 2";

    cleanFile.close();

    ofstream outputFile_binary("Max.hack");
    if (outputFile_binary.is_open()) {
        outputFile_binary << binary;// Write the content to the file
    } 
    outputFile_binary.close(); 
    //cout<<"done";
    //cout << binary; // Print the cleaned ASM code
    
    /*for (const auto& symbol : symbols) {
        cout << "Symbol: " << symbol.first << ", Quantity: " << symbol.second << endl;
    }*/


    return 0;
}