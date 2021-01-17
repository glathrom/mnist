#include <cstdlib>
#include <vector>
#include <string>
#include "mnist.hpp"

int main(){

    std::string dpath = "/home/grant/Projects/compiled/mnist/data/";
    MNIST mnist(dpath);


    std::ifstream fp;
    unsigned printbreak;
    int rows, cols;
    std::vector<unsigned char> *labels;
    std::vector<unsigned char> *images;


    /**********************************************/
    // load image labels
    /**********************************************/

    labels = mnist.get_testing_labels();
    
    printbreak = 30;
    printf("Label Data:");
    for(unsigned i = 0; i < 2*printbreak; i++){
        if( (i % printbreak) == 0 ) printf("\n\t");
        printf("%d ", labels->at(i));
    }
    printf("\n\n");

    /**********************************************/
    // load corresponding image file
    /**********************************************/
  

    images = mnist.get_testing_images(); 

    rows = mnist.image_size["rows"];
    cols = mnist.image_size["cols"];

    printf("Data:");
    for( int p = 0; p < 5; p++ ){
        for(int i = 0; i < rows*cols; i++){
            if( (i % rows) == 0 ) printf("\n\t");
            printf("%02x ", images->at(p*rows*cols+i));
        }
        printf("\n\n");
    }

    return 0;
}
