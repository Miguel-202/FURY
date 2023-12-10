#pragma once
#include "FURYpch.h"
#include "FURY/Core.h"

namespace FURY 
{
	// Events happen inmediately, they are not queued. They are blocking.
	// TODO: Make events queued into an event bus/buffer and process them during the event part of the update loop.

	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory 
	{
		None = 0,
		EventCategoryApplication = BIT_S(0),
		EventCategoryInput = BIT_S(1),
		EventCategoryKeyboard = BIT_S(2),
		EventCategoryMouse = BIT_S(3),
		EventCategoryMouseButton = BIT_S(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class FURY_API Event 
{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) 
		{
			return GetCategoryFlags() & category;
		}

		bool Handled = false;
	};

	class EventDispatcher 
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) 
		{
			if (m_Event.GetEventType() == T::GetStaticType()) 
			{
				/// Line Below explanation
				/// If you have a box filled with fruits (m_Event) and you want to take out an apple (T::GetStaticType()) to a person who only likes apples (func)
				/// (T*)&m_Event is like  "Trust me, this address points to an apple," 
				/// *(T*)&m_Event is like "Here's your apple, sir."
				/// &(T*)&m_Event is like "Here's the address of your apple, sir" without confirming that it is an apple.
				m_Event.Handled = func(*(T*)&m_Event); 
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}