//
// Data.cpp
//


#include "Data.hpp"


Data::Data()
{
    readData("ProlifPop.txt", prolifPopData);
    readData("MarkerMass_E_T.txt", markerETData);
}

int Data::size() const
{
    return prolifPopData.size();
}

const vector<float>& Data::getProlifPopData(int i) const
{
    return prolifPopData.at(i);
}

const vector<float>& Data::getMarkerETData(int i) const
{
    return markerETData.at(i);
}

void Data::readData(const string& filename, vector<vector<float>>& destination)
{
    ofBuffer buffer = ofBufferFromFile(filename);
    cout << "[Data] Reading data from file: " << filename << endl;

    int lineCount = 0;
    for (auto line : buffer.getLines())
    {
        ++lineCount;

        destination.push_back(vector<float>());
        istringstream iss(line);

        // parse the line

        transform(istream_iterator<string>(iss), 
                  istream_iterator<string>(),
                  back_inserter(destination.back()), 
                  ofToFloat);

        if (destination.back().size() != compartmentCount)
        {
            cout << "Error: data vector size != compartmentCount" << endl;
            cout << "length: " << destination.back().size() << endl;
            copy(destination.back().begin(), destination.back().end(), 
                    ostream_iterator<float>(cout, " "));
            break;
        }
    }

    cout << destination.size() << " lines parsed.\n" << flush;
}


void Data::printData(const vector<vector<float>>& data)
{
    for (auto dataVector : data)
    {
        copy(dataVector.begin(), dataVector.end(), ostream_iterator<float>(cout, " "));
        cout << endl;
    }
}


