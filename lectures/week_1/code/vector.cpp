#include <vector>
#include <iostream>

void printVectorCStyle(std::vector<int> const& vec)
{
    std::cout << "Size: " << vec.size() << std::endl;
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
}

void printVectorIterators(std::vector<int> const& vec)
{
    std::cout << "Size: " << vec.size() << std::endl;
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void printVectorRange(std::vector<int> const& vec)
{
    std::cout << "Size: " << vec.size() << std::endl;
    for (auto& elem : vec)
    {
        std::cout << elem << " ";
    }
    // Flush out cout
    std::cout << std::endl;
}

int main()
{
    // Can you guess why the braces are here?
    {
        // Initialize vector with values.
        std::vector<int> myVec{0, 1, 2, 3};
        std::cout << "Initial vector: " << std::endl;
        printVectorCStyle(myVec);

        myVec.push_back(4);         // Adds 4 at the end
        myVec.push_back(5);         // Adds 5 at the end
        std::cout << "New vector: " << std::endl;
        printVectorCStyle(myVec);
    }

    {
        std::vector<int> myVec;
        std::cout << "Initial vector: " << std::endl;
        printVectorIterators(myVec);

        for (int i = 0; i < 3; ++i)
        {
            // Insert elements at the front.
            myVec.insert(myVec.begin(), i);
        }

        std::cout << "New vector: " << std::endl;
        printVectorIterators(myVec);
    }

    {
        std::vector<int> list1{0, 1, 2};
        std::vector<int> list2{3, 4, 5};

        std::cout << "Initial vectors: " << std::endl;
        printVectorRange(list1);
        printVectorRange(list2);

        // Concatenate vectors
        list1.insert(list1.end(), list2.begin(), list2.end());
        std::cout << "New vector: " << std::endl;
        printVectorRange(list1);
    }

    return 0;
}
