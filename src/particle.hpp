// sample_particle class
#include <string>
#include <vector>
#include <stack>
#include <fstream>
/*
    struct event {
      union{
        double x;
        double y;
        double z;
      } pos;
      union{
        double u;
        double v;
        double w;
      }dir;
      std::string name;
      double erg;
      double wgt;
    };
 */ 
    struct event {
        double x;
        double y;
        double z;
        double u;
        double v;
        double w;
      std::string name;
      double erg;
      double wgt;
    };
class sample_particle {
  public:
    sample_particle(std::string filename);
    sample_particle(); // default constructor
   ~sample_particle(); // default destructor

    void open_file();
    void print_filename();
    void set_filename(std::string filename);
    

    int read_file(int size);
    
    char* delimiters = " "; 
  
    int pop_next_event(event &next_event); //return 1 when no more events left

  private:
    std::string sample_file; // filename of particles 
    std::ifstream filestream;  // filestream of filename

    std::stack<event> list;
   
    void tokenize( const std::string& str,
                   std::vector<std::string>& tokens,
                   const char* delimiters);

    int batch_size;

    
    
    
};


std::ostream& operator<<(std::ostream& os, const event& this_event);
