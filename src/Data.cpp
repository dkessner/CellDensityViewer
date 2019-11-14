//
// Data.cpp
//


#include "Data.hpp"


Data::Data()
{
    readDataMatrix("ProlifPop.txt", prolifPopData);
    readDataMatrix("MarkerMass_E_T.txt", markerETData);
    readDataVector("MarkerMass_E_P.txt", markerEPData);
}

int Data::size() const
{
    return prolifPopData.size();
}

const vector<float>& Data::getProlifPopData(int timeIndex) const
{
    return prolifPopData.at(timeIndex);
}

const vector<float>& Data::getMarkerETData(int timeIndex) const
{
    return markerETData.at(timeIndex);
}

void Data::readDataMatrix(const string& filename, vector<vector<float>>& destination)
{
    ofBuffer buffer = ofBufferFromFile(filename);
    cout << "[Data] Reading data from file: " << filename << endl;

    for (auto line : buffer.getLines())
    {
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


void Data::readDataVector(const string& filename, vector<float>& destination)
{
    ofBuffer buffer = ofBufferFromFile(filename);
    cout << "[Data] Reading data from file: " << filename << endl;

    for (auto line : buffer.getLines())
    {
        float value = ofToFloat(line);
        destination.push_back(value);
    }

    cout << destination.size() << " lines parsed.\n" << flush;
}


void Data::print(const vector<float>& dataVector)
{
    copy(dataVector.begin(), dataVector.end(), ostream_iterator<float>(cout, " "));
    cout << endl;
}


void Data::print(const vector<vector<float>>& dataMatrix)
{
    for (auto dataVector : dataMatrix)
        print(dataVector);
}


