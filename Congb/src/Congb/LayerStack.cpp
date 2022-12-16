#include "cbpch.h"
#include "LayerStack.h"

namespace Congb {

	LayerStack::LayerStack()
	{
		m_layerInsert = m_layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : m_layers)
			delete layer;
	}

	//普通层push 插入到vector指定位置
	void LayerStack::PushLayer(Layer* layer)
	{
		m_layerInsert = m_layers.emplace(m_layerInsert, layer);
	}

	//覆盖层push到最后 因为layers执行时是从后向前执行 所以覆盖层先执行
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			m_layerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
	}
}