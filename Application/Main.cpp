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

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();


		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		auto actor1 = scene->GetActorFromName("Ogre");
		
		auto actor2 = scene->GetActorFromName("Box");

		auto material = neu::g_resources.Get<neu::Material>("Materials/multi.mtrl");
		if (material)
		{
			//material->uv_offset.y += neu::g_time.deltaTime;
			//material->uv_offset.x += neu::g_time.deltaTime;
		}

		scene->Update();

		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();

	return 0;
}