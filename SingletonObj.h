#ifndef SINGLETONOBJ_H
#define SINGLETONOBJ_H

#include "GameObj.h"
#include "NiMemObject.h"

template <typename T>
class SingletonObj : public NiMemObject
{
protected:
	SingletonObj()
	{}

	virtual ~SingletonObj()
	{}

	static T* m_instance;

public:

	static T* Get()
	{
		if ( !m_instance )
		{
			m_instance = NiNew T();
		}

		return m_instance;
	}

	static void  Destroy()
	{
        NiDelete m_instance;
        m_instance = 0;
    }
	
};


template <typename T> T* SingletonObj<T>::m_instance = 0;

#endif