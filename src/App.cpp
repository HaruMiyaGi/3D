#include "App.h"

void App::MainLoop()
{
	auto delta = clock.Mark() * 0.1f;

	console.SetTitle(clock.Time());

	if (wnd.keyboard.IsPressed({ VK_F1 }) && !wnd.gfx().gui.IsEnabled())
		wnd.gfx().gui.Toggle();
	if (wnd.keyboard.IsPressed({ VK_F2 }) && wnd.gfx().gui.IsEnabled())
		wnd.gfx().gui.Toggle();


	//wnd.gfx().StartFrame(0.075f, 0.067f, 0.094f);
	wnd.gfx().StartFrame(1.0f, 1.0f, 1.0f);


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


	Grid(wnd.gfx()).Draw2(wnd.gfx());



	//int length = 10;
	//for (float x = 0.0f; x < length; x += 1.0f)
	//{
	//	for (float y = 0.0f; y < length; y += 1.0f)
	//	{
	//		Line l(wnd.gfx());
	//		l.LineUpdate(0.0f, y, 0.0f);
	//		l.Draw(wnd.gfx());
	//	}
	//}

	//Line(wnd.gfx(), Vec3(0.0f, 0.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f)).Draw(wnd.gfx());



	//for (auto& cube : cubes)
	//{
	//	cube->Update(delta);
	//	cube->Draw(wnd.gfx());
	//}

	shape.Draw(wnd.gfx());
	if (wnd.gfx().gui.IsEnabled())
		shape.Gui(wnd.gfx());

	//Vec2 mouse_pos = VecToNdc(Vec2(wnd.mouse.GetX(), wnd.mouse.GetY()), wnd.GetWidth(), wnd.GetHeight());
	//for (auto& line : lines)
	//	line->DrawLine(wnd.gfx(), Vec2(1.0f, 1.0f), mouse_pos);


	// Ray Tracing
	//{
	//	using namespace DirectX;

	//	XMVECTOR mouse_near = XMVectorSet((float)wnd.mouse.GetX(), (float)wnd.mouse.GetY(), 0.0f, 0.0f);
	//	XMVECTOR mouse_far = XMVectorSet((float)wnd.mouse.GetX(), (float)wnd.mouse.GetY(), 1.0f, 0.0f);

	//	auto view_matrix = wnd.gfx().camera.GetMatrix() * wnd.gfx().GetProjection();

	//	XMVECTOR ray_near = XMVector3Transform(mouse_near, view_matrix);
	//	XMVECTOR ray_far = XMVector3Transform(mouse_far, view_matrix);


	//	//DirectX::XMVECTOR unprojectedNear = DirectX::XMVector3Unproject(mouse_near, 0, 0, 1.0f, 1.0f, 0.5f, 100.0f,
	//	//	wnd.gfx().GetProjection(), wnd.gfx().camera.GetMatrix(), DirectX::XMMatrixIdentity());
	//	//DirectX::XMVECTOR unprojectedFar = DirectX::XMVector3Unproject(mouse_far, 0, 0, 1.0f, 1.0f, 0.5f, 100.0f,
	//	//	wnd.gfx().GetProjection(), wnd.gfx().camera.GetMatrix(), DirectX::XMMatrixIdentity());
	//	//DirectX::XMVECTOR result = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(unprojectedFar, unprojectedNear));

	//	//DirectX::XMFLOAT3 direction;
	//	//DirectX::XMStoreFloat3(&direction, result);
	//	//

	//	if (wnd.gfx().gui.IsEnabled() && false)
	//	{
	//		if (ImGui::Begin("Ray Tracing"))
	//		{
	//			ImGui::Text("Mouse Near: %.1f, %.1f, %.1f, %.1f", mouse_near.m128_f32[0], mouse_near.m128_f32[1], mouse_near.m128_f32[2], mouse_near.m128_f32[3]);
	//			ImGui::Text("Mouse Far: %.1f, %.1f, %.1f, %.1f", mouse_far.m128_f32[0], mouse_far.m128_f32[1], mouse_far.m128_f32[2], mouse_far.m128_f32[3]);
	//			ImGui::Text("Ray Near: %.1f, %.1f, %.1f, %.1f", ray_near.m128_f32[0], ray_near.m128_f32[1], ray_near.m128_f32[2], ray_near.m128_f32[3]);
	//			ImGui::Text("Ray Far: %.1f, %.1f, %.1f, %.1f", ray_far.m128_f32[0], ray_far.m128_f32[1], ray_far.m128_f32[2], ray_far.m128_f32[3]);
	//		} ImGui::End();


	//		if (ImGui::Begin("View Matrix"))
	//		{
	//			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", view_matrix.r->m128_f32[0], view_matrix.r->m128_f32[1], view_matrix.r->m128_f32[2], view_matrix.r->m128_f32[3]);
	//			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", view_matrix.r->m128_f32[4], view_matrix.r->m128_f32[5], view_matrix.r->m128_f32[6], view_matrix.r->m128_f32[7]);
	//			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", view_matrix.r->m128_f32[8], view_matrix.r->m128_f32[9], view_matrix.r->m128_f32[10], view_matrix.r->m128_f32[11]);
	//			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", view_matrix.r->m128_f32[12], view_matrix.r->m128_f32[13], view_matrix.r->m128_f32[14], view_matrix.r->m128_f32[15]);
	//		} ImGui::End();
	//	}
	//}







	/// [TODO]: for (auto& gui : guis) gui->Render();
	//if (wnd.gfx().gui.IsEnabled())
	//{
	//	if (ImGui::TreeNode("Objects"))
	//	{
	//		if (ImGui::TreeNode(shape.GetName()))
	//		{
	//			shape.Gui(wnd.gfx());
	//			ImGui::TreePop();
	//		}
	//		ImGui::TreePop();
	//	}

	//	//wnd.gfx().camera.Gui();
	//	//Gui();
	//}

	wnd.gfx().EndFrame();
}