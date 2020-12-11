#include <string>
#include <iostream>
#include <fstream>
#include "priorityqueue.h"
#include "json.hpp"

using namespace std;

PriorityQueue operation(nlohmann::json* jobject) {
    size_t maxheap = (*jobject)["metadata"]["maxHeapSize"];             /*extract the maxheapsize from jsonObject's metadata*/
    PriorityQueue result(maxheap);

    for (auto itr_ = jobject->begin(); itr_ != std::prev(jobject->end()); ++itr_) {    /*distinguish which operation it is, and then implement the operation */
        // insert operation
        if((*itr_)["operation"] == "insert") {
            result.insert((double)(*itr_)["key"]);
        } else if((*itr_)["operation"] == "removeMin") {
            result.removeMin();
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
    PriorityQueue output_ = operation(&jobject);
    out_jobject = output_.JSON();

    out_jobject["metadata"]["numOperations"] = jobject["metadata"]["numOperations"];
    out_jobject["metadata"]["maxHeapSize"] = jobject["metadata"]["maxHeapSize"];
    cout << out_jobject.dump(2) << endl;
}
