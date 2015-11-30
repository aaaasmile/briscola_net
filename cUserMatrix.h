//cUserMatrix.h
#ifndef _CUSER_MATRIX_H
#define _CUSER_MATRIX_H 

#include <iostream>
#include <valarray>
#include <algorithm>
#include <fstream>

////////////////////////////////////////////////////////////////////////////////
// File         : cUserMatrix.h
// Project      : 
// Subsystem    : 
// Component    : 
// Author       : Igor Sarzi Sartori
// Description  : Matrix implementation. This simple implementation is limited on integer
//                values and no operation between matrix are implemented. Why use it?
//                Because no new are needed (it is a STL stuff) and no define are needed.
//                cUserMatrix could be dumped with save_utility.
//                On microsoft compiler #include <valarray> should be come first (p.e. in stdafx.cpp) 
////////////////////////////////////////////////////////////////////////////////
// History      : 08.06.2001   Igor Sarzi Sartori    Created


namespace Matrix
{
    
template<class T> class Slice_iter 
{
    std::valarray<T>* v;
    std::slice s;
    size_t curr;	// index of current element
    
    T& ref(size_t i) const { return (*v)[s.start()+i*s.stride()];}
        
public:
    Slice_iter(std::valarray<T>* vv, std::slice ss) :v(vv), s(ss), curr(0) { }
    
    Slice_iter end() const
    {
        Slice_iter t = *this;
        t.curr = s.size();	// index of last-plus-one element
        return t;
    }
    
    Slice_iter& operator++() { curr++; return *this; }
    Slice_iter operator++(int) { Slice_iter t = *this; curr++; return t; }
    
    T& operator[](size_t i) { return ref(i); }		// C style subscript
    T& operator()(size_t i) { return ref(i); }		// Fortran-style subscript
    T& operator*() { return ref(curr); }			// current element
    
    //friend bool operator== <>(const Slice_iter& p, const Slice_iter& q);
    //friend bool operator!= <>(const Slice_iter& p, const Slice_iter& q);
    //friend bool operator< <>(const Slice_iter& p, const Slice_iter& q);
    
    };
    
    /*
    template<class T>
    bool operator==(const Slice_iter<T>& p, const Slice_iter<T>& q)
    {
    return p.curr==q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
    }
    
      template<class T>
      bool operator!=(const Slice_iter<T>& p, const Slice_iter<T>& q)
      {
      return !(p==q);
      }
      
        template<class T>
        bool operator<(const Slice_iter<T>& p, const Slice_iter<T>& q)
        {
        return p.curr<q.curr
        && p.s.stride()==q.s.stride()
        && p.s.start()==q.s.start();
        }
    */
    
    //-------------------------------------------------------------
    
    
    
template<class T> class Cslice_iter 
{
    std::valarray<T>* v;
    std::slice s;
    size_t curr; // index of current element
    const T& ref(size_t i) const { return (*v)[s.start()+i*s.stride()];}

public:
    Cslice_iter(std::valarray<T>* vv, std::slice ss): v(vv), s(ss), curr(0){}
    Cslice_iter end() const
    {
        Cslice_iter t = *this;
        t.curr = s.size(); // index of one plus last element
        return t;
    }
    Cslice_iter& operator++() { curr++; return *this; }
    Cslice_iter operator++(int) { Cslice_iter t = *this; curr++; return t; }
    
    const T& operator[](size_t i) const { return ref(i); }
    const T& operator()(size_t i) const { return ref(i); }
    const T& operator*() const { return ref(curr); }
    
    //friend bool operator==<>(const Cslice_iter& p, const Cslice_iter& q);
    //friend bool operator!=<>(const Cslice_iter& p, const Cslice_iter& q);
    //friend bool operator< <>(const Cslice_iter& p, const Cslice_iter& q);
    
    };
    /*
    template<class T>
    bool operator==(const Cslice_iter<T>& p, const Cslice_iter<T>& q)
    {
    return p.curr==q.curr
    && p.s.stride()==q.s.stride()
    && p.s.start()==q.s.start();
    }
    
      template<class T>
      bool operator!=(const Cslice_iter<T>& p, const Cslice_iter<T>& q)
      {
      return !(p==q);
      }
      
        template<class T>
        bool operator<(const Cslice_iter<T>& p, const Cslice_iter<T>& q)
        {
        return p.curr<q.curr
        && p.s.stride()==q.s.stride()
        && p.s.start()==q.s.start();
    */
    // -------------------------------------------------------
    
