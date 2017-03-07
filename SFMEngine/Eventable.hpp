#ifndef EVENTABLE_HPP
#define EVENTABLE_HPP

#include <map>

class IEventHandler
{
public:
	virtual void handle(int e) = 0;
};

template <class T>
class  EventHandler : public IEventHandler
{
public:
	EventHandler(T* context, void (T::*handler)(int))
	{
		m_xContext = context;
		m_xHandler = handler;
	}

	void handle(int e)
	{
		(m_xContext->*m_xHandler)(e);
	}

private:
	T* m_xContext;
	void(T::*m_xHandler)(int);
};
class Eventable
{
	std::multimap <int, IEventHandler*> handlers;
public:
	static virtual enum Event{};
	template <class T> void registerEventHandler(int e, T* context, void (T::*handler)(int))
	{
		handlers.insert(std::pair<int, IEventHandler*>(e, new EventHandler<T>(context, handler)));
	}

	void dispatchEvent(int e)
	{
		for (auto it = handlers.begin(); it != handlers.end(); ++it)
		{
			if (it->first == e)it->second->handle(e);
		}
	}
};
#endif