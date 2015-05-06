#include "particle.hpp"
#include <iostream>
#include <fstream>
#include <stack> 
#include <cstdlib>
#include <string>

// constructor
sample_particle::sample_particle(std::string filename)
{
  set_filename(filename);

  open_file();
  
  //read_file(filename);
  
}

// default constructor
sample_particle::sample_particle()
{
}

// open file
void sample_particle::open_file()
{
  // if filename not set exit
//  fp *file_stream = open(sample_file);
  filestream.open(sample_file.c_str(), std::ifstream::in); 
  return;
}

// set filename
void sample_particle::set_filename(std::string filename)
{
  sample_file = filename;
}

// destructor
sample_particle::~sample_particle()
{
}



void sample_particle::print_filename()
{
  std::cout << sample_file << std::endl;
  return;
}

//read file
int sample_particle::read_file(int batch_size)
{
  int error_code = 0;
  int i;
  std::string line, str;
  const char* delimiters = " "; 
//  event new_event;
  
  if (filestream.is_open())
    {
      for (i=0; i<batch_size; i++)
        {
          std::cout << "i= " << i << std::endl;
          std::getline (filestream,line);   
          if ( !filestream.eof() )
            {
             std::cout << "eof? " << filestream.eof() << std::endl; 
             //std::getline (std::cin, str);
             //if (!std::cin.eof())
              // std::cout << "failure" << std::endl;
   
             std::cout << "got line" << std::endl;         
             event new_event;
              std::vector<std::string> tokens;
              tokenize(line,tokens,delimiters);
             std::cout << "tokenized line" << std::endl;      
             std::cout << "line " << line <<  std::endl;      
//             std::cout << "token 0 " << std::stof(tokens[0]) << std::endl;      
               
              new_event.x = std::stof(tokens[0]);
              new_event.y = std::stof(tokens[1]);
              new_event.z = std::stof(tokens[2]);
              new_event.u = std::stof(tokens[3]);
              new_event.v = std::stof(tokens[4]);
              new_event.w = std::stof(tokens[5]);
              new_event.name = tokens[6];
              new_event.erg = std::stof(tokens[7]);
              new_event.wgt = std::stof(tokens[8]);
              
             std::cout << "event wgt" << new_event.wgt << std::endl;         
              list.push(new_event);
             std::cout << "pushed" << std::endl;         
            }
          else
            {
              error_code = 1;
              std::cout << " eof reached " << std::endl;
              filestream.close();
            }
           // filestream.close();
         }
   
          //  filestream.close();

   }

        //   filestream.close();
  return error_code;
}

void sample_particle::tokenize( const std::string& str,
                                std::vector<std::string>& tokens,
                                const char* delimiters)
{
  tokens.clear();
  
  std::string::size_type next_token_end, next_token_start =
                         str.find_first_not_of( delimiters, 0);
 
   while ( std::string::npos != next_token_start )
     {
       next_token_end = str.find_first_of( delimiters, next_token_start );
       if ( std::string::npos == next_token_end )
         {
           tokens.push_back(str.substr(next_token_start));
           next_token_start = std::string::npos;
         }
       else
         {
           tokens.push_back( str.substr( next_token_start, next_token_end -
                                         next_token_start ) );
           next_token_start = str.find_first_not_of( delimiters, next_token_end );
         }
     }

}

int sample_particle::pop_next_event(event& next_event)
{

   int error_code = 0;
   int ec; // error code from read file
   int batch_size = 6;

   if ( list.empty() )
     {
       std::cout << "reading file" << std::endl;
       ec = read_file(batch_size);
       std::cout << "read file ec in pop next" << ec << std::endl;
     }

   if ( !list.empty() )
     {
       std::cout << "popping event" << std::endl;
       std::cout << " from list size " << list.size() << std::endl;
       next_event = list.top();
       list.pop();
       std::cout << next_event << std::endl;
     }
   else
     {
       error_code = 1;
     }

   std::cout << "list empty EC " << error_code << std::endl;
   return error_code;
    

}

std::ostream& operator<<(std::ostream& os, const event& this_event)
{
    os << this_event.x << ' ' << this_event.y << ' ' <<
    this_event.z << ' ' << this_event.u << ' ' << this_event.v << ' '
    << this_event.w << ' ' << this_event.name << ' ' << this_event.erg;
    return os;
}

