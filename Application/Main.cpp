#include "Engine.h" 
#include <iostream> 
#include <Renderer/Program.h>
#include <Renderer/Material.h>

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

	auto scene = std::make_unique<neu::Scene>();

	rapidjson::Document document;
	bool success = neu::json::Load("scenes/texture.scn", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "Scenes/basic.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}

	glm::vec3 pos = {0,0,0};


	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		auto actor1 = scene->GetActorFromName("Ogre");
		if (actor1)
		{
			//actor1->m_transform.rotation.y += neu::g_time.deltaTime * 30;
		}


		actor1 = scene->GetActorFromName("Light");
		if (actor1)
		{
			actor1->m_transform.position = pos;
		}
	ImGui::Begin("Hello");
	ImGui::Button("Press me");
	ImGui::SliderFloat("X", &pos[0], -5.0f, 5.0f);
	ImGui::SliderFloat("Y", &pos[1], -5.0f, 5.0f);
	ImGui::SliderFloat("Z", &pos[2], -5.0f, 5.0f);
	ImGui::End();

		auto actor2 = scene->GetActorFromName("Box");

		scene->Update();

		neu::g_renderer.BeginFrame();

		scene->Render(neu::g_renderer);
		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();

	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();

	return 0;
}