#include <boost/filesystem.hpp>
#include <iostream>

using namespace std; 
using namespace boost::filesystem;

int main()
{
    
    boost::filesystem::directory_iterator iterator(string("."));
    
    for( ; iterator != boost::filesystem::directory_iterator(); ++iterator)
    {
        cout << (iterator->path().filename()) << endl;
    }

    boost::filesystem::path full_path( boost::filesystem::current_path() );
    std::cout << "Current path is : " << full_path << std::endl;
   
    return 0;

}