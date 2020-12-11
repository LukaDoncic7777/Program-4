#include <string>
#include <iostream>
#include <fstream>
#include "AVL.h"
#include "json.hpp"

using namespace std;

AVLTree operation(nlohmann::json* jobject) {
    size_t numOps = (*jobject)["metadata"]["numOps"];             /*extract the maxheapsize from jsonObject's metadata*/
    AVLTree result(numOps);

    for (auto itr_ = jobject->begin(); itr_ != std::prev(jobject->end()); ++itr_) {    /*distinguish which operation it is, and then implement the operation */
        // insert operation
        if((*itr_)["operation"] == "insert") {
            result.insert((*itr_)["key"]);
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
    out_jobject["metadata"]["maxHeapSize"] = jobject["metadata"]["numOps"];
    cout << out_jobject.dump(2) << endl;
}
