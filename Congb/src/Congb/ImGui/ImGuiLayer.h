#pragma once
#include "Congb/Layer.h"

#include "Congb/Events/ApplicationEvent.h"
#include "Congb/Events/KeyEvent.h"
#include "Congb/Events/MouseEvent.h"

namespace Congb{

	class CONGB_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}