#include "particle.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  //  sample_particle *SP = new sample_particle("filename.txt");
  sample_particle *SP = new sample_particle();
  SP->set_filename("sample.txt");
  SP->open_file();
  SP->print_filename();

  event next_event;
  int ec;
  for (int i=0; i<11; i++)
    {
      ec = SP->pop_next_event(next_event);
      std::cout << "ec from pop next " << ec << std::endl;
    }

  return 0;
}
