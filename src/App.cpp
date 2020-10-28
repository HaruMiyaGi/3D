#include "App.h"

void App::MainLoop()
{
	auto delta = clock.Mark() * 0.1f;

	console.SetTitle(clock.Time());

	if (wnd.keyboard.IsPressed({ VK_F1 }) && !wnd.gfx().gui.IsEnabled())
		wnd.gfx().gui.Toggle();
	if (wnd.keyboard.IsPressed({ VK_F2 }) && wnd.gfx().gui.IsEnabled())
		wnd.gfx().gui.Toggle();


	wnd.gfx().StartFrame(0.075f, 0.067f, 0.094f);


	if (wnd.keyboard.IsPressed({ 'W' }))
		wnd.gfx().camera.Move({ 0.0f, 0.0f, delta });
	if (wnd.keyboard.IsPressed({ 'S' }))
		wnd.gfx().camera.Move({ 0.0f, 0.0f, -delta });
	if (wnd.keyboard.IsPressed({ 'D' }))
		wnd.gfx().camera.Move({ delta, 0.0f, 0.0f });
	if (wnd.keyboard.IsPressed({ 'A' }))
		wnd.gfx().camera.Move({ -delta, 0.0f, 0.0f });
	if (wnd.keyboard.IsPressed({ 'R' }))
		wnd.gfx().camera.Move({ 0.0f, delta, 0.0f });
	if (wnd.keyboard.IsPressed({ 'F' }))
		wnd.gfx().camera.Move({ 0.0f, -delta, 0.0f });

	while (const auto delta = wnd.mouse.ReadRawDelta())
		wnd.gfx().camera.Rotate(delta->x, delta->y);


	for (auto& cube : cubes)
	{
		cube->Update(delta);
		cube->Draw(wnd.gfx());
	}

	Shape shape(wnd.gfx(), { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
	shape.Draw(wnd.gfx());

	Vec2 mouse_pos = VecToNdc(Vec2(wnd.mouse.GetX(), wnd.mouse.GetY()), wnd.GetWidth(), wnd.GetHeight());
	for (auto& line : lines)
		line->DrawLine(wnd.gfx(), Vec2(1.0f, 1.0f), mouse_pos);

	/// [TODO]: for (auto& gui : guis) gui->Render();
	if (wnd.gfx().gui.IsEnabled())
	{
		wnd.gfx().camera.Gui();
		Gui();
	}

	wnd.gfx().EndFrame();
}