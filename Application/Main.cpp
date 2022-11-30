#include "Engine.h" 
#include <iostream> 
#include <Renderer/Program.h>
#include <Renderer/Material.h>
#define POST_PROCESS

int main(int argc, char** argv)
{
	LOG("Application Started...");
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Initialized");
	
	neu::g_renderer.CreateWindow("Neumont", 800, 600);

	neu::g_gui.Initialize(neu::g_renderer);

	//create frambuffer texture
	/*auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(512, 512);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);*/

	// new texture
	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(1024, 1024);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);


	//create framebuffer
	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();


	//wave
	auto program = neu::g_resources.Get<neu::Program>("shaders/postprocess/postprocess.prog");
	if (program)
	{
		program->Use();
		program->SetUniform("offset", neu::g_time.time);
	}
	


	auto scene = neu::g_resources.Get<neu::Scene>("scenes/Post-Process.scn");

	glm::vec3 rot = {0,0,0};
	float ri = 1.04f;
	float interpolation = 0.5;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		auto actor1 = scene->GetActorFromName("Light");
		if (actor1)
		{
			actor1->m_transform.position = rot;
		}

		auto program = neu::g_resources.Get<neu::Program>("shaders/FX/reflection_refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
			program->SetUniform("interpolation", interpolation);
		}

		ImGui::Begin("Transform");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::SliderFloat("Interpolation", &interpolation, 0, 1);
		ImGui::SliderFloat("RI", &ri, 1, 2);
		ImGui::End();

		scene->Update();

#ifdef POST_PROCESS 
		// don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (render scene to framebuffer) 
		neu::g_renderer.SetViewport(0, 0, framebuffer -> GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(neu::g_renderer);
			}
		}
#else 
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
#endif // POST_PROCESS 

		/*{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(false);
			}
		}*/

		//renderer pass1 (renderer to framebuffer)
		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		/*{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(true);
			}
		}*/

		//render pass 2 (render to screen)
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);

		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();

	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();

	return 0;
}