#pragma once

#include "Event.h"

#include <sstream>

namespace Congb {

	//��Ϊ���̰����¼� �� ���� �� ���� �����¼� ����������д���ӿ��� 
	class CONGB_API KeyEvent : public Event 
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		//�����¼��ķ���
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		//���� ��Ϊ�������һ���ӿ��� ����ֱ��ʵ���� ������ʵ��ʱ����������캯��
		KeyEvent(int keycode)
			: m_KeyCode(keycode){}

		//���̰�����
		int m_KeyCode;
	};

	class CONGB_API KeyPressedEvent : public KeyEvent
	{
	public:
		// ���ø��๹�� ���Ҽ�¼�ظ�����
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		//���麯����
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;//�����ظ����� �����Ϳ������ֶ̰��ͳ���
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