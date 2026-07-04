#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <vector>

/** @brief Vector.h
* @author Delvin
     */
template <class T>
class Vector
{
public:
    /** @brief default constructor
     */
    Vector();
    /** @brief parameterized constructor
     * @param n
    */
    Vector(int n);
    /** @brief delete
     */
    ~Vector();
    /** @brief insert into the index array and move the rest behind by +1 index
     * @param index
     * @param data
     * @return boolean
     */
    bool Insert(int index, const T data); // C
    /** @brief delete the input index from the array and move everything behind by -1 index
     * @param index
     * @return boolean
     */
    bool Delete(int index); //D
    /** @brief reads the data from the array with the index
     * @param index
     * @return constant reference
     */
    const T& operator[] (int index) const; // R
    /** @brief updates changes the array's index value
     * @param index
     * @return non constant reference
     */
    T& operator[] (const int & index); //U
    /** @brief getter for size
     * @return m_size
     */
    int GetSize() const;
//void clear();
private:
    std::vector<T> m_vector;
};

template <class T>
Vector<T>::Vector()
{

    m_vector.reserve(8);
}

template <class T>
Vector<T>::Vector(int n)
{
    if(n >0 )
    {
        m_vector.reserve(n);
    }
    else
    {
        m_vector.reserve(8);
    }
}
template <class T>
Vector<T>::~Vector()
{

}

template <class T>
bool Vector<T>::Insert(int index, const T data)
{
    if(index >=0 && index < m_vector.size())
        {
            m_vector.insert(m_vector.cbegin() + index, data);
            return true;
        }
    else if(index == m_vector.size())
        {
            m_vector.push_back(data); //append
            return true;
        }
    else
    {
        return false;
    }
}
template <class T>
bool Vector<T>::Delete(int index)
{
    if(index >= 0 && index < m_vector.size())
    {

        m_vector.erase(m_vector.begin() + index);
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
const T& Vector<T>::operator[] (int index) const
{
    return m_vector[index];
}

template <class T>
T& Vector<T>::operator[] (const int & index)
{
    return m_vector[index];
}

template <class T>
int Vector<T>::GetSize() const
{
    return m_vector.size();
}

#endif // VECTOR_H_INCLUDED
