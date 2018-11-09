#include <string>
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <tr1/unordered_map>
#include <vector>
#include <set>
#include <numeric>
#include <cmath>
#include <unistd.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/dynamic_bitset.hpp>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <deque>
#include <iomanip>

using namespace std;
using namespace boost;

#define LINE_WIDTH 80

string wrapString(string str) {

string tmp_str= str ;
tmp_str += str.substr(0, 0.1*str.size() );
int i= 0;
int char_count= 0;

for(int j= 0; j< str.length(); j++) {
    if(char_count!= 0 && char_count% LINE_WIDTH== 0){
       tmp_str[i++]= '\n';
      }
    tmp_str[i++]= str[j];
    char_count ++;
   }
tmp_str[i]= '\0';
string result_str= tmp_str.substr(0, i);

return result_str;
}

int readSeqFile(string seqFileName, map<string,string> &seqSet) {

ifstream seqFile(seqFileName.c_str() );
assert(seqFile.is_open() );

string line= "", tag= "", seq= "";
getline(seqFile, line);
while( !seqFile.eof() ) {
      if(line[0] =='>') {
         if(tag!= "") {
            seqSet.insert(pair<string,string>(tag,seq) );
           }
         tag= line.substr(1);
         seq= "";
         }
      else
         seq += line;
     getline(seqFile, line);
     }
seqSet.insert(pair<string,string>(tag,seq) );
seqFile.close();
}

int random_pickup_int(int range) {

//srand ( (unsigned)time(0));
int n= rand()%range;

if(range== 1000)
   cerr << "range: " << n << endl;
return n;
}

int random_pickup_double(int range) {

//int range= 1000;
double n=(rand()%range)*0.001;
return n;
}

int check_snp(char& first_nt, char& second_nt) {

char major_nt= toupper(first_nt);

if(major_nt== 'N')
   return 0;

//--------check SNP frequency < 0.001
int snp_freq= random_pickup_int(1000);
if(snp_freq > 0) {
   return 0;
  } 


srand ( (unsigned)time(0));
vector<char> ntVec{'A', 'T', 'G', 'C'};
random_shuffle(ntVec.begin(), ntVec.end() );

char minor_nt= ntVec[0];
if(minor_nt== major_nt)
   minor_nt= ntVec[1];

int switch_nt= random_pickup_int(2);
if(switch_nt== 0) {
   char nt_tmp= major_nt;
   major_nt= minor_nt;
   minor_nt= nt_tmp;
  }

int first_freq= random_pickup_int(100);
int second_freq= random_pickup_int(100);

if(first_freq >= 5) 
  first_nt= major_nt;      
else
  first_nt= minor_nt;

if(second_freq >= 5) 
   second_nt= major_nt;
else
   second_nt= minor_nt;

if(first_nt== second_nt)
   return 1;
else
   return 2;
}

int main(int argc, char* argv[]) {

cerr<< "./snp_simulate <seq.fa>" << endl;
assert(argc== 2);


string seqFileName= argv[1];
map<string, string> seqSet;
readSeqFile(seqFileName, seqSet);

ofstream paternalFile("paternal.fa"), maternalFile("maternal.fa");

for(map<string,string>::iterator i= seqSet.begin(); i!= seqSet.end(); i++) {
    string alt_chrm= "";
    for(string::iterator j= i->second.begin(); j!= i->second.end(); j++) {
        char first_nt= *j, second_nt= *j;
        int snp_exist= check_snp(first_nt, second_nt);
        if(snp_exist== 2) {
            *j= first_nt; 
           alt_chrm += second_nt;
cout << i->first << "\t" << distance(i->second.begin(), j) << "\t" << first_nt << "\t" << second_nt << endl;
          }
        else
          alt_chrm += *j;
       }
//   paternalFile.width(80);
//   maternalFile.width(80);
//   paternalFile<< setw(80);
//   maternalFile<< setw(80);
   paternalFile<< ">" << i->first << "\n"  << wrapString(i->second) << endl;
   maternalFile<< ">" << i->first << "\n" << wrapString(alt_chrm) << endl;
  }








paternalFile.close();
maternalFile.close();
}
