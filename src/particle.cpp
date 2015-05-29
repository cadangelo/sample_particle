#include "particle.hpp"
#include <iostream>
#include <fstream>
#include <stack> 
#include <cstdlib>
#include <string>

// constructor
sample_particle::sample_particle(std::string filename, int size)
{
  set_filename(filename);

  open_file();
  
  set_batch_size(size); 
}

// default constructor
sample_particle::sample_particle()
{
}

// open file
void sample_particle::open_file()
{
  filestream.open(sample_file.c_str(), std::ifstream::in); 
  return;
}

// set filename
void sample_particle::set_filename(std::string filename)
{
  sample_file = filename;
}

// get filename
std::string sample_particle::get_filename()
{
  return sample_file; 
}

// set batch size
void sample_particle::set_batch_size(int size)
{
  batch_size = size;
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

//read file and push events to stack
int sample_particle::read_file(int batch_size)
{
  int error_code = 0;
  int i;
  std::string line, str;
  const char* delimiters = " "; 
  
  if (filestream.is_open())
    { 
      // read in batch size of file line by line 
      for (i=0; i<batch_size; i++)
        {
          std::getline (filestream,line);  
          
          // if the eof hasn't been reached, create new event
          // and push to stack
          if ( !filestream.eof() )
            {
              event new_event;

              new_event = create_event(line);
                
              push_next_event(new_event);
            }
 
          // if eof is reached, throw error and close filestream
          else
            {
              error_code = 1;
              std::cout << " eof reached " << std::endl;
              filestream.close();
            }
         }
   
   }

  return error_code;
}

// Split string into pieces based on delimiter
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

// Call tokenize to split line, then create particle event 
//  with appropriate attributes
event sample_particle::create_event( std::string line )
{
  event new_event;  // event to be created
  std::vector<std::string> tokens; // pieces of line
  
  tokenize(line,tokens,delimiters);
             
  new_event.x = std::stof(tokens[0]);
  new_event.y = std::stof(tokens[1]);
  new_event.z = std::stof(tokens[2]);
  new_event.u = std::stof(tokens[3]);
  new_event.v = std::stof(tokens[4]);
  new_event.w = std::stof(tokens[5]);
  new_event.name = tokens[6];
  new_event.erg = std::stof(tokens[7]);
  new_event.wgt = std::stof(tokens[8]);

  return new_event;
}

int sample_particle::pop_next_event(event& next_event)
{

   int error_code = 0;
   int ec; // error code from read file
   int batch_size = 6;

   // if the stack is empty read another batch from the file
   // will return error if file is empty
   if ( list.empty() )
     {
       ec = read_file(batch_size);
     }

   // if the stack is NOT empty, pop an event
   if ( !list.empty() )
     {
       next_event = list.top();
       list.pop();
     }
 
   // throw an error if the stack is not empty but 
   // can not pop an event
   else
     {
       error_code = 1;
     }

   return error_code;
    

}

// push an event to the stack
void sample_particle::push_next_event( event new_event )
{
  list.push(new_event);
}


std::ostream& operator<<(std::ostream& os, const event& this_event)
{
    os << this_event.x << ' ' << this_event.y << ' ' <<
    this_event.z << ' ' << this_event.u << ' ' << this_event.v << ' '
    << this_event.w << ' ' << this_event.name << ' ' << this_event.erg;
    return os;
}

