#pragma once
#include "Graphics.h"
#include "IndexBuffer.h"

#include "VertexBuffer.h"

#include <vector>

#include "Math.h"

template <typename C>
class Drawable
{
	template <typename T>
	friend class DrawableThunk;
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;
public:
	virtual DirectX::XMMATRIX GetTransformXM() const = 0;
	virtual void Update(float dt) = 0;

	void DrawLine(Graphics& gfx, Vec2 start, Vec2 end)
	{
		for (const auto& b : binds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
				count = p->GetCount();
			b->Bind(gfx);
		}

		for (const auto& b : static_binds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
				count = p->GetCount();

			if (const auto d = dynamic_cast<VertexBuffer*>(b.get()))
				d->Update(gfx, start, end);

			b->Bind(gfx);
		}

		gfx.DrawIndexed(count);
	}

	void Draw(Graphics& gfx)
	{
		for (const auto& b : binds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
				count = p->GetCount();

			b->Bind(gfx);
		}

		for (const auto& b : static_binds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
				count = p->GetCount();

			b->Bind(gfx);
		}

		gfx.DrawIndexed(count);
	}
	bool IsInit() const
	{
		return !static_binds.empty();
	}
protected:
	void AddBind(std::unique_ptr<Bindable> bind)
	{
		binds.push_back(std::move(bind));
	}
	void AddStaticBind(std::unique_ptr<Bindable> bind)
	{
		static_binds.push_back(std::move(bind));
	}
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> indexbuffer)
	{
		binds.push_back(std::move(indexbuffer));
	}
	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> indexbuffer)
	{
		static_binds.push_back(std::move(indexbuffer));
	}
private:
	UINT count = 0;
	std::vector<std::unique_ptr<Bindable>> binds;
	static std::vector<std::unique_ptr<Bindable>> static_binds;
	bool init = false;
};

template <typename C>
std::vector<std::unique_ptr<Bindable>> Drawable<C>::static_binds;