    //! class cUserMatrix
class cUserMatrix 
{
        std::valarray<int>* v;	// stores elements by column as described in 22.4.5
        size_t nCol, nRow;	// nCol == number of columns, nRow == number of rows
    public:
        cUserMatrix(size_t x /* num col*/, size_t y/* num row*/);		// note: no default constructor
        cUserMatrix(const cUserMatrix&);
        cUserMatrix& operator=(const cUserMatrix&);
        ~cUserMatrix();
        
        size_t size() const { return nCol*nRow; }
        size_t dim1() const { return nCol; }
        size_t dim2() const { return nRow; }
        
        Slice_iter<int> row(size_t i);
        Cslice_iter<int> row(size_t i) const;
        
        Slice_iter<int> column(size_t i);
        Cslice_iter<int> column(size_t i) const;
        
        int& operator()(size_t x, size_t y);					// Fortran-style subscripts
        int operator()(size_t x, size_t y) const;
        
        Slice_iter<int> operator()(size_t i) { return column(i); }
        Cslice_iter<int> operator()(size_t i) const { return column(i); }
        
        Slice_iter<int> operator[](size_t i) { return column(i); }	// C-style subscript
        Cslice_iter<int> operator[](size_t i) const { return column(i); }
        
        cUserMatrix& operator*=(int);
        
        std::valarray<int>& array() { return *v; }

        friend std::ostream &operator << (std::ostream &stream, const cUserMatrix  &o);
    };
    
    
    inline Slice_iter<int> cUserMatrix::row(size_t i)
    {
        return Slice_iter<int>(v,std::slice(i,nCol,nRow));
    }
    
    inline Cslice_iter<int> cUserMatrix::row(size_t i) const
    {
        return Cslice_iter<int>(v,std::slice(i,nCol,nRow));
    }
    
    inline Slice_iter<int> cUserMatrix::column(size_t i)
    {
        return Slice_iter<int>(v,std::slice(i*nRow,nRow,1));
    }
    
    inline Cslice_iter<int> cUserMatrix::column(size_t i) const
    {
        return Cslice_iter<int>(v,std::slice(i*nRow,nRow,1));
    }
    
    inline cUserMatrix::cUserMatrix(size_t x, size_t y)
    {
        // check that x and y are sensible
        nCol = x;
        nRow = y;
        v = new std::valarray<int>(0,x*y);
    }
    
    inline cUserMatrix::~cUserMatrix()
    {
        delete v;
    }
    
    inline int& cUserMatrix::operator()(size_t x, size_t y)
    {
        return column(x)[y];
    }
    
    inline cUserMatrix& cUserMatrix::operator *= (int d)
    {
        (*v) *= d;
        return *this;
    }
    
    // -----------------------------------------------------------------
    
    inline int mul(Cslice_iter<int>& v1, const std::valarray<int>& v2)
    {
        int res = 0;
        for (unsigned int i = 0; i < v2.size(); i++) res+=v1[i]*v2[i];
        return res;
    }
    
    inline std::valarray<int> operator* (const cUserMatrix& m, const std::valarray<int>& v)
    {
        std::valarray<int> res(m.dim1());
        for (unsigned int i = 0; i < m.dim1(); i++) res[i] = mul(m.row(i), v);
        return res;
    }
    
    
    inline std::ostream& operator<<(std::ostream& os, cUserMatrix& m)
    {
        for(unsigned int x=0; x<m.dim1(); x++)
        {
            for(unsigned int y=0; y<m.dim2(); y++)
                os<<m[x][y]<<"\t";
            os << "\n";
        }
        return os;
    }
    
    // save a matrix in a file
    inline void SaveMatrix(char *fname, cUserMatrix &m)
    {
        std::ofstream out(fname);
        
        if (out != NULL)
        {
            out << m;
            out.close();
        }
    }
    
    inline std::ostream& operator<<(std::ostream& os, const std::valarray<int>& v)
    {
        for (unsigned int i = 0; i<v.size(); i++) os << v[i] << '\n' ;
        return os;
    }

    inline std::ostream &operator << (std::ostream &stream, const cUserMatrix  &o)
    {
        for(unsigned int x = 0; x < o.dim1(); x++)
        {
            for(unsigned int y = 0; y < o.dim2(); y++)
            {
                stream << o[x][y] << "\t";
            }
            stream << "\n";
        }
    }
    
}//end namespace


#endif