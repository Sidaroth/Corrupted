#pragma once

/// The generic "interface" for our enemies. All types of enemies will inherit from this class
class Enemy 
{
protected:
	short m_shSoulsToDrop;

public:
	virtual void sayHello() = 0;
};