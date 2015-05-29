/* sample_particle class
   This class reads in a file of particle events
   x y z  u v w  name  energy  weight
   One batch size at a time
   There are functions to push and pop 
   events from the stack
*/
#include <string>
#include <vector>
#include <stack>
#include <fstream>

// event structure has attributes of 
// position, direction, name, energy, weight 
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

    char* delimiters = " "; // space between each attribute in event file

    sample_particle(std::string filename, int size); // constructor

    sample_particle(); // default constructor

   ~sample_particle(); // default destructor

    void open_file();

    void set_filename(std::string filename);

    std::string get_filename();

    void print_filename();

    int read_file(int size);

    // sets size of batch to be read in 
    // and pushed to stack at one time
    void set_batch_size(int size);

    // separates string into pieces based on delimiter    
    void tokenize( const std::string& str,
                   std::vector<std::string>& tokens,
                   const char* delimiters);

    // takes in a line from the file, calls tokenize
    // then creates a particle event with various attributes
    // (position, direction, name, energy, and weight)
    event create_event( std::string line );

    // pushes an event to the stack
    void push_next_event( event new_event );

    // pops and event from the stack
    // return 1 when no more events left
    int pop_next_event(event &next_event); 

  

  private:

    std::string sample_file; // filename of particle events
    std::ifstream filestream;  // filestream of filename
    std::stack<event> list;  // stack of events
    int batch_size; // max number of events on stack at one time

    
};


std::ostream& operator<<(std::ostream& os, const event& this_event);
