#include <string>
#include <iostream>
#include <fstream>
#include "AVL.h"
#include "json.hpp"

using namespace std;

AVLTree operation(nlohmann::json* jobject) {
    size_t numOps = (*jobject)["metadata"]["numOps"];             /*extract the numOps from jsonObject's metadata*/
    //AVLTree result(AVLTree);

    for (auto itr_ = jobject->begin(); itr_ != std::prev(jobject->end()); ++itr_) {    /*distinguish which operation it is, and then implement the operation */
        // insert operation
        if((*itr_)["operation"] == "insert") {
            result.insert((double)(*itr_)["key"]);
        }
       
    }
    
    return result;
}

int main(int argc, char** argv) {
    ifstream input_file;
    nlohmann::json jobject, out_jobject;
    input_file.open(argv[1]);
    input_file >> jobject;
    // assign operations and output json object
    AVLTree output_ = operation(&jobject);
    out_jobject = output_.JSON();

    root = root_;
    height = getHeight(root_);
    size = size_;

    for (auto itr_ = jobject->begin(); itr_ != std::prev(jobject->end()); ++itr_) {
       
        out_jobject[itr]["balance factor"] = balance_factor(itr);
        out_jobject[itr]["height"] = getHeight(itr);
            
        if(itr ->HasLeftChild() != false){
             out_jobject[itr]["left"] = itr -> left_;
        }
             
        if(itr_ != root_){
            out_jobject[itr]["parent"] = itr -> parent_.lock();
        }
         
        if(itr ->HasRightChild() != false){
            out_jobject[itr]["right"] = itr_right_;
        }
         
        if(itr_ == root_){
            out_jobject[itr]["root"] = "true";
        }
         
    }
    

    out_jobject["metadata"]["height"] = height;
    out_jobject["metadata"]["root"] = root;
    out_jobject["metadata"]["size"] = size;
    
    
    
    
    cout << out_jobject.dump(2) << endl;
}
