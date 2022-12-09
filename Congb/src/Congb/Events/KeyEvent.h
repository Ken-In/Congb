#pragma once

#include "Event.h"

#include <sstream>

namespace Congb {

	//因为键盘按键事件 分 按下 和 弹起 两个事件 所以我们再写个接口类 
	class CONGB_API KeyEvent : public Event 
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		//键盘事件的分类
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		//保护 因为这个类是一个接口类 不能直接实例化 在子类实例时调用这个构造函数
		KeyEvent(int keycode)
			: m_KeyCode(keycode){}

		//键盘按键号
		int m_KeyCode;
	};

	class CONGB_API KeyPressedEvent : public KeyEvent
	{
	public:
		// 调用父类构造 并且记录重复次数
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		//纯虚函数宏
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;//按键重复次数 这样就可以区分短按和长按
	};

	class CONGB_API KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keycode)
			: KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}