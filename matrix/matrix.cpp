#include <iostream>
#include <vector>
using namespace std;


template <typename T>
class matrix
{
public:

    matrix(int row , int column)
    {
        vector<T> rowV;
        for (int i = 0; i < row ; i++)
        {
            rowV.clear();
            for (int j = 0 ; j < column ; j++)
            {
                rowV.push_back(T());
            }
            data.push_back(rowV);
        }
    }

  
    const matrix& operator[] (int test)
    {
        //
    }
   
    void display()
    {
        for (vector<T> iterV : data)
        {
            for (T iter : iterV)
            {
                cout << iter << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void fill (T f)
    {
        for (vector<T> &iterV : data)
        {
            for (int i = 0 ; i < iterV.size(); i++)
            {
                iterV[i] = f;
            }
        }
    }
    void resize(int row , int column)
    {
        T val;
        bool def = false;
        if(data[0][0])
        {
            val = data[0][0];
            def =  true;
            
        }
        data.clear();
        vector<T> rowV;
        for (int i = 0; i < row ; i++)
        {
            rowV.clear();
            for (int j = 0 ; j < column ; j++)
            {
                rowV.push_back((def) ? val : T());
            }
            data.push_back(rowV);
        }
    }


    
private:
vector<vector<T>> data;

};


int main()
{

    matrix<int> table(2,5);
    table.display();
   table.resize(10,10);
   table.display();
    table.fill(7);
    table.display();
    table.resize(5,5);
    table.display();

    // table[0][1] = 5; write logic for this

    
    table.display();

    
    return 0;
}