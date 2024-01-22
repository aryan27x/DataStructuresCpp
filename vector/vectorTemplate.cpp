#include <iostream>
#include <ostream>

using namespace std;

template <typename T>
class vctr
{
  public:

  explicit vctr(int initCap = 10) : vCapacity(initCap) , vSize(0)
    {data = new T[vCapacity];}

  void reserve(int newCap)
  {
    if (newCap < vCapacity)
        return;
    
    T * temp = data;
    data = new T[newCap];

    for (int i = 0 ; i < vSize; i++)
        data[i] = temp[i];
    
    vCapacity = newCap;
    delete [] temp;
  }
  
  const T& back() const
  {
    if (vSize!=0)
        return data[vSize-1];
    cerr << "Error : cannot use back() on an empty vector" << endl;
    exit(1);
    
  }
 
  const T& at(int index) const
  {
    if (index >= 0 && index < vSize)
        return data[index];
    cerr << "Error : out of bound index for at() : " << index << endl;
    exit(1);
    
  }

  void push(const T& newValue)
  {
    if (vSize == vCapacity)
        reserve(2 * vCapacity + 1);
    
    data[vSize++] = newValue;
  }

  const T& pop() 
  {
    if (vSize != 0)
        return data[--vSize];
    cerr << "Error : Cannot pop an empty vector " << endl;
    exit(1);

  }

  void display()
  {
    cout << "[ ";
    for (int i = 0 ; i < vSize; i++ )
        cout << data[i] << " ";
    cout << "]" << endl;
  }

   const T& operator[](int index) {return at(index);}
  
  vctr(const vctr& rhsRef)
  {
  data = nullptr; // we need to set this to null as we are using the "this" keyword in the operator= , and we dont want this to 
  // be pointing to some garbage value    
  operator=(rhsRef);
  }

  
  const vctr& operator=(const vctr& rhsRef)
  {
    // "this" is a pointer to the object of the class
    // "*this" is the result of dereferencing , which would then give the actual object 
    if (this != &rhsRef)
    {
        delete [] data;
        // the rhsRef is defined as the const reference to vctr object
        // and the only way to call a function on such const object ref/pointer 
        // is to make the function which is to be called an accessor , using the const keyword
        // this is the reason why the size() and the capacity() function both are const
        
        this->vSize = rhsRef.size(); // since this is a pointer, we would be using the -> notation 
        vCapacity = rhsRef.vCapacity; //  alternatively , we could just write the member name
        
        data = new T[this->vCapacity];
        
        for (int i = 0; i < this->vSize; i++)
            data[i] = rhsRef.data[i];
        
    }
        return *this;
    
  }

  // overloading << operator
  template <typename overloadTemplate> //  we would need another template with different template name , else shadow error would occur
  friend ostream& operator<<(ostream& os , const vctr<overloadTemplate>& operand );  // we would need to declare friend function whose ~
  // ~ definition would be outside the scope of the class


  // both the size and the capacity function are const so that they could be called by the a const object ref/pointer
  int size() const {return vSize;} 
  int capacity() const { return vCapacity;}


  ~vctr()
  {
    delete [] data;
  }

  private:
  int vSize;
  int vCapacity;
  T * data;

};

template <typename overloadTemplate>
ostream& operator<<(ostream& os , const vctr<overloadTemplate>& operand )
{
    os << "[ ";
    for (int i = 0 ; i < operand.size(); i++)
        os << to_string(operand.at(i)) << " ";
    os << "]";
    return os;
}

int main()
{
    vctr<int> test(5);

    test.push(1);
    test.push(2);
    test.push(3);
    cout << "this is the value of the test vector using the display function : " << endl;
    test.display();

    vctr<int> test2(3);
    test2.push(1);
    cout << "this is the value of the test2 vector : " << test2 << endl;
    test2 = test;
    cout << "this is the new value of the test2 vector : " << test2 << endl;
    test2.pop();
    cout << "this is the value of the test2 vector after popping the last element : " << test2 << endl;
    cout << "this is the first element of the test2 vector : " << test2.at(0) << endl;
    int secondElement = test2[1];
    cout << "this is the second element of the test2 vector : " << secondElement << endl;
    
    return 0;
}