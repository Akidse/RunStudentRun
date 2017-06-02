#ifndef EVENTABLE_HPP
#define EVENTABLE_HPP

#include <map>

class IEventHandler
{
public:
	virtual void handle(std::string objectID, int e) = 0;
};

template <class T>
class  EventHandler : public IEventHandler
{
public:
	EventHandler(T* context, void (T::*handler)(std::string, int))
	{
		m_xContext = context;
		m_xHandler = handler;
	}

	void handle(std::string objectID, int e)
	{
		(m_xContext->*m_xHandler)(objectID, e);
	}

private:
	
	T* m_xContext;
	void(T::*m_xHandler)(std::string, int);
};
class Eventable
{
	std::string objectID = "undefined";
	std::multimap <int, IEventHandler*> handlers;
public:
	void setID(std::string pId)
	{
		objectID = pId;
	}
	std::string getID()
	{
		return objectID;
	}
	static virtual enum Event{};
	template <class T> void registerEventHandler(int e, T* context, void (T::*handler)(std::string, int))
	{
		handlers.insert(std::pair<int, IEventHandler*>(e, new EventHandler<T>(context, handler)));
	}

	void dispatchEvent(int e)
	{
		for (auto it = handlers.begin(); it != handlers.end(); ++it)
		{
			if (it->first == e)it->second->handle(objectID, e);
		}
	}
};
#endif