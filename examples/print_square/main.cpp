#include <iostream>
#include "visq/io.h"

using namespace visq;

int main(int argc, char *argv[]){

  char * imname = argv[1];
  size_t channel, print_square_size;
  char * error;
  channel = strtol(argv[2], &error, 10);
  
    
  print_square_size = strtol(argv[3], &error, 10);
    
  auto [error_code, image] = LoadImage(imname);
  if(error_code != ErrorCode::Ok) {
    std::cerr << "Could not load image" << std::endl;
    return 1;
  }
  std::cout << "Image size: (" << image.value().GetWidth() << ", " << image.value().GetHeight() << ")" << std::endl;  
  
  if(channel > image.value().GetChannels()){
    std::cerr <<"Invalid channel: " << error << std::endl;
    return 1;
  }
  if(print_square_size > std::min(image.value().GetWidth(), image.value().GetHeight())){
    std::cerr << "Invalid square size " << error << std::endl;
    return 1;
  }

  for(size_t y = 0; y < print_square_size; ++y){
    for( size_t x = 0; x < print_square_size; ++x){
      std::cout << (int)image.value().At(y,x,channel) << '\t';
    }
    std::cout << std::endl;
  }
  
  return 0;
}
